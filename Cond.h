#ifndef COND_H
#define COND_H
#include <pthread.h>
#include "Mutex.h"
class Cond
{
  pthread_cond_t m_Cond;
public:
  ~Cond();
  Cond();
  int Wait(Mutex&);
  int Broadcast();
  int Signal();
};
#endif
