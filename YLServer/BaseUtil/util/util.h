/*================================================================
*   
*   文件名称: util.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午12:43
*   描   述: 公共的函数和宏
*
================================================================*/


#ifndef BASEUTIL_UTIL_H
#define BASEUTIL_UTIL_H

#ifdef __GNUC__
#include <ext/hash_map>
#else
#include <hash_map>
#endif

#include <string.h>
#include "../log/log.h"


//输出日志
static youliao::log::Log g_log("youliao");
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__ )
#define log(format, args...) g_log.Info("<%s> | <%d> | <%s>" format, __FILENAME__, __LINE__, __FUNCTION__, ##args)
#define printSql2Log(sql) log("执行SQL语句: %s", sql)
//
#define NO_USERD(arg) ((void)arg)

#endif //BASEUTIL_UTIL_H
