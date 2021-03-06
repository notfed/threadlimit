#ifndef THREADLIMIT_H
#define THREADLIMIT_H 1
#include "Thread.h"
#include "Mutex.h"
#include "Event.h"
#include <queue>
class ThreadLimit;

// Encapsulates a thread routine with an argument
class ThreadStarter
{
  const Start_routine_f m_StartRoutine;
  const Start_routine_arg_t m_StartRoutineArg;
  ThreadLimit* const m_ThreadLimit;
  void* MonitorThread();
public:
  virtual ~ThreadStarter();
  ThreadStarter(Start_routine_f,Start_routine_arg_t, ThreadLimit* owner);
  void Start();
};
// Runs all threads added to it, with a cap on the number of simultaneous threads
class ThreadLimit
{
  const int m_Limit;
  int m_Available;
  bool m_Finished;
  Event m_AddEvent;
  Event m_ThreadCompleteEvent;
  Mutex m_QueueLock;
  Mutex m_FinishLock;
  Thread m_Thread;
  std::queue<ThreadStarter> m_ThreadQueue;
  void (*finish_event)();
  void SignalThreadCompleted();
  void* ThreadLimitLoop();
  void WaitForThreads();
  friend class ThreadStarter;
public:
  virtual ~ThreadLimit();
  ThreadLimit(int limit);
  void Add(Start_routine_f,Start_routine_arg_t=0);
  void Finish();
};
#endif
