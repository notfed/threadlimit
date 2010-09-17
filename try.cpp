#include <iostream>
#include "Thread.h"
using namespace std;
void* thread_func(void* arg)
{
  sleep(1);
  const char *ptr = (const char*)arg;
  cerr << ptr;
  return 0;
}
int main()
{
  Thread a(thread_func,(void*)"A");
  Thread b(thread_func,(void*)"B");
  Thread c(thread_func,(void*)"C");
  Thread d(thread_func,(void*)"D");
  Thread e(thread_func,(void*)"E");
  Thread f(thread_func,(void*)"F");
  Thread g(thread_func,(void*)"G");
  Thread h(thread_func,(void*)"H");
  Thread i(thread_func,(void*)"I");
  Thread j(thread_func,(void*)"J");
  cin.get(); 
  return 0;
}
