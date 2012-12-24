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

class ThreadMng
{
public:
//  ThreadMng(){}
//  ~ThreadMng() {}

public:
  //@brief: 初始化所有线程
  bool init();



private:
  Thread _threadPool[THREAD_COUNT] ;
};


} //end namespace

#endif   /* ----- #ifndef threadmng_INC  ----- */
