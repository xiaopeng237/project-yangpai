/**********************************************************************************/
/* proxy.c                                                                        */
/* generated by panda                                                             */
/**********************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "yangpi_mysql_proxy.h"
#include "mysql_base.h"

tInterfaceClient_yangpi_mysql INTERFACE_CLIENT_yangpi_mysql;

const char * const INTERFACE_NAME_yangpi_mysql = "yangpi.mysql";

	
static void yangpi_mysql_notification_incept_all(HProxy proxy, DBusMessage *message)
{
	DBusMessageIter arg;
	T_Arm_Mysql zdb_T_Arm_Mysql;
	yp_dbus_incept_message(message,&arg,DBUS_TYPE_ARRAY, &zdb_T_Arm_Mysql);

	T_Fpga_Set zdb_T_Fpga_Set;
	yp_dbus_mes_get_next_arry(&arg, &zdb_T_Fpga_Set);

	T_Flow_para zdb_T_Flow_para;
	yp_dbus_mes_get_next_arry(&arg, &zdb_T_Flow_para);


	INTERFACE_CLIENT_yangpi_mysql.on_signal_incept_all(proxy, &zdb_T_Arm_Mysql, &zdb_T_Fpga_Set, &zdb_T_Flow_para);
}



void yangpi_mysql_signals(HProxy proxy, DBusMessage *message)
{

	if (dbus_message_has_member(message, "incept_all"))
	{
		if (NULL != INTERFACE_CLIENT_yangpi_mysql.on_signal_incept_all)
		{
			yp_dbus_signal(yangpi_mysql_notification_incept_all,proxy,message);
		}
	}
    else
	{
		fprintf(stderr, "invalid signal\n");
	}

}

void yangpi_mysql_call_writelog(HProxy proxy, T_Write_Mysql_Log *zdb_T_Write_Mysql_Log) 
{
	DBusMessage *msg;
	DBusMessageIter arg;
	
	
	yp_dbus_method_call_create(&msg,&arg,proxy->service,proxy->path,"yangpi.mysql","writelog",DBUS_TYPE_ARRAY, (void *)(zdb_T_Write_Mysql_Log),sizeof(T_Write_Mysql_Log));


	yp_dbus_call(proxy, msg, NULL);
}
void yangpi_mysql_call_writeflow(HProxy proxy, T_Write_Flow_Result *zdb_T_Write_Flow_Result) 
{
	DBusMessage *msg;
	DBusMessageIter arg;
	
	
	yp_dbus_method_call_create(&msg,&arg,proxy->service,proxy->path,"yangpi.mysql","writeflow",DBUS_TYPE_ARRAY, (void *)(zdb_T_Write_Flow_Result),sizeof(T_Write_Flow_Result));


	yp_dbus_call(proxy, msg, NULL);
}
void yangpi_mysql_call_writeES(HProxy proxy, T_Write_ES *zdb_T_Write_ES) 
{
	DBusMessage *msg;
	DBusMessageIter arg;
	
	
	yp_dbus_method_call_create(&msg,&arg,proxy->service,proxy->path,"yangpi.mysql","writeES",DBUS_TYPE_ARRAY, (void *)(zdb_T_Write_ES),sizeof(T_Write_ES));


	yp_dbus_call(proxy, msg, NULL);
}
	
void yangpi_mysql_call_request_all(HProxy proxy)
{
	DBusMessage *msg = dbus_message_new_method_call(proxy->service, proxy->path, INTERFACE_NAME_yangpi_mysql, "request_all");
	yp_dbus_call(proxy, msg, NULL);
}




