/**
*  @file crossover.h
*  @brief Implement the corresponding function of the ADI "Filters/Crossover" module.
*/

#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "malloc.h"

#ifdef __cplusplus
extern "C" {
#endif
    // crossover structure
    enum CROSSOVER_STRUCT_TYPE {
        Two_Way = 0,
        Three_Way = 1,
    };

    // filter algorithm
    enum CROSSOVER_FILTER_TYPE {
        LR12 = 0, // LR: Linkwitz-Riley
        Butter12 = 1,
        Bessel12 = 2,
        Butter18 = 3,
        Bessel18 = 4,
        LR24 = 5,
        Butter24 = 6,
        Bessel24 = 7,
        LR36 = 8,
        LR48 = 9,
    };

    typedef struct CrossoverParam_ {
        int filter_type; // 0: 2-Way   1: 3-Way

        // Low frequency part
        int algorithm_low; // filter algorithm
        float fc_low; // cut-off frequency
        float gaindB_low; // gain in dB scale

        // High frequency part
        int algorithm_high; // filter algorithm
        float fc_high; // cut-off frequency
        float gaindB_high; // gain in dB scale

        // Intermediate frequency part
        int algorithm_med_lp; // filter algorithm
        int algorithm_med_hp; // filter algorithm
        float fc_med_lp; // cut-off frequency
        float fc_med_hp; // cut-off frequency
        float gaindB_med; // gain in dB scale

        // Invert Polarity
        int invert1;
        int invert2;
    }CrossoverParam;

    // Parameter structure initialization
    CrossoverParam* Filters_Crossover_paramInit();

    // Strucrture initialization
    void* Filters_Crossover_filterInit(int sampling_rate, int num_channel, void* param_);

    // Structure destory
    int Filters_Crossover_filterDestroy(void* st_);

    // Setting parameters
    void Filters_Crossover_filterSetParam(void* st_, void* param_);

    // Data processing
    void Filters_Crossover_filterProcess(void* st_, float* data_in, float* data_out);

    // Example of parameter setting
    inline static void Crossover_Param_Reset(void* param_ptr)
    {
        CrossoverParam* param = (CrossoverParam*)param_ptr;
        param->filter_type = Two_Way; // 0: 2-Way  1:3-Way

        // Low frequency part
        param->algorithm_low = LR24;
        param->fc_low = 250;
        param->gaindB_low = 0;

        // High frequency part
        param->algorithm_high = LR24;
        param->fc_high = 3000;
        param->gaindB_high = 0;

        // Additional intermediate frequency configuration is required in 3-Way
        if (param->filter_type == Three_Way)
        {
            param->algorithm_med_lp = LR24;
            param->algorithm_med_hp = LR24;
            param->fc_med_lp = 3000;
            param->fc_med_hp = 250;
            param->gaindB_med = 0;
        }

        // Invert Polarity
        param->invert1 = 0;
        param->invert2 = 0;
    }


#ifdef __cplusplus
}
#endif

/** @}*/
#endif // CROSSOVER_H

