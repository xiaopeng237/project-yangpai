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

int function_web_spectral_data_write(void);
int function_dd_set_sw_time(void);
void function_dd_get_spi_win_from_fpga(void);
void function_calculate_flow_main(void);
void function_dd_adjust_win(void);
int function_dd_get_spi_pull_from_fpga(void);
int function_dd_get_spi_energy_from_fpga(void);

int function_msql_to_apache(void);
void function_web_calculate_para_write(void);
int function_web_pulse_data_write(void);
void function_dd_energy_spectrum_errorCode(void);
extern void function_dd_get_sw_time(T_DateTime* DataTime);

/***************************以下为GPIO相关操作接口******************************/
int function_dd_gpio_export(int pin);
int function_dd_gpio_edge(int pin, int edge);
int function_dd_gpio_write(int pin, int value);
int function_dd_gpio_direction(int pin, int dir);

#endif //PROJECT_PINEERS_PIONEERS_SERVICE_H
