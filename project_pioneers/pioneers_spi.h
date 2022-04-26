//
// Created by Administrator on 2020/3/30.
//

#ifndef PROJECT_PINEERS_PIONEERS_SPI_H
#define PROJECT_PINEERS_PIONEERS_SPI_H
#include "yangpi_mysql_proxy.h"

extern int function_dd_spi_init(void);
extern void function_dd_fpga_set_init(T_Fpga_Set *tFpga_Set);
extern int function_dd_fpga_read(unsigned char FpgaReg, unsigned char *FpgaData);
extern int function_dd_fpga_write(unsigned char FpgaReg, unsigned int FpgaValue);
extern int function_dd_fpga_writes(unsigned char FpgaReg, unsigned int FpgaValue);

#endif //PROJECT_PINEERS_PIONEERS_SPI_H
