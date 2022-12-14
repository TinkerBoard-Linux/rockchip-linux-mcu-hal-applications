#ifndef _FILTER_H_
#define _FILTER_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    enum FILTER_ORDER {
        Filter2nd = 0,
        Filter1st = 1,
        Multi_Fir = 2,
    };

    static float fir_coeff1[5] = { 1.0f, 0.4f, -0.3f, 0.2f, -0.1f };//For High order FIR

    enum FILTER_TYPE {
        Parametric = 0,
        LowShelf = 1,
        HighShelf = 2,
        GeneralLP = 3,
        GeneralHP = 4,
        GeneralBP = 5,
        GeneralBS = 6,
        BesselLP = 7,
        BesselHP = 8,
        ButterLP = 9,
        ButterHP = 10,
        Tone = 11,
        IIR = 12,
        FirstOrderFilters = 13,
        APF = 14,
        Peaking = 15,
        Notch = 16,
        ChebyshevLP = 17,
        ChebyshevHP = 18,
        LP1st = 19,
        HP1st = 20,
        AP1st = 21,
        LS1st = 22,
        HS1st = 23,
    };

    typedef struct FilterParam_ {
        // --- 1st or 2nd ---
        int filter_type;
        int algorithm; // filter algorithm
        float gain; // linea gain:dB
        // Common filter parameters
        float fc; // cutoff freq or center freq
        float Q; // quality factor
        float boost_dB;
        // Tone Control
        float fc_treble;
        float boost_treble_dB;
        float fc_bass;
        float boost_bass_dB;
        // IIR
        float b0_p;
        float b1_p;
        float b2_p;
        float a1_p;
        float a2_p;
        // First Order Filters
        // multiplexed tone filter parameters
        int filter1st; // 0: NoActive 1:LP 2:HP 3:AP
        int filter2nd; // 0: NoActive 1:LP 2:HP 3:AP
        // --- fir ---
        int fir_len;    // fir coefficient length
        float* coeffs;  // coefficient struct
    } FilterParam;

    void* Filters_Struct_Init(int Smaple_Rate,int chan, FilterParam* param_ptr);

    FilterParam* Filters_Param_Init(void);

    void Filters_set_Param(void* st_ptr, void* param_ptr);

    void Filters_Process(void* st_ptr, float* data_in, float* data_out);

    int Filters_destroy(void* st_ptr);

    inline static void Filters_Param_Reset(FilterParam* param) {
        param->filter_type = Filter2nd;
        if (param->filter_type == Filter2nd) {
            param->algorithm = Notch;
            param->fc = 1000;
            param->Q = 1.4f;
            param->gain = 0;
        }
        else if (param->filter_type == Filter1st) {
            param->algorithm = LP1st;
            param->fc = 1000;
            param->gain = 0;
        }
        else if (param->filter_type == Multi_Fir) {
            param->fir_len = 5;
            param->coeffs = fir_coeff1;
        }
        else {
            fprintf(stderr, "wrong filter type in Param Reset\n");
        }
    }

#ifdef __cplusplus
}
#endif
#endif
