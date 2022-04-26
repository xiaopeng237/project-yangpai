//
// Created by Administrator on 2020/3/30.
//

#ifndef PROJECT_PINEERS_PIONEERS_SERVICE_H
#define PROJECT_PINEERS_PIONEERS_SERVICE_H

typedef struct
{
    int fd_RTC;
    int year;
    int month;
    int date;
    int hour;
    int day;
    int minute;
    int second;
    long int timestamp;
    long int timestamps[1440];
}T_DateTime;

typedef struct{
    int flag_modbus_en;
    int flag_oled_en;
    int flag_hightV_en;
    int flag_log_en;
    int flag_es_en;
    int flag_win_en;
    int flag_dog_en;
    int flag_5ms_en;
    int flag_1s_en;
}T_RunFlag;
int spectral_data_w(void);
void start_work(void);
int readtime(void);
void get_spi_win(void);
void calculate_flow(void);
void adjust_win(void);
int get_spi_pull(void);
int get_spi_energy(void);
int gpio_export(int pin);
int gpio_edge(int pin, int edge);
int gpio_write(int pin, int value);
int gpio_direction(int pin, int dir);

int write_msql_apache(void);
void calculate_apache_armp();
int pulse_data_w(void);
void errorCode(void);
#endif //PROJECT_PINEERS_PIONEERS_SERVICE_H
