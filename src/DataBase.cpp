#include <errmsg.h> //mysql/
#include "Skynet/src/log.h"
#include "Skynet/src/net_if.h"


DataBase gDataBase;

static const int LEN=512;
static char sqlBuf[LEN]; //sql 语句buf


//@brief: 执行SQL查询语句
bool DataBase::query(const std::string& sql)
{
  _last_query = sql;
again:
  if (mysql_real_query(&_mysql, sql.c_str(), sql.length())) {
    int ecode = mysql_errno(&_mysql);
    ERROR_LOG("query [%s] failed errno:%u  %s", sql.c_str(), ecode, mysql_error(&_mysql));
    if (ecode == 2013 ) {
      goto again;
    }

    if (ecode == CR_SERVER_GONE_ERROR) {
      do {//TODO send erro log
        disconnectDB();
      } while (!connectDB());
      goto again;
    }
    return false;
  }
  return true;
}

bool DataBase::getResult(const std::string& sql) 
{
  if (!query(sql))
    return false;

  _res = mysql_store_result(&_mysql);
  if (_res == NULL) return false;
  //返回行数
  //int count = mysql_num_rows(_res);
  //  DEBUG_LOG("rows :%d", count);
  while ((_row = mysql_fetch_row(_res)) != NULL) {
    // get cols
    for (size_t t=0; t < mysql_num_fields(_res); ++t) {
      DEBUG_LOG("%s",_row[t]);
    }
  }

  //  MYSQL_FIELD *f = nullptr; //得到每个列的名字
  //  while ((f = mysql_fetch_field(_res))) {
  //    DEBUG_LOG("ff:%s", f->name);
  //  }

  mysql_free_result(_res);

  return true;
}

bool DataBase::init() 
{
  if (!connectDB()) {
    return false;
  }
  return true;
}

void DataBase::unInit() 
{
  disconnectDB();
}

bool DataBase::connectDB()
{
  if (mysql_init(&_mysql) == NULL) {
    ERROR_LOG("mysql_init error");
    return false;
  }

  const char arg=1;
  mysql_options(&_mysql, MYSQL_SET_CHARSET_NAME, "utf8");
  mysql_options(&_mysql, MYSQL_OPT_RECONNECT, &arg);
  //TODO 读取配置;
  if (NULL == mysql_real_connect(&_mysql, 
                                 "localhost",
                                 "root", "12345",
                                 "xpoker",
                                 0/*port*/, NULL, 0)) { //CLIENT_FOUND_ROWS
    ERROR_LOG( "Could not connect to MySQL database at %s: %s\n",
              "localhost", mysql_error(&_mysql));
    mysql_close(&_mysql);
    return false;
  } 

  DEBUG_LOG("Connect Mysql %s %s Succuss", "localhost", "xpoker");
  return true;
}

bool DataBase::disconnectDB()
{
  mysql_close(&_mysql);
  return true;
}

void DataBase::interactiveConnect()
{
  if (mysql_ping(&_mysql) != 0 ) {
    ERROR_LOG( "ping MySQL database failed: %s\n",  mysql_error(&_mysql));
    return ;
  }


//  ///两分钟ping一次
//  UInt32 time = TimeUtil::timerTime(TimeUtil::MINUTE * 2);
//  VarMsg msg(Timer_ActiveMysqlConn);
//  Timer::addTimeOut(time, msg);
}
