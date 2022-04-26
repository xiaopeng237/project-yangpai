#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include "yangpi_i2c_stub.h"
#include "log_dlt.h"

extern void init_stub_yangpi_i2c(tInterfaceStub_yangpi_i2c *stub);


extern void main_start();


HStub STUB_yangpi_i2c;
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
        I2CBUS_ERROR("interface is missing\n");
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
        I2CBUS_ERROR("interface is missing\n");
    }
    else if (0 == strcmp(interface, "yangpi.i2c"))
    {
        HStub stub = (HStub)user_data;
        yangpi_i2c_methods(stub,message);
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}

int main(void)
{
    yp_bus_init();
    yp_dbus_connect();

    I2CBUS_DLT_INIT;
    yp_dbus_register_service("yangpi.i2c");

    struct tComponentInstance instance_yangpi_i2c;
    instance_yangpi_i2c.connection = gp_Connection;
    instance_yangpi_i2c.path = "/yangpi/i2c";
    STUB_yangpi_i2c = &instance_yangpi_i2c;
	init_stub_yangpi_i2c(&INTERFACE_STUB_yangpi_i2c);


    yp_dbus_register_component(STUB_yangpi_i2c,yp_msg_handler,bus_filter);

    yp_dbus_work(main_start);
    return 0;
}