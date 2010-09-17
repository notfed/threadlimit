#include "Thread.h"
#include "ThreadLimit.h"
#include "CallMemFun.h"
#include "Mutex.h"
#include "Lock.h"
#include <iostream>
#include <queue>
using namespace std;

static Mutex console_lock;
void debug(const char *str)
{
    Lock<Mutex> guard(console_lock);
    cerr << str << endl;
}

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
  m_Thread.Start();
}
ThreadLimit::~ThreadLimit()
{
  m_Thread.Cancel();
}
void* ThreadLimit::ThreadLimitLoop()
{
  bool empty;
  int available;
  for(;;)
  {
    // Safely fetch queue size
    { Lock<Mutex> guard(m_QueueLock);
      empty = m_ThreadQueue.empty(); }

    // Wait for a thread to be queued
    if(empty)  {
      debug("ThreadLimit: No threads are queued. Waiting for a thread to be queued.");
      m_AddEvent.Wait(); 
    }
    
    // Safely fetch m_Available
    { Lock<Mutex> guard(m_QueueLock);
      available = m_Available; }

    // Wait for an available thread slot
    if(available==0)  {
      debug("ThreadLimit: Limit reached.  Waiting for a thread to finish.");
      m_FinishEvent.Wait(); 
    }

    // Run the next thread
    {
      debug("ThreadLimit: Executing next thread");
      Lock<Mutex> guard(m_QueueLock);
      ThreadStarter nextThread = m_ThreadQueue.front();
      m_ThreadQueue.pop();
      --m_Available; nextThread.Start();
    }
  }
  return 0;
}
void ThreadLimit::SignalFinish()
{
      debug("ThreadLimit: A thread finished.");
      Lock<Mutex> guard(m_QueueLock);
      ++m_Available; m_FinishEvent.Signal();
}
void ThreadLimit::Add(Start_routine_f start_routine, Start_routine_arg_t start_routine_arg)
{
    Lock<Mutex> guard(m_QueueLock);
    m_ThreadQueue.push(ThreadStarter(start_routine,start_routine_arg, this));
    debug("ThreadLimit: Added a new thread.");
    m_AddEvent.Signal();
}
