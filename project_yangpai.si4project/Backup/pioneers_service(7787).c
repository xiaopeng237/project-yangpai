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
#include <stdio.h>
#include <signal.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <i2cbus_base.h>
#include <mysql_base.h>
#include "yangpi_ota_proxy.h"
#include "yangpi_mysql_proxy.h"
#include "yangpi_i2c_proxy.h"
#include "yangpi_adjust_proxy.h"
#include "pioneers_service.h"
#include "log_dlt.h"
#include "pioneers_spi.h"
#include "calculate_flow.h"
#include "pioneers.h"
#include "yangpi_rtu_proxy.h"

/*******************************外部变量**********************************/
extern HStub STUB_yangpi_pioneers;
extern HProxy PROXY_yangpi_mysql;
extern HProxy PROXY_yangpi_i2c;
extern HProxy PROXY_yangpi_adjust;
extern HProxy PROXY_yangpi_rtu;
extern HProxy PROXY_yangpi_ota;

extern T_Fpga_Set tFpga_Set;
extern T_Arm_Mysql tArm_Mysql;              //arm配置参数     
extern T_AdjustOut tAdjustOut;              //高压和偏置电压调节结果
extern T_AdjustIn tAdjustIn;                //高压和偏置电压调节参数
extern T_I2cAd1115 tI2cAd1115;              //IIC总线采集的温度、压力、差压
extern T_Write_ES tWriteEs;
extern T_CalculatePara FlowParass;          //流量计算相关数据
extern T_Calculatepara_result FlowParasult;
extern T_RunFlag tRunFlag;                  //设备模块启动情况

/***********************内部宏定义/函数声明/全局变量**************************/
#define ENERGY_SPECTRUM_LEN             8192
#define PULSE_SPECTRUM_LEN              512

T_DateTime tDateTime;
T_Write_Mysql_Log tWriteMysqlLog;
T_Write_Flow_Result tWriteFlowResult;
T_I2cOled tI2COled;                         //显示屏数据
T_Freemodbus tFreemodbus;                   /*定义但是并没使用*/


enum PulseSpectrum{
    PULSE_SPECTRUM_GET,
    PULSE_SPECTRUM_SET,
};

enum EnergySpectrum{
    ENERGY_SPECTRUM_GET,
    ENERGY_SPECTRUM_SET,
};
void function_dd_set_pulse_spectrum(int* pPulseData, PulseSpectrum Switch);
void function_dd_set_energy_spectrum(unsigned int* pEnergyS, EnergySpectrum Switch);
/*******************************************************************************
* 函数名称:spectral_data_w
* 函数功能:生成能谱文件 供网页使用
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
int spectral_data_w(void)
{

    int k = 0;
    char data_time1[25] = {};
    char spi_en[204800] = {};
    char p_log1[205800] = {};//add data
    FILE *fd_en;
    unsigned int EnergyS[ENERGY_SPECTRUM_LEN];
    
    function_dd_set_energy_spectrum(EnergyS, ENERGY_SPECTRUM_GET);
    fd_en = fopen("/usr/local/apache/htdocs/yangpai/data-eu-gdp-growth.json", "w+b");
    for(k=0; k < ENERGY_SPECTRUM_LEN; k++)
    {
        sprintf(data_time1,"[%d,%d],",k,EnergyS[k]);
        tWriteEs.EnergyS[k] = EnergyS[k];
        strcat(spi_en,data_time1);
    }

    sprintf(p_log1,"%s%s%s","{\"label\":\"能谱曲线\",\"data\":[",spi_en,"[8192,0]]}");

    fputs(p_log1,fd_en);

    fclose(fd_en);

    return 0;
}
/*******************************************************************************
* 函数名称: function_dd_get_sw_time
* 函数功能: 获取时间
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
void function_dd_get_sw_time(T_DateTime* DataTime)
{
    DataTime->timestamp = tDateTime.timestamp; 
    DataTime->fd_RTC = tDateTime.fd_RTC;
    DataTime->year = tDateTime.year;
    DataTime->month = tDateTime.month;
    DataTime->day = tDateTime.day;
    DataTime->hour = tDateTime.hour;
    DataTime->minute = tDateTime.minute;
    DataTime->second = tDateTime.second;
}
/*******************************************************************************
* 函数名称: readtime
* 函数功能: 从rtc获取系统时间
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
int readtime(void)
{
    int fd, retval;
    struct rtc_time rtc_tm;
    static time_t timep;

    fd = open("/dev/rtc0", O_RDONLY);
    if (fd == -1) {
        printf("/dev/rtc0\n");
    }

    /* Read the RTC time/date */
    retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
    if (retval == -1) {
        PRONEERS_ERROR("ioctl error\n");
    }
    //
    tDateTime.timestamp=time(&timep)+8*60*60; /*当前time_t类型UTC时间戳*/

    tDateTime.fd_RTC	=fd;
    tDateTime.year 	= rtc_tm.tm_year + 1900;
    tDateTime.month 	= rtc_tm.tm_mon + 1;
    tDateTime.day		= rtc_tm.tm_mday;
    tDateTime.hour		= rtc_tm.tm_hour;
    tDateTime.minute	= rtc_tm.tm_min;
    tDateTime.second	= rtc_tm.tm_sec;

    close(fd);
    PRONEERS_LOG("时钟--获取完成");
    return 0;
}

/*******************************************************************************
* 函数名称: get_spi_win
* 函数功能: 获取FPGA窗口数据
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
void get_spi_win()
{
    int win_C[200][6];            //计算用的二维数组
    int i,j;
    int k=0;
    int sumA=0;
    int sumB=0;
    int sumC=0;
    int sumD=0;
    int sumE=0;
    double aveA=0;
    double aveB=0;
    double aveC=0;
    double aveD=0;
    double aveE=0;
    int a=0;
    int b=0;
    int c=0;
    int d=0;
    int e=0;
    int win[1200];

    double winA=0.0;
    double winB=0.0;
    double winC=0.0;
    double winD=0.0;
    double winE=0.0;

    static int cn_c;

    unsigned char RxData[2];
    if(cn_c==1)
    {
        memset(win_C,-1,sizeof(win_C));

        win[0]=0xaa55;

        for(i=0;i<200;i++)
        {
            function_dd_fpga_read(0x0e, RxData);
            if((RxData[0] * 256 + RxData[1]) & 0x20){
                break;
            }
        }

        for(i=0;i<200;i++){
            function_dd_fpga_read(0x10, RxData);
            if((RxData[0] * 256 + RxData[1]) == 0xaa55){
                break;
            }
        }

        for(i=0;i<1199;i++)
        {
            function_dd_fpga_read(0x10, RxData);
            win[i+1] = RxData[0] * 256 + RxData[1];
//            if(i % 6 ==0)
//                printf("\n");
//            printf(" %d ",win[i+1]);
        }
//        printf("\n");

        for(k=0,i=0;k<200;k++)
        {
            if(win[i++]==0xaa55){
                for(j=0;j<5;j++)
                {
                    if(win[i]!=0xaa55)
                    {
                        win_C[k][j]=win[i++];
                    }
                    else
                    {
                        i--;
                        break;
                    }

                }

            }

        }

        for(i=0;i<99;i++){
            if(win_C[i][0]<1000)
            {
                sumA=sumA+win_C[i][0];
                a++;
            }
        }
        aveA=(double)sumA/a;
        if(aveA==0)
        {
            aveA=1;
        }
        for(i=0;i<200;i++)
        {
            //		if(win_C[i][0]==0)
            //			win_C[i][0]=1;
            if(win_C[i][0]>=1000)
                win_C[i][0]=(int)aveA;
            if(win_C[i][0]>(int)(aveA*10))//||win_C[i][0]<(aveA*0.1))
                win_C[i][0]=(int)aveA;
        }

        for(i=0;i<99;i++){
            if(win_C[i][1]<1000)
            {
                sumB=sumB+win_C[i][1];
                b++;
            }
        }
        aveB=(double)sumB/b;
        if(aveB==0)
        {
            aveB=1;
        }
        for(i=0;i<200;i++)
        {
            //		if(win_C[i][1]==0)
            //		win_C[i][1]=1;
            if(win_C[i][1]>=1000)
                win_C[i][1]=(int)aveB;
            if(win_C[i][1]>(int)(aveB*10))//||win_C[i][1]<(aveB*0.1))
                win_C[i][1]=(int)aveB;
        }

        for(i=0;i<99;i++){
            if(win_C[i][2]<1000)
            {
                sumC=sumC+win_C[i][2];
                c++;
            }
        }
        aveC=(double)sumC/c;
        if(aveC==0)
        {
            aveC=1;
        }
        for(i=0;i<200;i++)
        {
            //		if(win_C[i][2]==0)
            //		win_C[i][2]=1;
            if(win_C[i][2]>=1000)
                win_C[i][2]=(int)aveC;
            if(win_C[i][2]>(int)(aveC*10))//||win_C[i][2]<(aveC*0.1))
                win_C[i][2]=(int)aveC;
        }

        for(i=0;i<99;i++){
            if(win_C[i][3]<1000)
            {
                sumD=sumD+win_C[i][3];
                d++;
            }
        }
        aveD=(double)sumD/d;
        if(aveD==0)
        {
            aveD=1;
        }
        for(i=0;i<200;i++)
        {
            //		if(win_C[i][3]==0)
            //		win_C[i][3]=1;
            if(win_C[i][3]>=1000)
                win_C[i][3]=(int)aveD;
            if(win_C[i][3]>(int)(aveD*10))//||win_C[i][3]<(aveD*0.1))
                win_C[i][3]=(int)aveD;
        }

        for(i=0;i<99;i++){
            if(win_C[i][4]<1000)
            {
                sumE=sumE+win_C[i][4];
                e++;
            }
        }
        aveE=(double)sumE/e;
        if(aveE==0)
        {
            aveE=1;
        }
        for(i=0;i<200;i++)
        {
            //		if(win_C[i][4]==0)
            //		win_C[i][4]=1;
            if(win_C[i][4]>=1000)
                win_C[i][4]=(int)aveE;
            if(win_C[i][4]>(int)(aveE*10))//||win_C[i][4]<(aveE*0.1))
                win_C[i][4]=(int)aveE;
        }


        for(j=0;j<200;j++)
        {
            winA=winA+win_C[j][0];
            winB=winB+win_C[j][1];
            winC=winC+win_C[j][2];
            winD=winD+win_C[j][3];
            winE=winE+win_C[j][4];
        }


        FlowParass.winA_CPS=winA;
        FlowParass.winB_CPS=winB;
        FlowParass.winC_CPS=winC;
        FlowParass.winD_CPS=winD;
        FlowParass.winE_CPS=winE;

        PRONEERS_LOG("winA %d winB %d winC %d winD %d winE %d\n",(int)winA,(int)winB,(int)winC,(int)winD,(int)winE);
//        printf("%.4x,%.4x,%.4x,%.4x\n",win_C[0][5],win_C[198][5],win_C[199][5],win_C[54][5]);

    }
    if(cn_c==0)//开一个线程去读取数据
    {
        //system("/mnt/ad1115_datas &");
        function_dd_fpga_read(0x1e, RxData);
        cn_c=1;
        //system("/mnt/i2c_bus &");
    }



    PRONEERS_LOG("spi获取窗口数据完成");
}
/*******************************************************************************
* 函数名称:mysql_assignment
* 函数功能:数据对外输出显示填充
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
void mysql_assignment()
{
    T_DateTime DataTime;
    T_RtuData RtuData;
    function_dd_get_sw_time(&DataTime);
    tWriteMysqlLog.write_log_year           = DataTime.year;
    tWriteMysqlLog.write_log_month          = DataTime.month;
    tWriteMysqlLog.write_log_date           = DataTime.day;
    tWriteMysqlLog.write_log_hour           = DataTime.hour;
    tWriteMysqlLog.write_log_minute         = DataTime.minute;

    tWriteMysqlLog.write_log_Qmg        = FlowParass.Qmg_CPM;
    tWriteMysqlLog.write_log_Qml        = FlowParass.Qml_CPM;
    tWriteMysqlLog.write_log_Qvg        = FlowParass.Qvg_CPM;
    tWriteMysqlLog.write_log_Qvl        = FlowParass.Qvl_CPM;
    tWriteMysqlLog.write_log_GMF        = FlowParass.GMF_CPM_C;
    tWriteMysqlLog.write_log_LMF        = (1-FlowParass.GMF_CPM_C);
    tWriteMysqlLog.write_log_Qvg_Cumulative        = FlowParass.Qvg_add_CPS;
    tWriteMysqlLog.write_log_Qvl_Cumulative        = FlowParass.Qvl_add_CPS;
    tWriteMysqlLog.write_log_31keV        = FlowParass.winB_CPM;
    tWriteMysqlLog.write_log_81keV        = FlowParass.winC_CPM;
    tWriteMysqlLog.write_log_356keV       = FlowParass.winE_CPM;
    tWriteMysqlLog.write_log_Tem        = FlowParass.T_P_WC_CPS;
    tWriteMysqlLog.write_log_P          = FlowParass.P_WC_CPM;
    tWriteMysqlLog.write_log_DP         = FlowParass.DP_CPM;

    tWriteMysqlLog.write_log_31keV_Peak    = tAdjustOut.AdjustOut_F31;
    tWriteMysqlLog.write_log_81keV_Peak    = tAdjustOut.AdjustOut_F81;
    tWriteMysqlLog.write_log_356kev_Peak   = tAdjustOut.AdjustOut_F356;

    tWriteMysqlLog.write_log_Tem_in          = tI2cAd1115.i2cAd1115_BoardTem;//todo:待添加
    tWriteMysqlLog.write_log_Tem_DP          = FlowParass.T_DP_WC_CPS;//
    tWriteMysqlLog.write_log_HV              = (int)tAdjustOut.AdjustOut_Hight;
//    tWriteMysqlLog.write_log_BU              = tFpga_Set.Fpga_Set_WINB1;
//    tWriteMysqlLog.write_log_BD              = tFpga_Set.Fpga_Set_WINB2;
//    tWriteMysqlLog.write_log_CU              = tFpga_Set.Fpga_Set_WINC1;
//    tWriteMysqlLog.write_log_CD              = tFpga_Set.Fpga_Set_WINC2;
//    tWriteMysqlLog.write_log_EU              = tFpga_Set.Fpga_Set_WINE1;
//    tWriteMysqlLog.write_log_ED              = tFpga_Set.Fpga_Set_WINE2;
    tWriteMysqlLog.write_log_LVF_CPM         = FlowParass.LVF_CPM;
    tWriteMysqlLog.write_log_GVF_CPM         = FlowParass.GVF_CPM;
    tWriteMysqlLog.write_log_Qv_CPM          = FlowParass.Qv_CPM;
    tWriteMysqlLog.write_log_LMF_CPM         = FlowParass.LMF_CPM;
    tWriteMysqlLog.write_log_GMF_CPM         = FlowParass.GMF_CPM;
    tWriteMysqlLog.write_log_Qm_CPM          = FlowParass.Qm_CPM;

    //todo:数据库写入
    tWriteFlowResult.Write_FR_Qmg_CPM        = FlowParass.Qmg_add_CPS;
    tWriteFlowResult.Write_FR_Qml_CPM        = FlowParass.Qml_add_CPS;
    tWriteFlowResult.Write_FR_Add_Sctime     = FlowParass.Add_Sctime;

    tI2COled.hour           = DataTime.hour;
    tI2COled.minute         = DataTime.minute;
    tI2COled.second         = DataTime.second;
    tI2COled.GMF_CPM        = FlowParass.GMF_CPM;
    tI2COled.OMF_CPM        = FlowParass.LMF_CPM;
    tI2COled.Qv_SUM         = 0;
    tI2COled.Qmg_CPM        = FlowParass.Qmg_add_CPS;
    tI2COled.Qml_CPM        = FlowParass.Qml_add_CPS;
    tI2COled.DataP          = FlowParass.P_WC_CPS;
    tI2COled.DataDP         = FlowParass.DP_CPS;
    tI2COled.Qv_CPM         = FlowParass.Qv_CPM;
    tI2COled.GVF_CPM        = FlowParass.GVF_CPM;
    tI2COled.OVF_CPM        = FlowParass.LVF_CPM;
    tI2COled.Qml_CPS        = FlowParass.Qml_CPS;
    tI2COled.Qmg_CPS        = FlowParass.Qmg_CPS;
    tI2COled.Dg_SC          = FlowParass.Dg_SC;
    tI2COled.Dw_SC          = FlowParass.Dw_SC;

    RtuData.DP_CPS          = FlowParass.DP_CPS;
    RtuData.P_WC_CPS        = FlowParass.P_WC_CPS;
    RtuData.T_P_WC_CPS      = FlowParass.T_P_WC_CPS;
    RtuData.Qvg_CPS         = FlowParass.Qvg_CPS;
    RtuData.Qvl_CPS         = FlowParass.Qvl_CPS;
    RtuData.Qvg_add_CPS     = FlowParass.Qvg_add_CPS;
    RtuData.Qvl_add_CPS     = FlowParass.Qvl_add_CPS;
    RtuData.Add_Sctime     = FlowParass.Add_Sctime;

    yangpi_rtu_call_rtu_setdata(PROXY_yangpi_rtu, &RtuData);

//    printf("tFreemodbus.P_WC_CPS    %f==\n",tFreemodbus.P_WC_CPS);
//    printf("tFreemodbus.DP_CPS      %f==\n",tFreemodbus.DP_CPS);
//    printf("tFreemodbus.T_P_WC_CPS  %f==\n",tFreemodbus.T_P_WC_CPS);
//    printf("tFreemodbus.Qvg_CPS     %f==\n",tFreemodbus.Qvg_CPS);
//    printf("tFreemodbus.Qvl_CPS     %f==\n",tFreemodbus.Qvl_CPS);


    PRONEERS_LOG("mysql和485数据填充--执行完成 %d %d\n",tFpga_Set.Fpga_Set_WINA1,tFpga_Set.Fpga_Set_WINA2);
}
/*******************************************************************************
* 函数名称:calculate_flow
* 函数功能:流量计算主函数
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
void calculate_flow()
{
    calculate_para_init();
    if(tArm_Mysql.t_Arm_Set.Arm_Set_board_type)
    {//todo：预留
    }
    calculate_flow_start();
    calculate_para_result();
    mysql_assignment();
}

/*******************************************************************************
* 函数名称: get_spi_pull
* 函数功能: 获取脉冲数据
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
int get_spi_pull(void)
{
    static int pulse_en;
    static int pulse_sta;
    static int pulse_data;
    static int m;
    int i;
    int pulse_flag;
    unsigned char RxData[2];
    int PulseData[PULSE_SPECTRUM_LEN];

    if(pulse_en == 0){
        function_dd_fpga_read(0x1c, RxData);
        pulse_en = 1;
        pulse_sta = 1;
    }
    if(pulse_sta == 1){
        for(i=0; i < 60; i++)
        {
            function_dd_fpga_read(0x0E, RxData);
            pulse_flag = RxData[0] * 256 + RxData[1];
            //printf("@@@@%d\n",pulse_flag);
            if(pulse_flag&0x01){
                pulse_sta = 0;
                pulse_data = 1;
                break;
            }
        }

    }
    if(pulse_data == 1)
    {
        for(i=0; i < PULSE_SPECTRUM_LEN; i++){
            function_dd_fpga_read(0x0F, RxData);
            PulseData[m] = RxData[0] * 256 + RxData[1];
            
            function_dd_fpga_read(0x0E, RxData);
            pulse_flag = RxData[0] * 256 + RxData[1];

            //printf("%d,%d\n",i,spidatas.pul);
            m++;
        }
        function_dd_set_pulse_spectrum(PulseData, PULSE_SPECTRUM_SET);

        pulse_en = 0;
        pulse_data = 0;
        m=0;

    }
    PRONEERS_LOG("脉冲--获取完成");
    return 0;
}

/*******************************************************************************
* 函数名称: get_spi_energy
* 函数功能: 获取能谱数据
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
extern int flages_data_ready;
extern pthread_cond_t  esadjust_cond;
int get_spi_energy(void)
{
    int i;
    static int es_c;
    static int es_cn;
    static unsigned int dess[ENERGY_SPECTRUM_LEN];
    static int spectral_c = 0;
    unsigned char RxData[2];
    unsigned int SpiData_des[ENERGY_SPECTRUM_LEN];

    if(spectral_c==1)
    {
        function_dd_fpga_read(0x1D, RxData);
    }

    if(spectral_c >=30 && spectral_c <= 45)
    {
        for(i=0;i<512;i++)
        {
            function_dd_fpga_read(0x03,RxData);
            SpiData_des[es_c++] = RxData[0] * 256 + RxData[1];

        }
    }
    if(spectral_c == 45)
    {

        spectral_c = 0;
        es_c =0;
        es_cn++;
        for(i = 0;i < ENERGY_SPECTRUM_LEN;i++)
        {
            dess[i]=SpiData_des[i]+dess[i];

        }

        //	printf("#$##%d,%d\n",dess[1500],spisets.pch);

        if(es_cn==tFpga_Set.Fpga_Set_PCH)
        {
            function_dd_set_energy_spectrum(dess, ENERGY_SPECTRUM_SET);
            memset(dess, 0, sizeof(unsigned int) * ENERGY_SPECTRUM_LEN);
#if 0
            for(i=0;i<8192;i++)
            {
                //todo：mysql能谱写入
                //tMysqlLog.des[i]	=dess[i];

                EnergyS[i]			=dess[i];
                dess[i]			=0;
                //tMysqlLog.des[i]=65535;
            }
#endif
            es_cn=0;

            PRONEERS_LOG("能谱--获取完成 %d %d %d\n",spectral_c,es_cn,tFpga_Set.Fpga_Set_PCH);
            flages_data_ready = 1;
            pthread_cond_signal(&esadjust_cond);
            
        }

    }
 //   printf("spectral_c %d %d \n",spectral_c,es_over_flag);
    spectral_c++;
    return 0;
}

/*******************************************************************************
* 函数名称: adjust_win
* 函数功能: 调窗主函数
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
extern double calculate_a1;
extern double calculate_b1;
void adjust_win(void)
{
    int winB1ed;
    int winB2ed;
    int winC1ed;
    int winC2ed;
    int winE1ed;
    int winE2ed;
	/*以下6行为20200924之前调窗算法 */
//    winB1ed=(int)((((double)tFpga_Set.Fpga_Set_WINB1-calculate_b1)/calculate_a1)*tAdjustOut.AdjustOut_a2+tAdjustOut.AdjustOut_b2);
//    winB2ed=(int)((((double)tFpga_Set.Fpga_Set_WINB2-calculate_b1)/calculate_a1)*tAdjustOut.AdjustOut_a2+tAdjustOut.AdjustOut_b2);
//
//    winC1ed=(int)((((double)tFpga_Set.Fpga_Set_WINC1-calculate_b1)/calculate_a1)*tAdjustOut.AdjustOut_a2+tAdjustOut.AdjustOut_b2);
//    winC2ed=(int)((((double)tFpga_Set.Fpga_Set_WINC2-calculate_b1)/calculate_a1)*tAdjustOut.AdjustOut_a2+tAdjustOut.AdjustOut_b2);
//
//    winE1ed=(int)((((double)tFpga_Set.Fpga_Set_WINE1-calculate_b1)/calculate_a1)*tAdjustOut.AdjustOut_a2+tAdjustOut.AdjustOut_b2);
//    winE2ed=(int)((((double)tFpga_Set.Fpga_Set_WINE2-calculate_b1)/calculate_a1)*tAdjustOut.AdjustOut_a2+tAdjustOut.AdjustOut_b2);
 
  	/*20200924,ljy 修改调窗算法，仅根据31峰和81峰  */
  
  	#define win31_L ((double)tFpga_Set.Fpga_Set_WINB1)
 	#define win31_P (tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_B)
 	#define win31_R ((double)tFpga_Set.Fpga_Set_WINB2) 
  
  	#define win81_L ((double)tFpga_Set.Fpga_Set_WINC1) 
  	#define win81_P (tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_C) 
  	#define win81_R ((double)tFpga_Set.Fpga_Set_WINC2) 
  
  	#define win356_L ((double)tFpga_Set.Fpga_Set_WINE1) 
  	#define win356_P (tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_E) 
    #define win356_R ((double)tFpga_Set.Fpga_Set_WINE2)
  
  	#define win31_P_now tAdjustOut.AdjustOut_F31
  	#define win81_P_now tAdjustOut.AdjustOut_F81
  	#define win356_P_now tAdjustOut.AdjustOut_F356
  
  	winB1ed=(int)((win81_P_now-win31_P_now)*(win31_L-win31_P)/(win81_P-win31_P)+win31_P_now);
    winB2ed=(int)((win81_P_now-win31_P_now)*(win31_R-win31_P)/(win81_P-win31_P)+win31_P_now);

    winC1ed=(int)((win81_P_now-win31_P_now)*(win81_L-win31_P)/(win81_P-win31_P)+win31_P_now);
    winC2ed=(int)((win81_P_now-win31_P_now)*(win81_R-win31_P)/(win81_P-win31_P)+win31_P_now);

    winE1ed=(int)((win81_P_now-win31_P_now)*(win356_L-win31_P)/(win81_P-win31_P)+win31_P_now);
    winE2ed=(int)((win81_P_now-win31_P_now)*(win356_R-win31_P)/(win81_P-win31_P)+win31_P_now);

    tWriteMysqlLog.write_log_BU              = winB1ed;
    tWriteMysqlLog.write_log_BD              = winB2ed;
    tWriteMysqlLog.write_log_CU              = winC1ed;
    tWriteMysqlLog.write_log_CD              = winC2ed;
    tWriteMysqlLog.write_log_EU              = winE1ed;
    tWriteMysqlLog.write_log_ED              = winE2ed;


//	function_dd_fpga_write(0x01,winA1ed*2);
//	function_dd_fpga_write(0x02,winA2ed*2);

    function_dd_fpga_write(0x03,winB1ed*2);
    function_dd_fpga_write(0x04,winB2ed*2);

    function_dd_fpga_write(0x08,winC1ed*2);
    function_dd_fpga_write(0x0e,winC2ed*2);
//
    //function_dd_fpga_writes(0x1f,spisets.winD1*2);
    //function_dd_fpga_writes(0x21,spisets.winD2*2);

    function_dd_fpga_writes(0x23, winE1ed * 2);
    function_dd_fpga_writes(0x25, winE2ed * 2);
    PRONEERS_LOG("调窗--执行完成 %f %f %f %f\n",calculate_a1,calculate_b1,tAdjustOut.AdjustOut_a2,tAdjustOut.AdjustOut_b2);
    PRONEERS_LOG("调窗--执行完成 %d %d %d %d\n",winB1ed,winB2ed,tFpga_Set.Fpga_Set_WINB1,tFpga_Set.Fpga_Set_WINB2);

}
/*******************************************************************************
* 函数名称: function_web_flow_data_write
* 函数功能: 输出 流量事实数据文件
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* DataPath         char*      in            生成文件的绝对路径
* DataName         char*      in            数据曲线名称
* FlowDataOne      double     in            数据
* DataNo           int        in            数据存储位置（0-4）
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_web_flow_data_write(char* DataPath,char* DataName, double FlowDataOne, int DataNo)
{
    int i = 0;
    static int flowc =0;
    char data_time1[400000] = {};
    char spi_en[400000] = {};
    char p_log1[400000] = {};//add data
    T_DateTime DataTime;
    static long int timestamps[1440];
    static double FLowData[5][1440];
    FILE *F_fd = fopen(DataPath, "w+b");

    if (DataNo >= 5)
    {
        PRONEERS_ERROR("function_web_flow_data_write input error\n");
        return -1;
    }
    
    function_dd_get_sw_time(&DataTime);
    for(i=0; i < (1440 - 1); i++)
    {
        FLowData[DataNo][(1440 - 1)-i] = FLowData[DataNo][(1440 - 2)-i];
        timestamps[(1440 - 1)-i] = timestamps[(1440 - 2)-i];
    }
    
    FLowData[DataNo][0] = FlowDataOne; //FlowParass.Qvl_CPM;
    timestamps[0] = DataTime.timestamp;

    if(flowc == 0)
    {
        sprintf(data_time1, "[%.0f,%f]", (double)timestamps[flowc] * 1000, FLowData[DataNo][flowc]);
        strcat(spi_en,data_time1);
        flowc++;
    }
    else if (flowc < 1440)
    {
        for(i = 0;i < flowc; i++)
        {
            sprintf(data_time1, "[%.0f,%f],", (double)timestamps[i] * 1000, FLowData[DataNo][i]);
            strcat(spi_en,data_time1);
        }
        sprintf(data_time1, "[%.0f,%f]", (double)timestamps[flowc] * 1000, FLowData[DataNo][flowc]);
        strcat(spi_en,data_time1);
        flowc++;
    }
    else
    {
        for(i = 0; i < (1440 - 1); i++)
        {
            sprintf(data_time1, "[%.0f,%f],", (double)timestamps[i] * 1000, FLowData[DataNo][i]);
            strcat(spi_en,data_time1);
        }
        sprintf(data_time1, "[%.0f,%f]", (double)timestamps[(1440 - 1)] * 1000, FLowData[DataNo][(1440 - 1)]);
        strcat(spi_en,data_time1);
    }
   // Liquid-Flow (m3/h)
    sprintf(p_log1,"%s%s%s%s%s","{\"label\":\"", DataName, "\",\"data\":[", spi_en, "]}");

    fputs(p_log1,F_fd);
    fclose(F_fd);

    return 0;
}
#if 0 todo
/*******************************************************************************
* 函数名称: flow_table_w
* 函数功能: 生成流量json文件
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
int flow_table_w(void)
{
    double fwaters[1440];//未知
    char ftable[8192];
    static int flowT =0;
    T_DateTime DataTime;
    int i;
    
    function_dd_get_sw_time(&DataTime);
    for(i=0; i < (4 - 1); i++)
    {
        FLowData[DataNo][(4 - 1)-i] = FLowData[DataNo][(4 - 2)-i];
        timestamps[(4 - 1)-i] = timestamps[(4 - 2)-i];
    }
    if(flowT<4)
    {
        flowT++;
        return 0;
    }
    FILE *F_fd = fopen("/usr/local/apache/htdocs/yangpai/tables/flow-data.json", "w+b");
    sprintf(ftable,"[{\"z1\":\"%.2ld:%.2ld\",\"z2\":\"%.2f\",\"z3\":\"%.2f\",\"z4\":\"%.2f\",\"z5\":\"%.2f\",\"z6\":\"%.2f\","
                   "\"z7\":\"%.2ld:%.2ld\",\"z8\":\"%.2f\",\"z9\":\"%.2f\",\"z10\":\"%.2f\",\"z11\":\"%.2f\",\"z12\":\"%.2f\","
                   "\"z13\":\"%.2ld:%.2ld\",\"z14\":\"%.2f\",\"z15\":\"%.2f\",\"z16\":\"%.2f\",\"z17\":\"%.2f\",\"z18\":\"%.2f\","
                   "\"z19\":\"%.2ld:%.2ld\",\"z20\":\"%.2f\",\"z21\":\"%.2f\",\"z22\":\"%.2f\",\"z23\":\"%.2f\",\"z24\":\"%.2f\"}]",
            (((timestamps[3]/60)/60)%24),((timestamps[3]/60)%60),fgass[3],foils[3],tem1s[3],pres[3],fwaters[3],
            (((timestamps[2]/60)/60)%24),((timestamps[2]/60)%60),fgass[2],foils[2],tem1s[2],pres[2],fwaters[2],
            (((timestamps[1]/60)/60)%24),((timestamps[1]/60)%60),fgass[1],foils[1],tem1s[1],pres[1],fwaters[1],
            (((timestamps[0]/60)/60)%24),((timestamps[0]/60)%60),fgass[0],foils[0],tem1s[0],pres[0],fwaters[0]);
    fputs(ftable,F_fd);
    fclose(F_fd);
    return 0;
}
#endif
/*******************************************************************************
* 函数名称:write_msql_apache
* 函数功能:流量数据输出到数据库和显示屏中
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
int write_msql_apache()
{
    static int math_C=0;

    if(math_C<60)//（）每秒数据(五个窗口计数；温度；压力；差压)计算200次，数据结果累加输出
    {
        math_C++;
        if(math_C==60)//每分钟数据；数据存入mysql；生成流量表格.json；生成曲线文件；
        {


            function_web_flow_data_write("/usr/local/apache/htdocs/yangpai/tables/flow.json",
                                        "Liquid-Flow (m3/h)", FlowParass.Qvl_CPM, 0);
            function_web_flow_data_write("/usr/local/apache/htdocs/yangpai/tables/flow1.json",
                                        "Gas-Flow (m3/h)", FlowParass.Qvg_CPM, 1);
            function_web_flow_data_write("/usr/local/apache/htdocs/yangpai/tables/flow2.json",
                                        "Temperature", FlowParass.T_P_WC_CPS, 2);
            function_web_flow_data_write("/usr/local/apache/htdocs/yangpai/tables/flow5.json",
                                        "Pressure", FlowParass.P_WC_CPM, 3);
            flow_table_w();
            PRONEERS_LOG("调窗--执行完成\n");
            PRONEERS_LOG("tRunFlag.flag_log_en %d\n",tRunFlag.flag_log_en);
            if(tRunFlag.flag_log_en == 2 && tRunFlag.flag_1s_en == 0)
            {
                PRONEERS_LOG("****************write mysql************\n");
                yangpi_mysql_call_writelog(PROXY_yangpi_mysql, &tWriteMysqlLog);

            }

            if(FlowParass.DP_CPS > FlowParass.DP_th)
            {
                FlowParass.Add_Sctime = FlowParass.Add_Sctime + 0.000695;
                PRONEERS_LOG("FlowParass.Add_Sctime  = %f \n",FlowParass.Add_Sctime );
            }

            tWriteFlowResult.Write_FR_Add_Sctime     = FlowParass.Add_Sctime;

            yangpi_mysql_call_writeflow(PROXY_yangpi_mysql,&tWriteFlowResult);
            //W_FlowData();
            yangpi_ota_call_ota_send(PROXY_yangpi_ota, (T_OtaSendLog *) &tWriteMysqlLog);
            math_C=0;
        }

        if(tRunFlag.flag_log_en==0 && tRunFlag.flag_1s_en == 0x100)
        {
            PRONEERS_LOG("****************write mysql %d\n",tRunFlag.flag_log_en);

            yangpi_mysql_call_writelog(PROXY_yangpi_mysql, &tWriteMysqlLog);
        }

        yangpi_i2c_call_i2c_oled(PROXY_yangpi_i2c, &tI2COled);

    }
    else
    {
        PRONEERS_ERROR("math_C error \n");
        math_C=0;
    }


    return 0;
}
/*******************************************************************************
* 函数名称: function_web_calculate_para_write
* 函数功能: 生成网页使用的数据
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
void function_web_calculate_para_write(void)
{
    char afP[8192];

    static int arm_P_C=0;
    double P;
    double DP;

    if(arm_P_C==59)
    {
        //数据准备好了可以存储
        //数据整理好后存储

        DP =	FlowParass.DP_CPM;
        P =		FlowParass.P_WC_CPM;

        FILE *F_fd;
        F_fd = fopen("/usr/local/apache/htdocs/yangpai/tables/ARM-P.json", "w+b");
        sprintf(afP,"[{\"ac\":\"%.0lf\",\"bc\":\"%.0lf\",\"cc\":\"%10.4lf\",\"dc\":\"%10.4lf\","
                    "\"ec\":\"%.0lf\",\"hv\":\"%d\",\"vbb\":\"%d\",\"t1\":\"%.2f C\","
                    "\"t2\":\"%.2f C\",\"a_pre\":\"%.2fKPa\",\"d_pre\":\"%.2fPa\","
                    "\"t3\":\"%.2f C\",\"PAS\":\"%d\",\"PA\":\"%d\",\"PBS\":\"%d\","
                    "\"PB\":\"%d\",\"PCS\":\"%d\",\"PC\":\"%d\",\"PDS\":\"%d\",\"PD\":\"%d\","
                    "\"PES\":\"%d\",\"PE\":\"%d\"}]",
                (double)FlowParass.winB_CPM,(double)FlowParass.winC_CPM,((double)FlowParass.Qvl_add_CPS/10000)*24,(double)FlowParass.Add_Sctime,(double)FlowParass.winE_CPS,
                (int)tAdjustOut.AdjustOut_Hight,tArm_Mysql.t_Arm_Set.Arm_Set_vbb,tI2cAd1115.i2cAd1115_BoardTem,FlowParass.T_P_WC_CPS,P,
                DP,FlowParass.T_DP_WC_CPS,tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_B,tAdjustOut.AdjustOut_F31,
                tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_C,tAdjustOut.AdjustOut_F81,0,0,0,0,tArm_Mysql.t_Arm_Set.Arm_Set_PEAK_E,tAdjustOut.AdjustOut_F356);
        fputs(afP,F_fd);
        fclose(F_fd);
#if WIN_DATA_CPS
        flowresult.winA=S_winA;
		flowresult.winB=S_winB;
		flowresult.winC=S_winC;
		flowresult.winD=S_winD;
		flowresult.winE=S_winE;
#endif
        printf("B=%f\n DPT=%f PT=%f\n",tI2cAd1115.ad1115_buf[199][0],FlowParass.T_DP_WC_CPS,FlowParass.T_P_WC_CPS);

        arm_P_C	=	-1;
    }
    arm_P_C++;
    PRONEERS_LOG("网页表格写入--执行完成\n");
}
/*******************************************************************************
* 函数名称: function_web_pulse_data_write
* 函数功能: 生成脉冲数据文件供网页使用
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
int function_web_pulse_data_write(void)
{
    int k = 0;
    int c = 0;
    char data_time1[20] = {};
    char spi_en[8192] = {};
    char p_log1[40966] = {};//add data
    FILE *fd_pulse;
    int PulseData[PULSE_SPECTRUM_LEN];
    
    fd_pulse = fopen("/usr/local/apache/htdocs/yangpai/pulse_data.json", "w+b");  
    function_dd_set_pulse_spectrum(PulseData, PULSE_SPECTRUM_GET);
    for(k=0; k<500;k++)
    {
//		c = pt->pulse_data[2*k]*256+pt->pulse_data[2*k+1];
        c = PulseData[k+10];//横坐标用纳秒表示，
        if(c < 0){
            c = 0;
        }
        sprintf(data_time1,"[%d,%d],",k*10,c);
        strcat(spi_en,data_time1);
    }

    sprintf(p_log1,"%s%s%s%d%s","{\"label\":\"脉冲曲线 x:t/ns y:v/mv\",\"data\":[",spi_en,"[5000,",PulseData[500+10],"]]}");
//	fwrite(p_log1,strlen(p_log1),1,fd_en );
    fputs(p_log1,fd_pulse);

    fclose(fd_pulse);

    PRONEERS_LOG("脉冲存储--执行完成");
    return 0;

}
/*******************************************************************************
* 函数名称:function_dd_energy_spectrum_errorCode
* 函数功能:检查能谱中的异常数据并对齐进行修复
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
void function_dd_energy_spectrum_errorCode(void)
{
    int i;
    double sum;
    double a;
    double b;
    unsigned int EnergyS[ENERGY_SPECTRUM_LEN];
    
    function_dd_set_energy_spectrum(EnergyS, ENERGY_SPECTRUM_GET);
    for(i=200;i<7500;i++)//100道开始7500道结束
    {
        sum = EnergyS[i]+EnergyS[i+1];
        if(sum<=20.0)
        {
            if(EnergyS[i+2]>=30.0)
                EnergyS[i+2]=(EnergyS[i]+EnergyS[i+1])/2;
        }
/*		else if(sum>20 && sum <5000)
		{
			a = (double)(data_adj[i]+data_adj[i+1])/(2*(double)data_adj[i+2]);
			if(a<0.5 || a>1.5)
				data_adj[i+2]=(data_adj[i]+data_adj[i+1])/2;
		}*/
        else
        {
            a = EnergyS[i]+5*pow(EnergyS[i],0.5);//*2;
            b = EnergyS[i]-5*pow(EnergyS[i],0.5);//*0.2;
            if((EnergyS[i-1]<b||EnergyS[i-1]>a)&&(EnergyS[i+1]<b||EnergyS[i+1]>a))
            {
                EnergyS[i]=(EnergyS[i-1]+EnergyS[i+1])/2;
            }
            else if((EnergyS[i-1]<b||EnergyS[i-1]>a)&&(EnergyS[i+1]>b&&EnergyS[i+1]<a))
            {
                EnergyS[i-1]=(EnergyS[i]+EnergyS[i+1])/2;
            }
            else if((EnergyS[i-1]>b&&EnergyS[i-1]<a)&&(EnergyS[i+1]<b||EnergyS[i+1]>a))
            {
                EnergyS[i+1]=(EnergyS[i]+EnergyS[i-1])/2;
            }
            else
            {

            }

        }
    }
    function_dd_set_energy_spectrum(EnergyS, ENERGY_SPECTRUM_SET);
    memcpy(tAdjustIn.AdjustIn_S_es, EnergyS, sizeof(int) * ENERGY_SPECTRUM_LEN);
#if 0
    for(i=0;i<8192;i++)
    {
        tAdjustIn.AdjustIn_S_es[i]=EnergyS[i];
    }
#endif
}
/********************************局内函数**************************************/

/*******************************************************************************
* 函数名称: function_dd_set_energy_spectrum
* 函数功能: 设置、获取能谱数据
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* pEnergyS      unsigned int*   in/out       能谱数据
* int              switch         int        0：set 1：get
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
void function_dd_set_energy_spectrum(unsigned int* pEnergyS, EnergySpectrum Switch)
{
    static unsigned int EnergySpectrumData[ENERGY_SPECTRUM_LEN] = {0};
    switch(Switch)
    {
        case ENERGY_SPECTRUM_SET:
            memcpy(EnergySpectrumData, pEnergyS, sizeof(int) * ENERGY_SPECTRUM_LEN);
            break;
        case ENERGY_SPECTRUM_GET:
            memcpy(pEnergyS, EnergySpectrumData, sizeof(int) * ENERGY_SPECTRUM_LEN);
            break;
        default:
            PRONEERS_ERROR("function_dd_set_energy_spectrum input type error.");
    }

}
/*******************************************************************************
* 函数名称: function_dd_set_pulse_spectrum
* 函数功能: 设置、获取脉冲数据
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* pEnergyS      unsigned int*   in/out       脉冲数据
* int              switch         int        0：set 1：get
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
void function_dd_set_pulse_spectrum(int* pPulseData, PulseSpectrum Switch)
{
    static int SpiData_dpul[PULSE_SPECTRUM_LEN] = {0};
    switch(Switch)
    {
        case PULSE_SPECTRUM_SET:
            memcpy(SpiData_dpul, pPulseData, sizeof(int) * PULSE_SPECTRUM_LEN);
            break;
        case ENERGY_SPECTRUM_GET:
            memcpy(pPulseData, SpiData_dpul, sizeof(int) * PULSE_SPECTRUM_LEN);
            break;
        default:
            PRONEERS_ERROR("function_dd_set_energy_spectrum input type error.");
    }

}

/***************************以下为GPIO相关操作接口******************************/
/*******************************************************************************
* 函数名称: function_dd_gpio_export
* 函数功能: 初始化gpio端口
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* pin              int         in       管脚号
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_gpio_export(int pin)
{
    char buffer[64];
    int len;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        PRONEERS_ERROR("Failed to open export for writing!\n");
        return(-1);
    }

    len = snprintf(buffer, sizeof(buffer), "%d", pin);
    if (write(fd, buffer, len) < 0) {
        PRONEERS_ERROR("Failed to export gpio!");
//        return -1;
    }

    close(fd);
    return 0;
}
/*******************************************************************************
* 函数名称: function_dd_gpio_direction
* 函数功能: 设置gpio方向
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
*  pin               int        in          管脚号
*  dir               int        in         0：in  1：out
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_gpio_direction(int pin, int dir)
{
    static const char dir_str[] = "in\0out";
    char path[64];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        PRONEERS_ERROR("Failed to open gpio direction for writing!\n");
        return -1;
    }

    if (write(fd, &dir_str[dir == 0 ? 0 : 3], dir == 0 ? 2 : 3) < 0) {
        PRONEERS_ERROR("Failed to set direction!\n");
//        return -1;
    }

    close(fd);
    return 0;
}
/*******************************************************************************
* 函数名称: function_dd_gpio_write
* 函数功能: 设置gpio输出电压
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
*  pin               int        in          管脚号
*  value             int        in       0-->LOW, 1-->HIGH
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_gpio_write(int pin, int value)
{
    static const char values_str[] = "01";
    char path[64];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        PRONEERS_ERROR("Failed to open gpio value for writing!\n");
        return -1;
    }

    if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0) {
        PRONEERS_ERROR("Failed to write value!\n");
//        return -1;
    }

    close(fd);
    return 0;
}
/*******************************************************************************
* 函数名称: function_dd_gpio_edge
* 函数功能: 设置gpio的触发沿
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
*  pin               int        in          管脚号
*  edge              int        in      设置gpio的触发沿
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
int function_dd_gpio_edge(int pin, int edge)
{
    const char dir_str[] = "none\0rising\0falling\0both";
    int ptr;
    char path[64];
    int fd;
    switch(edge){
        case 0:
            ptr = 0;
            break;
        case 1:
            ptr = 5;
            break;
        case 2:
            ptr = 12;
            break;
        case 3:
            ptr = 20;
            break;
        default:
            ptr = 0;
            break;
    }

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/edge", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        PRONEERS_ERROR("Failed to open gpio edge for writing!\n");
        return -1;
    }

    if (write(fd, &dir_str[ptr], strlen(&dir_str[ptr])) < 0) {
        PRONEERS_ERROR("Failed to set edge!\n");
//        return -1;
    }

    close(fd);
    return 0;
}
