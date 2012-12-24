/*
 * =====================================================================================
 *
 *       Filename:  Thread.cpp
 *
 *    Description:  
 *
 *        Created:  12/24/2012 02:04:24 PM
 *         Author:  YOUR NAME (), 
 *
 * =====================================================================================
 */

#include "Thread.hpp"

namespace dbproxy {

//@param: arg is Thread *
void * thread_start(void *arg)
{
  Thread *t = static_cast<Thread *>(arg);

  printf("Thread[%u] num[%u]\n", t->getNumber(), static_cast<uint32_t>(t->getTid()));
  PCHECK(pthread_detach(t->getTid())); //Qus. need join???
  sleep(3);

  pthread_exit(0);
  return NULL;
}

void Thread::init(uint8_t num)
{
  assert(_num == THREAD_COUNT);
  _num = num;
  printf("create num:%u\n", num);
  PCHECK(pthread_create(&_tid, NULL, thread_start, this));
}


} //end namespace
