#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include "Mutex.h"
class Thread
{
  pthread_t m_Thread;
  void Exit(void*);
  bool m_IsDone;
  Mutex m_StateLock;
public:
  typedef void* (*Start_routine_f)(void*);
  typedef void* Start_routine_arg_t;
  Thread(Start_routine_f,Start_routine_arg_t);
  virtual ~Thread() { }
  int Cancel();
  int Kill(int);
  int Join();
  int Join(void**);
};
#endif
