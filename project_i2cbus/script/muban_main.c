#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include "<<LOCAL_INTFRFACE>>_stub.h"
<<INCLUDE>>

extern void init_stub_<<LOCAL_INTFRFACE>>(tInterfaceStub_<<LOCAL_INTFRFACE>> *stub);
<<main_extern>>

extern void main_start();


HStub STUB_<<LOCAL_INTFRFACE>>;
<<DEF_PROXY_INTERFACE>>;//HProxy PROXY_INTERFACE;


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
<<main_signal>>else
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
<<msg_handler>>else
    {
        printf("invalid interface\n");
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}

int main(void)
{
    yp_bus_init();
    yp_dbus_connect();
<<wait_service>>
    
    yp_dbus_register_service("<<LOCAL_INTFRFACE_SOURCE>>");

    struct tComponentInstance instance_<<LOCAL_INTFRFACE>>;
    instance_<<LOCAL_INTFRFACE>>.connection = gp_Connection;
    instance_<<LOCAL_INTFRFACE>>.path = "<<LOCAL_INTFRFACE_PATH>>";
    STUB_<<LOCAL_INTFRFACE>> = &instance_<<LOCAL_INTFRFACE>>;
	init_stub_<<LOCAL_INTFRFACE>>(&INTERFACE_STUB_<<LOCAL_INTFRFACE>>);
<<main_proxy_intf>>

    yp_dbus_register_component(STUB_<<LOCAL_INTFRFACE>>,yp_msg_handler,bus_filter);

    yp_dbus_work(main_start);
    return 0;
}