/**********************************************************************************/
/* stub.c                                                                         */
/* generated by panda                                                             */
/**********************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "yangpi_adjust_stub.h"

const char * const INTERFACE_NAME_yangpi_adjust = "yangpi.adjust";
tInterfaceStub_yangpi_adjust INTERFACE_STUB_yangpi_adjust;

	
static void yangpi_adjust_method_adjust_start(HStub stub, DBusMessage *message, DBusMessage *reply)
{
	DBusMessageIter arg;
	T_AdjustIn zdb_T_AdjustIn;
	yp_dbus_incept_message(message,&arg,DBUS_TYPE_ARRAY, &zdb_T_AdjustIn);


	INTERFACE_STUB_yangpi_adjust.adjust_start(stub, &zdb_T_AdjustIn);
}


void yangpi_adjust_methods(HStub stub, DBusMessage *message)
{
	
	if (dbus_message_has_member(message, "adjust_start"))
	{
		if (NULL != INTERFACE_STUB_yangpi_adjust.adjust_start)
		{
			yp_dbus_request(yangpi_adjust_method_adjust_start,stub,message,NULL);
		}
	}
    else
	{
		fprintf(stderr, "invalid method\n");
	}

}
void yangpi_adjust_signal_adjust_result(HStub stub, T_AdjustOut *zdb_T_AdjustOut) 
{
	DBusMessage *msg;
	DBusMessageIter arg;
	
	
	yp_dbus_signal_create(&msg,&arg,stub->path,"yangpi.adjust","adjust_result",DBUS_TYPE_ARRAY, (void *)(zdb_T_AdjustOut),sizeof(T_AdjustOut));


	yp_dbus_reply(stub,msg);
}

