//
// Created by Administrator on 2020/3/27.
//

#ifndef PROJECT_ADJUST_ADJUST_SERVICE_BASE_H
#define PROJECT_ADJUST_ADJUST_SERVICE_BASE_H

typedef struct {
    float           AdjustIn_th_sum;
    float           AdjustIn_WIN_en;
    float           AdjustIn_HIV_en;
    float           AdjustIn_Hight_Vf;
    float           AdjustIn_Hight_C;
    float           AdjustIn_Hight;
    float           AdjustIn_PCH31;
    float           AdjustIn_PCH81;
    float           AdjustIn_PCH356;
    float           AdjustIn_CON_B1;
    float           AdjustIn_CON_B2;
    float           AdjustIn_CON_C1;
    float           AdjustIn_CON_C2;
    float           AdjustIn_CON_E1;
    float           AdjustIn_CON_E2;
    unsigned int    AdjustIn_S_es[8192];

    int             AdjustIn_reality_b1;
    int             AdjustIn_reality_b2;
    int             AdjustIn_reality_e1;
    int             AdjustIn_reality_e2;
}T_AdjustIn;



typedef struct{

    float       AdjustOut_a2;
    float       AdjustOut_b2;
    int         AdjustOut_F31;
    int         AdjustOut_F81;
    int         AdjustOut_F356;
    float       AdjustOut_WIN_J;
    float       AdjustOut_Hight_Vf;
    float       AdjustOut_Hight;
}T_AdjustOut;
#endif //PROJECT_ADJUST_ADJUST_SERVICE_BASE_H
