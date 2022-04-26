//
// Created by Administrator on 2020/3/30.
//
#include <string.h>
#include <linux/watchdog.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <dlfcn.h>
#include <poll.h>
#include <mysql_base.h>

#include "pioneers.h"
#include "log_dlt.h"
#include "yangpi_pioneers_stub.h"
#include "yangpi_mysql_proxy.h"
#include "yangpi_i2c_proxy.h"
#include "yangpi_adjust_proxy.h"
#include "pioneers_spi.h"
#include "pioneers_service.h"
#include "yangpi_ota_proxy.h"
#include "yangpi_rtu_proxy.h"

T_Arm_Mysql tArm_Mysql;
T_Fpga_Set tFpga_Set;
T_Flow_para tFlow_para;
T_Write_ES tWriteEs;

T_I2cAd1115 tI2cAd1115;
T_I2cAdjust tI2cAdjust;

T_AdjustOut tAdjustOut;
T_AdjustIn tAdjustIn;

T_CalculatePara FlowParass;
T_Calculatepara_result FlowParasult;
T_RunFlag tRunFlag;

extern HStub STUB_yangpi_pioneers;
extern HProxy PROXY_yangpi_mysql;
extern HProxy PROXY_yangpi_i2c;
extern HProxy PROXY_yangpi_adjust;

pthread_t thread1;
pthread_attr_t attribute1;

pthread_t thread_1s;
pthread_attr_t attribute_1s;
pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t s_cond = PTHREAD_COND_INITIALIZER;

pthread_t thread_init;
pthread_attr_t attribute_init;
pthread_mutex_t init_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t init_cond = PTHREAD_COND_INITIALIZER;


pthread_t thread_run;
pthread_attr_t attribute_run;
pthread_mutex_t run_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t run_cond = PTHREAD_COND_INITIALIZER;

pthread_t thread_storage;
pthread_attr_t attribute_storage;
pthread_mutex_t storage_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t storage_cond = PTHREAD_COND_INITIALIZER;

pthread_t thread_esadjust;
pthread_attr_t attribute_esadjust;
pthread_mutex_t esadjust_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t esadjust_cond = PTHREAD_COND_INITIALIZER;

int flag2s_tick = 0;
int flagi2c_data_ready = 0;
int flag1S_data_ready = 0;
int flagca_data_ready = 0;
int flages_data_ready = 0;
int fd_dog;

double calculate_a1;
double calculate_b1;

void
mysql_incept_all(HProxy proxy, T_Arm_Mysql *zdb_T_Arm_Mysql, T_Fpga_Set *zdb_T_Fpga_Set, T_Flow_para *zdb_T_Flow_para) {
    memcpy(&tArm_Mysql, zdb_T_Arm_Mysql, sizeof(T_Arm_Mysql));
    memcpy(&tFpga_Set, zdb_T_Fpga_Set, sizeof(T_Fpga_Set));
    memcpy(&tFlow_para, zdb_T_Flow_para, sizeof(T_Flow_para));

    tRunFlag.flag_modbus_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x01;
    tRunFlag.flag_log_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x02;
    tRunFlag.flag_es_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x04;
    tRunFlag.flag_hightV_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x08;//改为是否自动调压 8为自动调整；
    tRunFlag.flag_5ms_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x10;
    tRunFlag.flag_win_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x20;
    tRunFlag.flag_dog_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x40;
    tRunFlag.flag_oled_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x80;
    tRunFlag.flag_1s_en = tArm_Mysql.t_Arm_Set.Arm_Set_flag & 0x100;

    FlowParass.Add_Sctime       =(double)tFlow_para.t_Flow_Result.Sctime;

    calculate_a1 = (tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_C - tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_B) / (81.0 - 31.0);//17.36
    calculate_b1 = tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_B - 31 * calculate_a1;//-6.18



    PRONEERS_LOG("\n mysql_incept_all %d %d  %d %d %f %f \n", tFpga_Set.Fpga_Set_WINB1, tFpga_Set.Fpga_Set_WINB2,
                 tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_C, tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_B,calculate_a1,calculate_b1);
}

void i2c_ad1115(HProxy proxy, T_I2cAd1115 *zdb_T_I2cAd1115) {
    memcpy(&tI2cAd1115, zdb_T_I2cAd1115, sizeof(T_I2cAd1115));
    flagi2c_data_ready = 1;
    pthread_cond_signal(&run_cond);
    PRONEERS_LOG("tI2cAd1115 绝压：%f 差压%f  \n", tI2cAd1115.ad1115_buf[0][1], tI2cAd1115.ad1115_buf[0][2]);
}

void adjust_result(HProxy proxy, T_AdjustOut *zdb_T_AdjustOut) {
    memcpy(&tAdjustOut, zdb_T_AdjustOut, sizeof(T_AdjustOut));
    PRONEERS_LOG("adjust_result %d %d \n", tAdjustOut.AdjustOut_Hight, tAdjustOut.AdjustOut_F31);
}

void init_stub_yangpi_pioneers(tInterfaceStub_yangpi_pioneers *stub) {

}

void init_client_yangpi_mysql(tInterfaceClient_yangpi_mysql *client) {
    client->on_signal_incept_all = mysql_incept_all;
}

void init_client_yangpi_i2c(tInterfaceClient_yangpi_i2c *client) {
    client->on_signal_i2c_ad1115 = i2c_ad1115;
}

void init_client_yangpi_adjust(tInterfaceClient_yangpi_adjust *client) {
    client->on_signal_adjust_result = adjust_result;
}

void init_client_yangpi_ota(tInterfaceClient_yangpi_ota *client) {

}
/*******************************************************************************
* 函数名称:esadjust_function
* 函数功能:能谱主函数：1.调窗 2.调压 3.能谱存储
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
void *esadjust_function(void *a) {
    T_DateTime DataTime;
    
    for (;;) {
        pthread_mutex_lock(&esadjust_mutex);
        while (0 == flages_data_ready) {
            pthread_cond_wait(&esadjust_cond, &esadjust_mutex);
        }
        flages_data_ready = 0;
        pthread_mutex_unlock(&esadjust_mutex);
        errorCode();
        tAdjustIn.AdjustIn_th_sum = tArm_Mysql.t_Arm_Set.Arm_Set_th_sum;
        tAdjustIn.AdjustIn_WIN_en = tRunFlag.flag_win_en;
        tAdjustIn.AdjustIn_HIV_en = tRunFlag.flag_hightV_en;
        tAdjustIn.AdjustIn_Hight_C = tArm_Mysql.t_Arm_Set.Arm_Set_hv_c;
        tAdjustIn.AdjustIn_Hight = tArm_Mysql.t_Arm_Set.Arm_Set_hv;
        tAdjustIn.AdjustIn_PCH31 = tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_B;
        tAdjustIn.AdjustIn_PCH81 = tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_C;
        tAdjustIn.AdjustIn_PCH356 = tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_E;
        tAdjustIn.AdjustIn_CON_B1 = tArm_Mysql.t_Arm_Set.Arm_Set_CON_B1;
        tAdjustIn.AdjustIn_CON_B2 = tArm_Mysql.t_Arm_Set.Arm_Set_CON_B2;
        tAdjustIn.AdjustIn_CON_C1 = tArm_Mysql.t_Arm_Set.Arm_Set_CON_C1;
        tAdjustIn.AdjustIn_CON_C2 = tArm_Mysql.t_Arm_Set.Arm_Set_CON_C2;
        tAdjustIn.AdjustIn_CON_E1 = tArm_Mysql.t_Arm_Set.Arm_Set_CON_E1;
        tAdjustIn.AdjustIn_CON_E2 = tArm_Mysql.t_Arm_Set.Arm_Set_CON_E2;
        tAdjustIn.AdjustIn_reality_b1 = tArm_Mysql.t_Arm_Set.Arm_set_reality_b1;
        tAdjustIn.AdjustIn_reality_b2 = tArm_Mysql.t_Arm_Set.Arm_set_reality_b2;
        tAdjustIn.AdjustIn_reality_e1 = tArm_Mysql.t_Arm_Set.Arm_set_reality_e1;
        tAdjustIn.AdjustIn_reality_e2 = tArm_Mysql.t_Arm_Set.Arm_set_reality_e2;


        function_dd_get_sw_time(&DataTime);
        tWriteEs.write_log_year           = DataTime.year;
        tWriteEs.write_log_month          = DataTime.month;
        tWriteEs.write_log_date           = DataTime.day;
        tWriteEs.write_log_hour           = DataTime.hour;
        tWriteEs.write_log_minute         = DataTime.minute;


        yangpi_adjust_call_adjust_start(PROXY_yangpi_adjust, &tAdjustIn);
        spectral_data_w();
        if(tRunFlag.flag_es_en != 0)
            yangpi_mysql_call_writeES(PROXY_yangpi_mysql, &tWriteEs);

        PRONEERS_LOG("能谱线程--执行完成 %d",tRunFlag.flag_es_en);
    }
}
/*******************************************************************************
* 函数名称:storage_function
* 函数功能:相关数据对外输出主函数
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
void *storage_function(void *a) {
    for (;;) {
        pthread_mutex_lock(&storage_mutex);
        while (0 == flagca_data_ready) {
            pthread_cond_wait(&storage_cond, &storage_mutex);
        }
        flagca_data_ready = 0;
        pthread_mutex_unlock(&storage_mutex);

        calculate_apache_armp();
        pulse_data_w();
        write_msql_apache();
        PRONEERS_LOG("存储线程--执行完成\n");
    }

}

struct timeval start, end, end2;
/*******************************************************************************
* 函数名称: run_function
* 函数功能: 等待能量窗数据、温度、压力、绝压原始数据准备好，进行流量计算
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
void *run_function(void *a) {
    for (;;) {
        pthread_mutex_lock(&run_mutex);
        while (0 == flagi2c_data_ready || 0 == flag1S_data_ready) {
            pthread_cond_wait(&run_cond, &run_mutex);
        }
        flagi2c_data_ready = 0;
        flag1S_data_ready = 0;
        pthread_mutex_unlock(&run_mutex);


        int i = 0;
        double tmp = 0;

        /*将5ms 绝压 差压 温度数据进行修正 （此处可以用一个函数实现）*/
        for (i = 0; i < 200; i++) {
            tmp = tI2cAd1115.ad1115_buf[i][0];
            tI2cAd1115.ad1115_buf[i][0] =
                    tmp * tArm_Mysql.t_Arm_Ad1115.Ad1115_PreT_a + tArm_Mysql.t_Arm_Ad1115.Ad1115_PreT_b;// pt

            tmp = tI2cAd1115.ad1115_buf[i][1];
            tI2cAd1115.ad1115_buf[i][1] =
                    tmp * tArm_Mysql.t_Arm_Ad1115.Ad1115_Pre_a + tArm_Mysql.t_Arm_Ad1115.Ad1115_Pre_b;// p

            tmp = tI2cAd1115.ad1115_buf[i][2];
            tI2cAd1115.ad1115_buf[i][2] =
                    tmp * tArm_Mysql.t_Arm_Ad1115.Ad1115_DP_a + tArm_Mysql.t_Arm_Ad1115.Ad1115_DP_b;// dp
        }
        gettimeofday(&end, NULL);
        double total_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("run_work time1 %f \n", total_time / 1000);


        calculate_flow();
        flagca_data_ready = 1;
        pthread_cond_signal(&storage_cond);



        gettimeofday(&end2, NULL);
        double total_time2 = (end2.tv_sec - end.tv_sec) * 1000000 + (end2.tv_usec - end.tv_usec);
        printf("run_work time2 %f \n", total_time2 / 1000);

        PRONEERS_LOG("计算线程--执行完成");

    }

}
/*******************************************************************************
* 函数名称: run_work
* 函数功能: 1s 定时负责数据同步
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
void *run_work(void *a) {

    int gpio_fd;
    int ret;
    char buff[10];
    struct pollfd fds[1];
    int i = 0;
    T_DateTime DataTime;
    
    function_dd_get_sw_time(&DataTime);
    gpio_export(53);
    gpio_direction(53, 0);
    gpio_edge(53, 1);
    gpio_fd = open("/sys/class/gpio/gpio53/value", O_RDONLY);
    if (gpio_fd < 0) {
        PRONEERS_ERROR("Failed to open value!\n");
    }
    fds[0].fd = gpio_fd;
    fds[0].events = POLLPRI;
    ret = read(gpio_fd, buff, 10);
    if (ret == -1)
        PRONEERS_ERROR("read\n");

    static int time_count = 0;
    while (time_count == 0) {
        readtime();
        if ((DataTime.second > 20 || DataTime.second < 40) && flagi2c_data_ready == 1)
            time_count = 1;
        usleep(500);
    }

    for (;;) {
        ret = poll(fds, 1, 0);
        if (ret == -1)
            PRONEERS_ERROR("poll\n");
        if (fds[0].revents & POLLPRI) {
            ret = lseek(gpio_fd, 0, SEEK_SET);
            if (ret == -1)
                PRONEERS_ERROR("lseek\n");
            ret = read(gpio_fd, buff, 10);
            if (ret == -1)
                PRONEERS_ERROR("read\n");
            if (i >= 199) {
                i = 0;
                flag2s_tick = 1;
                pthread_cond_signal(&s_cond);
            } else {
                i++;
            }

        }
    }


}
/*******************************************************************************
* 函数名称: timer_mysql
* 函数功能: 1s定时主函数
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
void *timer_mysql(void *a) {
    T_DateTime DataTime;

    for (;;) {
        pthread_mutex_lock(&s_mutex);
        while (0 == flag2s_tick) {
            pthread_cond_wait(&s_cond, &s_mutex);
        }
        flag2s_tick = 0;
        pthread_mutex_unlock(&s_mutex);

        /*获取系统时间*/
        readtime();
        gettimeofday(&start, NULL);
        /*获取能量窗数据*/
        get_spi_win();
        flag1S_data_ready = 1;
        /*使用信号量保证数据同步*/
        pthread_cond_signal(&run_cond);//计算要考虑i2c数据时效性，所以采用条件变量。保证spi和i2c数据是1S前的

        //todo: 存储
        /*获取脉冲数据*/
        get_spi_pull();
        /*获取能谱数据*/
        get_spi_energy();

        if (tAdjustOut.AdjustOut_WIN_J == 1) {
            tAdjustOut.AdjustOut_WIN_J = 0;
            /*调窗*/
            adjust_win();
        }


        if (tRunFlag.flag_dog_en != 0) {
            int dummy;
            ioctl(fd_dog, WDIOC_KEEPALIVE, &dummy);
            PRONEERS_LOG("flag_dog end\n");
        }
        function_dd_get_sw_time(&DataTime);
        PRONEERS_LOG("===== 1S定时执行 flag1S_data_ready= %d %d:%d=====\n", flag1S_data_ready, DataTime.minute,
                     DataTime.second);

    }
}
/*******************************************************************************
* 函数名称: start_work
* 函数功能: 获取窗口计数数据
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
void start_work() {
//    struct itimerval tv, otv;
//    signal(SIGALRM, timer_mysql);
//    //how long to run the first time
//    tv.it_value.tv_sec = 1;
//    tv.it_value.tv_usec = 0;
//    //after the first time, how long to run next time
//    tv.it_interval.tv_sec = 1;
//    tv.it_interval.tv_usec = 0;
//
//    if (setitimer(ITIMER_REAL, &tv, &otv) != 0)
//        PRONEERS_ERROR("setitimer err\n");

    /*1s 主循环*/
    pthread_attr_init(&attribute_1s);
    pthread_attr_setdetachstate(&attribute_1s, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_1s, &attribute_1s, timer_mysql, NULL);

    /*1s 定时器*/
    pthread_attr_init(&attribute_init);
    pthread_attr_setdetachstate(&attribute_init, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_init, &attribute_init, run_work, NULL);

}
/*******************************************************************************
* 函数名称: init_function
* 函数功能: 主程序任务初始化
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
void *init_function(void *a) {
    int res;
    //发送接收数据请求
    yangpi_mysql_call_request_all(PROXY_yangpi_mysql);
    sleep(3);

    tI2cAdjust.i2cAdjust_Hight_Vf = 1;
    tI2cAdjust.i2cAdjust_Hight = tArm_Mysql.t_Arm_Set.Arm_Set_hv;
    tI2cAdjust.i2cAdjust_Bias_Vf = 1;
    tI2cAdjust.i2cAdjust_Bias = tArm_Mysql.t_Arm_Set.Arm_Set_vbb;
    yangpi_i2c_call_i2c_adjust(PROXY_yangpi_i2c, &tI2cAdjust);

    PRONEERS_LOG("proneers to adjust end\n");

    char sys[30];
    if (tArm_Mysql.t_Arm_Set.Arm_Set_vbb < 3500) {
        sprintf(sys, "/mnt/i2c_2631vbb %d", tArm_Mysql.t_Arm_Set.Arm_Set_vbb);
		/*调节偏置电压*/
        res = system(sys);
    }
    if (tArm_Mysql.t_Arm_Set.Arm_Set_hv < 3500) {
        sprintf(sys, "/mnt/i2c_2631hv %d", tArm_Mysql.t_Arm_Set.Arm_Set_hv);
		/*调节高压*/
        res = system(sys);
    }

    /*流量计算线程*/
    pthread_attr_init(&attribute_run);
    pthread_attr_setdetachstate(&attribute_run, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_run, &attribute_run, run_function, NULL);
    /*数据存储线程*/
    pthread_attr_init(&attribute_storage);
    pthread_attr_setdetachstate(&attribute_storage, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_storage, &attribute_storage, storage_function, NULL);
    /*能谱线程*/
    pthread_attr_init(&attribute_esadjust);
    pthread_attr_setdetachstate(&attribute_esadjust, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_esadjust, &attribute_esadjust, esadjust_function, NULL);

    PRONEERS_LOG("运算线程，存储线程，能谱线程初始化完成\n");

    /*初始化spi控制器*/
    (void)function_dd_spi_init();
    /*设置FPGA参数*/
    function_dd_fpga_set_init(&tFpga_Set);
    PRONEERS_LOG("spi初始化完成\n");
    /*生成能谱   此处是不是可以考虑删掉*/
    spectral_data_w();

    /*循环流程*/
    start_work();
    PRONEERS_LOG("定时器初始化完成\n");
}
/*******************************************************************************
* 函数名称: main_start
* 函数功能: 主程序启动
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
void main_start() {

    pthread_attr_init(&attribute1);
    pthread_attr_setdetachstate(&attribute1, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread1, &attribute1, init_function, NULL);

    if (1) {
        int timeout = 30;
        fd_dog = open("/dev/watchdog", O_WRONLY);

        if (fd_dog == -1) {
            PRONEERS_ERROR("Watchdog device not enabled.\n");

        }
        ioctl(fd_dog, WDIOC_SETTIMEOUT, &timeout);


        PRONEERS_LOG("看门狗初始化完毕 %d ", timeout);
    }

}