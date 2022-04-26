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
#include <pthread.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2cbus_module_base.h"
#include "log_dlt.h"

#include "i2cbus_base.h"


#include "i2c_adjust.h"

extern pthread_mutex_t adjust_mutex;
extern T_I2cAdjust tI2CAdjust;

void i2c_adjust_write()
{
    T_I2cAdjust tI2CAdjust_tmp;
    pthread_mutex_lock(&adjust_mutex);
    memcpy(&tI2CAdjust_tmp,&tI2CAdjust,sizeof(tI2CAdjust));
    pthread_mutex_unlock(&adjust_mutex);

    unsigned int uiRet;
    unsigned char tx_buf[4];

    int hv;
    int vbb;
    static int count_HIVf = 0;
    static int count_VBBf = 0;

    I2CBUS_LOG("voltage_adjust %d %d %d %d\n",tI2CAdjust_tmp.i2cAdjust_Hight_Vf,tI2CAdjust_tmp.i2cAdjust_Bias_Vf,count_HIVf,count_VBBf);
    int res = 0;
    if(tI2CAdjust_tmp.i2cAdjust_Hight_Vf==1 && count_HIVf == 0)
    {
        count_HIVf = 0;
        tI2CAdjust_tmp.i2cAdjust_Hight_Vf=0;
        hv=tI2CAdjust_tmp.i2cAdjust_Hight;

        if(hv>3500){
            I2CBUS_ERROR("数值过大\n");
            hv=0;
        }

        I2CBUS_LOG("tp_Adjust_->S_HIV %d\n",hv);

        uiRet = ioctl(GiFd2631, I2C_SLAVE_FORCE, I2C_2631_A >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            return;
        }
        tx_buf[0]=0x30;
        tx_buf[1]=(unsigned char) (hv>>4);
        tx_buf[2]=(unsigned char) ((0x000f & hv)<<4);
        I2CBUS_LOG("%.2x,%.2x\n",tx_buf[1],tx_buf[2]);
        res = write(GiFd2631, tx_buf, 3); //写数据
    }

    if(tI2CAdjust_tmp.i2cAdjust_Bias_Vf==1 && count_VBBf == 0)
    {
        count_VBBf = 0;
        tI2CAdjust_tmp.i2cAdjust_Bias_Vf=0;
        vbb=tI2CAdjust_tmp.i2cAdjust_Bias;

        if(vbb>1500)
        {
            I2CBUS_ERROR("数值过大\n");
            vbb=1100;
        }
        uiRet = ioctl(GiFd2631, I2C_SLAVE_FORCE, I2C_2631_B >> 1);
        if (uiRet < 0) {
            I2CBUS_ERROR("setenv address faile ret: %x \n", uiRet);
            return;
        }
        tx_buf[0]=0x30;
        tx_buf[1]=(unsigned char) (vbb>>4);
        tx_buf[2]=(unsigned char) ((0x000f & vbb)<<4);
        I2CBUS_LOG("%.2x,%.2x\n",tx_buf[1],tx_buf[2]);
        res = write(GiFd2631, tx_buf, 3); //写数据
    }

    if(count_HIVf != 0)
        count_HIVf--;
    if(count_VBBf != 0)
        count_VBBf--;
}