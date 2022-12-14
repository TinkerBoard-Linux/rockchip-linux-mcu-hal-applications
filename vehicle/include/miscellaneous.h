/**
*  @file miscellaneous.h
*  @brief Implement the corresponding function of the ADI "Filters/Miscellaneous" module.
*/

#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "malloc.h"

#ifdef __cplusplus
extern "C" {
#endif

    // ================= DC Blocking =================
    // Strucrture initialization
    void* Filters_Miscell_dcBlockingInit(int num_channel);

    // Structure destory
    int Filters_Miscell_dcBlockingDestroy(void* st_);

    // Data processing
    void Filters_Miscell_dcBlockingProcess(void* st_, float* data_in, float* data_out);


    // ================= State Variable =================
    // Strucrture initialization
    void* Filters_Miscell_stateVariableInit(int sampling_rate, int num_channel, float fc, float Q);

    // Structure destory
    int Filters_Miscell_stateVariableDestroy(void* st);

    // Setting parameters
    void Filters_Miscell_stateVariableReset(void* st, float fc, float Q);

    // Data processing
    void Filters_Miscell_stateVariableProcess(void* st, float* data_in, float* data_out);

    // ================= Pinking =================
    // Strucrture initialization
    void* Filters_Miscell_pinkingInit(int num_channel);

    // Structure destory
    int Filters_Miscell_pinkingDestroy(void* st);

    // Data processing
    void Filters_Miscell_pinkingProcess(void* st, float* data_in, float* data_out);

#ifdef __cplusplus
}
#endif

/** @}*/
#endif // MISCELLANEOUS_H
