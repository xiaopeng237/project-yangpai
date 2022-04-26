//
// Created by Administrator on 2020/7/6.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <poll.h>
#include <sys/time.h>
#include <signal.h>
#define I2C_SLAVE_FORCE	0x0706
#define I2C_2631_A	0x20
#define I2C_2631_B 0x24

int main(int argc, char **argv)
{
    int GiFd2631 = open("/dev/i2c-1",O_RDWR);//在fcntl的头文件里
    unsigned int uiRet;
    unsigned char tx_buf[4];
    int hv;
    int vbb;

    if(GiFd2631 == -1)
        printf("open i2c-1\n");

    hv = atof(argv[1]);

    if(hv>3500){
        printf("数值过大\n");
    }



    uiRet = ioctl(GiFd2631, I2C_SLAVE_FORCE, I2C_2631_A >> 1);
    if (uiRet < 0) {
        printf("setenv address faile ret: %x \n", uiRet);
        return 0;
    }
    tx_buf[0]=0x30;
    tx_buf[1]=(unsigned char) (hv>>4);
    tx_buf[2]=(unsigned char) ((0x000f & hv)<<4);

    uiRet = write(GiFd2631, tx_buf, 3); //写数据

    printf("%.2x,%.2x %d\n",tx_buf[1],tx_buf[2],uiRet);
    return 0;
}