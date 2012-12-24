#include <errmsg.h> //mysql/
#include "DataBase.hpp"

namespace dbproxy {

static const int LEN=512;
static char sqlBuf[LEN]; //sql 语句buf

uint32_t DataBase::getServerVersion()
{
  return mysql_get_server_version(&_mysql);
}

//@brief: 执行SQL查询语句
bool DataBase::query(const std::string& sql)
{
  _last_query = sql;
again:
  if (mysql_real_query(&_mysql, sql.c_str(), sql.length())) {
    int ecode = mysql_errno(&_mysql);
    printf("query [%s] failed errno:%u  %s", sql.c_str(), ecode, mysql_error(&_mysql));
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
      printf("%s",_row[t]);
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
    printf("mysql_init error");
    return false;
  }

  const char arg=1;
  mysql_options(&_mysql, MYSQL_SET_CHARSET_NAME, "utf8");
  mysql_options(&_mysql, MYSQL_OPT_RECONNECT, &arg);
  //TODO 读取配置;
  if (NULL == mysql_real_connect(&_mysql, 
                                 "localhost",
                                 "root", "12345",
                                 "test",
                                 0/*port*/, NULL, 0)) { //CLIENT_FOUND_ROWS
    printf( "Could not connect to MySQL database at %s: %s\n",
              "localhost", mysql_error(&_mysql));
    mysql_close(&_mysql);
    return false;
  } 
  printf("Connect Mysql %s %s Succuss\n", "localhost", "xpoker");
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
    printf( "ping MySQL database failed: %s\n",  mysql_error(&_mysql));
    return ;
  }

}

} //end namespace
