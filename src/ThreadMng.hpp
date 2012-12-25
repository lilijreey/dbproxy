/*
 * =====================================================================================
 *
 *       Filename:  ThreadMng.hpp
 *
 *    Description:  一个线程池管理器
 *
 *        Version:  1.0
 *        Created:  12/24/2012 03:53:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  THREADMNG_INC
#define  THREADMNG_INC


#include "Thread.hpp"

namespace dbproxy {

//每个线程执行自己的mysql connect
class ThreadMng
{
public:
//  ThreadMng(){}
//  ~ThreadMng() {}

public:
  //@brief: 初始化所有线程
  bool init();
  Thread *getThread(uint8_t who) ;

private:
  Thread _threadPool[THREAD_COUNT] ;
};

extern ThreadMng gThreadMng;

inline
Thread *ThreadMng::getThread(uint8_t num)
{
  if (num >= THREAD_COUNT)
    return nullptr;
  return &_threadPool[num];
}

} //end namespace

#endif   /* ----- #ifndef threadmng_INC  ----- */
