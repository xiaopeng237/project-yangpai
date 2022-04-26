//
// Created by Administrator on 2020/3/25.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log_dlt.h"
#include "read_mysql.h"
#include "mysql_base.h"
#include "mysql.h"



extern T_Write_Mysql_Log       t_Write_Mysql_Log;
extern T_Write_Flow_Result     t_Write_Flow_Result;
extern T_YangP_Mysql           t_YangP_Mysql;
extern MYSQL mysql_conn;

FILE *F_fd;


int read_fpga_setpara(void)
{
    unsigned  int ret = 0;
    unsigned  int num = 0;
    char execsql[1024] = {0};
    int spi_set[20] = {0};
    MYSQL_RES 				*res;
    MYSQL_ROW 				row;
    mysql_select_db(&mysql_conn, "FPGA_SET");
    sprintf(execsql,"select * from FPGA_SET");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                spi_set[num]=atoi(row[num]);
            }
            if(spi_set[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_PCH        = spi_set[1];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_TH         = spi_set[2];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINA1      = spi_set[3];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINA2      = spi_set[4];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINB1      = spi_set[5];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINB2      = spi_set[6];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINC1      = spi_set[7];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINC2      = spi_set[8];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WIND1      = spi_set[9];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WIND2      = spi_set[10];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINE1      = spi_set[11];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINE2      = spi_set[12];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_ST         = spi_set[13];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_CT         = spi_set[14];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_P_th       = spi_set[15];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_P_min      = spi_set[16];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_P_max      = spi_set[17];
                t_YangP_Mysql.t_Fpga_Set->Fpga_Set_BaseL      = spi_set[18];
            }
//				printf("\n");
        }
        mysql_free_result(res);// 释放查询结果
    }

    //FPGA to json
    F_fd = fopen("/usr/local/apache/htdocs/yangpai/tables/fpga-P.json", "w+b");
    sprintf(execsql,"[{\"para1\":\"WIN-AU\", \"value1\":\"%d\",\"para2\": \"WIN-AD\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"WIN-BU\", \"value1\":\"%d\",\"para2\": \"WIN-BD\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"WIN-CU\", \"value1\":\"%d\",\"para2\": \"WIN-CD\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"WIN-DU\", \"value1\":\"%d\",\"para2\": \"WIN-DD\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"WIN-EU\", \"value1\":\"%d\",\"para2\": \"WIN-ED\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"ES-T\", \"value1\":\"%d s\",\"para2\": \"CYC-T\",\"value2\":\"%d ms\"},\n"
                    "{\"para1\":\"ES-TH\", \"value1\":\"%d\",\"para2\": \"PUL-TH\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"PUL-U\", \"value1\":\"%d\",\"para2\": \"PUL-D\",\"value2\":\"%d\"},\n"
                    "{\"para1\":\"ES-BASE\", \"value1\":\"%d\",\"para2\": \"NULL\",\"value2\":\"NULL\"}]",
            t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINA1,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINA2,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINB1,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINB2,\
            t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINC1,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINC2,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WIND1,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WIND2,\
            t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINE1,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_WINE2,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_CT,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_ST,\
            t_YangP_Mysql.t_Fpga_Set->Fpga_Set_TH, t_YangP_Mysql.t_Fpga_Set->Fpga_Set_P_th ,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_P_max,t_YangP_Mysql.t_Fpga_Set->Fpga_Set_P_th,\
            t_YangP_Mysql.t_Fpga_Set->Fpga_Set_BaseL);
    fputs(execsql,F_fd);
    fclose(F_fd);

    return 0;
}


int read_ad1115(void)
{
    unsigned int ret = 0;
    unsigned int num = 0;
    char execsql[1024] = {0};
    float flow_p[20] = {0};
    MYSQL_RES 				*res;
    MYSQL_ROW 				row;

    mysql_select_db(&mysql_conn, "ARM_SET");
    sprintf(execsql,"select * from AD1115");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //		printf("%s ",row[t]);	// 输出每列的数据
                flow_p[num]=atof(row[num]);
                //MYSQL_LOG("%f\n",flow_p[num]);
            }
            if(flow_p[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Ad1115.Ad1115_Pre_a     =	(int)flow_p[1];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Ad1115.Ad1115_Pre_b     =	(int)flow_p[2];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Ad1115.Ad1115_DP_a      =	(int)flow_p[3];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Ad1115.Ad1115_DP_b      =	(int)flow_p[4];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Ad1115.Ad1115_PreT_a    =	(int)flow_p[5];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Ad1115.Ad1115_PreT_b    =	(int)flow_p[6];
            }
//			printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }
    return 0;

}


int read_adjust(void)
{
    unsigned int ret = 0;
    unsigned int num = 0;
    char execsql[1024] = {0};
    float flow_p[20] = {0};
    MYSQL_RES 				*res;
    MYSQL_ROW 				row;

    mysql_select_db(&mysql_conn, "ARM_SET");
    sprintf(execsql,"select * from Adjust");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //		printf("%s ",row[t]);	// 输出每列的数据
                flow_p[num]=atof(row[num]);
                //MYSQL_LOG("%f\n",flow_p[num]);
            }
            if(flow_p[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Arm_Mysql->t_ARM_Adjust.Adjust_WinB_a		=	flow_p[1];
                t_YangP_Mysql.t_Arm_Mysql->t_ARM_Adjust.Adjust_WinB_b		=	flow_p[2];
                t_YangP_Mysql.t_Arm_Mysql->t_ARM_Adjust.Adjust_WinC_a		=	flow_p[3];
                t_YangP_Mysql.t_Arm_Mysql->t_ARM_Adjust.Adjust_WinC_b		=	flow_p[4];
                t_YangP_Mysql.t_Arm_Mysql->t_ARM_Adjust.Adjust_WinE_a		=	flow_p[5];
                t_YangP_Mysql.t_Arm_Mysql->t_ARM_Adjust.Adjust_WinE_b		=	flow_p[6];
            }
//			printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }
    return 0;

}

int read_arm_para(void)
{
    unsigned int ret = 0;
    unsigned int num = 0;
    char execsql[1024] = {0};
    int spi_set[26] = {0};
    MYSQL_RES 				*res;
    MYSQL_ROW 				row;
    mysql_select_db(&mysql_conn, "ARM_SET");
    sprintf(execsql,"select * from ARM_SET");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //		printf("%s ",row[t]);	// 输出每列的数据
                spi_set[num]=atoi(row[num]);
                //MYSQL_ERROR("%d\n",spi_set[num]);
            }
            if(spi_set[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_flag             = spi_set[1];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_hv               = spi_set[2];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_vbb              = spi_set[3];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_hv_c             = (float)((float)spi_set[4]/100.0);
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_A1           = spi_set[5];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_A2           = spi_set[6];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_PEAK_A           = spi_set[7];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_B1           = spi_set[8];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_B2           = spi_set[9];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_PEAK_B           = spi_set[10];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_C1           = spi_set[11];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_C2           = spi_set[12];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_PEAK_C           = spi_set[13];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_D1           = spi_set[14];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_D2           = spi_set[15];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_PEAK_D           = spi_set[16];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_E1           = spi_set[17];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_CON_E2           = spi_set[18];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_PEAK_E           = spi_set[19];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_th_sum           = spi_set[20];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_board_type       = spi_set[21];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_set_reality_b1       = spi_set[22];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_set_reality_b2       = spi_set[23];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_set_reality_e1       = spi_set[24];
                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_set_reality_e2       = spi_set[25];

                MYSQL_LOG("Arm_Set_hv_c %f %d %d\n" ,t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_hv_c,
                          t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_vbb,
                        t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_Set_hv);
//                t_YangP_Mysql.t_Arm_Mysql->t_Arm_Set.Arm_set_flag_modbus	=	spi_set[1]	&0x01;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.flag_log		=	spi_set[1]	&0x02;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.flag_es		=	spi_set[1]	&0x04;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.HIV_en		=	spi_set[1]	&0x08;//改为是否自动调压 8为自动调整；
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.flag_5ms		=	spi_set[1]	&0x10;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.F_WIN_en	    =	spi_set[1]	&0x20;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.flag_dog		=	spi_set[1]	&0x40;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.OLED_en		=	spi_set[1]	&0x80;
//                t_Mysql.t_Arm_Mysql->t_Arm_Set.flag_1s		=	spi_set[1]	&0x100;

            }
//			printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }
    /*
     * 数据处理
     */


//   t_Mysql.t_Arm_Mysql->t_Arm_Set.a1 = (t_Mysql.t_Arm_Mysql->t_Arm_Set.S_PCH81 - t_Mysql.t_Arm_Mysql->t_Arm_Set.S_PCH31)/(81.0 - 31.0);
//    t_Mysql.t_Arm_Mysql->t_Arm_Set.b1 = t_Mysql.t_Arm_Mysql->t_Arm_Set.S_PCH31 - 31* t_Mysql.t_Arm_Mysql->t_Arm_Set.a1;
//    MYSQL_LOG("a1=%f,b1=%f\n",t_Mysql.t_Arm_Mysql->t_Arm_Set.a1,t_Mysql.t_Arm_Mysql->t_Arm_Set.b1);

    return 0;
}

int read_flow_para(void)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int ret = 0;
    unsigned int num = 0;
    char execsql[1024] = {0};
    float flow_p[40] = {0};
    char flow_ota[10][30];

    mysql_select_db(&mysql_conn, "FLOW_Para");
    sprintf(execsql,"select * from freemodbus");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //		printf("%s ",row[t]);	// 输出每列的数据
                flow_p[num]=atof(row[num]);
                //MYSQL_LOG("%f\n",flow_p[num]);
            }
            if(flow_p[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Flow_para->t_Freemodbus.mode            =	(int)flow_p[1];
                t_YangP_Mysql.t_Flow_para->t_Freemodbus.slaveadd        =	(int)flow_p[2];
                t_YangP_Mysql.t_Flow_para->t_Freemodbus.port            =	(int)flow_p[3];
                t_YangP_Mysql.t_Flow_para->t_Freemodbus.baudrate        =	(int)flow_p[4];
                t_YangP_Mysql.t_Flow_para->t_Freemodbus.parity          =	(int)flow_p[5];
            }
            MYSQL_LOG("mode=%d\n",t_YangP_Mysql.t_Flow_para->t_Freemodbus.mode );
            MYSQL_LOG("slaveadd=%d\n",flow_p[2]);
            MYSQL_LOG("port=%d\n",flow_p[3]);
            MYSQL_LOG("baudrate=%d\n",t_YangP_Mysql.t_Flow_para->t_Freemodbus.baudrate);
            MYSQL_LOG("parity=%d\n",flow_p[5]);
//			printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }

    sprintf(execsql,"select * from ota");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //printf("%s ",row[t]);	// 输出每列的数据
                strcpy(flow_ota[num],row[num]);

                //MYSQL_LOG("%f\n",flow_p[num]);
            }

            strcpy(t_YangP_Mysql.t_Flow_para->t_Ota.ip,flow_ota[1]);
            strcpy(t_YangP_Mysql.t_Flow_para->t_Ota.adds,flow_ota[2]);
            strcpy(t_YangP_Mysql.t_Flow_para->t_Ota.station,flow_ota[3]);
            strcpy(t_YangP_Mysql.t_Flow_para->t_Ota.device,flow_ota[4]);
            strcpy(t_YangP_Mysql.t_Flow_para->t_Ota.port,flow_ota[5]);

//			printf("\n");
            MYSQL_LOG("ip %s=%s\n",t_YangP_Mysql.t_Flow_para->t_Ota.ip,flow_ota[1]);
            MYSQL_LOG("adds %s=%s\n",t_YangP_Mysql.t_Flow_para->t_Ota.adds,flow_ota[2]);
            MYSQL_LOG("station %s=%s\n",t_YangP_Mysql.t_Flow_para->t_Ota.station,flow_ota[3]);
            MYSQL_LOG("device %s=%s\n",t_YangP_Mysql.t_Flow_para->t_Ota.device,flow_ota[4]);
            MYSQL_LOG("port %s=%s\n",t_YangP_Mysql.t_Flow_para->t_Ota.port,flow_ota[5]);
        }
        mysql_free_result(res);										// 释放查询结果
    }

    /*
     *
*/

/*
*
*/
    sprintf(execsql,"select * from FlowMinute");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
//				printf("%s ",row[t]);	// 输出每列的数据
                flow_p[num]=atof(row[num]);
                //MYSQL_LOG("%f\n",flow_p[num]);
            }
            if(flow_p[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.P_CPM_A           =	flow_p[1];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.P_CPM_B           =	flow_p[2];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.DP_CPM_A          =	flow_p[3];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.DP_CPM_B          =	flow_p[4];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.DP_CPM_C          =	flow_p[5];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.DP_CPM_D          =	flow_p[6];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.TF_PCPM_SC        =	flow_p[7];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.P_CPM_SC          =	flow_p[8];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.F_CPM             =	flow_p[9];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.D_CPM             =	flow_p[10];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.G31_CPM_A	        =	flow_p[11];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.G31_CPM_B	        =	flow_p[12];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.W31_CPM           =	flow_p[13];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.G356_CPM_A        =	flow_p[14];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.G356_CPM_B        =	flow_p[15];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.W356_CPM          =	flow_p[16];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.WD_CPM            =	flow_p[17];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.GD_CPM_SC         =	flow_p[18];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.b_CPM             =	flow_p[19];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.C_CPM             =	flow_p[20];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.E_CPM             =	flow_p[21];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.Z_CPM             =	flow_p[22];
                t_YangP_Mysql.t_Flow_para->t_Flow_Minute.reservedF			=	flow_p[23];


            }
//			printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }

/*
*
*/
    sprintf(execsql,"select * from Correction");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //			printf("%s ",row[t]);	// 输出每列的数据
                flow_p[num]=atof(row[num]);
                //MYSQL_LOG("%f\n",flow_p[num]);
            }
            if(flow_p[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.GVF_CPS_A          =	flow_p[1];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.GVF_CPS_B         	=	flow_p[2];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.GMF_CPS_A         	=	flow_p[3];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.GMF_CPS_B         	=	flow_p[4];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.GasMode_A         	=	flow_p[5];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.GasMode_B         	=	flow_p[6];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.Qm_A_n        	    =	flow_p[7];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.Qm_B_n        	    =	flow_p[8];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.K31_Empty         	=	flow_p[9];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.CMP_Ave_n         	=	flow_p[10];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.DP_th         	    =	flow_p[11];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.LMF_th        	    =	flow_p[12];//青白江临时添加
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.Qml_A         	    =	flow_p[13];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.Qml_B         	    =	flow_p[14];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.Qmg_A         	    =	flow_p[15];
                t_YangP_Mysql.t_Flow_para->t_Flow_Correction.Qmg_B         	    =	flow_p[16];

            }
//			printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }

    /*
    *
    */
    sprintf(execsql,"select * from Flow_Result");								//设置将要操作的数据库
    ret = mysql_real_query(&mysql_conn,execsql,strlen(execsql));			// 执行查询语句
    if (ret)
        MYSQL_ERROR("查询数据库失败：%s\n", mysql_error(&mysql_conn));
    else {
        res = mysql_store_result(&mysql_conn);								// 获得查询结果
        while((row = mysql_fetch_row(res))) {								// 在结果集内步进
            for(num = 0; num < mysql_num_fields(res); num++){
                //			printf("%s ",row[t]);	// 输出每列的数据
                flow_p[num]=atof(row[num]);
                //MYSQL_LOG("%f\n",flow_p[num]);
            }
            if(flow_p[0]== 1)                                              //这个位置以后可以设置多组数据用num替换1，判断用那一组参数
            {
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Qmg            = flow_p[1];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Qml            = flow_p[2];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Empty_Year     = (int)flow_p[3];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Empty_Month    = (int)flow_p[4];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Empty_Day      = (int)flow_p[5];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Qvg            = flow_p[6];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Qvl            = flow_p[7];
                t_YangP_Mysql.t_Flow_para->t_Flow_Result.Sctime         = flow_p[8];

            }
//				printf("\n");
        }
        mysql_free_result(res);										// 释放查询结果
    }

    return 0;
}

void read_mysql_all()
{
    read_fpga_setpara();
    read_ad1115();
    read_adjust();
    read_arm_para();
    read_flow_para();
}