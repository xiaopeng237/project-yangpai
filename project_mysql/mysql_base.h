//
// Created by Administrator on 2020/3/25.
//

#ifndef TMP_MYSQL_MYSQL_BASE_H
#define TMP_MYSQL_MYSQL_BASE_H

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
}T_Write_Mysql_Log;

typedef struct {
    double       Write_FR_Qmg_CPM;
    double       Write_FR_Qml_CPM;
    double       Write_FR_Add_Sctime;
}T_Write_Flow_Result;

typedef struct {
    int         write_log_year;
    int         write_log_month;
    int         write_log_date;
    int         write_log_hour;
    int         write_log_minute;
    unsigned int EnergyS[8192];
}T_Write_ES;

//mysql ARM相关数据
//------------------1115----------------------------//
typedef struct
{
    int  		id;
    int         Ad1115_Pre_a;
    int         Ad1115_Pre_b;
    int         Ad1115_DP_a;
    int         Ad1115_DP_b;
    int         Ad1115_PreT_a;
    int         Ad1115_PreT_b;
}T_Arm_Ad1115;
//------------------Adjust----------------------------//
typedef struct
{
    int  		id;
    double       Adjust_WinB_a;
    double       Adjust_WinB_b;
    double       Adjust_WinC_a;
    double       Adjust_WinC_b;
    double       Adjust_WinE_a;
    double       Adjust_WinE_b;
}T_Arm_Adjust;
//------------------arm_set----------------------------//
typedef struct
{
    int			Arm_Set_flag;
    int			Arm_Set_hv;
    int			Arm_Set_vbb;
    double			Arm_Set_hv_c;
    int			Arm_Set_CON_A1;
    int			Arm_Set_CON_A2;
    int			Arm_Set_PEAK_A;
    int			Arm_Set_CON_B1;
    int			Arm_Set_CON_B2;
    int			Arm_Set_PEAK_B;
    int			Arm_Set_CON_C1;
    int			Arm_Set_CON_C2;
    int			Arm_Set_PEAK_C;
    int			Arm_Set_CON_D1;
    int			Arm_Set_CON_D2;
    int			Arm_Set_PEAK_D;
    int			Arm_Set_CON_E1;
    int			Arm_Set_CON_E2;
    int			Arm_Set_PEAK_E;
    int			Arm_Set_th_sum;
    int			Arm_Set_board_type;
    int         Arm_set_reality_b1;
    int         Arm_set_reality_b2;
    int         Arm_set_reality_e1;
    int         Arm_set_reality_e2;
}T_Arm_Set;

//------------------ARM集合----------------------------//
typedef struct
{
    T_Arm_Ad1115    t_Arm_Ad1115;
    T_Arm_Adjust    t_ARM_Adjust;
    T_Arm_Set       t_Arm_Set;
}T_Arm_Mysql;

//----------------------------------------------//
typedef struct
{
    int			Fpga_Set_PCH;
    int			Fpga_Set_TH;
    int			Fpga_Set_WINA1;
    int			Fpga_Set_WINA2;
    int			Fpga_Set_WINB1;
    int			Fpga_Set_WINB2;
    int			Fpga_Set_WINC1;
    int			Fpga_Set_WINC2;
    int			Fpga_Set_WIND1;
    int			Fpga_Set_WIND2;
    int			Fpga_Set_WINE1;
    int			Fpga_Set_WINE2;
    int			Fpga_Set_ST;
    int			Fpga_Set_CT;
    int			Fpga_Set_P_th;
    int			Fpga_Set_P_min;
    int			Fpga_Set_P_max;
    int			Fpga_Set_BaseL;

}T_Fpga_Set;
//-------------------correction---------------------------//
typedef struct
{
    double		GVF_CPS_A;
    double		GVF_CPS_B;
    double		GMF_CPS_A;
    double		GMF_CPS_B;
    double		GasMode_A;
    double		GasMode_B;
    double		Qm_A_n;
    double		Qm_B_n;
    double		K31_Empty;
    double		CMP_Ave_n;
    double		DP_th;
    double		LMF_th;
    double		Qml_A;
    double		Qml_B;
    double		Qmg_A;
    double		Qmg_B;
}T_Flow_Correction;

//-------------------Result---------------------------//
typedef struct
{
    double      Qmg;
    double      Qml;
    int         Empty_Year;
    int         Empty_Month;
    int         Empty_Day;
    double      Qvg;
    double      Qvl;
    double      Sctime;
}T_Flow_Result;

//-------------------FlowMinute---------------------------//
typedef struct
{
    double       P_CPM_A;		//绝压数值修正系数 数据库读取
    double       P_CPM_B;		//绝压数值修正系数 数据库读取
    double       DP_CPM_A;		//差压数值修正系数 数据库读取
    double       DP_CPM_B;		//差压数值修正系数 数据库读取
    double       DP_CPM_C;		//差压温度补偿 数据库读取
    double       DP_CPM_D;		//差压绝压补偿 数据库读取

    double       TF_PCPM_SC;		//标况华式摄氏度 数据库读取
    double       P_CPM_SC;		//标况压力 数据库读取
    double       F_CPM;			//356/31比值 数据库读取
    double       D_CPM;			//管直径，喉颈位置 数据库读取
    double       G31_CPM_A;
    double       G31_CPM_B;
    double       W31_CPM;		//满水31吸收系数 数据库读取
    double       G356_CPM_A;
    double       G356_CPM_B;
    double       W356_CPM;		//满水356吸收系数 数据库读取
    double       WD_CPM;			//水密度LC 工况；数据库读取
    double       GD_CPM_SC;		//气密度SC 标况；数据库读取
    double       b_CPM;			//贝塔值 数据库读取
    double       C_CPM;			//流出系数 数据库读取
    double       E_CPM;			//流束膨胀系数 数据库读取
    double       Z_CPM;			//流束膨胀系数 数据库读取

    double       reservedF;
}T_Flow_Minute;

//-------------------Three---------------------------//
typedef struct
{
    int     mode;
    int     slaveadd;
    int     port;
    int     baudrate;
    int     parity;

}T_Flow_Freemodbus;

typedef struct
{
    char ip[30];
    char adds[20];
    char station[20];
    char device[8];
    char port[20];
}T_Flow_Ota;

//extern T_Write_Mysql_Log       t_Write_Mysql_Log;
//extern T_Write_Flow_Result     t_Write_Flow_Result;
//-------------------Flow集合---------------------------//
typedef struct
{
    T_Flow_Ota              t_Ota;
    T_Flow_Freemodbus       t_Freemodbus;
    T_Flow_Result           t_Flow_Result;
    T_Flow_Correction       t_Flow_Correction;
    T_Flow_Minute           t_Flow_Minute;
}T_Flow_para;

//--------------------数据库集合------------------------------//
typedef struct
{
    T_Fpga_Set      *t_Fpga_Set;
    T_Arm_Mysql     *t_Arm_Mysql;
    T_Flow_para     *t_Flow_para;
}T_YangP_Mysql;

#endif //TMP_MYSQL_MYSQL_BASE_H
