//
// Created by Administrator on 2020/3/26.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2cbus_module_base.h"
#include "log_dlt.h"
#include "i2c_ad1115.h"
#include "i2cbus_base.h"

extern T_I2cAdjust tI2CAdjust;
extern T_I2cOled   tI2COled;
extern T_I2cAd1115 tI2CAd1115;
extern unsigned short modbusdata[5];
int i2c_1115_init(void)
{
    unsigned int uiRet;
    unsigned char tx_buf[4];
//    unsigned char rx_buf[4];
    int res = 0;
    uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_B >> 1);
    if (uiRet < 0) {
        I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
        return -1;
    }
    tx_buf[0]=0x01;
    tx_buf[1]=0xB0;
    tx_buf[2]=0xe3;
    res = write(GiFd, tx_buf, 3); //写数据
    tx_buf[0]=0x00;
    res = write(GiFd,tx_buf,1);

    uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_C >> 1);
    if (uiRet < 0) {
        I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
        return -1;
    }
    tx_buf[0]=0x01;

    tx_buf[1]=0xB0;
    tx_buf[2]=0xe3;
    res = write(GiFd, tx_buf, 3); //写数据
    tx_buf[0]=0x00;
    res = write(GiFd,tx_buf,1);

    return 0;
}

extern T_I2cAd1115 tI2CAd1115;
extern float i2cAd1115_P;
extern float i2cAd1115_DP;
extern float i2cAd1115_PTem;
void i2c_1115_P(void)
{
    int uiRet = 0;
    unsigned char tx_buf[4];
    unsigned char rx_buf[4];

    uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_B >> 1);
    if (uiRet < 0) {
        I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
        return;
    }


    uiRet = read(GiFd, rx_buf, 2);

    if(rx_buf[0]<128)
    {
        i2cAd1115_P = ((float)rx_buf[0]*256+rx_buf[1])*6.144/32767.0;
    }
    else if(rx_buf[0]>=128)
    {
        i2cAd1115_P = (((float)(rx_buf[0]-128)*256+rx_buf[1])*6.144/32767.0)-6.144;
    }

    static int i = 0;
    if(i < 100)
        I2CBUS_LOG("rx_buf[0]=%x rx_buf[1]=%x i2cAd1115_P=%f",rx_buf[0],rx_buf[1],i2cAd1115_P);
    else
        i = 0;

    i++;
}
void i2c_1115_DP(void)
{
    int uiRet = 0;
    unsigned char tx_buf[4];
    unsigned char rx_buf[4];

    uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_C >> 1);
    if (uiRet < 0) {
        I2CBUS_ERROR("setenv address faile ret:%x \n", uiRet);
        return ;
    }

    uiRet = read(GiFd, rx_buf, 2);

    if (rx_buf[0] < 128) {
        i2cAd1115_DP = ((float) rx_buf[0] * 256 + rx_buf[1]) * 6.144 / 32767.0;
    } else if (rx_buf[0] >= 128) {

        i2cAd1115_DP = (((float) (rx_buf[0] - 128) * 256 + rx_buf[1]) * 6.144 / 32767.0) - 6.144;
    }
}
void i2c_1115_Ptem(int *flag_index)
{
    int uiRet = 0;
    unsigned char tx_buf[4];
    unsigned char rx_buf[4];
    static int flag_Ptem = 0;

    float R1	=	10000;
    float R2	=	1000;
    float V0	=	5;

    flag_Ptem++;

    if(flag_Ptem == 1)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_Ptem = 0;
            *flag_index = 1;
            return ;
        }
        tx_buf[0]=0x01;
        tx_buf[1]=I2C_MUX_1;
        tx_buf[2]=I2C_RATE;
        uiRet = write(GiFd, tx_buf, 3); //写数据
    }
    else if(flag_Ptem == 2)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_Ptem = 0;
            *flag_index = 1;
            return;
        }
        tx_buf[0]=0x00;
        uiRet = write(GiFd,tx_buf,1);
    }
    else if(flag_Ptem >= 3)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_Ptem = 0;
            *flag_index = 1;
            return;
        }
        uiRet = read(GiFd, rx_buf, 2);

        if(rx_buf[0]<128)
        {
            i2cAd1115_PTem = ((float)rx_buf[0]*256+rx_buf[1])*0.256/32767.0;
        }
        else if(rx_buf[0]>=128)
        {
            i2cAd1115_PTem = (((float)(rx_buf[0]-128)*256+rx_buf[1])*0.256/32767.0)-0.256;
        }

        i2cAd1115_PTem = (0.258137*(((i2cAd1115_PTem*(R1*(R1+R2)))+(V0*R1*R2))/((V0-i2cAd1115_PTem)*(R1+R2)-(V0*R2))))-257.990783;
        flag_Ptem = 0;
        *flag_index = 1;
    }

}
void i2c_1115_DPtem(int *flag_index)
{
    int uiRet = 0;
    unsigned char tx_buf[4];
    unsigned char rx_buf[4];
    static int flag_DPtem = 0;

    float R1	=	10000;
    float R2	=	1000;
    float V0	=	5;

    flag_DPtem++;

    if(flag_DPtem == 1)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_DPtem = 0;
            *flag_index = 2;
            return ;
        }
        tx_buf[0]=0x01;
        tx_buf[1]=I2C_MUX_2;
        tx_buf[2]=I2C_RATE;
        uiRet = write(GiFd, tx_buf, 3); //写数据
    }
    else if(flag_DPtem == 2)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_DPtem = 0;
            *flag_index = 2;
            return;
        }
        tx_buf[0]=0x00;
        uiRet = write(GiFd,tx_buf,1);
    }
    else if(flag_DPtem == 3)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_DPtem = 0;
            *flag_index = 2;
            return ;
        }
        uiRet = read(GiFd, rx_buf, 2);

        modbusdata[2]=rx_buf[0];
        modbusdata[3]=rx_buf[1];

        if(rx_buf[0]<128)
        {
            tI2CAd1115.i2cAd1115_DPTem = ((float)rx_buf[0]*256+rx_buf[1])*0.256/32767.0;
        }
        else if(rx_buf[0]>=128)
        {
            tI2CAd1115.i2cAd1115_DPTem = (((float)(rx_buf[0]-128)*256+rx_buf[1])*0.256/32767.0)-0.256;
        }
        tI2CAd1115.i2cAd1115_DPTem = (0.258137*(((tI2CAd1115.i2cAd1115_DPTem*(R1*(R1+R2)))+(V0*R1*R2))/((V0-tI2CAd1115.i2cAd1115_DPTem)*(R1+R2)-(V0*R2))))-257.990783;

        flag_DPtem = 0;
        *flag_index = 2;

    }


}
void i2c_1115_Boardtem(int *flag_index)
{
    int uiRet = 0;
    unsigned char tx_buf[4];
    unsigned char rx_buf[4];
    static int flag_Boardtem = 0;

    float R1	=	10000;
    float R2	=	1000;
    float V0	=	5;

    flag_Boardtem++;

    if(flag_Boardtem == 1)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_Boardtem = 0;
            *flag_index = 0;
            return ;
        }
        tx_buf[0]=0x01;
        tx_buf[1]=I2C_MUX_3;
        tx_buf[2]=I2C_RATE;
        uiRet = write(GiFd, tx_buf, 3); //写数据
    }
    else if(flag_Boardtem == 2)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_Boardtem = 0;
            *flag_index = 0;
            return ;
        }
        tx_buf[0]=0x00;
        uiRet = write(GiFd,tx_buf,1);
    }
    else if(flag_Boardtem == 3)
    {
        uiRet = ioctl(GiFd, I2C_SLAVE_FORCE, I2C_1115_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            flag_Boardtem = 0;
            *flag_index = 0;
            return ;
        }
        uiRet = read(GiFd, rx_buf, 2);

        modbusdata[0]=rx_buf[0];
        modbusdata[1]=rx_buf[1];

        if(rx_buf[0]<128)
        {
            tI2CAd1115.i2cAd1115_BoardTem = ((float)rx_buf[0]*256+rx_buf[1])*0.256/32767.0;
        }
        else if(rx_buf[0]>128)
        {
            tI2CAd1115.i2cAd1115_BoardTem = (((float)(rx_buf[0]-128)*256+rx_buf[1])*0.256/32767.0)-0.256;
        }

        I2CBUS_LOG("tI2CAd1115.i2cAd1115_BoardTem: %f \n", tI2CAd1115.i2cAd1115_BoardTem );
        tI2CAd1115.i2cAd1115_BoardTem = (0.258137*(((tI2CAd1115.i2cAd1115_BoardTem*(R1*(R1+R2)))+(V0*R1*R2))/((V0-tI2CAd1115.i2cAd1115_BoardTem)*(R1+R2)-(V0*R2))))-257.990783;
        flag_Boardtem = 0;
        *flag_index = 0;

    }

}

void i2c_1115_temp()
{

    static int flag_index = 0;

    if(flag_index == 0)
    {
        i2c_1115_Ptem(&flag_index);
    }
    else if(flag_index == 1)
    {
        i2c_1115_DPtem(&flag_index);
    }
    if(flag_index >= 2)
    {
        i2c_1115_Boardtem(&flag_index);
    }
}