//
// Created by Administrator on 2020/3/26.
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
#include "yangpai_service.h"
#include "i2c_bus.h"
#include "log_dlt.h"
#include "i2cbus_module_base.h"
#include "i2c_oled.h"
#include "i2c_ad1115.h"
#include "i2c_adjust.h"

pthread_t select_thread;
pthread_attr_t select_attribute;
pthread_mutex_t select_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  select_cond = PTHREAD_COND_INITIALIZER;

pthread_t s1_thread;
pthread_attr_t s1_attribute;
pthread_mutex_t s1_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  s1_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t oled_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t adjust_mutex = PTHREAD_MUTEX_INITIALIZER;

int GiFd;
int GiFd2631;
T_I2cAdjust tI2CAdjust;
T_I2cOled   tI2COled;
T_I2cAd1115 tI2CAd1115;

int flag_adjust = 0;
int flag_oled = 0;
int flag_ustime = 0;
int flag2s_tick = 0;
static int msTime = 0;

extern HStub STUB_yangpi_i2c;

float i2cAd1115_P;
float i2cAd1115_DP;
float i2cAd1115_PTem;
unsigned short modbusdata[5];
void data_operation()
{
    static int count_200 = 0;
    static char fist_run_flag = 0;
    int i = 0;
    tI2CAd1115.ad1115_buf[199][0] = i2cAd1115_PTem;
    tI2CAd1115.ad1115_buf[199][1] = i2cAd1115_P;
    tI2CAd1115.ad1115_buf[199][2] = i2cAd1115_DP;

    for(i=0;i<199;i++)
    {
        tI2CAd1115.ad1115_buf[i][0] = tI2CAd1115.ad1115_buf[i+1][0];
        tI2CAd1115.ad1115_buf[i][1] = tI2CAd1115.ad1115_buf[i+1][1];
        tI2CAd1115.ad1115_buf[i][2] = tI2CAd1115.ad1115_buf[i+1][2];
    }

    count_200++;
    if(count_200 >= 20)
    {
        if(fist_run_flag < 5)
        {
            fist_run_flag++;
            count_200 = 0;
            return;
        }
        else
        {
            fist_run_flag = 10;
        }
        yangpi_i2c_signal_i2c_ad1115(STUB_yangpi_i2c,&tI2CAd1115);
        count_200 = 0;
        I2CBUS_LOG("i2cbus data send \n");
    }


}

void *select_thread_function(void* a)
{
    for(;;) {
        pthread_mutex_lock(&select_mutex);
        while (0 == flag2s_tick) {
            pthread_cond_wait(&select_cond, &select_mutex);
        }
        flag2s_tick = 0;
        pthread_mutex_unlock(&select_mutex);


        if (msTime%207 == 0) {
            i2c_1115_temp();
            I2CBUS_LOG("i2cbus 温度获取 \n");
        }

        if (flag_oled == 1 && msTime%2003 == 0) {
            i2c_oled_write();
            flag_oled = 0;
            I2CBUS_LOG("i2cbus oled写入 \n");
        }

        if (flag_adjust == 1 && msTime%509 == 0) {
            i2c_adjust_write();
            flag_adjust = 0;
            I2CBUS_LOG("i2cbus 调压写入 \n");
        }

        if (msTime >= 60000)
            msTime = 0;

    }

}
void *s1_thread_function(void* a)
{
    int gpio_fd;
    int ret;
    char buff[10];
    struct pollfd fds[1];

    gpio_export(53);
    gpio_direction(53, 0);
    gpio_edge(53,1);
    gpio_fd = open("/sys/class/gpio/gpio53/value",O_RDONLY);
    if(gpio_fd < 0){
        I2CBUS_ERROR("Failed to open value!\n");
    }
    fds[0].fd = gpio_fd;
    fds[0].events  = POLLPRI;
    ret = read(gpio_fd,buff,10);
    if( ret == -1 )
        I2CBUS_ERROR("read\n");

    for(;;)
    {
        ret = poll(fds,1,0);
        if( ret == -1 )
            I2CBUS_ERROR("poll\n");
        if( fds[0].revents & POLLPRI) {
            ret = lseek(gpio_fd, 0, SEEK_SET);
            if (ret == -1)
                I2CBUS_ERROR("lseek\n");
            ret = read(gpio_fd, buff, 10);
            if (ret == -1)
                I2CBUS_ERROR("read\n");

            msTime++;

            if (msTime%10 == 0) {
                i2c_1115_P();
                i2c_1115_DP();

                data_operation();
            }

            flag2s_tick = 1;
            pthread_cond_signal(&select_cond);
        }

    }
}

void i2cbus_idle()
{


}


void i2c_adjust_handle(HStub stub, T_I2cAdjust *zdb_T_I2cAdjust)
{
    pthread_mutex_lock(&adjust_mutex);
    memcpy(&tI2CAdjust,zdb_T_I2cAdjust,sizeof(tI2CAdjust));
    pthread_mutex_unlock(&adjust_mutex);
    flag_adjust = 1;
    I2CBUS_ERROR("i2c_adjust_handle %d %d %d %d\n",tI2CAdjust.i2cAdjust_Hight_Vf,tI2CAdjust.i2cAdjust_Hight,tI2CAdjust.i2cAdjust_Bias_Vf,tI2CAdjust.i2cAdjust_Bias);

}
void i2c_oled_handle(HStub stub, T_I2cOled *zdb_T_I2cOled)
{
    pthread_mutex_lock(&oled_mutex);
    memcpy(&tI2COled,zdb_T_I2cOled,sizeof(T_I2cOled));
    pthread_mutex_unlock(&oled_mutex);
    flag_oled = 1;

}

void init_stub_yangpi_i2c(tInterfaceStub_yangpi_i2c *stub)
{
    stub->i2c_adjust = i2c_adjust_handle;
    stub->i2c_oled = i2c_oled_handle;
}


extern void main_start()
{
    GiFd = open("/dev/i2c-2",O_RDWR);//在fcntl的头文件里
    if(GiFd == -1)
        I2CBUS_ERROR("open i2c-2\n");

    GiFd2631 = open("/dev/i2c-1",O_RDWR);//在fcntl的头文件里
    if(GiFd2631 == -1)
        I2CBUS_ERROR("open i2c-1\n");

    i2c_oled_init();
    i2c_1115_init();
//
//    struct itimerval tv, otv;
//    signal(SIGALRM, i2cbus_idle);
//    //how long to run the first time
//    tv.it_value.tv_sec = 0;
//    tv.it_value.tv_usec = 500;
//    //after the first time, how long to run next time
//    tv.it_interval.tv_sec = 0;
//    tv.it_interval.tv_usec = 500;
//
//    if (setitimer(ITIMER_REAL, &tv, &otv) != 0)
//        I2CBUS_ERROR("setitimer err");

    pthread_attr_init(&s1_attribute);
    pthread_attr_setdetachstate(&s1_attribute, PTHREAD_CREATE_DETACHED);
    pthread_create(&s1_thread, &s1_attribute, s1_thread_function, NULL);

    pthread_attr_init(&select_attribute);
    pthread_attr_setdetachstate(&select_attribute, PTHREAD_CREATE_DETACHED);
    pthread_create(&select_thread, &select_attribute, select_thread_function, NULL);

}