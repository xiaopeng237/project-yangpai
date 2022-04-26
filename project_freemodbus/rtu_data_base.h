//
// Created by Administrator on 2020/4/29.
//

#ifndef BUILDROOT_PROJECT_RTU_DATA_BASE_H
#define BUILDROOT_PROJECT_RTU_DATA_BASE_H
typedef struct{
    float DP_CPS;
    float P_WC_CPS;
    float T_P_WC_CPS;
    float Qvg_CPS;
    float Qvl_CPS;
    float Qvg_add_CPS;
    float Qvl_add_CPS;
    float Add_Sctime;
}T_RtuData;
#endif //BUILDROOT_PROJECT_RTU_DATA_BASE_H
