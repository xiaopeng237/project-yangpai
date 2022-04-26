//
// Created by Administrator on 2020/4/29.
//


#include <dbus/dbus.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "yangpi_rtu_stub.h"
#include "rtu_service.h"
#include "yangpi_mysql_proxy.h"
pthread_t thread_modbus;
pthread_attr_t attribute_modbus;
pthread_mutex_t mutex_modbus = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_modbus = PTHREAD_COND_INITIALIZER;
int flages_data_ready = 0;

T_Flow_para tFlow_para;

void mysql_incept_all(HProxy proxy, T_Arm_Mysql *zdb_T_Arm_Mysql, T_Fpga_Set *zdb_T_Fpga_Set, T_Flow_para *zdb_T_Flow_para) {
    memcpy(&tFlow_para, zdb_T_Flow_para, sizeof(T_Flow_para));
    flages_data_ready = 1;
    pthread_cond_signal(&cond_modbus);
//    printf("%d %d %d %d %d\n",tFlow_para.t_Freemodbus.port,tFlow_para.t_Freemodbus.parity,tFlow_para.t_Freemodbus.baudrate,tFlow_para.t_Freemodbus.slaveadd,tFlow_para.t_Freemodbus.mode);
}

void rtusetdata(HStub stub, T_RtuData *zdb_T_RtuData)
{
    setShare_rtu(zdb_T_RtuData);
}
void init_stub_yangpi_rtu(tInterfaceStub_yangpi_rtu *stub)
{
    stub->rtu_setdata = rtusetdata;

}
void init_client_yangpi_mysql(tInterfaceClient_yangpi_mysql *client) {
    client->on_signal_incept_all = mysql_incept_all;
}

void *fmb_pthread(void* a)
{
    char *argv[] = {"a", "e"};
    while(1)
    {
        pthread_mutex_lock(&mutex_modbus);
        while (0 == flages_data_ready) {
            pthread_cond_wait(&cond_modbus, &mutex_modbus);
        }
        flages_data_ready = 0;
        pthread_mutex_unlock(&mutex_modbus);

        freeModbusInit(2, argv);

        pthread_exit(NULL);
    }

    return 0;
}
void main_start()
{
    char *argv[] = {"a", "e"};
    pthread_attr_init(&attribute_modbus);
    pthread_attr_setdetachstate(&attribute_modbus, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_modbus, &attribute_modbus, fmb_pthread, NULL);
}