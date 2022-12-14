#ifndef _LOUNDNESS_H_
#define _LOUNDNESS_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    void** rkstudio_loudness_init(int In_SampleRate, int In_NumChannel, int Bass_Freq, int Bass_Gain, int Treble_Freq, int Treble_Gain, int Post_Gain);
    void rkstudio_loudness_process(void** st_ptr, float* data_in, float* data_out);
    void rkstudio_loudness_destroy(void** st_ptr);

#ifdef __cplusplus
}
#endif
#endif
