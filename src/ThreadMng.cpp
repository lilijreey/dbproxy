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

bool ThreadMng::init() 
{
  for (uint8_t i=0; i < THREAD_COUNT; ++i) {
    _threadPool[i].init(i); 
  }

  return true;
}


} //end namespace
