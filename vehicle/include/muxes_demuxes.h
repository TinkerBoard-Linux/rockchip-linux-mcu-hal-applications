/**
*  @file muxes_demuxes.h
*  @brief Implement the corresponding function of the ADI "Muxes_Demuxes" module.
*/
#ifndef MUXES_DEMUXES_H
#define MUXES_DEMUXES_H

#include <malloc.h>

#define NUM_CHAN 2
// fadein/fadeout time:80ms
#define SLEW_RATE 0.99971659f

#ifdef __cplusplus
extern "C" {
#endif
    // ====== state machine ======
    static int state_machine_coeff1[NUM_CHAN *2] = {1, 2, 3, 4,};

    // init function, num_channel should be equal tp NUM_CHAN
    void* Statemachine_Init(int num_channel, int* coeffs);

    // destroy function
    int Statemachine_Destroy(void* st_);

    // set parameter
    void Statemachine_Reset(void* st_, int num_channel, int* coeffs);

    // process function
    void Statemachine_Process(void* st_, int control, float* data_in, float* data_out);

    // ====== multiplexers ======
    void* Multiplexers_Init(int sample_rate, int num_MX, int output_channel, int slew_flag);

    int Multiplexers_Destroy(void* st_);

    void Multiplexers_Process(void* st_, int idx, float* data_in, float* data_out);


    // ====== demultiplexers ======
    void* DeMultiplexers_Init(int sample_rate, int num_DmX, int type, int slew_flag);

    int DeMultiplexers_Destroy(void* st);

    void DeMultiplexers_Process(void* st, int idx, float* data_in, float* data_out);


#ifdef __cplusplus
}
#endif

/** @}*/
#endif // MUXES_DEMUXES_H
