//
// Created by Administrator on 2020/4/21.
//

#ifndef BUILDROOT_PROJECT_OTA_DATA_BASE_H
#define BUILDROOT_PROJECT_OTA_DATA_BASE_H

typedef struct{

}T_OtaBeginDay,T_OtaEndDay;

typedef struct{
    int         write_log_year;
    int         write_log_month;
    int         write_log_date;
    int         write_log_hour;
    int         write_log_minute;
    int			write_log_write_log_num;
//    char        write_log_time[20];
    double		write_log_Qmg;
    double		write_log_Qml;
    double		write_log_Qvg;
    double		write_log_Qvl;
    double		write_log_GMF;
    double		write_log_LMF;
    double		write_log_Qvg_Cumulative;
    double		write_log_Qvl_Cumulative;
    int			write_log_31keV;
    int			write_log_81keV;
    int			write_log_356keV;
    double		write_log_Tem;
    double		write_log_P;
    double		write_log_DP;
    int			write_log_31keV_Peak;
    int			write_log_81keV_Peak;
    int			write_log_356kev_Peak;
    double		write_log_Tem_in;
    double		write_log_Tem_DP;
    int			write_log_HV;
    int			write_log_BU;
    int			write_log_BD;
    int			write_log_CU;
    int			write_log_CD;
    int			write_log_EU;
    int			write_log_ED;
    double		write_log_LVF_CPM;
    double		write_log_GVF_CPM;
    double		write_log_Qv_CPM;
    double		write_log_LMF_CPM;
    double		write_log_GMF_CPM;
    double		write_log_Qm_CPM;
}T_OtaSendLog;

typedef struct{

}T_OtaDownloadInfo;
#endif //BUILDROOT_PROJECT_OTA_DATA_BASE_H
