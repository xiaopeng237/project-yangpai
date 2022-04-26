#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include "yangpi_pioneers_stub.h"
#include "yangpi_mysql_proxy.h"
#include "yangpi_i2c_proxy.h"
#include "yangpi_adjust_proxy.h"
#include "log_dlt.h"
#include "yangpi_ota_proxy.h"


extern void init_stub_yangpi_pioneers(tInterfaceStub_yangpi_pioneers *stub);
extern void init_client_yangpi_mysql(tInterfaceClient_yangpi_mysql *client);
extern void init_client_yangpi_i2c(tInterfaceClient_yangpi_i2c *client);
extern void init_client_yangpi_adjust(tInterfaceClient_yangpi_adjust *client);
extern void init_client_yangpi_ota(tInterfaceClient_yangpi_ota *client);

extern void main_start();


HStub STUB_yangpi_pioneers;
HProxy PROXY_yangpi_mysql;
HProxy PROXY_yangpi_i2c;
HProxy PROXY_yangpi_adjust;
HProxy PROXY_yangpi_ota;
HProxy PROXY_yangpi_rtu;
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
        PRONEERS_LOG("interface is missing\n");
    }
	
    else if (dbus_message_has_path(message, PROXY_yangpi_mysql->path))
    {
        if (0 == strcmp(interface, "yangpi.mysql"))
        {
            yangpi_mysql_signals(PROXY_yangpi_mysql,message);
            PRONEERS_LOG("mysql_incept_all bus_filter \n");
            return DBUS_HANDLER_RESULT_HANDLED;
        }
    }
	
    else if (dbus_message_has_path(message, PROXY_yangpi_i2c->path))
    {
        if (0 == strcmp(interface, "yangpi.i2c"))
        {
            yangpi_i2c_signals(PROXY_yangpi_i2c,message);
            PRONEERS_LOG("i2c_ad1115 bus_filter \n");
            return DBUS_HANDLER_RESULT_HANDLED;
        }
    }
	
    else if (dbus_message_has_path(message, PROXY_yangpi_adjust->path))
    {
        if (0 == strcmp(interface, "yangpi.adjust"))
        {
            yangpi_adjust_signals(PROXY_yangpi_adjust,message);
            return DBUS_HANDLER_RESULT_HANDLED;
        }
    }
    else
	{
        PRONEERS_LOG("invalid signal\n");
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
        PRONEERS_LOG("interface is missing\n");
    }
    else if (0 == strcmp(interface, "yangpi.pioneers"))
    {
        HStub stub = (HStub)user_data;
        yangpi_pioneers_methods(stub,message);
    }
    else
    {
        PRONEERS_LOG("invalid interface\n");
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}

int main(void)
{
    yp_bus_init();
    yp_dbus_connect();
    yp_dbus_wait_service("yangpi.mysql");
    yp_dbus_wait_service("yangpi.i2c");
    yp_dbus_wait_service("yangpi.adjust");

    PRONEERS_DLT_INIT;
    yp_dbus_register_service("yangpi.pioneers");

    struct tComponentInstance instance_yangpi_pioneers;
    instance_yangpi_pioneers.connection = gp_Connection;
    instance_yangpi_pioneers.path = "/yangpi/pioneers";
    STUB_yangpi_pioneers = &instance_yangpi_pioneers;
	init_stub_yangpi_pioneers(&INTERFACE_STUB_yangpi_pioneers);
	
    struct tRemoteComponent proxy_yangpi_mysql;
    proxy_yangpi_mysql.connection = gp_Connection;
    proxy_yangpi_mysql.path = "/yangpi/mysql";
    proxy_yangpi_mysql.service = "yangpi.mysql";
    PROXY_yangpi_mysql = &proxy_yangpi_mysql;
    init_client_yangpi_mysql(&INTERFACE_CLIENT_yangpi_mysql);

	
    struct tRemoteComponent proxy_yangpi_i2c;
    proxy_yangpi_i2c.connection = gp_Connection;
    proxy_yangpi_i2c.path = "/yangpi/i2c";
    proxy_yangpi_i2c.service = "yangpi.i2c";
    PROXY_yangpi_i2c = &proxy_yangpi_i2c;
    init_client_yangpi_i2c(&INTERFACE_CLIENT_yangpi_i2c);

	
    struct tRemoteComponent proxy_yangpi_adjust;
    proxy_yangpi_adjust.connection = gp_Connection;
    proxy_yangpi_adjust.path = "/yangpi/adjust";
    proxy_yangpi_adjust.service = "yangpi.adjust";
    PROXY_yangpi_adjust = &proxy_yangpi_adjust;
    init_client_yangpi_adjust(&INTERFACE_CLIENT_yangpi_adjust);

    struct tRemoteComponent proxy_yangpi_ota;
    proxy_yangpi_ota.connection = gp_Connection;
    proxy_yangpi_ota.path = "/yangpi/ota";
    proxy_yangpi_ota.service = "yangpi.ota";
    PROXY_yangpi_ota = &proxy_yangpi_ota;
    init_client_yangpi_ota(&INTERFACE_CLIENT_yangpi_ota);

    struct tRemoteComponent proxy_yangpi_rtu;
    proxy_yangpi_rtu.connection = gp_Connection;
    proxy_yangpi_rtu.path = "/yangpi/rtu";
    proxy_yangpi_rtu.service = "yangpi.rtu";
    PROXY_yangpi_rtu = &proxy_yangpi_rtu;

    yp_dbus_register_component(STUB_yangpi_pioneers,yp_msg_handler,bus_filter);

    yp_dbus_work(main_start);
    return 0;
}