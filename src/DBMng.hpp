/*
 * =====================================================================================
 *
 *       Filename:  DBMng.hpp
 *
 *    Description:  DB Pool 管理所有mysql链接
 *
 *        Version:  1.0
 *        Created:  12/24/2012 01:11:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DBMNG_INC
#define  DBMNG_INC


#include "Config.hpp"
#include "DataBase.hpp"

namespace dbproxy {

class DBMng
{
  //NOCOPY
public:
  DBMng() {};
  ~DBMng() {};

public:
  //@brief:初始化所有db connect
  bool init() ;
  bool unInit() ;


  DataBase *getDB(uint8_t index);

private:
 DataBase _dbPool[DB_CONNECT_COUNT];
};

inline
DataBase *DBMng::getDB(uint8_t index)
{
  if (index >= DB_CONNECT_COUNT) 
    return nullptr;
  return &_dbPool[index]; 
}

extern DBMng gDBMng;

} //end namespace

#endif   /* ----- #ifndef dbmng_INC  ----- */
