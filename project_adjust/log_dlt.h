//
// Created by Administrator on 2020/3/27.
//

#ifndef PROJECT_ADJUST_LOG_DLT_H
#define PROJECT_ADJUST_LOG_DLT_H
#pragma once

#define ADJUST_DLT 1
#define VERSION "19.09.25.V1"
#define SERVICE "ADJUST"


#ifdef ADJUST_DLT
#include <dlt/dlt.h>
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if ADJUST_DLT
#define ADJUST_DLT_INIT yp_dlt_log_init()

#define ADJUST_TRACE(format, ...) yp_dlt_log(DLT_LOG_DEBUG, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define ADJUST_TRACE_IN ADJUST_TRACE("IN")
#define ADJUST_LOG(format, ...) yp_dlt_log(DLT_LOG_INFO, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define ADJUST_WARNING(format, ...) yp_dlt_log(DLT_LOG_WARN, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define ADJUST_ERROR(format, ...) yp_dlt_log(DLT_LOG_ERROR, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
void yp_dlt_log_init();
void yp_dlt_log(DltLogLevelType level, const char *format, ...);

#else

#define ADJUST_DLT_INIT

#define ADJUST_TRACE(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define ADJUST_TRACE_IN ADJUST_TRACE("IN")
#define ADJUST_LOG(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define ADJUST_WARNING(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define ADJUST_ERROR(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)


#endif

#define E_RELEASE 0
#define E_DEBUG	1
#define ADJUST_DEBUG(format, ...) yp_dlt_debug(E_DEBUG,format,##__VA_ARGS__)


#ifdef __cplusplus
}
#endif
#endif //PROJECT_ADJUST_LOG_DLT_H
