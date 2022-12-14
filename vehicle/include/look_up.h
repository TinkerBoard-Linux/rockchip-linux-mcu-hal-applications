/**
*  @file look_up.h
*  @brief Implement the corresponding function of the ADI "Filters/Second Order/Look Up" module.
*/

#ifndef LOOK_UP_H
#define LOOK_UP_H

#include "malloc.h"

#ifdef __cplusplus
extern "C" {
#endif

    enum LOOKUP_TYPE {
        Tone_Low_Shelf = 0,
        Tone_High_Shelf = 1,
        LU_Peaking = 2,
        LU_GeneralLP = 3,
        LU_GeneralHP = 4,
        LU_ButterLP = 5,
        LU_ButterHP = 6,
        LU_BesselLP = 7,
        LU_BesselHP = 8,
        LU_ChebyshevLP = 9,
        LU_ChebyshevHP = 10,
    };

    typedef struct LookUpParam_ {
        int algorithm; // filter algorithm
        int num_curves; // number of filter curves
        float boost_min; // minimum value of boost range
        float boost_max; // maximum value of boost range
        float gain; // overall filter gain(unit:dB)
        float Q; // quality factor
        float fc_min; // minimum value of cut-off freq range
        float fc_max; // maximum value of cut-off freq range
    }LookUpParam;

    LookUpParam* Filters_LookUp_paramInit();

    // Strucrture initialization
    void* Filters_LookUp_filterInit(int sampling_rate, int num_channel, void* param_);

    // Structure destory
    int Filters_LookUp_filterDestroy(void* st_);

    // Setting parameters
    void Filters_LookUp_filterSetParam(void* st_, void* param_);

    // Data processing
    void Filters_LookUp_filterProcess(void* st_, int idx, float* data_in, float* data_out);

    // Example of parameter setting
    inline static void LookUp_Param_Reset(void* param_ptr)
    {
        LookUpParam* param = (LookUpParam*)param_ptr;

        param->algorithm = 0;
        param->num_curves = 4;
        param->boost_min = -10.0f;
        param->boost_max = 10.0f;
        param->gain = -5.0f;
        param->Q = 0.7071f;
        param->fc_min = 100.0f;
        param->fc_max = 300.0f;
	}

#ifdef __cplusplus
}
#endif

/** @}*/
#endif // LOOK_UP_H
