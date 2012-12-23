#ifndef  DATABASE_INC
#define  DATABASE_INC

//#include "Common/Common.hpp"
//#include "Common/MsgHandler.hpp"
//#include "DataBase.hpp"

#include <mysql/my_global.h>
#include <mysql/my_sys.h>
#include <mysql/mysql.h>


class DataBase
{
public:
  DataBase() 
      :_res(nullptr)
  {}
	~DataBase() {} 

  void update( UInt32 now );
public:
  //@biref: 连接DB 
  bool init() ;
  //@biref: 清理
  void unInit();

private:
  //@brief: 连接保活
  void interactiveConnect();
  //@biref: 连接Mysql 返回是否连接成功
  bool connectDB();
  bool disconnectDB();
  bool getResult(const std::string& sql) ;
  bool query(const std::string& sql) ;

  //@brief: 查询是否存在
  //@return: 存在返回true
  bool isExists(const std::string& sql);

private:
  MYSQL_RES *_res;
  MYSQL_ROW _row;
  MYSQL _mysql;
  std::string _last_query; //最后一条SQL
};

extern DataBase gDataBase;

#endif   /* ----- #ifndef database_INC  ----- */
