#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include "Mutex.h"
typedef void* (*Start_routine_f)(void*);
typedef void* Start_routine_arg_t;
class Thread
{
public:
  Thread(Start_routine_f,Start_routine_arg_t);
  virtual ~Thread() { }
  void Start();
  int Cancel();
  int Kill(int);
  int Join();
  int Join(void**);
private:
  pthread_t m_Thread;
  bool m_IsDone;
  Start_routine_f m_StartRoutine;
  Start_routine_arg_t m_StartRoutineArg;
  void Exit(void*);
  Mutex m_StateLock;
};
#endif
