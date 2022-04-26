//
// Created by Administrator on 2020/3/30.
//

#ifndef PROJECT_PINEERS_PIONEERS_H
#define PROJECT_PINEERS_PIONEERS_H
typedef struct
{
    /*仅开机读取一次的量，理论上为非变量*/
    int boardtype;		//场景类型选择，数据库读取
    int flagtype;		//flag选择

    int	K31_Empty;		//31空管计数标定值，长时间标定求一分钟平均值，数据库读取

    int Empty_Year;		//时间-年，计算当前空管计数用，数据库读取
    int Empty_Month;	//时间-月，计算当前空管计数用，数据库读取
    int Empty_Day;

    double G31_CPM_A;	//气体吸收系数计算参数，自变量为绝压，数据库读取
    double G31_CPM_B;
//    double G81_CPM_A;
//    double G81_CPM_B;
    double G356_CPM_A;
    double G356_CPM_B;

    double W31_CPM;		//液体吸收系数，数据库读取
//    double W81_CPM;
    double W356_CPM;

    double F_CPM;		//空管时356峰与31峰计数的比值，数据库读取

    double Vp_A;			//绝压修正系数，自变量为绝压传感器电压值，数据库读取
    double Vp_B;			//绝压修正截距，自变量为绝压传感器电压值，数据库读取

    double Vdp_A;		//差压修正系数，自变量为差压传感器电压值，数据库读取
    double Vdp_B;		//差压修正截距，自变量为差压传感器电压值，数据库读取
    double Vdp_C;		//差压修正系数，自变量为差压传感器电压值，数据库读取
    double Vdp_D;		//差压修正截距，自变量为差压传感器电压值，数据库读取


    double B_CPM;		//直径比，数据库读取
    double C_CPM;		//流出系数，0.995，数据库读取
    double E_CPM;		//膨胀系数，待确认膨胀系数与压缩因子的关系，暂时数据库读取
    double Z_CPM;		//气体压缩因子，根据查表法写入，后续代入公式，暂时数据库读取

    double GasMode_A;	//干气修正系数，数据库读取
    double GasMode_B;	//干气修正截距，数据库读取

    double T_P_SC;		//标况温度，摄氏度，计算公式中需换算为开尔文温度，数据库读取
    double P_SC;			//标况压力，单位为kPa，数据库读取
    double Dg_SC;		//标况气密度，单位kg/m3，数据库读取
    double Dw_SC;		//水密度，单位kg/m3，数据库读取
    double d_CPM;		//喉径，单位m，数据库读取

    double DP_th;		//小流量切除阈值，数据库读取
    double LMF_th;		//小液量切除，质量含液率阈值，数据库读取

    double Qmg_ori;		//流量累加原始值，为了掉电累计流量不清零，数据库读取
    double Qml_ori;		//流量累加原始值，为了掉电累计流量不清零，数据库读取

    double Qm_A;			//总质量流量修正系数，在气液单独修正不可用的情况下备用，数据库读取
    double Qm_B;

    double GVF_CPS_A;	//体积含气率修正系数，在数据库中增加，只在青白江用，数据库读取
    double GVF_CPS_B;	//体积含气率修正截距，在数据库中增加，只在青白江用，数据库读取

    double GMF_CPS_A;	//质量含气率修正系数，在数据库中OMF修改得到，在气液单独修正不可用的情况下备用，数据库读取
    double GMF_CPS_B;	//质量含气率修正截距，在数据库中OMF修改得到，在气液单独修正不可用的情况下备用，数据库读取

    double Qmg_A;		//气体质量流量单独修正系数，数据库读取
    double Qmg_B;

    double Qml_A;		//液体质量流量单独修正系数，数据库读取
    double Qml_B;

    /*需每秒钟传递过来的量（变量）*/
    int winA_CPS;
    int winB_CPS;		//每秒的31计数
    int winC_CPS;
    int winD_CPS;
    int winE_CPS;

    int year;			//当前的时间-年
    int month;			//当前的时间-月
    int day;

    double Vp_CPS;		//绝压传感器电压值，单位V

    double Vdp_CPS;		//差压传感器电压值，单位V

    double T_P_WC_CPS;	//工况绝压温度，℃
    double T_DP_WC_CPS;	//工况差压温度，℃

    /*计算结果按秒上报，显示在OLED屏和485显示器，OLED屏上质量流量和体积流量显示二选一，485屏上全显示*/
    double P_WC_CPS;			//当前秒的工况压力值，根据需要或硬件能力是否显示
    double DP_CPS;			//当前秒的差压值，大几率不会显示，仅参与计算
    //double T_DP_WC_CPS；	//每秒传递过来的工况差压温度，℃，根据需要选择是否每秒显示
    //double Dgwc_CPS;		//当前秒工况气密度，预留
    //double Dmix_CPS;		//当前秒工况混合密度，预留，使用修正后的体积相分率计算，或使用修正后的质量相分率反演体积相分率计算

    double Qmg_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上
    double Qml_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上

    double Qmg_CPS;			//kg/h 同步到OLED显示屏或485显示器瞬时流量
    double Qml_CPS;			//kg/h 同步到OLED显示屏或485显示器瞬时流量

    double Qvg_CPS;			//Nm3/h 同步到OLED显示屏或485显示器瞬时流量
    double Qvl_CPS;			//Nm3/h 同步到OLED显示屏或485显示器瞬时流量

    double Qvg_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上
    double Qvl_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上

    /*计算结果上报，按分钟存入日志*/
    int winA_CPM;
    int winB_CPM;
    int winC_CPM;
    int winD_CPM;
    int winE_CPM;

    double P_WC_CPM;		//前60秒的绝压平均值
    double DP_CPM;		//前60秒的差压平均值

    double GVF_CPM;		//原始计算工况体积含气率，未修正，存日志
    double LVF_CPM;		//原始计算工况体积含液率，未修正，存日志
    double GVF_CPM_C;	//工况体积含气率修正，存日志，这个值可能仅仅青白江测试时有用

    double Dgwc_CPM;		//工况气密度，前60秒的工况气密度平均值
    double Dmix_CPM;		//工况混合密度，前60秒的混合密度平均值

    double GMF_CPM;		//质量含气率，存日志
    double LMF_CPM;		//质量含液率，存日志
    double GMF_CPM_C;	//质量含气率修正，存日志

    double Qm_CPM;		//总质量流量  存日志	单位kg/h
    double Qv_CPM;		//总工况体积流量 存日志 单位m3/h，总标况体积流量没有意义

    double Qmg_CPM;		//气瞬时质量流量 单位kg/h （存在数据库flow_gas中）
    double Qml_CPM;		//液瞬时质量流量 单位kg/h （存在数据库flow_water）

    double Qvg_CPM;		//标况气流量（存日志中，与网页显示对应），由质量流量除以标况密度得到
    double Qvl_CPM;		//标况液流量（存日志中，与网页显示对应）

    double Add_Sctime;
}T_CalculatePara;

typedef struct {
   double DP_CPS;
   double P_WC_CPS;
   double T_P_WC_CPS;
   double Qvg_CPS;
   double Qvl_CPS;
   double Qvg_add_CPS;
   double Qvl_add_CPS;
}T_Freemodbus;


typedef struct {
   double Qm_CPM;
   double Qv_CPM;
   double GMF_CPM;
   double LMF_CPM;
   double GVF_CPM;
   double LVF_CPM;
   double Qml_add_CPS;
   double Qmg_add_CPS;
   double Qvl_CPM;
   double Qvg_CPM;
   double Qml_CPS;
   double Qmg_CPS;
   double T_P_WC_CPS;
   double P_WC_CPM;
}T_Calculatepara_result;

#endif //PROJECT_PINEERS_PIONEERS_H
