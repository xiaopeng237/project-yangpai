// Logger macros for YPAI
// using DLT for logging
//

#pragma once

#define MYSQL_DLT 1
#define VERSION "19.09.25.V1"
#define SERVICE "MYSQL"


#ifdef MYSQL_DLT
#include <dlt/dlt.h>
#else 
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if MYSQL_DLT
#define MYSQL_DLT_INIT yp_dlt_log_init()

#define MYSQL_TRACE(format, ...) yp_dlt_log(DLT_LOG_DEBUG, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define MYSQL_TRACE_IN MYSQL_TRACE("IN")
#define MYSQL_LOG(format, ...) yp_dlt_log(DLT_LOG_INFO, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define MYSQL_WARNING(format, ...) yp_dlt_log(DLT_LOG_WARN, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define MYSQL_ERROR(format, ...) yp_dlt_log(DLT_LOG_ERROR, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
void yp_dlt_log_init();
void yp_dlt_log(DltLogLevelType level, const char *format, ...);

#else 

#define MYSQL_DLT_INIT

#define MYSQL_TRACE(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define MYSQL_TRACE_IN MYSQL_TRACE("IN")
#define MYSQL_LOG(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define MYSQL_WARNING(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define MYSQL_ERROR(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)


#endif

#define E_RELEASE 0
#define E_DEBUG	1
#define MYSQL_DEBUG(format, ...) yp_dlt_debug(E_DEBUG,format,##__VA_ARGS__)


#ifdef __cplusplus
}
#endif
