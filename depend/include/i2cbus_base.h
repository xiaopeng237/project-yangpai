//
// Created by Administrator on 2020/3/26.
//

#ifndef TMP_I2CBUS_I2CBUS_BASE_H
#define TMP_I2CBUS_I2CBUS_BASE_H

typedef struct{
    int i2cAdjust_Bias_Vf;//调节偏置电压位
    int i2cAdjust_Hight_Vf;//调压命令位

    int i2cAdjust_Hight;//高压
    int i2cAdjust_Bias;
}T_I2cAdjust;

typedef struct{
    int		hour;
    int		minute;
    int		second;
    float   GMF_CPM;
    float   OMF_CPM;
    float	Qv_SUM;
    float	Qmg_CPM;
    float	Qml_CPM;
    float	DataP;//绝压
    float	DataDP;//差压
    float	Qv_CPM;
    float	GVF_CPM;
    float	OVF_CPM;
    float	Qml_CPS;
    float	Qmg_CPS;
    float   Dg_SC;		//标况气密度，单位kg/m3，数据库读取
    float   Dw_SC;		//水密度，单位kg/m3，数据库读取
}T_I2cOled;

typedef struct{
    float ad1115_buf[200][3];
    float i2cAd1115_DPTem;
    float i2cAd1115_BoardTem;

}T_I2cAd1115;

#endif //TMP_I2CBUS_I2CBUS_BASE_H
