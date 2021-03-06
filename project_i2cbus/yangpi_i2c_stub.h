/**********************************************************************************/
/* stub.h                                                                         */
/* generated by panda                                                             */
/**********************************************************************************/

#pragma once

#include <dbus/dbus.h>
#include "yangpai_service.h"
#include "i2cbus_base.h"
#ifdef __cplusplus
extern "C" {
#endif

extern const char * const INTERFACE_NAME_yangpi_i2c;

typedef struct tInterfaceStub_yangpi_i2c
{
	void (*i2c_adjust)(HStub stub, T_I2cAdjust *zdb_T_I2cAdjust);
	void (*i2c_oled)(HStub stub, T_I2cOled *zdb_T_I2cOled);

}tInterfaceStub_yangpi_i2c;

extern tInterfaceStub_yangpi_i2c INTERFACE_STUB_yangpi_i2c;

void yangpi_i2c_methods(HStub stub, DBusMessage *message);

void yangpi_i2c_signal_i2c_ad1115(HStub stub, T_I2cAd1115 *zdb_T_I2cAd1115);




#ifdef __cplusplus
}
#endif
