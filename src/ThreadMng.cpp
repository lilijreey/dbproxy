/*
 * =====================================================================================
 *
 *       Filename:  ThreadMng.cpp
 *
 *    Description:  
 *
 *        Created:  12/24/2012 03:59:28 PM
 *         Author:  YOUR NAME (), 
 *
 * =====================================================================================
 */


#include "ThreadMng.hpp"

namespace dbproxy { 

ThreadMng gThreadMng;

//用于存放调用线程的参数
//如果要放到init中有可能主线程已经运行完init
//子线程才开始，导致参数有误
//uint8_t numArry[THREAD_COUNT];

//@param: arg is Thread *
static
void * threadStart(void *arg)
{
  //block 
  ////线程不会共享局部变量,因为这些局部变量都是在调用
  //堆上的，每个线程有自己的调用堆栈
  uint8_t num = *static_cast<uint8_t*>(arg);
  free(arg);
  //printf("[%u][%u] [%p]\n", num, *(uint8_t*)arg, arg);
  gThreadMng.getThread(num)->init(num);

  //unblock
  return NULL;
}

bool ThreadMng::init() 
{
  pthread_t tid;
  //BUG 由于引用i的地址，所以thread执行时看到的arg
  //不一定和传入的arg相同
  for (uint8_t i=0; i < THREAD_COUNT; ++i) {
    uint8_t *id=static_cast<uint8_t*>(malloc(sizeof(uint8_t)));
    *id=i;
    PCHECK(pthread_create(&tid, NULL, threadStart, id));
    //sleep(1); //必须等待到创建的子进程看到i后才更新
    //HACK 使用条件
  }
  sleep(1);

  return true;
}

} //end namespace
