#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>
#include "Lock.h"
class Mutex
{
  pthread_mutex_t m_Mutex;
  friend class Lock<Mutex>;
  friend class Cond;
  void lock();
  void unlock();
public:
  ~Mutex();
  Mutex();
};
#endif
