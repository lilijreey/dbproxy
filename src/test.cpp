/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  test server
 *
 *        Created:  12/23/2012 03:29:08 PM
 *         Author:  YOUR NAME (), 
 *
 * =====================================================================================
 */

#include "DBMng.hpp"
#include "ThreadMng.hpp"

int main() 
{
  dbproxy::gDBMng.init();
//  dbproxy::ThreadMng mng;
//  mng.init();


  dbproxy::DataBase *db = dbproxy::gDBMng.getDB(0);
  printf("get version:%u\n", db->getServerVersion());


  return 0;
}
