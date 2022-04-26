#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include "yangpi_ota_stub.h"
#include "yangpi_mysql_proxy.h"


extern void init_stub_yangpi_ota(tInterfaceStub_yangpi_ota *stub);
extern void init_client_yangpi_mysql(tInterfaceClient_yangpi_mysql *client);


extern void main_start();


HStub STUB_yangpi_ota;
HProxy PROXY_yangpi_mysql;
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
        printf("interface is missing\n");
    }
	
    else if (dbus_message_has_path(message, PROXY_yangpi_mysql->path))
    {
        if (0 == strcmp(interface, "yangpi.mysql"))
        {
            yangpi_mysql_signals(PROXY_yangpi_mysql,message);
            printf("ota_ready1\n");
            return DBUS_HANDLER_RESULT_HANDLED;
        }
    }
    else
	{
		fprintf(stderr, "invalid signal\n");
	}

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


DBusHandlerResult yp_msg_handler(DBusConnection *connection, DBusMessage *message,void *user_data) 
{
    if (dbus_message_get_type(message) == DBUS_MESSAGE_TYPE_SIGNAL)
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	
    const char *interface = dbus_message_get_interface(message);

    if (NULL == interface)
    {
        printf("interface is missing\n");
    }
    else if (0 == strcmp(interface, "yangpi.ota"))
    {
        HStub stub = (HStub)user_data;
        yangpi_ota_methods(stub,message);
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}

int main(void)
{
    yp_bus_init();
    yp_dbus_connect();
    yp_dbus_wait_service("yangpi.mysql");

    
    yp_dbus_register_service("yangpi.ota");

    struct tComponentInstance instance_yangpi_ota;
    instance_yangpi_ota.connection = gp_Connection;
    instance_yangpi_ota.path = "/yangpi/ota";
    STUB_yangpi_ota = &instance_yangpi_ota;
	init_stub_yangpi_ota(&INTERFACE_STUB_yangpi_ota);
	
    struct tRemoteComponent proxy_yangpi_mysql;
    proxy_yangpi_mysql.connection = gp_Connection;
    proxy_yangpi_mysql.path = "/yangpi/mysql";
    proxy_yangpi_mysql.service = "yangpi.mysql";
    PROXY_yangpi_mysql = &proxy_yangpi_mysql;
    init_client_yangpi_mysql(&INTERFACE_CLIENT_yangpi_mysql);



    yp_dbus_register_component(STUB_yangpi_ota,yp_msg_handler,bus_filter);

    yp_dbus_work(main_start);
    return 0;
}