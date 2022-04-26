/*
 * shmdata.h
 *
 *  Created on: 2016-5-3
 *      Author: vmuser
 */


#ifndef _SHMDATA_H_HEADER
#define _SHMDATA_H_HEADER

#define TEXT_SZ 2048

typedef struct
	{
	/*仅开机读取一次的量，理论上为非变量*/
		int boardtype;		//场景类型选择，数据库读取
		int flagtype;		//flag选择

		int	K31_Empty;		//31空管计数标定值，长时间标定求一分钟平均值，数据库读取

		int Empty_Year;		//时间-年，计算当前空管计数用，数据库读取
		int Empty_Month;	//时间-月，计算当前空管计数用，数据库读取

		float G31_CPM_A;	//气体吸收系数计算参数，自变量为绝压，数据库读取
		float G31_CPM_B;
		float G81_CPM_A;
		float G81_CPM_B;
		float G356_CPM_A;
		float G356_CPM_B;

		float W31_CPM;		//液体吸收系数，数据库读取
		float W81_CPM;
		float W356_CPM;

		float F_CPM;		//空管时356峰与31峰计数的比值，数据库读取

		float Vp_A;			//绝压修正系数，自变量为绝压传感器电压值，数据库读取
		float Vp_B;			//绝压修正截距，自变量为绝压传感器电压值，数据库读取

		float Vdp_A;		//差压修正系数，自变量为差压传感器电压值，数据库读取
		float Vdp_B;		//差压修正截距，自变量为差压传感器电压值，数据库读取

		float B_CPM;		//直径比，数据库读取
		float C_CPM;		//流出系数，0.995，数据库读取
		float E_CPM;		//膨胀系数，待确认膨胀系数与压缩因子的关系，暂时数据库读取
		float Z_CPM;		//气体压缩因子，根据查表法写入，后续代入公式，暂时数据库读取

		float GasMode_A;	//干气修正系数，数据库读取
		float GasMode_B;	//干气修正截距，数据库读取

		float T_P_SC;		//标况温度，摄氏度，计算公式中需换算为开尔文温度，数据库读取
		float P_SC;			//标况压力，单位为kPa，数据库读取
		float Dg_SC;		//标况气密度，单位kg/m3，数据库读取
		float Dw_SC;		//水密度，单位kg/m3，数据库读取
		float d_CPM;		//喉径，单位m，数据库读取

		float DP_th;		//小流量切除阈值，数据库读取
		float LMF_th;		//小液量切除，质量含液率阈值，数据库读取

		float Qmg_ori;		//流量累加原始值，为了掉电累计流量不清零，数据库读取
		float Qml_ori;		//流量累加原始值，为了掉电累计流量不清零，数据库读取

		float Qm_A;			//总质量流量修正系数，在气液单独修正不可用的情况下备用，数据库读取
		float Qm_B;

		float GVF_CPS_A;	//体积含气率修正系数，在数据库中增加，只在青白江用，数据库读取
		float GVF_CPS_B;	//体积含气率修正截距，在数据库中增加，只在青白江用，数据库读取

		float GMF_CPS_A;	//质量含气率修正系数，在数据库中OMF修改得到，在气液单独修正不可用的情况下备用，数据库读取
		float GMF_CPS_B;	//质量含气率修正截距，在数据库中OMF修改得到，在气液单独修正不可用的情况下备用，数据库读取

		float Qmg_A;		//气体质量流量单独修正系数，数据库读取
		float Qmg_B;

		float Qml_A;		//液体质量流量单独修正系数，数据库读取
		float Qml_B;

	/*需每秒钟传递过来的量（变量）*/
		int winA_CPS;
		int winB_CPS;		//每秒的31计数
		int winC_CPS;
		int winD_CPS;
		int winE_CPS;

		int year;			//当前的时间-年
		int month;			//当前的时间-月

		float Vp_CPS;		//绝压传感器电压值，单位V

		float Vdp_CPS;		//差压传感器电压值，单位V

		float T_P_WC_CPS;	//工况绝压温度，℃
		float T_DP_WC_CPS;	//工况差压温度，℃

	/*计算结果按秒上报，显示在OLED屏和485显示器，OLED屏上质量流量和体积流量显示二选一，485屏上全显示*/
		float P_WC_CPS;			//当前秒的工况压力值，根据需要或硬件能力是否显示
		float DP_CPS;			//当前秒的差压值，大几率不会显示，仅参与计算
		//float T_DP_WC_CPS；	//每秒传递过来的工况差压温度，℃，根据需要选择是否每秒显示
		//float Dgwc_CPS;		//当前秒工况气密度，预留
		//float Dmix_CPS;		//当前秒工况混合密度，预留，使用修正后的体积相分率计算，或使用修正后的质量相分率反演体积相分率计算

		float Qmg_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上
		float Qml_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上

		float Qmg_CPS;			//kg/h 同步到OLED显示屏或485显示器瞬时流量
		float Qml_CPS;			//kg/h 同步到OLED显示屏或485显示器瞬时流量

		float Qvg_CPS;			//Nm3/h 同步到OLED显示屏或485显示器瞬时流量
		float Qvl_CPS;			//Nm3/h 同步到OLED显示屏或485显示器瞬时流量

		float Qvg_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上
		float Qvl_add_CPS;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上

	/*计算结果上报，按分钟存入日志*/
		int winA_CPM;
		int winB_CPM;
		int winC_CPM;
		int winD_CPM;
		int winE_CPM;

		float P_WC_CPM;		//前60秒的绝压平均值
		float DP_CPM;		//前60秒的差压平均值

		float GVF_CPM;		//原始计算工况体积含气率，未修正，存日志
		float LVF_CPM;		//原始计算工况体积含液率，未修正，存日志
		float GVF_CPM_C;	//工况体积含气率修正，存日志，这个值可能仅仅青白江测试时有用

		float Dgwc_CPM;		//工况气密度，前60秒的工况气密度平均值
		float Dmix_CPM;		//工况混合密度，前60秒的混合密度平均值

		float GMF_CPM;		//质量含气率，存日志
		float LMF_CPM;		//质量含液率，存日志
		float GMF_CPM_C;	//质量含气率修正，存日志

		float Qm_CPM;		//总质量流量  存日志	单位kg/h
		float Qv_CPM;		//总工况体积流量 存日志 单位m3/h，总标况体积流量没有意义

		float Qmg_CPM;		//气瞬时质量流量 单位kg/h （存在数据库flow_gas中）
		float Qml_CPM;		//液瞬时质量流量 单位kg/h （存在数据库flow_water）

		float Qvg_CPM;		//标况气流量（存日志中，与网页显示对应），由质量流量除以标况密度得到
		float Qvl_CPM;		//标况液流量（存日志中，与网页显示对应）
	}
MSMQ;

struct shared_use_st
{
	int written;//用于差压读取
	char text[TEXT_SZ];//记录写入和读取的文本
	unsigned short modbusdata[1024];
	float ad1115[200][3];
	float tem1;
	float tem2;
	int S_HV;//高压
	int S_VBB;
	float S_HV_C;//高压调节系数
	int S_PCH31;//三个峰的预设位置
	int S_PCH81;
	int S_PCH356;
	float change31;//三个峰的偏移系数，根据他们调整WIN
	float change81;
	float change356;
	int F_WIN_J;//卷积控制位
	int S_F31;//实际峰位
	int S_F81;
	int S_F356;
	int CON_A1;
	int CON_A2;
	int CON_B1;
	int CON_B2;
	int CON_C1;
	int CON_C2;
	int CON_D1;
	int CON_D2;
	int CON_E1;
	int CON_E2;
	unsigned int S_es[8192];//能普
	float DEV_T1;//设备板温度
	float DEV_T2;
	float DEV_T3;
	int S_HIV;//高压
	int pid;
	int S_VBBf;//调节偏置电压位
	int S_HIVf;//调压命令位
	float Pre_a;
	float Pre_b;
	float DP_a;
	float DP_b;
	float PreT_a;
	float PreT_b;
	int HIV_en;//是否自动调压
	int F_WIN_en;//是否自动卷机
	int OLED_en;//是否oled显示
	int W_Es;
	int W_5ms;
	int W_log;
	int W_pulse;
	unsigned int th_sum;
	int			flag_hv;
	float a1;
	float b1;
	float a2;
	float b2;
	int adjust_HV;
	float	OMF_CPM;
	float	GMF_CPM;
	float	Qm_CPM;
	float	Qm_SUM;
	float	Gm_SUM;
	float	DataP;//绝压
	float	DataDP;//差压

	int		hour;
	int		minute;
	int		second;
	float	Qml_CPM;
	float	Qmg_CPM;
	float	Qml_CPS;
	float	Qmg_CPS;
	float	OVF_CPM;
	float	GVF_CPM;
	float	Qvl_CPM;
	float	Qvg_CPM;
	float	Qv_CPM;
	float	Qv_SUM;
	float	Gv_SUM;

	float	OMF_CPM_th;

	int 	BoardType;

	MSMQ	MsmqData;
};

#endif


