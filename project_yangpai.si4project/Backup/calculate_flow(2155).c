//
// Created by Administrator on 2020/3/31.
// 20200901增加绝压对差压的补偿分段公式
#include <math.h>
#include "calculate_flow.h"
#include "pioneers.h"
#include "pioneers_service.h"
#include "yangpi_mysql_proxy.h"
#include "yangpi_i2c_proxy.h"
#include "log_dlt.h"
extern T_CalculatePara FlowParass;
extern T_Calculatepara_result FlowParasult;
extern T_Arm_Mysql tArm_Mysql;
extern T_Flow_para tFlow_para;
extern T_I2cAd1115 tI2cAd1115;

int fast_flag = 0;
double g_qmg_add = 0;
double g_qml_add = 0;
/*******************************************************************************
* 函数名称:calculate_para_init
* 函数功能:完成对FlowParass结构体的参数赋值（流量计算参数入参）
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* 
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
void calculate_para_init()
{
    T_DateTime DataTime;
    function_dd_get_sw_time(&DataTime);

    FlowParass.year             = DataTime.year;
    FlowParass.month            = DataTime.month;
    FlowParass.day              = DataTime.day;


    FlowParass.Vdp_CPS          = tI2cAd1115.ad1115_buf[199][2];
    FlowParass.Vp_CPS           = tI2cAd1115.ad1115_buf[199][1];//绝压
    FlowParass.T_P_WC_CPS       = tI2cAd1115.ad1115_buf[199][0];//绝压温度
    FlowParass.T_DP_WC_CPS      = tI2cAd1115.i2cAd1115_DPTem;//差压温度;

    FlowParass.K31_Empty        = (int)tFlow_para.t_Flow_Correction.K31_Empty;
    FlowParass.GVF_CPS_A        = tFlow_para.t_Flow_Correction.GVF_CPS_A;
    FlowParass.GVF_CPS_B        = tFlow_para.t_Flow_Correction.GVF_CPS_B;
    FlowParass.GMF_CPS_A        = tFlow_para.t_Flow_Correction.GMF_CPS_A;
    FlowParass.GMF_CPS_B        = tFlow_para.t_Flow_Correction.GMF_CPS_B;
    FlowParass.Qm_A             = tFlow_para.t_Flow_Correction.Qm_A_n;
    FlowParass.Qm_B             = tFlow_para.t_Flow_Correction.Qm_B_n;
    FlowParass.GasMode_A        = tFlow_para.t_Flow_Correction.GasMode_A;
    FlowParass.GasMode_B        = tFlow_para.t_Flow_Correction.GasMode_B;
    FlowParass.DP_th            = tFlow_para.t_Flow_Correction.DP_th;
    FlowParass.Qml_A            = tFlow_para.t_Flow_Correction.Qml_A;
    FlowParass.Qml_B            = tFlow_para.t_Flow_Correction.Qml_B;
    FlowParass.Qmg_A            = tFlow_para.t_Flow_Correction.Qmg_A;
    FlowParass.Qmg_B            = tFlow_para.t_Flow_Correction.Qmg_B;
    FlowParass.LMF_th           = tFlow_para.t_Flow_Correction.LMF_th;



    FlowParass.boardtype        = tArm_Mysql.t_Arm_Set.Arm_Set_board_type;//t_Fpga_Mysql


    FlowParass.Empty_Year       = (int)tFlow_para.t_Flow_Result.Empty_Year;
    FlowParass.Empty_Month      = (int)tFlow_para.t_Flow_Result.Empty_Month;
    FlowParass.Empty_Day        =(int)tFlow_para.t_Flow_Result.Empty_Day;
    FlowParass.Add_Sctime       =(double)tFlow_para.t_Flow_Result.Sctime;
    if(fast_flag == 0)
    {
        fast_flag = 1;
        FlowParass.Qmg_ori          = tFlow_para.t_Flow_Result.Qmg;
        FlowParass.Qml_ori          = tFlow_para.t_Flow_Result.Qml;

    } else{
        FlowParass.Qmg_ori          = g_qmg_add;
        FlowParass.Qml_ori          = g_qml_add;
    }


    FlowParass.F_CPM            = tFlow_para.t_Flow_Minute.F_CPM;
    FlowParass.d_CPM            = tFlow_para.t_Flow_Minute.D_CPM;
    FlowParass.G31_CPM_A        = tFlow_para.t_Flow_Minute.G31_CPM_A;
    FlowParass.G31_CPM_B        = tFlow_para.t_Flow_Minute.G31_CPM_B;
//FlowParass.G81_CPM_A        = tFlow_para.t_Flow_Minute.G81_CPM_A;
//FlowParass.G81_CPM_B        = tFlow_para.t_Flow_Minute.G81_CPM_B;
    FlowParass.G356_CPM_A       = tFlow_para.t_Flow_Minute.G356_CPM_A;
    FlowParass.G356_CPM_B       = tFlow_para.t_Flow_Minute.G356_CPM_B;
    FlowParass.W31_CPM          = tFlow_para.t_Flow_Minute.W31_CPM;
//FlowParass.W81_CPM          = tFlow_para.t_Flow_Minute.W81_CPM;
    FlowParass.W356_CPM         = tFlow_para.t_Flow_Minute.W356_CPM;
    FlowParass.Dg_SC            = tFlow_para.t_Flow_Minute.GD_CPM_SC;
    FlowParass.T_P_SC           = tFlow_para.t_Flow_Minute.TF_PCPM_SC;
    FlowParass.P_SC             = tFlow_para.t_Flow_Minute.P_CPM_SC;
    FlowParass.Vp_A             = tFlow_para.t_Flow_Minute.P_CPM_A;
    FlowParass.Vp_B             = tFlow_para.t_Flow_Minute.P_CPM_B;
    FlowParass.Vdp_A            = tFlow_para.t_Flow_Minute.DP_CPM_A;
    FlowParass.Vdp_B            = tFlow_para.t_Flow_Minute.DP_CPM_B;
    FlowParass.Vdp_C            = tFlow_para.t_Flow_Minute.DP_CPM_C;
    FlowParass.Vdp_D            = tFlow_para.t_Flow_Minute.DP_CPM_D;
    FlowParass.B_CPM            = tFlow_para.t_Flow_Minute.b_CPM;
    FlowParass.C_CPM            = tFlow_para.t_Flow_Minute.C_CPM;
    FlowParass.E_CPM            = tFlow_para.t_Flow_Minute.E_CPM;
    FlowParass.Dw_SC            = tFlow_para.t_Flow_Minute.WD_CPM;
    FlowParass.Z_CPM            = tFlow_para.t_Flow_Minute.Z_CPM;
    PRONEERS_LOG("算法初始化完成--执行完成\n");
}
#define PI 3.1415926
#define HLP 10.54
/*******************************************************************************
* 函数名称:calculate_flow_start
* 函数功能:根据入参和从硬件获得的数据进行流量计算
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* 
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
void calculate_flow_start()
{
    /*仅开机读取一次的量，理论上为非变量*/
    static int boardtype 	= 0;		//场景类型选择，数据库读取
    static int flagtype 	= 0;		//场景类型选择，数据库读取

    static int K31_Empty 	= 0;		//31空管计数标定值，长时间标定后求一分钟平均值，数据库读取

    static int Empty_Year 	= 0; 		//时间-年，计算当前空管计数用，数据库读取
    static int Empty_Month	= 0;		//时间-月，计算当前空管计数用，数据库读取
    static int Empty_Day	= 0;		//时间-日，计算当前空管计数用，数据库读取

    static double G31_CPM_A = 0;			//气体吸收系数计算参数，自变量为绝压，数据库读取,后续改为与工况气密度相关到函数
    static double G31_CPM_B = 0;
    static double G81_CPM_A = 0;
    static double G81_CPM_B = 0;
    static double G356_CPM_A = 0;
    static double G356_CPM_B = 0;

    static double W31_CPM = 0;			//液体吸收系数，数据库读取
    static double W81_CPM = 0;
    static double W356_CPM = 0;

    static double F_CPM = 0;				//空管时356峰与31峰计数的比值，数据库读取

    static double Vp_A = 0; 				//绝压修正系数，自变量为绝压传感器电压值，数据库读取
    static double Vp_B = 0; 				//绝压修正截距，自变量为绝压传感器电压值，数据库读取

    static double Vdp_A = 0;				//差压修正系数，自变量为差压传感器电压值，数据库读取
    static double Vdp_B = 0;				//差压修正截距，自变量为差压传感器电压值，数据库读取
    static double Vdp_C = 0;
    static double P_inf_p = 0;

    static double B_CPM = 0;				//直径比，数据库读取
    static double C_CPM = 0;				//流出系数，0.995，数据库读取
    static double E_CPM = 0;				//膨胀系数，待确认膨胀系数与压缩因子的关系，暂时数据库读取
    static double e_CPM = 0;				//daiding
    static double Z_CPM = 0;				//气体标况压缩因子，根据查表法写入，后续代入公式，暂时数据库读取

    static double GasMode_A = 0;			//干气修正系数，数据库读取
    static double GasMode_B = 0;			//干气修正截距，数据库读取

    static double T_P_SC = 0;			//标况温度，摄氏度，计算公式中需换算为开尔文温度，数据库读取
    static double P_SC = 0; 				//标况压力，单位为kPa，数据库读取
    static double Dg_SC = 0;				//标况气密度，单位kg/m3，数据库读取
    static double Dw_SC = 0;				//水密度，单位kg/m3，数据库读取
    static double d_CPM = 0;				//喉径，单位m，数据库读取

    static double DP_th = 0;				//小流量切除阈值，数据库读取
    static double LMF_th = 0;			//小液量切除，质量含液率阈值，数据库读取

    static double Qmg_ori = 0;			//流量累加原始值，为了掉电累计流量不清零，数据库读取
    static double Qml_ori = 0;			//流量累加原始值，为了掉电累计流量不清零，数据库读取

    static double Qvg_ori = 0;			//预留标况体积累积流量输出
    static double Qvl_ori = 0;

    static double Qm_A = 0; 				//总质量流量修正系数，在气液单独修正不可用的情况下备用，数据库读取
    static double Qm_B = 0;

    static double GVF_CPS_A = 0;		//体积含气率修正系数，在数据库中增加，只在青白江用，数据库读取
    static double GVF_CPS_B = 0;		//体积含气率修正截距，在数据库中增加，只在青白江用，数据库读取

    static double GMF_CPS_A = 0;		//质量含气率修正系数，在数据库中OMF修改得到，在气液单独修正不可用的情况下备用，数据库读取
    static double GMF_CPS_B = 0;		//质量含气率修正截距，在数据库中OMF修改得到，在气液单独修正不可用的情况下备用，数据库读取

    static double Qmg_A = 0;			//气体质量流量单独修正系数，数据库读取
    static double Qmg_B = 0;

    static double Qml_A = 0;			//液体质量流量单独修正系数，数据库读取
    static double Qml_B = 0;

    /*需每秒钟传递过来的量（变量）*/
    int winA_CPS;
    int winD_CPS;

    int winB_CPS;
    int winC_CPS;
    int winE_CPS;

    int year;			//当前的时间-年
    int month;			//当前的时间-月
    int day;			//当前到时间-日

    double Vp_CPS;		//绝压传感器电压值，单位V

    double Vdp_CPS;		//差压传感器电压值，单位V

    double T_P_WC_CPS;	//工况绝压温度，℃
    double T_DP_WC_CPS;	//工况差压温度，℃,每秒传递过来的工况差压温度,根据需要选择是否每秒显示

    /*计算结果按秒上报，显示在OLED屏和485显示器，OLED屏上质量流量和体积流量显示二选一，485屏上全显示*/
    double P_WC_CPS = 0; 	//当前秒的工况压力值，根据需要或硬件能力是否显示
    double DP_CPS = 0;		//当前秒的差压值，大几率不会显示，仅参与计算

    double Dgwc_CPS = 0;		//当前秒工况气密度，预留
    double Dmix_CPS = 0;		//当前秒工况混合密度，预留，使用修正后的体积相分率计算，或使用修正后的质量相分率反演体积相分率计算

    double GVF_CPS = 0;
    double LVF_CPS = 0;
    double GMF_CPS = 0;
    double LMF_CPS = 0;

    static double Qmg_add_CPS = 0;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上
    static double Qml_add_CPS = 0;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上

    double Qmg_CPS = 0;			//kg/h 同步到OLED显示屏或485显示器瞬时流量
    double Qml_CPS = 0;			//kg/h 同步到OLED显示屏或485显示器瞬时流量

    double Qvg_CPS = 0;			//Nm3/h 同步到OLED显示屏或485显示器瞬时流量
    double Qvl_CPS = 0;			//Nm3/h 同步到OLED显示屏或485显示器瞬时流量

    double Qvg_add_CPS = 0;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上
    double Qvl_add_CPS = 0;		//流量累加返回值 每秒增加的流量  每秒累积到OLED显示屏累加流量上

    /*计算结果上报，按分钟存入日志*/
    double winA_CPM = 0;
    double winD_CPM = 0;

    int winB_CPM = 0;
    int winC_CPM = 0;
    int winE_CPM = 0;

    double T_P_WC_CPM = 0;	//前60秒的绝压温度值
    double T_DP_WC_CPM = 0;	//前60秒的差压温度值
    double P_WC_CPM = 0; 	//前60秒的绝压平均值
    double DP_CPM = 0;		//前60秒的差压平均值

    double GVF_CPM = 0;		//原始计算工况体积含气率，未修正，存日志
    double LVF_CPM = 0;		//原始计算工况体积含液率，未修正，存日志
    //double GVF_CPM_C;	//工况体积含气率修正，存日志，这个值可能仅仅青白江测试时有用

    double Dgwc_CPM = 0; 	//工况气密度，前60秒的工况气密度平均值
    double Dmix_CPM = 0; 	//工况混合密度，前60秒的混合密度平均值，修正后还是修正前？待定

    double GMF_CPM = 0;		//质量含气率，存日志
    double LMF_CPM = 0;		//质量含液率，存日志
    //double GMF_CPM_C;	//质量含气率修正，存日志

    double Qm_CPM = 0;		//总质量流量  存日志	单位kg/h
    double Qv_CPM = 0;		//总工况体积流量 存日志 单位m3/h，总标况体积流量没有意义

    double Qmg_CPM = 0;		//气瞬时质量流量 单位kg/h （存在数据库flow_gas中）
    double Qml_CPM = 0;		//液瞬时质量流量 单位kg/h （存在数据库flow_water）

    double Qvg_CPM = 0;		//标况气流量（存日志中，与网页显示对应），由质量流量除以标况密度得到
    double Qvl_CPM = 0;		//标况液流量（存日志中，与网页显示对应）

    double 	Zg 	= 0;			//添加关于工况压缩因子的计算

    double 	z0 	= 9.9944E-01;
    double 	A01 = -5.06945E-5;
    double 	B01 = 1.232E-2;
    double 	B02 = 6.00782E-05;
    double 	B03 = 1.40002E-08;
    double 	A1	= -2.22993E-05;
    double 	A2 	= -1.05705E-09;
    double 	A3 	= -3.65404E-15;
    double 	B1 	= 1.233E-02;
    double 	B2 	= 6.00791E-05;

    double DP_CCL = 0;			//用于差压计算的值，目的是为了在网页上显示负差压。

    static double  	G31_CPS;		//气体吸收系数
    static double	G31_CPM;
    double	dl;				//每秒钟计算出来的液体厚度
    double	dg;				//每秒钟计算出来的喉径内气体厚度

    static double	Qm_CPS;

    double 	GVF_CPS_C;		//这个值是为了使GMF在GVF大于1时不跳变
    double	LVF_CPS_C;

    double	GVF_CPM_C;
    double	LVF_CPM_C;

    double	GVF_CPS_Temp;	//20191011添加，为了限定原始GVF在0-1之间增加到临时值
    double	LVF_CPS_Temp;

    double 	GMF_CPS_C;		//质量含气率修正
    double	LMF_CPS_C;

    double	GMF_CPM_C;
    double	LMF_CPM_C;

    static double 	GMF_th;			//质量含气率阈值，用于小液量切除

//	static unsigned int count = 1;

    static int	 	j[60]={0};		//winB_CPM,累加
    static int	 	v[60]={0};		//winC_CPM,累加
    static int	 	w[60]={0};		//winE_CPM,累加

    static double	k[60]={0};		//P_WC_CPM
    static double	l[60]={0};		//GVF_CPM
    static double	m[60]={0};		//GMF_CPM
    static double	n[60]={0};		//GMF_CPM_C
    static double	o[60]={0};		//GVF_CPM_C
    static double	p[60]={0};		//Dmix_CPM
    static double	q[60]={0};		//DP_CPM
    static double	r[60]={0};		//Qm_CPM
    static double	s[60]={0};		//Qmg_CPM
    static double	t[60]={0};		//Qml_CPM
    static double	u[60]={0};		//Dgwc_CPM

    static int indx = 0;			//winB_CPM,累加
    int effective = 0;
    int		i=0;

    static int indx_81 = 0;			//winC_CPM,累加
    int effective_81 = 0;
    int		i_81=0;

    static int indx_356 = 0;			//winE_CPM,累加
    int effective_356 = 0;
    int		i_356=0;

    static int indx_P = 0;			//P_WC_CPM
    int effective_P = 0;
    int		i_P=0;

    static int indx_GVF = 0;		//GVF_CPM
    int effective_GVF = 0;
    int		i_GVF=0;

    static int indx_GMF = 0;		//GMF_CPM
    int effective_GMF = 0;
    int		i_GMF=0;

    static int indx_GMF_C = 0;		//GMF_CPM_C
    int effective_GMF_C = 0;
    int		i_GMF_C=0;

    static int indx_GVF_C = 0;		//GVF_CPM_C
    int effective_GVF_C = 0;
    int		i_GVF_C=0;

    static int indx_Dmix = 0;		//Dmix_CPM
    int effective_Dmix = 0;
    int		i_Dmix=0;

    static int indx_DP = 0;			//DP_CPM
    int effective_DP = 0;
    int		i_DP=0;

    static int indx_Qm = 0;			//Qm_CPM
    int effective_Qm = 0;
    int		i_Qm=0;

    static int indx_Qmg = 0;		//Qmg_CPM
    int effective_Qmg = 0;
    int		i_Qmg=0;

    static int indx_Qml = 0;		//Qml_CPM
    int effective_Qml = 0;
    int		i_Qml=0;

    static int indx_Dgwc = 0;		//Dgwc_CPM
    int effective_Dgwc = 0;
    int		i_Dgwc=0;

    //赋值到本地
    /*理论应该仅读取一次的值，现在还是每秒读一次*/
    boardtype	=	FlowParass.boardtype;
    flagtype	=	FlowParass.flagtype;
    K31_Empty	=	FlowParass.K31_Empty;
    Empty_Year	=	FlowParass.Empty_Year;
    Empty_Month	=	FlowParass.Empty_Month;
    Empty_Day	=	FlowParass.Empty_Day;

    G31_CPM_A	=	FlowParass.G31_CPM_A;
    G31_CPM_B	=	FlowParass.G31_CPM_B;
//    G81_CPM_A	=	FlowParass.G81_CPM_A;
//    G81_CPM_B	=	FlowParass.G81_CPM_B;
    G356_CPM_A	=	FlowParass.G356_CPM_A;
    G356_CPM_B	=	FlowParass.G356_CPM_B;

    W31_CPM 	=	FlowParass.W31_CPM;
//    W81_CPM		=	FlowParass.W81_CPM;
    W356_CPM	=	FlowParass.W356_CPM;

    F_CPM		=	FlowParass.F_CPM;

    Vp_A		=	FlowParass.Vp_A;
    Vp_B		=	FlowParass.Vp_B;

    Vdp_A		=	FlowParass.Vdp_A;
    Vdp_B		=	FlowParass.Vdp_B;
    Vdp_C		=	FlowParass.Vdp_C;
    P_inf_p		=	FlowParass.Vdp_D;

    B_CPM		=	FlowParass.B_CPM;
    C_CPM		=	FlowParass.C_CPM;
    E_CPM		=	FlowParass.E_CPM;
    Z_CPM		=	FlowParass.Z_CPM;
    d_CPM		=	FlowParass.d_CPM;

    GasMode_A	=	FlowParass.GasMode_A;
    GasMode_B	=	FlowParass.GasMode_B;

    T_P_SC		=	FlowParass.T_P_SC;
    P_SC		=	FlowParass.P_SC;
    Dg_SC		=	FlowParass.Dg_SC;
    Dw_SC		=	FlowParass.Dw_SC;
    d_CPM		=	FlowParass.d_CPM;

    DP_th		=	FlowParass.DP_th;
    LMF_th		=	FlowParass.LMF_th;

    Qmg_ori		=	FlowParass.Qmg_ori;
    Qml_ori		=	FlowParass.Qml_ori;

    Qm_A		=	FlowParass.Qm_A;
    Qm_B		=	FlowParass.Qm_B;

    GVF_CPS_A	=	FlowParass.GVF_CPS_A;
    GVF_CPS_B   =	FlowParass.GVF_CPS_B;

    GMF_CPS_A   =	FlowParass.GMF_CPS_A;
    GMF_CPS_B   =	FlowParass.GMF_CPS_B;

    Qmg_A		=	FlowParass.Qmg_A;
    Qmg_B		=	FlowParass.Qmg_B;

    Qml_A		=	FlowParass.Qml_A;
    Qml_B		=	FlowParass.Qml_B;

    /*按秒读取的值*/
    winA_CPS	=	FlowParass.winA_CPS;
    winD_CPS	=	FlowParass.winD_CPS;

    winB_CPS	=	FlowParass.winB_CPS;
    winC_CPS	=	FlowParass.winC_CPS;
    winE_CPS	=	FlowParass.winE_CPS;

    year		=	FlowParass.year;
    month		=	FlowParass.month;
    day			=	FlowParass.day;

    Vp_CPS		=	FlowParass.Vp_CPS;
    Vdp_CPS		=	FlowParass.Vdp_CPS;

    T_P_WC_CPS	=	FlowParass.T_P_WC_CPS;	//5绝压传感器温度，摄氏度，建议用这个计算
    T_DP_WC_CPS	=	FlowParass.T_DP_WC_CPS;	//6差压传感器温度，摄氏度


//    	printf("boardtype	= %d\n",boardtype);
//		printf("K31_Empty	= %d\n",K31_Empty);
//		printf("Empty_Year	= %d\n",Empty_Year);
//		printf("Empty_Month	= %d\n",Empty_Month);
//		printf("G31_CPM_A	= %f\n",G31_CPM_A);
//		printf("G31_CPM_B	= %f\n",G31_CPM_B);
//		printf("G81_CPM_A	= %f\n",G81_CPM_A);
//		printf("G81_CPM_B	= %f\n",G81_CPM_B);
//		printf("G356_CPM_A	= %f\n",G356_CPM_A);
//		printf("G356_CPM_B	= %f\n",G356_CPM_B);
//		printf("W31_CPM		= %f\n",W31_CPM);
//		printf("W81_CPM		= %f\n",W81_CPM);
//		printf("W356_CPM	= %f\n",W356_CPM);
//		printf("F_CPM		= %f\n",F_CPM);
//		printf("Vp_A		= %f\n",Vp_A);
//		printf("Vp_B		= %f\n",Vp_B);
//		printf("Vdp_A		= %f\n",Vdp_A);
//		printf("Vdp_B		= %f\n",Vdp_B);
//		printf("B_CPM		= %f\n",B_CPM);
//		printf("C_CPM		= %f\n",C_CPM);
//		printf("E_CPM		= %f\n",E_CPM);
//		printf("Z_CPM		= %f\n",Z_CPM);
//		printf("GasMode_A	= %f\n",GasMode_A);
//		printf("GasMode_B	= %f\n",GasMode_B);
//		printf("T_P_SC		= %f\n",T_P_SC);
//		printf("P_SC		= %f\n",P_SC);
//		printf("Dg_SC		= %f\n",Dg_SC);
//		printf("Dw_SC		= %f\n",Dw_SC);
//		printf("d_CPM		= %f\n",d_CPM);
//		printf("DP_th		= %f\n",DP_th);
//		printf("LMF_th		= %f\n",LMF_th);
//		printf("Qmg_ori		= %f\n",Qmg_ori);
//		printf("Qml_ori		= %f\n",Qml_ori);
//		printf("Qm_A		= %f\n",Qm_A);
//		printf("Qm_B		= %f\n",Qm_B);
//		printf("GVF_CPS_A	= %f\n",GVF_CPS_A);
//		printf("GVF_CPS_B	= %f\n",GVF_CPS_B);
//		printf("GMF_CPS_A	= %f\n",GMF_CPS_A);
//		printf("GMF_CPS_B	= %f\n",GMF_CPS_B);
//		printf("Qmg_A		= %f\n",Qmg_A);
//		printf("Qmg_B		= %f\n",Qmg_B);
//		printf("Qml_A		= %f\n",Qml_A);
//		printf("Qml_B		= %f\n",Qml_B);
//		printf("winA_CPS	= %d\n",winA_CPS);
//		printf("winB_CPS	= %d\n",winB_CPS);
//		printf("winC_CPS	= %d\n",winC_CPS);
//		printf("winD_CPS	= %d\n",winD_CPS);
//		printf("winE_CPS	= %d\n",winE_CPS);
//		printf("year		= %d\n",year);
//		printf("month		= %d\n",month);
//		printf("Vp_CPS		= %f\n",Vp_CPS);
//		printf("Vdp_CPS		= %f\n",Vdp_CPS);
//		printf("T_P_WC_CPS	= %f\n",T_P_WC_CPS);
//		printf("T_DP_WC_CPS	= %f\n",T_DP_WC_CPS);


    /*(1)衰减后的空管计数*/
    K31_Empty = K31_Empty * pow(0.5,(((year * 365 + month*30+day) - (Empty_Year*365 + Empty_Month*30+Empty_Day))/(HLP*365)));
    PRONEERS_LOG("(1):K31_Empty = %d ; year = %d ; month = %d ; day = %d ; Empty_Year = %d ; Empty_Month = %d ; Empty_Day = %d; HLP = %f\n",K31_Empty,year,month,day,Empty_Year,Empty_Month,Empty_Day,HLP);

    /*(2)对前n分钟的31/81/356峰秒计数求和*/
    if (indx >= 60)
    {
        indx = 0;
    }

    j[indx] = winB_CPS;
    v[indx] = winC_CPS;
    w[indx] = winE_CPS;

    for (i = 0; i < 60; i++)
    {
        if (j[i] != 0)
        {
            effective++;
            winB_CPM = winB_CPM + j[i];
            winC_CPM = winC_CPM + v[i];
            winE_CPM = winE_CPM + w[i];
        }
    }

    if (effective != 0)
    {
        winB_CPM = ((double)winB_CPM / (double)effective) * 60;
        winC_CPM = ((double)winC_CPM / (double)effective) * 60;
        winE_CPM = ((double)winE_CPM / (double)effective) * 60;
    }

    indx++;

	PRONEERS_LOG("(2):winB_CPS = %d\n",winB_CPS);

    if (winB_CPM == 0)
    {
        winB_CPM = 1;
    }

//		PRONEERS_LOG("(2):winB_CPM = %d\n",winB_CPM);

    /*(3)计算每秒的工况压力*/
    P_WC_CPS = Vp_A	* Vp_CPS + Vp_B;					//由读取的电压值计算绝压
	PRONEERS_LOG("(3):P_WC_CPS = %f\n",P_WC_CPS);

    /*(4)计算工况气密度*/
    Zg = (z0+A01*P_WC_CPS+B01*T_P_WC_CPS+B02*T_P_WC_CPS*T_P_WC_CPS+B03*T_P_WC_CPS*T_P_WC_CPS*T_P_WC_CPS)/(1+A1*P_WC_CPS+A2*P_WC_CPS*P_WC_CPS+A3*P_WC_CPS*P_WC_CPS*P_WC_CPS+B1*T_P_WC_CPS+B2*T_P_WC_CPS*T_P_WC_CPS);

    Dgwc_CPS = (P_WC_CPS / P_SC) * ((T_P_SC + 273.15) / (T_P_WC_CPS + 273.15)) * Dg_SC * (Z_CPM/Zg);	//工况气密度,温度单位为摄氏度
    PRONEERS_LOG("(4):Zg = %f Dgwc_CPS = %f\n" ,Zg,Dgwc_CPS);

    /*(5)气体吸收系数计算*/
    G31_CPS = G31_CPM_A * Dgwc_CPS + G31_CPM_B;

    PRONEERS_LOG("(5):G31_CPS = %f\n",G31_CPS);

    /*(6)计算喉径内气体厚度*/
    dg = (log((double)K31_Empty / (double)winB_CPM) - d_CPM * W31_CPM) / (G31_CPS - W31_CPM);
	PRONEERS_LOG("(6):dg = %f\n",dg);

    /*(7)计算原始体积相分率*/
    GVF_CPS	= dg / d_CPM;
    LVF_CPS	= 1-GVF_CPS;
    PRONEERS_LOG("(7):GVF_CPS = %f LVF_CPS = %f\n",GVF_CPS,LVF_CPS);

    /*(7)对体积相分率进行范围框定*/
    if((GVF_CPS >= 0.0) && (GVF_CPS <= 1))
    {
        GVF_CPS_Temp = GVF_CPS;
        LVF_CPS_Temp = 1 - GVF_CPS_Temp;
    }
    else if(GVF_CPS < 0)
    {
        GVF_CPS_Temp =	0;
        LVF_CPS_Temp =	1;
    }
    else if(GVF_CPS > 1)
    {
        GVF_CPS_Temp =	1;
        LVF_CPS_Temp =	0;
    }

    /*(8)计算质量相分率*/
    GMF_CPS = (GVF_CPS_Temp*Dgwc_CPS) / (LVF_CPS_Temp*Dw_SC+GVF_CPS_Temp*Dgwc_CPS);	//分母不能为零，以后验证
    LMF_CPS = 1- GMF_CPS;
	PRONEERS_LOG("(8):GMF_CPS = (GVF_CPS*Dgwc_CPS) / (LVF_CPS*Dw_SC+GVF_CPS*Dgwc_CPS)\n");
	PRONEERS_LOG("(8):GMF_CPS = %f\n",GMF_CPS);
	PRONEERS_LOG("(8):LMF_CPS = %f\n",LMF_CPS);

    /*(9)质量相分率修正*/
    GMF_CPS_C = GMF_CPS_A * GMF_CPS + GMF_CPS_B;
    LMF_CPS_C = 1 - GMF_CPS_C;
	PRONEERS_LOG("(9):GMF_CPS_A = %f ; GMF_CPS_B = %f\n",GMF_CPS_A,GMF_CPS_B);
	PRONEERS_LOG("(9):GMF_CPS_C = %f\n",GMF_CPS_C);

    /*(10)修正后的质量相分率限定及小液量切除*/
    GMF_th = 1 - LMF_th;


    if((GMF_CPS_C >= 0.0) && (GMF_CPS_C <= GMF_th))
    {
        LMF_CPS_C = 1 - GMF_CPS_C;
        //Qmg_A = Qmg_A;				//湿气模型下，使用湿气的修正系数
        //Qmg_B = Qmg_A;				//湿气模型下，使用湿气的修正系数
    }
    else if(GMF_CPS_C < 0)
    {
        GMF_CPS_C =	0;
        LMF_CPS_C =	1;
    }
    else if(GMF_CPS_C > GMF_th)
    {
        GMF_CPS_C =	1;
        LMF_CPS_C =	0;
        Qmg_A = GasMode_A;			//干气模型下，使用单独的修正系数
        Qmg_B = GasMode_B;			//干气模型下，使用单独的修正系数
    }
	PRONEERS_LOG("(10):Qmg_A = %f ; Qmg_B = %f\n",Qmg_A,Qmg_B);
	PRONEERS_LOG("(10):GMF_CPS_C = %f LMF_CPS_C = %f\n",GMF_CPS_C,LMF_CPS_C);

    /*(11)反演体积相分率*/
    GVF_CPS_C = (Dw_SC * GMF_CPS_C) / (Dgwc_CPS * LMF_CPS_C + Dw_SC * GMF_CPS_C);
	PRONEERS_LOG("(11):GVF_CPS_C = (Dw_SC * GMF_CPS_C)/(Dgwc_CPS * (1-GMF_CPS_C) + Dw_SC * GMF_CPS)\n");
	PRONEERS_LOG("(11):GVF_CPS_C = %f ; Dw_SC = %f ; GMF_CPS_C = %f ; Dgwc_CPS = %f\n",GVF_CPS_C,Dw_SC,GMF_CPS_C,Dgwc_CPS);
    LVF_CPS_C = 1-GVF_CPS_C;
	PRONEERS_LOG("(11):LVF_CPS_C = %f\n",LVF_CPS_C);

    /*(12)反演混合密度*/
    Dmix_CPS = GVF_CPS_C * Dgwc_CPS + LVF_CPS_C * Dw_SC;
	PRONEERS_LOG("(12):Dmix_CPS = GVF_CPS_C * Dgwc_CPS + LVF_CPS_C * Dw_SC\n");
	PRONEERS_LOG("(12):Dmix_CPS = %f\n",Dmix_CPS);

    /*(13)计算每秒的差压*/
  	if (P_WC_CPS < P_inf_p)				//P_inf_p表示Press inflection point,绝压拐点放入DP_CPM_D栏
    {
      DP_CPS = Vdp_A * Vdp_CPS + Vdp_B * P_WC_CPS + Vdp_C;		//Vdp_B * P_WC_CPS为加入的绝压对差压的补偿，仅包含系数，截距和现场修正量相加后一起写入Vdp_C，Vdp_C放入DP_CPM_C栏
    }
	else
    {
      DP_CPS = Vdp_A * Vdp_CPS + Vdp_B * P_inf_p + Vdp_C;	//当绝压大于拐点时，由绝压造成的偏移量仅为定值
    }
	PRONEERS_LOG("(13):DP_CPS = %f ; Vdp_CPS = %f\n",DP_CPS,Vdp_CPS);

    DP_CCL = DP_CPS;					//为了在日志中显示负差压

    /*(14)小差压切除*/
    if(DP_CCL < DP_th)
    {
        DP_CCL = 0;
    }


    /*(15)计算总流量*/
    Qm_CPS = (1/pow((1-B_CPM*B_CPM*B_CPM*B_CPM), 0.5))* (PI / 4) * C_CPM* E_CPM * d_CPM * d_CPM * pow((2*DP_CCL * Dmix_CPS), 0.5);	//全用国标单位，计算结果单位：kg/s


    Qm_CPS = Qm_A * Qm_CPS + Qm_B;
	PRONEERS_LOG("(15):Qm_CPS = %f ; Qm_A = %f ; Qm_B = %f\n",Qm_CPS,Qm_A,Qm_B);

    /*(16)计算气液流量*/
    Qmg_CPS = 3600*Qm_CPS * GMF_CPS_C;			//此时Qmg_CPS与Qml_CPS均为kg/h
    Qml_CPS = 3600*Qm_CPS * LMF_CPS_C;


    /*(17)气液流量单独修正*/
    Qmg_CPS = Qmg_A * Qmg_CPS + Qmg_B;
    Qml_CPS = Qml_A * Qml_CPS + Qml_B;
	PRONEERS_LOG("(17):Qmg_A = %f ; Qmg_B = %f\n",Qmg_A,Qmg_B);
	PRONEERS_LOG("(17):Qml_A = %f ; Qmg_l = %f\n",Qml_A,Qml_B);


    /*(14)小流量切除*/		//消除小流量切除后，修正截距不为零的情况
    if(DP_CCL < DP_th)
    {
        Qmg_CPS = 0;
        Qml_CPS = 0;
    }

    /*(18)质量流量累加计算*/
    PRONEERS_LOG("(18):Qmg_ori = %f ; Qml_ori = %f\n",Qmg_ori,Qml_ori);

    Qmg_add_CPS = Qmg_ori;			//将上一秒计算的原始累加量赋值到本地
    Qml_add_CPS = Qml_ori;
    PRONEERS_LOG("(18):Qmg_add_CPS = %f ; Qml_add_CPS = %f\n",Qmg_add_CPS,Qml_add_CPS);
    PRONEERS_LOG("(18):Qmg_ori = %f ; Qml_ori = %f\n",Qmg_ori,Qml_ori);

    Qmg_add_CPS = Qmg_CPS / 3600 + Qmg_add_CPS;
    Qml_add_CPS = Qml_CPS / 3600 + Qml_add_CPS;
    PRONEERS_LOG("(18):Qmg_add_CPS = %f ; Qml_add_CPS = %f\n",Qmg_add_CPS,Qml_add_CPS);
    PRONEERS_LOG("(18):Qmg_ori = %f ; Qml_ori = %f\n",Qmg_ori,Qml_ori);

    /*(19)标况体积流量计算*/
    Qvg_CPS = Qmg_CPS / Dg_SC;		//Nm3/h
    Qvl_CPS = Qml_CPS / Dw_SC;
    PRONEERS_LOG("(19):Qvg_CPS = %f ; Qvl_CPS = %f\n",Qvg_CPS,Qvl_CPS);

    /*(20)标况体积流量累加计算*/
    Qvg_ori = Qmg_ori / Dg_SC;		//Nm3
    Qvl_ori = Qml_ori / Dw_SC;		//m3
    PRONEERS_LOG("(20):Qvg_ori = %f ; Qvl_ori = %f\n",Qvg_ori,Qvl_ori);

    Qvg_add_CPS = Qvg_ori;			// Nm3/h
    Qvl_add_CPS = Qvl_ori;


    Qvg_add_CPS = Qvg_CPS/3600 + Qvg_add_CPS;
    Qvl_add_CPS = Qvl_CPS/3600 + Qvl_add_CPS;
    PRONEERS_LOG("(20):Qvg_add_CPS = %f ; Qvl_add_CPS = %f\n",Qvg_add_CPS,Qvl_add_CPS);

    /*1,前60秒压力及工况气密度平均值*/
    if (indx_P >= 60)
    {
        indx_P = 0;
    }

    k[indx_P] = P_WC_CPS;		//1
    u[indx_P] = Dgwc_CPS;		//2

    for (i_P = 0; i_P < 60; i_P++)
    {
        if (k[i_P] != 0)
        {
            effective_P++;
            P_WC_CPM 	= P_WC_CPM 	+ k[i_P];		//1
            Dgwc_CPM	= Dgwc_CPM 	+ u[i_P];		//2
        }
    }

    if (effective_P != 0)
    {
        P_WC_CPM 	= (P_WC_CPM 	/ effective_P);	//1
        Dgwc_CPM 	= (Dgwc_CPM 	/ effective_P);	//2
    }

    indx_P++;

	PRONEERS_LOG("1,P_WC_CPM = %f ; P_WC_CPS = %f\n",P_WC_CPM,P_WC_CPS);

    /*2,前60秒原始GVF平均值*/
    if (indx_GVF >= 60)
    {
        indx_GVF = 0;
    }

    l[indx_GVF] = GVF_CPS;
    for (i_GVF = 0; i_GVF < 60; i_GVF++)
    {
        if (l[i_GVF] != 0)
        {
            effective_GVF++;
            GVF_CPM = GVF_CPM + l[i_GVF];
        }
    }

    if (effective_GVF != 0)
    {
        GVF_CPM = (GVF_CPM / effective_GVF);
    }

    indx_GVF++;
    LVF_CPM = 1 - GVF_CPM;
	PRONEERS_LOG("2,GVF_CPM = %f ; GVF_CPS = %f\n",GVF_CPM,GVF_CPS);
	PRONEERS_LOG("2,LVF_CPM = %f ; LVF_CPS = %f\n",LVF_CPM,LVF_CPS);

    /*3,前60秒原始GMF平均值*/
    if (indx_GMF >= 60)
    {
        indx_GMF = 0;
    }

    m[indx_GMF] = GMF_CPS;
    for (i_GMF = 0; i_GMF < 60; i_GMF++)
    {
        if (m[i_GMF] != 0)
        {
            effective_GMF++;
            GMF_CPM = GMF_CPM + m[i_GMF];
        }
    }

    if (effective_GMF != 0)
    {
        GMF_CPM = (GMF_CPM / effective_GMF);
    }

    indx_GMF++;
    LMF_CPM = 1 - GMF_CPM;
    PRONEERS_LOG("3,GMF_CPM = %f ; GMF_CPS = %f\n",GMF_CPM,GMF_CPS);
    PRONEERS_LOG("3,LMF_CPM = %f ; LMF_CPS = %f\n",LMF_CPM,LMF_CPS);

    /*4,前60秒GMF_C(修正值)平均值*/
    if (indx_GMF_C >= 60)
    {
        indx_GMF_C = 0;
    }

    n[indx_GMF_C] = GMF_CPS_C;
    for (i_GMF_C = 0; i_GMF_C < 60; i_GMF_C++)
    {
        if (n[i_GMF_C] != 0)
        {
            effective_GMF_C++;
            GMF_CPM_C = GMF_CPM_C + n[i_GMF_C];
        }
    }

    if (effective_GMF_C != 0)
    {
        GMF_CPM_C = (GMF_CPM_C / effective_GMF_C);
    }
    indx_GMF_C++;
    LMF_CPM_C = 1 - GMF_CPM_C;
	PRONEERS_LOG("4,GMF_CPM_C = %f ; GMF_CPS_C = %f\n",GMF_CPM_C,GMF_CPS_C);
	PRONEERS_LOG("4,LMF_CPM_C = %f ; LMF_CPS_C = %f\n",LMF_CPM_C,LMF_CPS_C);

    /*5,前60秒反演GVF平均值*/
    if (indx_GVF_C >= 60)
    {
        indx_GVF_C = 0;
    }

    o[indx_GVF_C] = GVF_CPS_C;
    for (i_GVF_C = 0; i_GVF_C < 60; i_GVF_C++)
    {
        if (o[i_GVF_C] != 0)
        {
            effective_GVF_C++;
            GVF_CPM_C = GVF_CPM_C + o[i_GVF_C];
        }
    }

    if (effective_GVF_C != 0)
    {
        GVF_CPM_C = (GVF_CPM_C / effective_GVF_C);
    }
    indx_GVF_C++;
    LVF_CPM_C = 1 - GVF_CPM_C;
	PRONEERS_LOG("5,GVF_CPM_C = %f ; GVF_CPS_C = %f\n",GVF_CPM_C,GVF_CPS_C);
    PRONEERS_LOG("5,LVF_CPM_C = %f ; LVF_CPS_C = %f\n",LVF_CPM_C,LVF_CPS_C);


    /*6,前60秒反演混合密度平均值*/
    if (indx_Dmix >= 60)
    {
        indx_Dmix = 0;
    }

    p[indx_Dmix] = Dmix_CPS;
    for (i_Dmix = 0; i_Dmix < 60; i_Dmix++)
    {
        if (p[i_Dmix] != 0)
        {
            effective_Dmix++;
            Dmix_CPM = Dmix_CPM + p[i_Dmix];
        }
    }

    if (effective_Dmix != 0)
    {
        Dmix_CPM = (Dmix_CPM / effective_Dmix);
    }
    indx_Dmix++;
    PRONEERS_LOG("6,Dmix_CPM = %f ; Dmix_CPS = %f\n",Dmix_CPM,Dmix_CPS);


    /*7,前60秒差压平均值*/
    if (indx_DP >= 60)
    {
        indx_DP = 0;
    }
    q[indx_DP] = DP_CPS;
    for (i_DP = 0; i_DP < 60; i_DP++)
    {
        if (q[i_DP] != 0)
        {
            effective_DP++;
            //printf("effective_DP = %d\n",effective_DP);
            DP_CPM = DP_CPM + q[i_DP];
            //printf("DP_CPM = %f\n",DP_CPM);
        }
    }

    if (effective_DP != 0)
    {
        DP_CPM = (DP_CPM / effective_DP);
    }

    indx_DP++;
	PRONEERS_LOG("7,indx_DP = %d\n",indx_DP);
    PRONEERS_LOG("7,DP_CPM = %f ; DP_CPS = %f\n",DP_CPM,DP_CPS);

    /*8,总质量流量平均值*/
    if (indx_Qm >= 60)
    {
        indx_Qm = 0;
    }
    r[indx_Qm] = Qm_CPS;

    for (i_Qm = 0; i_Qm < 60; i_Qm++)
    {
        if (r[i_Qm] != 0)
        {
            effective_Qm++;
            //printf("effective_DP = %d\n",effective_DP);
            Qm_CPM = Qm_CPM + r[i_Qm];
            //printf("DP_CPM = %f\n",DP_CPM);
        }
    }

    if (effective_Qm != 0)
    {
        Qm_CPM = (Qm_CPM / effective_Qm);
    }

    indx_Qm++;
    PRONEERS_LOG("8,Qm_CPM = %f ; Qm_CPS = %f\n",Qm_CPM,Qm_CPS);

    /*9,气液流量前60秒平均值*/
    if (indx_Qmg >= 60)
    {
        indx_Qmg = 0;
    }
    s[indx_Qmg] = Qmg_CPS;
    for (i_Qmg = 0; i_Qmg < 60; i_Qmg++)
    {
        if (s[i_Qmg] != 0)
        {
            effective_Qmg++;
            //printf("effective_DP = %d\n",effective_DP);
            Qmg_CPM = Qmg_CPM + s[i_Qmg];
            //printf("DP_CPM = %f\n",DP_CPM);
        }
    }

    if (effective_Qmg != 0)
    {
        Qmg_CPM = (Qmg_CPM / effective_Qmg);
    }

    indx_Qmg++;

    if (indx_Qml >= 60)
    {
        indx_Qml = 0;
    }
    t[indx_Qml] = Qml_CPS;
    for (i_Qml = 0; i_Qml < 60; i_Qml++)
    {
        if (t[i_Qml] != 0)
        {
            effective_Qml++;
            Qml_CPM = Qml_CPM + t[i_Qml];
        }
    }

    if (effective_Qml != 0)
    {
        Qml_CPM = (Qml_CPM / effective_Qml);
    }

    indx_Qml++;

    PRONEERS_LOG("9,Qmg_CPM = %f ; Qmg_CPS = %f\n",Qmg_CPM,Qmg_CPS);
    PRONEERS_LOG("9,Qml_CPM = %f ; Qml_CPS = %f\n",Qml_CPM,Qml_CPS);


    /*10,体积流量*/
    Qv_CPM	= Qm_CPM / Dmix_CPM;	//总的工况体积流量，实际没有什么意义
    Qvg_CPS = Qmg_CPS / Dg_SC;
    Qvl_CPS = Qml_CPS / Dw_SC;
    Qvg_CPM = Qmg_CPM / Dg_SC;
    Qvl_CPM = Qml_CPM / Dw_SC;
    PRONEERS_LOG("10,Qvg_CPS = %f ; Qvl_CPS = %f ; Qmg_CPM= %f ; Qmg_CPM= %f\n",Qvg_CPS,Qvl_CPS,Qvg_CPM,Qvl_CPM);


    /*返回值到结构体*/
    PRONEERS_LOG("flagtype = %d\n",flagtype);
    if (flagtype >= 256)					//按秒存日志
    {
        FlowParass.P_WC_CPS 	=	P_WC_CPS;   //1
        FlowParass.DP_CPS		=	DP_CPS;		//2
        FlowParass.Qmg_CPS		=	Qmg_CPS;	//3,kg/h
        FlowParass.Qml_CPS		=	Qml_CPS;	//4,kg/h

        if(isnormal(Qmg_add_CPS) && isnormal(Qml_add_CPS))
        {
            FlowParass.Qmg_add_CPS	=	Qmg_add_CPS;	//累计流量，kg
            FlowParass.Qml_add_CPS	=	Qml_add_CPS;	//累计流量，kg
            g_qmg_add               =   Qmg_add_CPS;
            g_qml_add               =   Qml_add_CPS;
        }


        FlowParass.Qvg_CPS		=	Qvg_CPS;	//3,Nm3/h
        FlowParass.Qvl_CPS		=	Qvl_CPS;	//4,m3/h

        FlowParass.Qvg_add_CPS	=	Qvg_add_CPS;	//累计流量，Nm3
        FlowParass.Qvl_add_CPS	=	Qvl_add_CPS;	//累计流量，m3

        FlowParass.P_WC_CPM 	=	P_WC_CPS;
        FlowParass.DP_CPM		=	DP_CPS;

//			FlowParass.winA_CPM 	=	Qmg_add_CPS;
//			FlowParass.winD_CPM 	=	Qml_add_CPS;

        FlowParass.winB_CPM 	=	winB_CPS;
        FlowParass.winC_CPM 	=	winC_CPS;
        FlowParass.winE_CPM 	=	winE_CPS;

        FlowParass.GVF_CPM		=	GVF_CPS;
        FlowParass.LVF_CPM		=	LVF_CPS;
        FlowParass.GVF_CPM_C	=	GVF_CPS_C;
        //FlowParass.Dgwc_CPM 	=	Dgwc_CPS;
        //FlowParass.Dmix_CPM 	=	Dmix_CPS;
        FlowParass.GMF_CPM		=	GMF_CPS;
        FlowParass.LMF_CPM		=	LMF_CPS;
        FlowParass.GMF_CPM_C	=	GMF_CPS_C;
        FlowParass.Qm_CPM		=	Qm_CPS;
        FlowParass.Qv_CPM		=	Dgwc_CPS; 		//因工况体积流量无意义，因此暂赋值为工况气密度
        FlowParass.Qmg_CPM		=	Qmg_CPS;
        FlowParass.Qml_CPM		=	Qml_CPS;
        FlowParass.Qvg_CPM		=	Qvg_CPS;
        FlowParass.Qvl_CPM		=	Qvl_CPS;
    }
    else
    {
        FlowParass.P_WC_CPS 	=	P_WC_CPS;
        FlowParass.DP_CPS		=	DP_CPS;

        FlowParass.Qmg_CPS		=	Qmg_CPS;
        FlowParass.Qml_CPS		=	Qml_CPS;

        if(isnormal(Qmg_add_CPS) && isnormal(Qml_add_CPS))
        {
            FlowParass.Qmg_add_CPS	=	Qmg_add_CPS;	//累计流量，kg
            FlowParass.Qml_add_CPS	=	Qml_add_CPS;	//累计流量，kg
            g_qmg_add               =   Qmg_add_CPS;
            g_qml_add               =   Qml_add_CPS;
        }

        FlowParass.Qvg_CPS		=	Qvg_CPS;
        FlowParass.Qvl_CPS		=	Qvl_CPS;

        FlowParass.Qvg_add_CPS	=	Qvg_add_CPS;
        FlowParass.Qvl_add_CPS	=	Qvl_add_CPS;

        FlowParass.P_WC_CPM 	=	P_WC_CPM;
        FlowParass.DP_CPM		=	DP_CPM;

//			FlowParass.winA_CPM 		=	winA_CPM;
//			FlowParass.winD_CPM 		=	winD_CPM;

        FlowParass.winB_CPM 	=	winB_CPM;
        FlowParass.winC_CPM 	=	winC_CPM;
        FlowParass.winE_CPM 	=	winE_CPM;

        FlowParass.GVF_CPM		=	GVF_CPM;
        FlowParass.LVF_CPM		=	LVF_CPM;

        FlowParass.GVF_CPM_C	=	GVF_CPM_C;
        //FlowParass.LVF_CPM_C	=	LVF_CPM_C;

        FlowParass.Dgwc_CPM 	=	Dgwc_CPM;
        FlowParass.Dmix_CPM 	=	Dmix_CPM;

        FlowParass.GMF_CPM		=	GMF_CPM;
        FlowParass.LMF_CPM		=	LMF_CPM;

        FlowParass.GMF_CPM_C	=	GMF_CPM_C;
        //FlowParass.LMF_CPM_C	=	LMF_CPM_C;
        FlowParass.Qm_CPM		=	Qm_CPM;
        FlowParass.Qv_CPM		=	Dgwc_CPM;

        FlowParass.Qmg_CPM		=	Qmg_CPM;
        FlowParass.Qml_CPM		=	Qml_CPM;

        FlowParass.Qvg_CPM		=	Qvg_CPM;
        FlowParass.Qvl_CPM		=	Qvl_CPM;
    }

    PRONEERS_LOG("计算--执行完成\n");
}
/*******************************************************************************
* 函数名称:calculate_para_result
* 函数功能:完成数据合理性检查
* 相关文档:
* 函数参数:
* 参数名称:         类型      输入/输出     描述
* 
* 返回值:
* 函数类型:
* 函数说明:
* 修改日期    版本号   修改人  修改内容（局限在本函数内的缺陷修改需要写在此处）
* -----------------------------------------------------------------
* 
*******************************************************************************/
void calculate_para_result()
{
    int ret;

    ret = isfinite(FlowParass.P_WC_CPS);
    if (ret == 0)
    {
        FlowParass.P_WC_CPS = 0;
    }
    ret = isfinite(FlowParass.DP_CPS);
    if (ret == 0)
    {
        FlowParass.DP_CPS = 0;
    }
    ret = isfinite(FlowParass.Qmg_add_CPS);
    if (ret == 0)
    {
        FlowParass.Qmg_add_CPS = 0;
    }
    ret = isfinite(FlowParass.Qml_add_CPS);
    if (ret == 0)
    {
        FlowParass.Qml_add_CPS = 0;
    }
    ret = isfinite(FlowParass.Qmg_CPS);
    if (ret == 0)
    {
        FlowParass.Qmg_CPS = 0;
    }
    ret = isfinite(FlowParass.Qml_CPS);
    if (ret == 0)
    {
        FlowParass.Qml_CPS = 0;
    }
    ret = isfinite(FlowParass.Qvg_CPS);
    if (ret == 0)
    {
        FlowParass.Qvg_CPS = 0;
    }
    ret = isfinite(FlowParass.Qvl_CPS);
    if (ret == 0)
    {
        FlowParass.Qvl_CPS = 0;
    }
    ret = isfinite(FlowParass.Qvg_add_CPS);
    if (ret == 0)
    {
        FlowParass.Qvg_add_CPS = 0;
    }
    ret = isfinite(FlowParass.Qvl_add_CPS);
    if (ret == 0)
    {
        FlowParass.Qvl_add_CPS = 0;
    }
    ret = isfinite(FlowParass.winA_CPM);
    if (ret == 0)
    {
        FlowParass.winA_CPM = 0;
    }
    ret = isfinite(FlowParass.winB_CPM);
    if (ret == 0)
    {
        FlowParass.winB_CPM = 0;
    }
    ret = isfinite(FlowParass.winC_CPM);
    if (ret == 0)
    {
        FlowParass.winC_CPM = 0;
    }
    ret = isfinite(FlowParass.winD_CPM);
    if (ret == 0)
    {
        FlowParass.winD_CPM = 0;
    }
    ret = isfinite(FlowParass.winE_CPM);
    if (ret == 0)
    {
        FlowParass.winE_CPM = 0;
    }
    ret = isfinite(FlowParass.P_WC_CPM);
    if (ret == 0)
    {
        FlowParass.P_WC_CPM = 0;
    }
    ret = isfinite(FlowParass.DP_CPM);
    if (ret == 0)
    {
        FlowParass.DP_CPM = 0;
    }
    ret = isfinite(FlowParass.GVF_CPM);
    if (ret == 0)
    {
        FlowParass.GVF_CPM = 0;
    }
    ret = isfinite(FlowParass.LVF_CPM);
    if (ret == 0)
    {
        FlowParass.LVF_CPM = 0;
    }
    ret = isfinite(FlowParass.GVF_CPM_C);
    if (ret == 0)
    {
        FlowParass.GVF_CPM_C = 0;
    }
    ret = isfinite(FlowParass.Dgwc_CPM);
    if (ret == 0)
    {
        FlowParass.Dgwc_CPM = 0;
    }
    ret = isfinite(FlowParass.Dmix_CPM);
    if (ret == 0)
    {
        FlowParass.Dmix_CPM = 0;
    }
    ret = isfinite(FlowParass.GMF_CPM);
    if (ret == 0)
    {
        FlowParass.GMF_CPM = 0;
    }
    ret = isfinite(FlowParass.LMF_CPM);
    if (ret == 0)
    {
        FlowParass.LMF_CPM = 0;
    }
    ret = isfinite(FlowParass.GMF_CPM_C);
    if (ret == 0)
    {
        FlowParass.GMF_CPM_C = 0;
    }
    ret = isfinite(FlowParass.Qm_CPM);
    if (ret == 0)
    {
        FlowParass.Qm_CPM = 0;
    }
    ret = isfinite(FlowParass.Qv_CPM);
    if (ret == 0)
    {
        FlowParass.Qv_CPM = 0;
    }
    ret = isfinite(FlowParass.Qmg_CPM);
    if (ret == 0)
    {
        FlowParass.Qmg_CPM = 0;
    }
    ret = isfinite(FlowParass.Qml_CPM);
    if (ret == 0)
    {
        FlowParass.Qml_CPM = 0;
    }
    ret = isfinite(FlowParass.Qvg_CPM);
    if (ret == 0)
    {
        FlowParass.Qvg_CPM = 0;
    }
    ret = isfinite(FlowParass.Qvl_CPM);
    if (ret == 0)
    {
        FlowParass.Qvl_CPM = 0;
    }

    //todo:数据呗冲掉 flowresult
    FlowParasult.Qm_CPM       = FlowParass.Qm_CPM;
    FlowParasult.Qv_CPM       = FlowParass.Qv_CPM;
    FlowParasult.GMF_CPM      = FlowParass.GMF_CPM;
    FlowParasult.LMF_CPM      = FlowParass.LMF_CPM;
    FlowParasult.GVF_CPM      = FlowParass.GVF_CPM;
    FlowParasult.LVF_CPM      = FlowParass.LVF_CPM;
    FlowParasult.Qml_add_CPS  = FlowParass.Qml_add_CPS;
    FlowParasult.Qmg_add_CPS  = FlowParass.Qmg_add_CPS;
    FlowParasult.Qvl_CPM      = FlowParass.Qvl_CPM;
    FlowParasult.Qvg_CPM      = FlowParass.Qvg_CPM;
    FlowParasult.Qml_CPS      = FlowParass.Qml_CPS;
    FlowParasult.Qmg_CPS      = FlowParass.Qmg_CPS;
    FlowParasult.T_P_WC_CPS   = FlowParass.T_P_WC_CPS;
    FlowParasult.P_WC_CPM     = FlowParass.P_WC_CPM;
    PRONEERS_LOG("数据检查--执行完成\n");
}
