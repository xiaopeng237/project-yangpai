//
// Created by Administrator on 2020/3/26.
//

#ifndef TMP_I2CBUS_LOG_DLT_H
#define TMP_I2CBUS_LOG_DLT_H
#pragma once

#define I2CBUS_DLT 1
#define VERSION "19.09.25.V1"
#define SERVICE "I2CBUS"


#ifdef I2CBUS_DLT
#include <dlt/dlt.h>
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if I2CBUS_DLT
#define I2CBUS_DLT_INIT yp_dlt_log_init()

#define I2CBUS_TRACE(format, ...) yp_dlt_log(DLT_LOG_DEBUG, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define I2CBUS_TRACE_IN I2CBUS_TRACE("IN")
#define I2CBUS_LOG(format, ...) yp_dlt_log(DLT_LOG_INFO, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define I2CBUS_WARNING(format, ...) yp_dlt_log(DLT_LOG_WARN, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
#define I2CBUS_ERROR(format, ...) yp_dlt_log(DLT_LOG_ERROR, "[%s][%d]"format, __func__, __LINE__, ##__VA_ARGS__)
void yp_dlt_log_init();
void yp_dlt_log(DltLogLevelType level, const char *format, ...);

#else

#define I2CBUS_DLT_INIT

#define I2CBUS_TRACE(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define I2CBUS_TRACE_IN I2CBUS_TRACE("IN")
#define I2CBUS_LOG(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define I2CBUS_WARNING(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)
#define I2CBUS_ERROR(format, ...) printf("[%s][%s][%d]"format"", __FILE__,__func__, __LINE__, ##__VA_ARGS__)


#endif

#define E_RELEASE 0
#define E_DEBUG	1
#define I2CBUS_DEBUG(format, ...) yp_dlt_debug(E_DEBUG,format,##__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif //TMP_I2CBUS_LOG_DLT_H
