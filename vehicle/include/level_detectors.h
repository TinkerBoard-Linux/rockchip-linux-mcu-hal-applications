/**
*  @file level_detectors.h
*  @brief Implement the corresponding function of the ADI "Level Detectors" module.
*/

#ifndef LEVEL_DETECTORS_H
#define LEVEL_DETECTORS_H

#include "malloc.h"

enum LEVEL_DETECTOR_TYPE {
    Single_Band = 0,
    Seven_Band = 1,
};

#ifdef __cplusplus
extern "C" {
#endif

    void* Level_Detectors_Init(int bit_rate, int sampling_rate, int detector_type);

    int Level_Detectors_Destory(void* st_);

    float* Level_Detectors_Process(void* st_, float* data_in, float* data_out);

#ifdef __cplusplus
}
#endif

/** @}*/
#endif // LEVEL_DETECTORS_H
