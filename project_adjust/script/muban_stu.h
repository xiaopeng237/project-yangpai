/**********************************************************************************/
/* stub.h                                                                         */
/* generated by panda                                                             */
/**********************************************************************************/

#pragma once

#include <dbus/dbus.h>
#include "yangpai_service.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char * const INTERFACE_NAME_<<INTERFACE>>;

typedef struct tInterfaceStub_<<INTERFACE>>
{
<<proxy_method_struct>>
}tInterfaceStub_<<INTERFACE>>;

extern tInterfaceStub_<<INTERFACE>> INTERFACE_STUB_<<INTERFACE>>;

void <<INTERFACE>>_methods(HStub stub, DBusMessage *message);

<<proxy_signal_struct>>



#ifdef __cplusplus
}
#endif
