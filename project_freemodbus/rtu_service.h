//
// Created by Administrator on 2020/4/29.
//

#ifndef BUILDROOT_PROJECT_RTU_SERVICE_H
#define BUILDROOT_PROJECT_RTU_SERVICE_H

#include "rtu_data_base.h"

int freeModbusInit( int argc, char *argv[] );
void setShare_rtu(T_RtuData *tRtuData);
#endif //BUILDROOT_PROJECT_RTU_SERVICE_H
