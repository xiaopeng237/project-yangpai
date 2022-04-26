//
// Created by Administrator on 2020/3/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "mysql.h"
#include "mysql_service.h"
#include "yangpi_mysql_stub.h"
#include "log_dlt.h"
#include "read_mysql.h"

extern HStub STUB_yangpi_mysql;

MYSQL mysql_conn;

pthread_t write_thread;
pthread_attr_t write_attribute;
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  write_cond = PTHREAD_COND_INITIALIZER;


pthread_t read_thread;
pthread_attr_t read_attribute;
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  read_cond = PTHREAD_COND_INITIALIZER;

int flag_write_ready_log = 0;
int flag_write_ready_result = 0;
int flag_write_ready_es = 0;
int flag_read_ready_log = 0;

pthread_mutex_t write_ready_mutex = PTHREAD_MUTEX_INITIALIZER;
int flag_write_ready = 0;

T_Write_Mysql_Log       t_Write_Mysql_Log;
T_Write_Flow_Result     t_Write_Flow_Result;
T_YangP_Mysql           t_YangP_Mysql;
T_Write_ES              t_Write_Es;
void *read_log_thread_function(void* a)
{
#if 0
    for(;;) {
        pthread_mutex_lock(&read_mutex);

        while (0 == flag_read_ready_log) {
            pthread_cond_wait(&read_cond, &read_mutex);
        }

        flag_read_ready_log = 0;

        pthread_mutex_unlock(&read_mutex);

        pthread_mutex_lock(&write_ready_mutex);
        while(flag_write_ready == 1)
        {
            pthread_mutex_unlock(&write_ready_mutex);
            sleep(1);
            pthread_mutex_lock(&write_ready_mutex);
        }




        pthread_mutex_unlock(&write_ready_mutex);
        MYSQL_LOG("flag_read_ready_log \n");
    }
#endif
}

void yp_mysql_query(MYSQL *mysql_conn,char *str_db,char *str_cmd)
{
    if(mysql_query(mysql_conn,str_cmd))
    {
        MYSQL_ERROR("指令输入错误，重新执行，%s %s",mysql_error(mysql_conn),str_cmd);

        mysql_close(mysql_conn);

        if (mysql_init(mysql_conn) == NULL)
        {
            MYSQL_ERROR("指令输入错误，重新执行，Initialization Failed.\n");
            MYSQL_ERROR("致命错误，无法修复\n");
            return;
        }

        if (mysql_real_connect(mysql_conn, "localhost", "root", "root", NULL, MYSQL_PORT, NULL, 0) == NULL)//链接一个mysql数据库
        {
            MYSQL_ERROR("指令输入错误，重新执行，MYSQL Connection Failed!\n");
            MYSQL_ERROR("致命错误，无法修复\n");
            return;
        }
        mysql_select_db(mysql_conn, str_db);
        if(mysql_query(mysql_conn,str_cmd))
        {
            MYSQL_ERROR("致命错误，无法修复\n");
        }
    }
}

int write_es_data(void)
{

    int i;
    static int esnum;
    char execsql[2048];
    static int esmysql_year;
    static int esmysql_month;
    static int esmysql_day;
    static int esmysql_hour;
    static int esmysql_minute;


    //创建文件夹     判断年月
    if((esmysql_year != t_Write_Es.write_log_year)||(esmysql_month != t_Write_Es.write_log_month))
    {

        sprintf(execsql,"create database es%4d_%.2d",t_Write_Es.write_log_year,t_Write_Es.write_log_month);

        mysql_real_query(&mysql_conn, execsql, strlen(execsql));//执行查询语句：创建数据库
        i = mysql_affected_rows(&mysql_conn);
        if (i<=0){
            MYSQL_LOG("Can not create database\n");
        }
    }


    //创建数据表格   判断日期
    if((esmysql_year != t_Write_Es.write_log_year)||(esmysql_month != t_Write_Es.write_log_month)||(esmysql_day != t_Write_Es.write_log_date)||(esmysql_hour != t_Write_Es.write_log_hour)||(esmysql_minute != t_Write_Es.write_log_minute))
    {
        sprintf(execsql,"es%4d_%.2d",t_Write_Es.write_log_year,t_Write_Es.write_log_month);

        mysql_select_db(&mysql_conn, execsql);//设置要操作的数据库
        sprintf(execsql, "create table es%4d_%.2d_%.2d_%.2d_%.2d(num char(30), es int(16))",t_Write_Es.write_log_year,t_Write_Es.write_log_month,t_Write_Es.write_log_date,t_Write_Es.write_log_hour,t_Write_Es.write_log_minute);//以年月日为名字
        MYSQL_LOG("write_es_data %s\n",execsql);
        mysql_real_query(&mysql_conn, execsql, strlen(execsql));
        esnum = 0;

    }
    //数据填充
    for(i=0;i<8192;i++)
    {

        sprintf(execsql,"insert into es%4d_%.2d_%.2d_%.2d_%.2d values('%d',%d)",t_Write_Es.write_log_year,t_Write_Es.write_log_month,t_Write_Es.write_log_date,t_Write_Es.write_log_hour,t_Write_Es.write_log_minute,i ,t_Write_Es.EnergyS[i]);
        mysql_query(&mysql_conn, execsql);
        esnum++;
    }


    esmysql_year 	= 	t_Write_Es.write_log_year;
    esmysql_month	=	t_Write_Es.write_log_month;
    esmysql_day		=	t_Write_Es.write_log_date;
    esmysql_hour	=	t_Write_Es.write_log_hour;
    esmysql_minute	=	t_Write_Es.write_log_minute;
    MYSQL_LOG("write_es_data \n");
    return 0;
}

void *write_log_thread_function(void* a)
{
    char execsql[2048] = {0};
    char execsql_db[512] = {0};
    char write_log_time[20] = {0};
    int mysql_year_log = 0;
    int mysql_month_log = 0;
    int mysql_date_log = 0;
    int num_logg = 0;

    int ret = 0;

    sleep(1);
    yangpi_mysql_signal_incept_all(STUB_yangpi_mysql, t_YangP_Mysql.t_Arm_Mysql, t_YangP_Mysql.t_Fpga_Set, t_YangP_Mysql.t_Flow_para);
    for(;;)
    {
        pthread_mutex_lock(&write_mutex);

        while( 0 == flag_write_ready_log && 0 == flag_write_ready_result && 0 == flag_read_ready_log && 0 == flag_write_ready_es)
        {
            pthread_cond_wait(&write_cond, &write_mutex);
        }

//        pthread_mutex_lock(&write_ready_mutex);
//        flag_write_ready = 1;
//        pthread_mutex_unlock(&write_ready_mutex);

        memset(write_log_time,0,20);
        memset(execsql,0,2048);

        if(flag_read_ready_log == 1)
        {
            flag_read_ready_log = 0;
            read_mysql_all();
            yangpi_mysql_signal_incept_all(STUB_yangpi_mysql, t_YangP_Mysql.t_Arm_Mysql, t_YangP_Mysql.t_Fpga_Set, t_YangP_Mysql.t_Flow_para);
        }

        if(flag_write_ready_result == 1)
        {
            mysql_select_db(&mysql_conn, "FLOW_Para");

            sprintf(execsql," update Flow_Result set Qmg='%f' where id=1",t_Write_Flow_Result.Write_FR_Qmg_CPM);
            yp_mysql_query(&mysql_conn, "FLOW_Para", execsql);

            sprintf(execsql," update Flow_Result set Qml='%f' where id=1",t_Write_Flow_Result.Write_FR_Qml_CPM);
            yp_mysql_query(&mysql_conn, "FLOW_Para", execsql);

            sprintf(execsql," update Flow_Result set sctime='%f' where id=1",t_Write_Flow_Result.Write_FR_Add_Sctime);
            yp_mysql_query(&mysql_conn, "FLOW_Para", execsql);

            flag_write_ready_result = 0;
        }



        if(flag_write_ready_log == 1)
        {
            memset(write_log_time,0,20);
            memset(execsql,0,2048);

            sprintf(write_log_time,"%.2d:%.2d",t_Write_Mysql_Log.write_log_hour,t_Write_Mysql_Log.write_log_minute);

            //创建文件夹     判断年月ri
            if((mysql_year_log != t_Write_Mysql_Log.write_log_year)||(mysql_month_log != t_Write_Mysql_Log.write_log_month))
            {
                sprintf(execsql,"create database %4d_%.2d_log",t_Write_Mysql_Log.write_log_year,t_Write_Mysql_Log.write_log_month);
                MYSQL_LOG("%s \n", execsql);
                mysql_real_query(&mysql_conn, execsql, strlen(execsql));//执行查询语句：创建数据库
                ret = mysql_affected_rows(&mysql_conn);
                if (ret<=0){
                    MYSQL_ERROR("Can not create log database\n");
                }
            }

            MYSQL_LOG("new %d %d %d\n",t_Write_Mysql_Log.write_log_year,t_Write_Mysql_Log.write_log_month,t_Write_Mysql_Log.write_log_date);
            MYSQL_LOG("pld %d %d %d\n",mysql_year_log,mysql_month_log,mysql_date_log);


            //创建数据表格   判断日期
            if((mysql_year_log != t_Write_Mysql_Log.write_log_year)||(mysql_month_log != t_Write_Mysql_Log.write_log_month)||(mysql_date_log != t_Write_Mysql_Log.write_log_date))
            {
                num_logg=0;
                sprintf(execsql,"%4d_%.2d_log",t_Write_Mysql_Log.write_log_year,t_Write_Mysql_Log.write_log_month);
                MYSQL_LOG("%s \n", execsql);
                mysql_select_db(&mysql_conn, execsql);//设置要操作的数据库
                sprintf(execsql, "create table %4d_%.2d_%.2d(num char(30),time char(20),Qmg float(32),Qml float(32),"
                                 "Qvg float(32),Qvl float(32),GMF float(32),LMF float(32),Qvg_Cumulative float(32),Qvl_Cumulative float(16),31keV int(16),"
                                 "81keV int(16),356keV int(16),Tem float(32),P float(32),DP float(32),31keV_Peak int(16),"
                                 "81keV_Peak int(16),356kev_Peak int(16),Tem_in float(32),Tem_DP float(32),HV int(16),BU int(16),BD int(16),"
                                 "CU int(16),CD int(16),EU int(16),ED int(16),LVF_CPM float(32),GVF_CPM float(32),Qv_CPM float(32),"
                                 "LMF_CPM float(32),GMF_CPM float(32),Qm_CPM float(32))",
                        t_Write_Mysql_Log.write_log_year,t_Write_Mysql_Log.write_log_month,t_Write_Mysql_Log.write_log_date);//以年月日为名字
                MYSQL_LOG("%s \n", execsql);
                mysql_real_query(&mysql_conn, execsql, strlen(execsql));
            }
            else
            {
                sprintf(execsql_db,"%4d_%.2d_log",mysql_year_log,mysql_month_log);
                mysql_select_db(&mysql_conn, execsql_db);//设置要操作的数据库
                MYSQL_LOG("%s \n", execsql_db);
            }
            num_logg++;
#if 1
            sprintf(execsql,"insert into %4d_%.2d_%.2d values('%d','%s',%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f,%f,%f,%d,%d,%d,%f,%f,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f)",
                    t_Write_Mysql_Log.write_log_year,t_Write_Mysql_Log.write_log_month,t_Write_Mysql_Log.write_log_date,
                    num_logg,write_log_time,
                    t_Write_Mysql_Log.write_log_Qmg,
                    t_Write_Mysql_Log.write_log_Qml,
                    t_Write_Mysql_Log.write_log_Qvg,
                    t_Write_Mysql_Log.write_log_Qvl,
                    t_Write_Mysql_Log.write_log_GMF,
                    t_Write_Mysql_Log.write_log_LMF,
                    t_Write_Mysql_Log.write_log_Qvg_Cumulative,
                    t_Write_Mysql_Log.write_log_Qvl_Cumulative,
                    t_Write_Mysql_Log.write_log_31keV,
                    t_Write_Mysql_Log.write_log_81keV,
                    t_Write_Mysql_Log.write_log_356keV,
                    t_Write_Mysql_Log.write_log_Tem,
                    t_Write_Mysql_Log.write_log_P,
                    t_Write_Mysql_Log.write_log_DP,
                    t_Write_Mysql_Log.write_log_31keV_Peak,
                    t_Write_Mysql_Log.write_log_81keV_Peak,
                    t_Write_Mysql_Log.write_log_356kev_Peak,
                    t_Write_Mysql_Log.write_log_Tem_in,
                    t_Write_Mysql_Log.write_log_Tem_DP,
                    t_Write_Mysql_Log.write_log_HV,
                    t_Write_Mysql_Log.write_log_BU,
                    t_Write_Mysql_Log.write_log_BD,
                    t_Write_Mysql_Log.write_log_CU,
                    t_Write_Mysql_Log.write_log_CD,
                    t_Write_Mysql_Log.write_log_EU,
                    t_Write_Mysql_Log.write_log_ED,
                    t_Write_Mysql_Log.write_log_LVF_CPM,
                    t_Write_Mysql_Log.write_log_GVF_CPM,
                    t_Write_Mysql_Log.write_log_Qv_CPM,
                    t_Write_Mysql_Log.write_log_LMF_CPM,
                    t_Write_Mysql_Log.write_log_GMF_CPM,
                    t_Write_Mysql_Log.write_log_Qm_CPM
            );
#endif

            yp_mysql_query(&mysql_conn, execsql_db,execsql);
            MYSQL_LOG(" %s\n",execsql);

            mysql_year_log 	= t_Write_Mysql_Log.write_log_year;
            mysql_month_log	= t_Write_Mysql_Log.write_log_month;
            mysql_date_log	= t_Write_Mysql_Log.write_log_date;

            flag_write_ready_log = 0;
        }


        if(flag_write_ready_es = 1)
        {
            flag_write_ready_es = 0;
            write_es_data();
        }

//        pthread_mutex_lock(&write_ready_mutex);
//        flag_write_ready = 0;
//        pthread_mutex_unlock(&write_ready_mutex);


        pthread_mutex_unlock(&write_mutex);
    }

}


void Write_Mysql_Log(HStub stub, T_Write_Mysql_Log *zdb_T_Write_Mysql_Log)
{
    //todo:写入数据库
    memcpy(&t_Write_Mysql_Log,zdb_T_Write_Mysql_Log, sizeof(T_Write_Mysql_Log));

    pthread_mutex_lock(&write_ready_mutex);
    pthread_mutex_lock(&write_mutex);

    flag_write_ready_log = 1;
    MYSQL_LOG("t_Write_Mysql_Log.write_log_date %f %f \n",t_Write_Mysql_Log.write_log_Qvg_Cumulative,t_Write_Mysql_Log.write_log_Qvl_Cumulative);
    pthread_cond_signal(&write_cond);

    pthread_mutex_unlock(&write_mutex);
    pthread_mutex_unlock(&write_ready_mutex);
}
void Write_Flow_Result(HStub stub, T_Write_Flow_Result *zdb_T_Write_Flow_Result)
{
    //todo:写入数据库
    memcpy(&t_Write_Flow_Result,zdb_T_Write_Flow_Result, sizeof(T_Write_Flow_Result));

    pthread_mutex_lock(&write_ready_mutex);
    pthread_mutex_lock(&write_mutex);

    flag_write_ready_result = 1;
    pthread_cond_signal(&write_cond);
    MYSQL_LOG("Write_Flow_Result\n");

    pthread_mutex_unlock(&write_mutex);
    pthread_mutex_unlock(&write_ready_mutex);
}
void writeES(HStub stub, T_Write_ES *zdb_T_Write_ES)
{
    memcpy(&t_Write_Es,zdb_T_Write_ES, sizeof(T_Write_ES));
    flag_write_ready_es = 1;
    pthread_cond_signal(&write_cond);
    MYSQL_LOG("writeES \n");
}
void request_all(HStub stub)
{
//    yangpi_mysql_signal_incept_all(stub, t_YangP_Mysql.t_Arm_Mysql, t_YangP_Mysql.t_Fpga_Set, t_YangP_Mysql.t_Flow_para);

    pthread_mutex_lock(&write_ready_mutex);
    pthread_mutex_lock(&write_mutex);

    flag_read_ready_log = 1;
    //pthread_cond_signal(&read_cond);
    pthread_cond_signal(&write_cond);
    MYSQL_LOG("request_all\n");

    pthread_mutex_unlock(&write_mutex);
    pthread_mutex_unlock(&write_ready_mutex);
}

void init_stub_yangpi_mysql(tInterfaceStub_yangpi_mysql *stub)
{
    stub->writelog = Write_Mysql_Log;
    stub->writeflow = Write_Flow_Result;
    stub->writeES = writeES;
    stub->request_all = request_all;
}



void main_start()
{
    t_YangP_Mysql.t_Arm_Mysql = malloc(sizeof(T_Arm_Mysql));
    t_YangP_Mysql.t_Fpga_Set  = malloc(sizeof(T_Fpga_Set));
    t_YangP_Mysql.t_Flow_para = malloc(sizeof(T_Flow_para));


    //初始化mysql结构
    //*********************************
    if (mysql_init(&mysql_conn) == NULL)
    {
        MYSQL_ERROR("Initialization Failed.\n");
        return;
    }


    if (mysql_real_connect(&mysql_conn, "localhost", "root", "root", NULL, MYSQL_PORT, NULL, 0) == NULL)//链接一个mysql数据库
    {
        MYSQL_ERROR("MYSQL Connection Failed!\n");
        return;
    }


    read_mysql_all();
    yangpi_mysql_signal_incept_all(STUB_yangpi_mysql, t_YangP_Mysql.t_Arm_Mysql, t_YangP_Mysql.t_Fpga_Set, t_YangP_Mysql.t_Flow_para);
    MYSQL_LOG("main_start ok! \n");

    pthread_attr_init(&write_attribute);
    pthread_attr_setdetachstate(&write_attribute, PTHREAD_CREATE_DETACHED);
    pthread_create(&write_thread, &write_attribute, write_log_thread_function, NULL);

    //预留未使用
    pthread_attr_init(&read_attribute);
    pthread_attr_setdetachstate(&read_attribute, PTHREAD_CREATE_DETACHED);
    pthread_create(&read_thread, &read_attribute, read_log_thread_function, NULL);

//    flag_read_ready_log = 1;
//    pthread_cond_signal(&read_cond);

}