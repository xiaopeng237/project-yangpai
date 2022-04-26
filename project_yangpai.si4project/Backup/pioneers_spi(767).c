//
// Created by Administrator on 2020/3/30.
//
#include <linux/spi/spidev.h>
#include <string.h>
#include <linux/watchdog.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "pioneers_spi.h"
#include "log_dlt.h"

/*spi 控制器参数配置*/
#define DD_SPI_CTL_MODE     0
#define DD_SPI_CTL_BITS     8
#define DD_SPI_CTL_SPEED    2000000
#define DD_SPI_CTL_DELAY    0
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
unsigned int EnergyS[8192];
T_FPGA_SpiData tFpgaSpiData;

/*******************************************************************************
* 函数名称:function_dd_spi_init
* 函数功能:spi控制器初始化
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* 
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_spi_init(void)
{
    static const char *device = "/dev/spidev1.0";
    //static const char *device = "/dev/spidev1.1";

    int ret1 = 0;
    int fd1;
    char mode = DD_SPI_CTL_MODE;
    char bits = DD_SPI_CTL_BITS;
    int speed = DD_SPI_CTL_SPEED;

    fd1 = open(device, O_RDWR);
    if (fd1 < 0)
        PRONEERS_ERROR("can't open device");


    ret1 = ioctl(fd1, SPI_IOC_WR_MODE, &mode);//数据输入 模式0
    if (ret1 == -1)
        PRONEERS_ERROR("can't set wr spi mode");

    ret1 = ioctl(fd1, SPI_IOC_RD_MODE, &mode);//数据发送 模式0
    if (ret1 == -1)
        PRONEERS_ERROR("can't get spi mode");


    ret1 = ioctl(fd1, SPI_IOC_WR_BITS_PER_WORD, &bits);//设置每字长度8字节
    if (ret1 == -1)
        PRONEERS_ERROR("can't set bits per word");

    ret1 = ioctl(fd1, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret1 == -1)
        PRONEERS_ERROR("can't get bits per word");


    ret1 = ioctl(fd1, SPI_IOC_WR_MAX_SPEED_HZ, &speed);//输入命令
    if (ret1 == -1)
        PRONEERS_ERROR("can't set max speed hz");

    ret1 = ioctl(fd1, SPI_IOC_RD_MAX_SPEED_HZ, &speed);//输出命令
    if (ret1 == -1)
        PRONEERS_ERROR("can't get max speed hz");

    PRONEERS_LOG("spi mode: %d\n", mode);
    PRONEERS_LOG("bits per word: %d\n", bits);
    PRONEERS_LOG("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
    return fd1;
}
/*******************************************************************************
* 函数名称: function_dd_spi_write
* 函数功能: spi写
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* Len             int         in      写长度
* *SpiData       unsigned char* in    写入数据地址
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_spi_write(int Len, unsigned char* SpiData)
{

    int ret;
    struct spi_ioc_transfer tr_txrxw = {

            .tx_buf = (unsigned long)SpiData,
            .rx_buf = 0,
            .len = Len,
            .delay_usecs = DD_SPI_CTL_DELAY,
            .speed_hz = DD_SPI_CTL_SPEED,
            .bits_per_word = DD_SPI_CTL_BITS,
    };
    ret = ioctl(tFpgaSpiData.SpiData_fd_spi, SPI_IOC_MESSAGE(1), &tr_txrxw);
    return ret;

}
/*******************************************************************************
* 函数名称: function_dd_spi_read
* 函数功能: spi读
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* Len             int         in      读长度
* *SpiData       unsigned char* in    读入数据地址
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_spi_read(int Len ,unsigned char *SpiData)
{
    unsigned char tx[2] = {0};
    unsigned char rx[ARRAY_SIZE(tx)] = {0, };
    int ret;
    struct spi_ioc_transfer tr_txrx2 = {
            .tx_buf = 0,
            .rx_buf = (unsigned long)SpiData,
            .len = Len,
            .delay_usecs = DD_SPI_CTL_DELAY,
            .speed_hz = DD_SPI_CTL_SPEED,
            .bits_per_word = DD_SPI_CTL_BITS,
    };
    ret = ioctl(tFpgaSpiData.SpiData_fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx2);
    if (ret == 1) {
        printf("can't revieve spi message");
    }
    return ret;
}
/*******************************************************************************
* 函数名称: function_dd_fpga_write
* 函数功能: FPGA寄存器写
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* FpgaReg      unsigned char     in      写地址
* FpgaValue    unsigned int      in      写数据  
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_fpga_write(unsigned char FpgaReg, unsigned int FpgaValue)
{
    int ret = 0;
    unsigned char Data[2];
    
    Data[0] =(char) (0x81 + FpgaReg * 2);
    Data[1] = (char) (0x00ff & FpgaValue);
    ret = function_dd_spi_write(2, Data);
    
    Data[0] =(char) (0x82 + FpgaReg * 2);
    Data[1] = (char) (FpgaValue >> 8);
    ret |= function_dd_spi_write(2, Data);
    
    return ret;
}
/*******************************************************************************
* 函数名称: function_dd_fpga_writes
* 函数功能: FPGA寄存器写
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* FpgaReg      unsigned char     in      写地址
* FpgaValue    unsigned int      in      写数据  
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_fpga_writes(unsigned char FpgaReg, unsigned int FpgaValue)
{
    int ret = 0;
    unsigned char Data[2];
    
    Data[0] =(char) (0x81 + FpgaReg);
    Data[1] = (char) (0x00ff & FpgaValue);
    ret = function_dd_spi_write(2, Data);
    
    Data[0] =(char) (0x82 + FpgaReg);
    Data[1] = (char) (FpgaValue >> 8);
    ret |= function_dd_spi_write(2, Data);
    
    return ret;
}

/*******************************************************************************
* 函数名称: function_dd_fpga_set_init
* 函数功能: FPGA寄存器初始化
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* 
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
void function_dd_fpga_set_init(T_Fpga_Set *tFpga_Set)
{
    int a;
    a = tFpga_Set->Fpga_Set_PCH;
    a = a + 8192;

    (void)function_dd_fpga_write(0x09,tFpga_Set->Fpga_Set_TH);
    PRONEERS_LOG("th = %d\n",tFpga_Set->Fpga_Set_TH);

    (void)function_dd_fpga_write(0x00,tFpga_Set->Fpga_Set_BaseL);
    PRONEERS_LOG("Base Line = %d\n",tFpga_Set->Fpga_Set_BaseL);

    (void)function_dd_fpga_write(0x01,tFpga_Set->Fpga_Set_WINA1*2);
    (void)function_dd_fpga_write(0x02,tFpga_Set->Fpga_Set_WINA2*2);

    (void)function_dd_fpga_write(0x03,tFpga_Set->Fpga_Set_WINB1*2);
    (void)function_dd_fpga_write(0x04,tFpga_Set->Fpga_Set_WINB2*2);

    (void)function_dd_fpga_write(0x08,tFpga_Set->Fpga_Set_WINC1*2);
    (void)function_dd_fpga_write(0x0e,tFpga_Set->Fpga_Set_WINC2*2);

    (void)function_dd_fpga_writes(0x1f,tFpga_Set->Fpga_Set_WIND1*2);
    (void)function_dd_fpga_writes(0x21,tFpga_Set->Fpga_Set_WIND2*2);

    (void)function_dd_fpga_writes(0x23,tFpga_Set->Fpga_Set_WINE1*2);
    (void)function_dd_fpga_writes(0x25,tFpga_Set->Fpga_Set_WINE2*2);

    a = tFpga_Set->Fpga_Set_ST;//pt->st;
    (void)function_dd_fpga_write(0x05,5);

    a = tFpga_Set->Fpga_Set_CT;//pt->ct;
    (void)function_dd_fpga_write(0x07,30000);

    a = tFpga_Set->Fpga_Set_P_th;//pt->pulse_thr;
    (void)function_dd_fpga_write(0x0d,tFpga_Set->Fpga_Set_P_th);


    a = tFpga_Set->Fpga_Set_P_min;//pt->pulse_min;
    (void)function_dd_fpga_write(0x0b,tFpga_Set->Fpga_Set_P_min);

    a = tFpga_Set->Fpga_Set_P_max;//pt->pulse_max;
    (void)function_dd_fpga_write(0x0c,tFpga_Set->Fpga_Set_P_max);
}

/*******************************************************************************
* 函数名称: function_dd_fpga_read
* 函数功能: 回读FPGA数据
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
*  FpgaReg     unsigned char    in        寄存器地址
*  FpgaData    unsigned char   out        回读的数据
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_fpga_read(unsigned char FpgaReg, unsigned char *FpgaData)
{
    int ret = 0;
    unsigned char TxData[2];
    unsigned char RxData[2];

    TxData[0] = FpgaReg;
    TxData[1] = 0x00;

    ret = function_dd_spi_write(2, TxData);
    ret = function_dd_spi_read(2, RxData);
    FpgaData[0] = RxData[0];
    FpgaData[1] = RxData[1];
    return ret;
}


