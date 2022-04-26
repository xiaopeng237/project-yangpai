//
// Created by Administrator on 2020/3/30.
//

#ifndef PROJECT_PINEERS_PIONEERS_SPI_H
#define PROJECT_PINEERS_PIONEERS_SPI_H
#include "yangpi_mysql_proxy.h"
typedef struct
{
    int SpiData_k31;
    int SpiData_k81;
    int SpiData_k160;
    int SpiData_k302;
    int SpiData_k356;
    int SpiData_es;
    int SpiData_esF;
    int SpiData_pul;//脉冲
    int SpiData_pulF;
    int SpiData_dpul[512];
    unsigned int SpiData_des[8192];
    int SpiData_fd_spi;
}T_FPGA_SpiData;


extern int function_dd_spi_init(void);
extern void function_dd_fpga_set_init(T_Fpga_Set *tFpga_Set);
extern int function_dd_fpga_read(unsigned char FpgaReg, unsigned char *FpgaData);
extern int function_dd_fpga_write(unsigned char FpgaReg, unsigned int FpgaValue);
extern int function_dd_fpga_writes(unsigned char FpgaReg, unsigned int FpgaValue);



#endif //PROJECT_PINEERS_PIONEERS_SPI_H
