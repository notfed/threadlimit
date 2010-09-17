#ifndef COND_H
#define COND_H
#include <pthread.h>
#include "Mutex.h"
class Cond
{
  pthread_cond_t* m_Cond;
  const pthread_t m_Owner;
public:
  virtual ~Cond();
  Cond();
  int Wait(Mutex&);
  int Broadcast();
  int Signal();
  operator pthread_cond_t* const();
};
#endif
