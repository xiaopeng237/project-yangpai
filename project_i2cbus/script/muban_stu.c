/**********************************************************************************/
/* stub.c                                                                         */
/* generated by panda                                                             */
/**********************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "<<INTERFACE>>_stub.h"

const char * const INTERFACE_NAME_<<INTERFACE>> = "<<INTERFACE_SOURCE>>";
tInterfaceStub_<<INTERFACE>> INTERFACE_STUB_<<INTERFACE>>;

<<stub_signal_select_function>>

void <<INTERFACE>>_methods(HStub stub, DBusMessage *message)
{
	
<<stub_signal_select>>else
	{
		fprintf(stderr, "invalid method\n");
	}

}
<<stub_call_function>>