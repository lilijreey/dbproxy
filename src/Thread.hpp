/*
 * =====================================================================================
 *
 *       Filename:  Thread.hpp
 *
 *    Description:  线程类
 *
 *        Version:  1.0
 *        Created:  12/24/2012 02:00:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  THREAD_INC
#define  THREAD_INC

#include <pthread.h>

#include "Config.hpp"

namespace dbproxy {


class DataBase;
class Thread 
{
public:
  Thread():
      _num(THREAD_COUNT)
  {}

  ~Thread() {}

  // s = pthread_attr_destroy(&attr);
public:
  void init(uint8_t num);

public:
  uint8_t getNumber() const {return _num; }
  pthread_t getTid() const  {return _tid; }

private:

private:
  uint8_t  _num; //application-define id
  pthread_t _tid; // return by pthread_create
  DataBase *_db; 
};

} //end namespace

#endif   /* ----- #ifndef thread_INC  ----- */
