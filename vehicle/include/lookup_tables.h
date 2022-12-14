/**
*  @file lookup_tables.h
*  @brief Implement the corresponding function of the ADI "Lookup Tables" module.
*/

#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include "malloc.h"

#define RMS_TABLE_LEN 33

static float mapped_value_reference[RMS_TABLE_LEN] = {
    0.01f, 0.01f, 0.01f, 0.02f, 0.02f, 0.02f, 0.02f, 0.03f, 0.03f, 0.04f, 0.04f,
    0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.10f, 0.12f, 0.13f, 0.15f, 0.18f, 0.21f,
    0.24f, 0.28f, 0.32f, 0.37f, 0.42f, 0.49f, 0.57f, 0.65f, 0.75f, 0.87f, 1.01f,
};


#ifdef __cplusplus
extern "C" {
#endif

    void* RMS_Tables_Init(int bit_rate, int sampling_rate, int Increase, int Hold, int Decay, int len_table, float* table);

    int RMS_Tables_Destory(void* st_);

    void RMS_Tables_Reset(void* st_, int Increase, int Hold, int Decay, int len_table, float* table);

    void RMS_Tables_Process(void* st_, float* data_in, float* mapped_out);

    void* Lookup_Tables_Init(int len_table, float* table);

    int Lookup_Tables_Destory(void* st_);

    void Lookup_Tables_Process(void* st_, int* index_in, float* mapped_out);


#ifdef __cplusplus
}
#endif

/** @}*/
#endif // LOOKUP_TABLES_H
