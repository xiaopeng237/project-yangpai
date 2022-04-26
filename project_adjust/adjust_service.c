//
// Created by Administrator on 2020/3/27.
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
#include "adjust_service.h"
#include "yangpi_adjust_stub.h"
#include "yangpi_i2c_proxy.h"
#include "i2cbus_base.h"
#include "adjust_service_base.h"
#include "log_dlt.h"
#include <math.h>
extern HStub STUB_yangpi_adjust;
extern HProxy PROXY_yangpi_i2c;

pthread_t adfunct_thread;
pthread_attr_t adfunct_attribute;
pthread_mutex_t adfunct_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  adfunct_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t adjust_mutex = PTHREAD_MUTEX_INITIALIZER;

T_I2cAdjust tI2CAdjust;
T_AdjustIn tAdjustIn;
T_AdjustOut tAdjustOut;

int flag_adjust = 0;



float data_adj[8192];
float peak356[1500];
float peak81[1000];
float peak31[1000];
float data_adjs[8192];


int PCH356;
int PCH81;
int PCH31;

int HV = 0;

int CON_B1;
int CON_B2;
int CON_C1;
int CON_C2;
int CON_E1;
int CON_E2;

int WIN_A_W;
int WIN_B_W;
int WIN_E_W;



int adjust_HV;
int flag_hv = 1;

int new_p31kev = 0;
int p31kev_flag = 0;

void readFile356(void)
{
    FILE *fd;
    char para[8192][20]={{0},{0}};
    int i;
    int j;
    int k;
    int m;
    fd = fopen("/peak356.csv", "rb");
    if(fd==NULL)
    {
        ADJUST_LOG("文件打开失败或者文件不存在\n");
    }
    fseek(fd,0,SEEK_END);
    long len = ftell(fd);
    ADJUST_LOG("longs=%ld\n",len);
    fseek(fd,0,SEEK_SET);
    char *data=(char*)malloc(len+1);
    int res = 0;
    res = fread(data,1,len,fd);
    m=0;
    for(i=0;i<=len;i++)
    {
        if(*(data+i)==44)
        {
            for(j=1;j<20;j++)
            {
                if(*(data+i+j)>47 && *(data+i+j)<58)
                    break;
            }
            for(k=1;k<20;k++)
            {
                if(*(data+i+j+k)<=47 || *(data+i+j+k)>=58)
                    break;
            }
            strncpy(para[m],(data+i+j),k);
            peak356[m]=(float)atof(para[m]);
            //printf("%d=%f\n",m,peak356[m]);
            m++;
            WIN_E_W	= m;
        }
    }
    fclose(fd);
    free(data);
}

void readFile81(void)
{
    FILE *fd = NULL;
    char para[8192][20]={{0},{0}};
    int i;
    int j;
    int k;
    int m;
    fd = fopen("/peak81.csv", "rb");
    if(fd==NULL)
    {
        ADJUST_LOG("文件打开失败或者文件不存在\n");
    }
    fseek(fd,0,SEEK_END);
    long len = ftell(fd);
    ADJUST_LOG("longs=%ld\n",len);
    fseek(fd,0,SEEK_SET);
    char *data=(char*)malloc(len+1);

    int res = 0;
    res = fread(data,1,len,fd);
    m=0;
    //printf("HV_C3.1=%f\n",HV_C);
    for(i=0;i<=len;i++)
    {
        //printf("HV_C3.2=%f\n",HV_C);
        if(*(data+i)==44)
        {
            for(j=1;j<20;j++)
            {
                if(*(data+i+j)>47 && *(data+i+j)<58)
                    break;
            }
            for(k=1;k<20;k++)
            {
                if(*(data+i+j+k)<=47 || *(data+i+j+k)>=58)
                    break;
            }
            strncpy(para[m],(data+i+j),k);
            peak81[m]=(float)atof(para[m]);
            //printf("%d=%f\n",m,peak81[m]);
            m++;
            WIN_B_W	= m;
        }
    }
    fclose(fd);
    free(data);
}

void readFile31(void)
{
    FILE *fd = NULL;
    char para[8192][20]={{0},{0}};
    int i;
    int j;
    int k;
    int m;
    fd = fopen("/peak31.csv", "rb");
    if(fd==NULL)
    {
        printf("文件打开失败或者文件不存在\n");
    }
    fseek(fd,0,SEEK_END);
    long len = ftell(fd);
    printf("longs=%ld\n",len);
    fseek(fd,0,SEEK_SET);
    char *data=(char*)malloc(len+1);
    int res = 0;
    res = fread(data,1,len,fd);
    m=0;
    for(i=0;i<=len;i++)
    {
        if(*(data+i)==44)
        {
            for(j=1;j<20;j++)
            {
                if(*(data+i+j)>47 && *(data+i+j)<58)
                    break;
            }
            for(k=1;k<20;k++)
            {
                if(*(data+i+j+k)<=47 || *(data+i+j+k)>=58)
                    break;
            }
            strncpy(para[m],(data+i+j),k);
            peak31[m]=(float)atof(para[m]);
            //printf("%d=%f\n",m,peak31[m]);
            m++;
            WIN_A_W	=	m;
        }
    }
    fclose(fd);
    free(data);
}
void errorCode(void)
{
    int i;
    float sum;
    float a;
    float b;
    for(i=200;i<7500;i++)//100道开始7500道结束
    {
        sum = data_adj[i]+data_adj[i+1];
        if(sum<=20.0)
        {
            if(data_adj[i+2]>=30.0)
                data_adj[i+2]=(data_adj[i]+data_adj[i+1])/2;
        }
/*		else if(sum>20 && sum <5000)
		{
			a = (float)(data_adj[i]+data_adj[i+1])/(2*(float)data_adj[i+2]);
			if(a<0.5 || a>1.5)
				data_adj[i+2]=(data_adj[i]+data_adj[i+1])/2;
		}*/
        else
        {
            a = data_adj[i]+3*pow(data_adj[i],2);
            b = data_adj[i]-3*pow(data_adj[i],2);
            if((data_adj[i-1]<b||data_adj[i-1]>a)&&(data_adj[i+1]<b||data_adj[i+1]>a))
            {
                data_adj[i]=(data_adj[i-1]+data_adj[i+1])/2;
            }
            else if((data_adj[i-1]<b||data_adj[i-1]>a)&&(data_adj[i+1]>b&&data_adj[i+1]<a))
            {
                data_adj[i-1]=(data_adj[i]+data_adj[i+1])/2;
            }
            else if((data_adj[i-1]>b&&data_adj[i-1]<a)&&(data_adj[i+1]<b||data_adj[i+1]>a))
            {
                data_adj[i+1]=(data_adj[i]+data_adj[i-1])/2;
            }
            else
            {

            }

        }
    }
}
int es_flag = 0;
void integral_es(void)
{
    int i=0;
    int k;
    double sum31=0;
    double sum31s=0;
    double sum81=0;
    double sum81s=0;
    double sum356=0;
    double sum356s=0;
    int F356 = 0;
    int F81 = 0;
    int F31 = 0;
    //for(i=0;i<8192;i++)
    //printf("%d=%f\n",i,data_adj[i]);
    /*
     * 标准设置三点拟合
     */

    for(i=CON_E1;i<CON_E2;i++)
    {
        for(k=0;k<WIN_E_W;k++)
        {
            sum356=sum356+data_adj[i+k]*peak356[k];

        }
        //printf("data_adj=%f,sum356=%f\n",data_adj[4000+k+i],sum356);
        if(sum356>sum356s)
        {
            F356=i+WIN_E_W/2;
            sum356s=sum356;
        }
        //printf("%f---%f\n",sum356,sum356s);
        sum356=0;
    }
//printf("F356=%d\n",F356);
    for(i=CON_C1;i<CON_C2;i++)
    {
        for(k=0;k<WIN_B_W;k++)
        {
            sum81=sum81+data_adj[i+k]*peak81[k];
        }
        if(sum81>sum81s)
        {
            F81=i+WIN_B_W/2;
            sum81s=sum81;
        }
        //printf("%f---%f\n",sum81,sum81s);

        sum81=0;
    }

    for(i=CON_B1;i<CON_B2;i++)
    {
        for(k=0;k<WIN_A_W;k++)
        {
            sum31=sum31+data_adj[i+k]*peak31[k];
        }
        if(sum31>sum31s)
        {
            F31=i+WIN_A_W/2;
            sum31s=sum31;
        }

        sum31=0;
    }

    ADJUST_LOG("F31=%d,F81=%d,F356=%d\n",F31,F81,F356);
    //三点  改两点
/*	float ave_x		=	(31+81+356)/3.0;
	float ave_y		=	(F31+F81+F356)/3.0;
	float ave_xy	=	(31*F31+81*F81+356*F356)/3.0;
	float ave_xx	=	(31*31+81*81+356*356)/3.0;
	shared->a2		=	(ave_x*ave_y-ave_xy)/(ave_x*ave_x-ave_xx);
	shared->b2		=	ave_y-shared->a2*ave_x;*/


//	if(TEXT==0)
    //{
    new_p31kev = F31;
    tAdjustOut.AdjustOut_F31	=	F31;
    tAdjustOut.AdjustOut_F81	=	F81;
    tAdjustOut.AdjustOut_F356	=	F356;

    tAdjustOut.AdjustOut_a2 = (F81 - F31)/(81.0 - 31.0);
    tAdjustOut.AdjustOut_b2 = F31 - 31* tAdjustOut.AdjustOut_a2;
    tAdjustOut.AdjustOut_WIN_J  = 1;

    tAdjustOut.AdjustOut_Hight = HV;

    /*
     * 计算窗位偏移量
     */
    //todo:发送
    es_flag = 0;
    yangpi_adjust_signal_adjust_result(STUB_yangpi_adjust,&tAdjustOut);
    ADJUST_LOG("F31 = %d F81 = %d  %f  %f\n",F31,F81,tAdjustOut.AdjustOut_a2,tAdjustOut.AdjustOut_b2);

    //}

}

void findPeak(void)
{
    int 				i,k;
    float	 			fullE	=	0;	//溢出道上的计数
    int 				fullE_F = 0;		//溢出道的位置
    float				peakH;			//最高能峰计数
    int					peakH_F=0;		//最高能峰位置
    double 				sum100 	= 0;
    double				sum100s = 0;
    int 				up_es	= 0;
    int					down_es	= 0;

    /*
     * 寻找溢出峰,目前没有使用
     */
    for(i=0;i<8192;i++)
    {
        if(data_adj[8191-i]!=0)
        {
            fullE_F = 8191-i;
            break;
        }
    }
    ADJUST_LOG("fullE_F=%d data=%f\n",fullE_F,data_adj[8191-i]);
    for(k=0;k<100;k++)
    {
        fullE=fullE+data_adj[8191-k];

    }
    ADJUST_LOG("%f\n",fullE);
    /*
     * 寻找高能峰
     */
    for(k=0;k<100;k++)
    {
        sum100s = sum100s+data_adj[fullE_F-100-1-k];
    }
    ADJUST_LOG("sum100s=%f\n",sum100s);
    for(i=0;i<(fullE_F-100-100);i++)
    {
        for(k=0;k<100;k++)
        {
            sum100 = sum100+data_adj[fullE_F-100-i-k];
        }
        //printf("sum100=%f  sum100s=%f up=%d  down =%d\n",sum100,sum100s,up_es,down_es);
        //printf("%f,%d\n",sum100,fullE_F-100-i);
        if(sum100>tAdjustIn.AdjustIn_th_sum)//这里的数字最好根据总数调整
        {
            if(sum100>sum100s)
            {
                up_es++;
            }
            else if(sum100 < sum100s)
            {
                down_es++;
            }
            else
            {
                down_es++;
            }

            if(up_es<180 && down_es>120)
            {
                up_es=0;
                down_es=0;
            }
            if(up_es>150 && down_es>150)
            {
                peakH_F=fullE_F-100-i+60;
                peakH = data_adj[peakH_F];
                ADJUST_LOG("peakH_F=%d,peakH=%f\n",peakH_F,peakH);
                up_es=0;
                down_es=0;
                //if判断是不是要调整高压否则算卷积
                break;
            }

/*			if((up_es+down_es)>350)
			{
				up_es=0;
				down_es=0;
			}*/
        }
        else{
            up_es=0;
            down_es=0;
        }
        sum100s=sum100;
        sum100=0;

    }

    double sum31 = 0;
    double sum31s = 0;
    int F31 = 0;
    for(i=CON_B1;i<CON_B2;i++)
    {
        for(k=0;k<WIN_A_W;k++)
        {
            sum31=sum31+data_adj[i+k]*peak31[k];
        }
        if(sum31>sum31s)
        {
            F31=i+WIN_A_W/2;
            sum31s=sum31;
        }

        sum31=0;
    }
    new_p31kev = F31;
    ADJUST_LOG("PCH356-peakH_F=%d\n",(PCH356-peakH_F));
    ADJUST_LOG("PCH31-new_p31kev=%d %f %d %d\n",(PCH31-new_p31kev),tAdjustIn.AdjustIn_WIN_en,tAdjustIn.AdjustIn_reality_b1,tAdjustIn.AdjustIn_reality_b2);

    if((PCH31-new_p31kev)>tAdjustIn.AdjustIn_reality_b1 && (PCH31-new_p31kev)<tAdjustIn.AdjustIn_reality_b2)
    {
        if(tAdjustIn.AdjustIn_WIN_en!=0){
            integral_es();
            p31kev_flag = 1;
            flag_hv=0;
        }
        return;
    }

    if(p31kev_flag == 1 || ((PCH31-new_p31kev)>tAdjustIn.AdjustIn_reality_b1*5 && (PCH31-new_p31kev)< tAdjustIn.AdjustIn_reality_b2*5))
    {

        if(tAdjustIn.AdjustIn_HIV_en!=0) {
            if (((PCH31 - new_p31kev)*tAdjustIn.AdjustIn_Hight_C) > 100) {
                HV = HV + 100;
            } else if (((PCH31 - new_p31kev)*tAdjustIn.AdjustIn_Hight_C) < -100) {
                HV = HV - 100;
            } else {
                HV = (int) (HV + ((PCH31 - new_p31kev)*tAdjustIn.AdjustIn_Hight_C*5));
            }

            if(HV >= 4000)
            {
                HV = 2500;
            }

            if (flag_hv == 1) {
                tI2CAdjust.i2cAdjust_Hight_Vf = 1;
                tI2CAdjust.i2cAdjust_Hight = HV;
                yangpi_i2c_call_i2c_adjust(PROXY_yangpi_i2c, &tI2CAdjust);

                ADJUST_LOG("HV=%d \n", HV);
                ADJUST_LOG("HV_C=%f\n", tAdjustIn.AdjustIn_Hight_C);
                ADJUST_LOG("new_p31kev=%d\n", new_p31kev);

                tAdjustOut.AdjustOut_WIN_J  = 0;
                tAdjustOut.AdjustOut_Hight = HV;
                yangpi_adjust_signal_adjust_result(STUB_yangpi_adjust,&tAdjustOut);
            }
            ADJUST_LOG("PCH31=%d\n", PCH31);
            flag_hv = 1;
        }

        return;
    }

    if((PCH356-peakH_F)>tAdjustIn.AdjustIn_reality_e1 && (PCH356-peakH_F)<tAdjustIn.AdjustIn_reality_e2)//容忍的误差范围
    {

        if((PCH356-peakH_F)>tAdjustIn.AdjustIn_reality_e1/2 && (PCH356-peakH_F)<tAdjustIn.AdjustIn_reality_e2/2)
        {
            flag_hv=0;
            if(tAdjustIn.AdjustIn_WIN_en!=0){
                integral_es();
                p31kev_flag = 1;
            }
        }
        else{
            if(tAdjustIn.AdjustIn_HIV_en!=0){
                if(((PCH356-peakH_F)*tAdjustIn.AdjustIn_Hight_C)>100){
                    HV=HV+100;
                }
                else if(((PCH356-peakH_F)*tAdjustIn.AdjustIn_Hight_C)<-100){
                    HV=HV-100;
                }
                else{
                    HV=(int)(HV+((PCH356-peakH_F)*tAdjustIn.AdjustIn_Hight_C));
                }
                if(HV >= 4000)
                {
                    HV = 2500;
                }
                ADJUST_LOG("flag_hv=%d\n",flag_hv);
                if(flag_hv==1)
                {
                    tI2CAdjust.i2cAdjust_Hight_Vf = 1;
                    tI2CAdjust.i2cAdjust_Hight = HV;
                    yangpi_i2c_call_i2c_adjust(PROXY_yangpi_i2c, &tI2CAdjust);

                    tAdjustOut.AdjustOut_WIN_J  = 0;
                    tAdjustOut.AdjustOut_Hight = HV;
                    yangpi_adjust_signal_adjust_result(STUB_yangpi_adjust,&tAdjustOut);

                    ADJUST_LOG("HV=%d\n",HV);
                    ADJUST_LOG("HV_C=%f\n",tAdjustIn.AdjustIn_Hight_C);
                    ADJUST_LOG("peakH_F=%d\n",peakH_F);
                }
                ADJUST_LOG("PCH356=%d\n",PCH356);
                flag_hv=1;

            }
        }

    }
    else
    {

        if(tAdjustIn.AdjustIn_HIV_en!=0){
            if(((PCH356-peakH_F)*tAdjustIn.AdjustIn_Hight_C)>100){
                HV=HV+100;
            }
            else if(((PCH356-peakH_F)*tAdjustIn.AdjustIn_Hight_C)<-100){
                HV=HV-100;
            }
            else{
                HV=(int)(HV+((PCH356-peakH_F)*tAdjustIn.AdjustIn_Hight_C));
            }
            if(HV >= 4000)
            {
                HV = 2500;
            }
            ADJUST_LOG("flag_hv=%d\n",flag_hv);
            if(flag_hv==1)
            {
                tI2CAdjust.i2cAdjust_Hight_Vf = 1;
                tI2CAdjust.i2cAdjust_Hight = HV;
                yangpi_i2c_call_i2c_adjust(PROXY_yangpi_i2c, &tI2CAdjust);

                tAdjustOut.AdjustOut_WIN_J  = 0;
                tAdjustOut.AdjustOut_Hight = HV;
                yangpi_adjust_signal_adjust_result(STUB_yangpi_adjust,&tAdjustOut);

                ADJUST_LOG("HV=%d\n",HV);
                ADJUST_LOG("HV_C=%f\n",tAdjustIn.AdjustIn_Hight_C);
                ADJUST_LOG("peakH_F=%d\n",peakH_F);
            }


            ADJUST_LOG("PCH356=%d\n",PCH356);
            flag_hv=1;
            //system(peakC);
        }
    }

}

void adjust_opertion(void)
{
    int i;


    for(i=0;i<8192;i++){
        data_adj[i]=0;
        data_adj[i]=(float)tAdjustIn.AdjustIn_S_es[i];
        //printf("%d,%f\n",i,data_adj[i]);
    }
    //readFile();
    if(HV == 0)
    {

        PCH31	=	(int)tAdjustIn.AdjustIn_PCH31;
        PCH81	=	(int)tAdjustIn.AdjustIn_PCH81;
        PCH356	=	(int)tAdjustIn.AdjustIn_PCH356;
        HV		=	(int)tAdjustIn.AdjustIn_Hight;


        CON_B1	=	(int)tAdjustIn.AdjustIn_CON_B1;
        CON_B2	=	(int)tAdjustIn.AdjustIn_CON_B2;
        CON_C1	=	(int)tAdjustIn.AdjustIn_CON_C1;
        CON_C2	=	(int)tAdjustIn.AdjustIn_CON_C2;
        CON_E1	=	(int)tAdjustIn.AdjustIn_CON_E1;
        CON_E2	=	(int)tAdjustIn.AdjustIn_CON_E2;

        readFile31();
        readFile81();
        readFile356();
    }
    ADJUST_LOG("----HV %d",HV);
    errorCode();

    findPeak();
}






void adjust_start(HStub stub, T_AdjustIn *zdb_T_AdjustIn)
{
    pthread_mutex_lock(&adjust_mutex);
    memcpy(&tAdjustIn,zdb_T_AdjustIn,sizeof(T_AdjustIn));
    pthread_mutex_unlock(&adjust_mutex);

    flag_adjust = 1;
    pthread_cond_signal(&adfunct_cond);
    ADJUST_LOG("adjust_start\n");

}
void init_stub_yangpi_adjust(tInterfaceStub_yangpi_adjust *stub)
{
    stub->adjust_start  = adjust_start;
}

void *adjust_thread_function(void* a)
{
    for(;;) {
        pthread_mutex_lock(&adfunct_mutex);
        while (0 == flag_adjust) {
            pthread_cond_wait(&adfunct_cond, &adfunct_mutex);
        }
        flag_adjust = 0;
        pthread_mutex_unlock(&adfunct_mutex);

        adjust_opertion();
    }
}

void main_start()
{
    pthread_attr_init(&adfunct_attribute);
    pthread_attr_setdetachstate(&adfunct_attribute, PTHREAD_CREATE_DETACHED);
    pthread_create(&adfunct_thread, &adfunct_attribute, adjust_thread_function, NULL);
}