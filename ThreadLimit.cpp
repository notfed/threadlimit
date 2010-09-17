#include "Thread.h"
#include "ThreadLimit.h"
#include "CallMemFun.h"
#include "Lock.h"
#include <queue>

//
// ThreadStarter
//
ThreadStarter::ThreadStarter(Start_routine_f start_routine, 
                             Start_routine_arg_t start_routine_arg, 
                             ThreadLimit* owner)
  : m_StartRoutine(start_routine),
    m_StartRoutineArg(start_routine_arg),
    m_ThreadLimit(owner)
{
}
void ThreadStarter::Start()
{
    Thread newThread(&CallMemFun<ThreadStarter,&ThreadStarter::MonitorThread>,this);
    newThread.Start();
}
void* ThreadStarter::MonitorThread()
{
    (*m_StartRoutine)(m_StartRoutineArg);
    m_ThreadLimit->SignalFinish();
    return 0;
}
ThreadStarter::~ThreadStarter()
{
}

//
// ThreadLimit
//
ThreadLimit::ThreadLimit(int limit)
  : m_Limit(limit),
    m_Available(limit),
    m_Thread(&CallMemFun<ThreadLimit,&ThreadLimit::ThreadLimitLoop>,this)
{
}
ThreadLimit::~ThreadLimit()
{
  m_Thread.Cancel();
}
void* ThreadLimit::ThreadLimitLoop()
{
  int queued;
  int available;
  for(;;)
  {
    // Safely fetch queue size
    { Lock<Mutex> guard(m_QueueLock);
      queued = m_ThreadQueue.size(); }

    // Wait for a thread to be queued
    if(queued==0) 
      m_AddEvent.Wait(); 
    
    // Safely fetch m_Available
    { Lock<Mutex> guard(m_QueueLock);
      available = m_Available; }

    // Wait for an available thread slot
    if(available==0) 
      m_FinishEvent.Wait(); 

    // Run the next thread
    {
      Lock<Mutex> guard(m_QueueLock);
      if(m_ThreadQueue.empty()) continue;
      --m_Available;
      ThreadStarter nextThread = m_ThreadQueue.front();
      m_ThreadQueue.pop();
      nextThread.Start();
    }
  }
  return 0;
}
void ThreadLimit::SignalFinish()
{
      Lock<Mutex> guard(m_QueueLock);
      ++m_Available;
      m_FinishEvent.Signal();
}
void ThreadLimit::Add(Start_routine_f start_routine, Start_routine_arg_t start_routine_arg)
{
    Lock<Mutex> guard(m_QueueLock);
    m_ThreadQueue.push(ThreadStarter(start_routine,start_routine_arg, this));
    m_AddEvent.Signal();
}
