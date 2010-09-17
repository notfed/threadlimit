#ifndef EVENT_H 
#define EVENT_H
#include "Mutex.h"
#include "Cond.h"
class Event
{
  Cond m_Cond;
  Mutex m_Mutex;
public:
  virtual ~Event() { }
  int Signal();
  int Broadcast();
  int Wait();
};
#endif
