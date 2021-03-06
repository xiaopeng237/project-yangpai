/**********************************************************************************/
/* stub.h                                                                         */
/* generated by panda                                                             */
/**********************************************************************************/

#pragma once

#include <dbus/dbus.h>
#include "yangpai_service.h"
#include "adjust_service_base.h"
#ifdef __cplusplus
extern "C" {
#endif

extern const char * const INTERFACE_NAME_yangpi_adjust;

typedef struct tInterfaceStub_yangpi_adjust
{
	void (*adjust_start)(HStub stub, T_AdjustIn *zdb_T_AdjustIn);

}tInterfaceStub_yangpi_adjust;

extern tInterfaceStub_yangpi_adjust INTERFACE_STUB_yangpi_adjust;

void yangpi_adjust_methods(HStub stub, DBusMessage *message);

void yangpi_adjust_signal_adjust_result(HStub stub, T_AdjustOut *zdb_T_AdjustOut);




#ifdef __cplusplus
}
#endif
