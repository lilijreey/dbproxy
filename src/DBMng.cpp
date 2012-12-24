/*
 * =====================================================================================
 *
 *       Filename:  DBMng.cpp
 *
 *    Description:  
 *
 *        Created:  12/24/2012 01:18:33 PM
 *         Author:  YOUR NAME (), 
 *
 * =====================================================================================
 */

#include "DBMng.hpp"

namespace dbproxy
{
DBMng gDBMng;

bool DBMng::init() 
{
  for (uint32_t i=0; i < DB_CONNECT_COUNT; ++i)
    _dbPool[i].init();

 return true;
}

bool DBMng::unInit()
{
  for (uint32_t i=0; i < DB_CONNECT_COUNT; ++i)
    _dbPool[i].unInit();

  return true;
}


}//end namespace 
