
#ifndef SCHEMATIC_DESIGN_H
#define SCHEMATIC_DESIGN_H

#include <stdio.h>
#include "string.h"


#ifdef __cplusplus
extern "C" {
#endif

    void ChannelCopy(float* in, float* out, int n);
    void HardClip_Controll(float* in, float high_thresh, float low_thresh, int chan_num, int Out_bitPerSample);
    void SoftClip_Controll(float* in, float alpha, int chan_num, int Out_bitPerSample);
    void eq_response_check(void** st_ptr, int Band_Num, int In_SampleRate, int resolution, char* Spk_File, FILE* fp_xls);
    void LookupFilter_Response_Check(void* st_fltlkup, int In_sampleRate, float Freqresol, FILE* fp_xls);
    void CrossoverFilter_Response_Check(void* st_fltcrossover, int In_sampleRate, float Freqresol, FILE* fp_xls);
    void MiscellFilter_Response_Check(void* st_miscell, int In_sampleRate, float Freqresol, FILE* fp_xls);

#ifdef __cplusplus
}
#endif

#endif // SCHEMATIC_DESIGN_H
