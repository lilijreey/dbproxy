#ifndef  DATABASE_INC_
#define  DATABASE_INC_

#include <string>
#include <mysql/my_global.h>
#include <mysql/my_sys.h>
#include <mysql/mysql.h>


namespace dbproxy {

class DataBase
{
public:
  DataBase() 
      :_res(nullptr)
  {}
	~DataBase() {} 

  void update(uint32_t now );
public:
  //@biref: 连接DB 
  bool init() ;
  //@biref: 清理
  void unInit();

public:
  uint32_t getServerVersion();

private:
  //@brief: 连接保活
  void interactiveConnect();
  //@biref: 连接Mysql 返回是否连接成功
  bool connectDB();
  bool disconnectDB();
  bool getResult(const std::string& sql) ;
  bool query(const std::string& sql) ;


private:
  MYSQL_RES *_res;
  MYSQL_ROW _row;
  MYSQL _mysql;
  std::string _last_query; //最后一条SQL
  //Thread * _thread ??
};

} // end namespace

#endif   /* ----- #ifndef database_INC  ----- */
