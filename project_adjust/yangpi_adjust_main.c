#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include "yangpi_adjust_stub.h"
#include "yangpi_i2c_proxy.h"
#include "log_dlt.h"

extern void init_stub_yangpi_adjust(tInterfaceStub_yangpi_adjust *stub);
extern void init_client_yangpi_i2c(tInterfaceClient_yangpi_i2c *client);


extern void main_start();


HStub STUB_yangpi_adjust;
HProxy PROXY_yangpi_i2c;
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
        ADJUST_LOG("interface is missing\n");
    }
	
    else if (dbus_message_has_path(message, PROXY_yangpi_i2c->path))
    {
        if (0 == strcmp(interface, "yangpi.i2c"))
        {
            yangpi_i2c_signals(PROXY_yangpi_i2c,message);
            return DBUS_HANDLER_RESULT_HANDLED;
        }
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
        ADJUST_LOG("interface is missing\n");
    }
    else if (0 == strcmp(interface, "yangpi.adjust"))
    {
        HStub stub = (HStub)user_data;
        yangpi_adjust_methods(stub,message);
    }


    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}

int main(void)
{
    yp_bus_init();
    yp_dbus_connect();
    yp_dbus_wait_service("yangpi.i2c");

    ADJUST_DLT_INIT;
    yp_dbus_register_service("yangpi.adjust");

    struct tComponentInstance instance_yangpi_adjust;
    instance_yangpi_adjust.connection = gp_Connection;
    instance_yangpi_adjust.path = "/yangpi/adjust";
    STUB_yangpi_adjust = &instance_yangpi_adjust;
	init_stub_yangpi_adjust(&INTERFACE_STUB_yangpi_adjust);
	
    struct tRemoteComponent proxy_yangpi_i2c;
    proxy_yangpi_i2c.connection = gp_Connection;
    proxy_yangpi_i2c.path = "/yangpi/i2c";
    proxy_yangpi_i2c.service = "yangpi.i2c";
    PROXY_yangpi_i2c = &proxy_yangpi_i2c;
 //   init_client_yangpi_i2c(&INTERFACE_CLIENT_yangpi_i2c);



    yp_dbus_register_component(STUB_yangpi_adjust,yp_msg_handler,bus_filter);

    yp_dbus_work(main_start);
    return 0;
}