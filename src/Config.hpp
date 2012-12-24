/*
 * =====================================================================================
 *
 *       Filename:  Config.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/2012 01:12:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  CONFIG_INC_
#define  CONFIG_INC_


#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <sys/wait.h>

#include <cstring>
#include <cstdint>
#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <functional>


#include "common/tools.h"

//配置

//mysql 链接的数量
static const uint32_t  DB_CONNECT_COUNT = 5;


//总共的子线程数量
static const uint8_t THREAD_COUNT = 2;


#endif   /* ----- #ifndef config_INC  ----- */
