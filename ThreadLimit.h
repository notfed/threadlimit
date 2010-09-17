#ifndef THREADLIMIT_H
#define THREADLIMIT_H 1
#include "Thread.h"
#include "Mutex.h"
#include "Semaphore.h"
#include "Event.h"
#include <queue>
class ThreadLimit;

// Encapsulates a thread routine with an argument
class ThreadStarter
{
  Start_routine_f m_StartRoutine;
  Start_routine_arg_t m_StartRoutineArg;
  ThreadLimit* m_ThreadLimit;
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
  Event m_AddEvent;
  Event m_FinishEvent;
  Mutex m_QueueLock;
  void (*finish_event)();
  std::queue<ThreadStarter> m_ThreadQueue;
  void SignalFinish();
  void* ThreadLimitLoop();
  Thread m_Thread;
  friend class ThreadStarter;
public:
  virtual ~ThreadLimit();
  ThreadLimit(int limit);
  void Add(Start_routine_f,Start_routine_arg_t=0);
};
#endif
