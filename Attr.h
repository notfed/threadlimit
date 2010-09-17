#ifndef ATTR_H
#define ATTR_H
#include <pthread.h>
class Attr
{
  pthread_attr_t m_Attr;
public:
  operator const pthread_attr_t*();
  Attr(int state = PTHREAD_CREATE_JOINABLE);
  ~Attr();
};
#endif
