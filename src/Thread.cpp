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
#include "DBMng.hpp"

namespace dbproxy {

static std::pair<pthread_mutex_t, uint8_t> 
    initMutex = {PTHREAD_MUTEX_INITIALIZER, 0};

void *Thread::threadStart(void *thread)
{
  Thread *t = static_cast<Thread*>(thread);
  t->doThreadRun();
  return nullptr;
}

void Thread::doThreadRun()
{
  PCHECK(pthread_detach(_tid));

  PCHECK(pthread_mutex_lock(&initMutex.first));
  printf("Thread num[%u] pthreadId[%tu] pid[%u] tid[%tu]\n", _num, _tid, getpid(), gettid());
 // printf("vsersion[%u]\n",_db->getServerVersion());
  PCHECK(pthread_mutex_unlock(&initMutex.first));
  //do specifiy things

  sleep(3);
}

void Thread::start(uint8_t num)
{
  assert(!_started);

  assert(num <= THREAD_COUNT);
  _num = num;
  _started = true;
//  _db = gDBMng.getDB(_num); 

  PCHECK(pthread_create(&_tid, NULL, &threadStart, this));
}


} //end namespace
