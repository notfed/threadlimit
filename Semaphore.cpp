#include "Semaphore.h"
#include <stdexcept>
#include <errno.h>
#include <iostream>

Semaphore::Semaphore(bool pshared,int initial)
   : m_Sem(new sem_t())
{
  if(m_Sem==0)
    throw std::runtime_error("Semaphore constructor error: m_Sem == 0");
  if(sem_init(m_Sem,(pshared?1:0),initial)==-1)
    throw std::runtime_error("sem_init failed");
}

Semaphore::~Semaphore()
{
    sem_destroy(m_Sem);
    delete m_Sem;
}
void Semaphore::lock()
{
  if(m_Sem==0)
    throw std::runtime_error("Semaphore::lock error: m_Sem == 0");

  int rc;
  for(;;){
    rc = sem_wait(m_Sem); 
    if(rc==0) break;
    if(errno==EINTR) continue;
    throw std::runtime_error("sem_wait failed");
  }
}
void Semaphore::unlock()
{
  if(sem_post(m_Sem)!=0)
    throw std::runtime_error("sem_post failed");
}
