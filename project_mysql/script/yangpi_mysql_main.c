#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include "yangpi_mysql_stub.h"
#include "log_dlt.h"


extern void init_stub_yangpi_mysql(tInterfaceStub_yangpi_mysql *stub);


extern void main_start();


HStub STUB_yangpi_mysql;
//HProxy PROXY_INTERFACE;


DBusHandlerResult bus_filter(DBusConnection *connection, DBusMessage *message,void *user_data) 
{
    if (dbus_message_get_type(message) != DBUS_MESSAGE_TYPE_SIGNAL)
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    if (dbus_message_has_interface(message, "org.freedesktop.DBus"))
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	
    const char *interface = dbus_message_get_interface(message);
    if (NULL == interface)
    {
        MYSQL_LOG("interface is missing\n");
    }
//    else
//	{
//		fprintf(stderr, "invalid signal\n");
//	}

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


DBusHandlerResult yp_msg_handler(DBusConnection *connection, DBusMessage *message,void *user_data)
{
    if (dbus_message_get_type(message) == DBUS_MESSAGE_TYPE_SIGNAL)
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	
    const char *interface = dbus_message_get_interface(message);

    if (NULL == interface)
    {
        MYSQL_LOG("interface is missing\n");
    }
    else if (0 == strcmp(interface, "yangpi.mysql"))
    {
        HStub stub = (HStub)user_data;
        yangpi_mysql_methods(stub,message);
    }
//    else
//    {
//        printf("invalid interface\n");
//    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}

int main(void)
{
    yp_bus_init();
    yp_dbus_connect();

    MYSQL_DLT_INIT;

    yp_dbus_register_service("yangpi.mysql");

    struct tComponentInstance instance_yangpi_mysql;
    instance_yangpi_mysql.connection = gp_Connection;
    instance_yangpi_mysql.path = "/yangpi/mysql";
    STUB_yangpi_mysql = &instance_yangpi_mysql;
	init_stub_yangpi_mysql(&INTERFACE_STUB_yangpi_mysql);


    yp_dbus_register_component(STUB_yangpi_mysql,yp_msg_handler,bus_filter);

    yp_dbus_work(main_start);
    return 0;
}