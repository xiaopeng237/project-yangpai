//
// Created by Administrator on 2020/3/27.
//

#include "log_dlt.h"

#if ADJUST_DLT

#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>


#define STR_BUFFER_LEN 1000
DLT_DECLARE_CONTEXT(con_adjust);


void yp_dlt_log_init()
{
	char ver_str[STR_BUFFER_LEN] = {0};

	DLT_REGISTER_APP(SERVICE,SERVICE);
	DLT_REGISTER_CONTEXT(con_adjust,"SERV","Service");

	snprintf(ver_str, STR_BUFFER_LEN, "[%s][v%s]\n", SERVICE,VERSION);
	dlt_log_string(&con_adjust, DLT_LOG_INFO, ver_str);
}

void yp_dlt_log(DltLogLevelType level, const char *format, ...)
{
	DltContext *handle = &con_adjust;
	DltContextData log;

	if ((handle == 0) || (format == 0))
	{
		return;
	}

	if (dlt_user_log_write_start(handle, &log, level) > 0)
	{
		char text[STR_BUFFER_LEN];
		int len;
		va_list var_args;

		va_start (var_args, format);
		len = vsnprintf(text, STR_BUFFER_LEN, format, var_args);
		va_end (var_args);

		if (len < 0)
			return;

		if (dlt_user_log_write_string(&log, text) == -1)
		{
			return;
		}
		if (dlt_user_log_write_finish(&log) == -1)
		{
			return;
		}
	}
}

void yp_dlt_debug(int mode, const char *format, ...)
{

	char text[STR_BUFFER_LEN];
	int len;
	va_list var_args;

	if ((format == 0))
	{
		return;
	}

	va_start (var_args, format);
	len = vsnprintf(text, STR_BUFFER_LEN, format, var_args);
	va_end (var_args);

	if(mode >= E_DEBUG)
	{
		 printf("[%s_DEBUG]%s\n",SERVICE,text);
	}
	if(mode >= E_RELEASE)
	{
		dlt_log_string(&con_adjust, DLT_LOG_INFO, text);
	}

}

#endif /* 1 */