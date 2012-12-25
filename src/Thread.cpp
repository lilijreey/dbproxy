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

void Thread::init(uint8_t num)
{
  initMutex.second = num;
  assert(num <= THREAD_COUNT);
  _num = initMutex.second;
  _tid = pthread_self();
  _db = gDBMng.getDB(_num); 
  PCHECK(pthread_detach(_tid));

  PCHECK(pthread_mutex_lock(&initMutex.first));
  printf("Thread[%u] num[%tu]\n", _num, _tid);
  printf("vsersion[%u]\n",_db->getServerVersion());
  PCHECK(pthread_mutex_unlock(&initMutex.first));



  sleep(3);

  //pthread_exit(0);
}


} //end namespace
