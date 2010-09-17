#include <iostream>
#include "Thread.h"
#include "Lock.h"
#include "Semaphore.h"
using namespace std;
Mutex console_lock;
void* thread_func(void* arg)
{
  sleep(1);
  const char *ptr = (const char*)arg;
  {
    Lock<Mutex> guard(console_lock);
    cout << "Thread " << ptr << endl;;
  }
  return 0;
}
int main()
{
  Thread a(thread_func,(void*)"A"); a.Start();
  Thread b(thread_func,(void*)"B"); b.Start();
  Thread c(thread_func,(void*)"C"); c.Start();
  Thread d(thread_func,(void*)"D"); d.Start();
  Thread e(thread_func,(void*)"E"); e.Start();
  Thread f(thread_func,(void*)"F"); f.Start();
  Thread g(thread_func,(void*)"G"); g.Start();
  Thread h(thread_func,(void*)"H"); h.Start();
  Thread i(thread_func,(void*)"I"); i.Start();
  Thread j(thread_func,(void*)"J"); j.Start();
  cin.get(); 
  return 0;
}
