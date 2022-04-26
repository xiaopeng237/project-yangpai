//
// Created by Administrator on 2020/4/21.
//
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "ota_data_base.h"
#include "yangpi_ota_stub.h"
#include "curl/curl.h"
#include "yangpi_mysql_proxy.h"

pthread_t thread_send;
pthread_attr_t attribute_send;
pthread_mutex_t send_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  send_cond = PTHREAD_COND_INITIALIZER;

T_OtaSendLog tOtaSendLog;
T_Flow_para tFlow_para;

char ota_send_flag = 0;

//char url_path[200];
char url_path[100];//="http://yangpai06.51vip.biz:3001/bseries/ys118/001";
//pthread_t thread_storage;
//pthread_attr_t attribute_storage;
//pthread_mutex_t storage_mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t  storage_cond = PTHREAD_COND_INITIALIZER;

void ota_send(HStub stub, T_OtaSendLog *zdb_T_OtaSendLog)
{
    memcpy(&tOtaSendLog,zdb_T_OtaSendLog, sizeof(T_OtaSendLog));
    ota_send_flag = 1;
    pthread_cond_signal(&send_cond);//计算要考虑i2c数据时效性，所以采用条件变量。保证spi和i2c数据是1S前的
    printf("ota_send\n");
}
void init_stub_yangpi_ota(tInterfaceStub_yangpi_ota *stub)
{
    stub->ota_send = ota_send;
}

void mysql_incept_all(HProxy proxy, T_Arm_Mysql *zdb_T_Arm_Mysql, T_Fpga_Set *zdb_T_Fpga_Set, T_Flow_para *zdb_T_Flow_para) {
    memcpy(&tFlow_para, zdb_T_Flow_para, sizeof(T_Flow_para));
    sprintf(url_path,"http://%s:%s/%s/%s/%s",tFlow_para.t_Ota.ip,tFlow_para.t_Ota.port,tFlow_para.t_Ota.adds,tFlow_para.t_Ota.station,tFlow_para.t_Ota.device);
    printf("ota_ready2\n");
    printf("%s\n",url_path);
}
void init_client_yangpi_mysql(tInterfaceClient_yangpi_mysql *client) {
    client->on_signal_incept_all = mysql_incept_all;
}


static size_t _write_data(char *ptr, size_t size, size_t nmemb, void *stream)
{
    strcat(stream, (char *)ptr);
    puts(stream);
    return size*nmemb;
}

size_t (*write_data)(char *ptr, size_t size,size_t nmemb, void *stream) = &_write_data;



void *send_function(void* a)
{
    CURL *curl;
    static char str[2048];
    char execsql[4096] = {0};
    char write_log_time[20] = {0};
    int num_logg = 0;

    while(1)
    {
        memset(str,0,2048);
        pthread_mutex_lock(&send_mutex);
        while (0 == ota_send_flag ) {
            pthread_cond_wait(&send_cond, &send_mutex);
        }
        ota_send_flag = 0;

        pthread_mutex_unlock(&send_mutex);

        num_logg++;
        printf(" num_logg %d \n",num_logg);

        sprintf(write_log_time,"%.2d:%.2d",tOtaSendLog.write_log_hour,tOtaSendLog.write_log_minute);
        sprintf(execsql,"{\"num\":\"%d\",\"time\":\"%s\",\"Qmg\":\"%f\",\"Qml\":\"%f\",\"Qvg\":\"%f\",\"Qvl\":\"%f\",\"GMF\":\"%f\",\"LMF\":\"%f\",\"Qvg_Cumulative\":\"%f\",\"Qvl_Cumulative\":\"%f\",\"31keV\":\"%d\","
                        "\"81keV\":\"%d\",\"356keV\":\"%d\",\"Tem\":\"%f\",\"P\":\"%f\",\"DP\":\"%f\",\"31keV_Peak\":\"%d\",\"81keV_Peak\":\"%d\",\"356kev_Peak\":\"%d\",\"Tem_in\":\"%f\",\"Tem_DP\":\"%f\",\"HV\":\"%d\",\"BU\":\"%d\","
                        "\"BD\":\"%d\",\"CU\":\"%d\",\"CD\":\"%d\",\"EU\":\"%d\",\"ED\":\"%d\",\"LVF_CPM\":\"%f\",\"GVF_CPM\":\"%f\",\"Qv_CPM\":\"%f\",\"LMF_CPM\":\"%f\",\"GMF_CPM\":\"%f\",\"Qm_CPM\":\"%f\"}",
                num_logg,write_log_time,
                tOtaSendLog.write_log_Qmg,
                tOtaSendLog.write_log_Qml,
                tOtaSendLog.write_log_Qvg,
                tOtaSendLog.write_log_Qvl,
                tOtaSendLog.write_log_GMF,
                tOtaSendLog.write_log_LMF,
                tOtaSendLog.write_log_Qvg_Cumulative,
                tOtaSendLog.write_log_Qvl_Cumulative,
                tOtaSendLog.write_log_31keV,
                tOtaSendLog.write_log_81keV,
                tOtaSendLog.write_log_356keV,
                tOtaSendLog.write_log_Tem,
                tOtaSendLog.write_log_P,
                tOtaSendLog.write_log_DP,
                tOtaSendLog.write_log_31keV_Peak,
                tOtaSendLog.write_log_81keV_Peak,
                tOtaSendLog.write_log_356kev_Peak,
                tOtaSendLog.write_log_Tem_in,
                tOtaSendLog.write_log_Tem_DP,
                tOtaSendLog.write_log_HV,
                tOtaSendLog.write_log_BU,
                tOtaSendLog.write_log_BD,
                tOtaSendLog.write_log_CU,
                tOtaSendLog.write_log_CD,
                tOtaSendLog.write_log_EU,
                tOtaSendLog.write_log_ED,
                tOtaSendLog.write_log_LVF_CPM,
                tOtaSendLog.write_log_GVF_CPM,
                tOtaSendLog.write_log_Qv_CPM,
                tOtaSendLog.write_log_LMF_CPM,
                tOtaSendLog.write_log_GMF_CPM,
                tOtaSendLog.write_log_Qm_CPM
        );

        printf(" %s \n",execsql);
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url_path);

        struct curl_slist *pList = NULL;
        pList = curl_slist_append(pList,"Content-Type:application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, pList);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, execsql);//这是post的内容
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//数据请求到以后的回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, str);//选择输出到字符串
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);    /*timeout 30s,add by edgeyang*/
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);    /*no signal,add by edgeyang*/
        curl_easy_perform(curl); /* ignores error */
        curl_easy_cleanup(curl);
//        printf("%s\n",url_path);
    }

}

void main_start()
{
    curl_global_init(CURL_GLOBAL_ALL);

//    sprintf(url_path,"%s");
    pthread_attr_init(&attribute_send);
    pthread_attr_setdetachstate(&attribute_send, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_send, &attribute_send, send_function, NULL);

}