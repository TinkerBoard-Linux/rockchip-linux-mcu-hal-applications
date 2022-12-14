/**
*  @file source.h
*  @brief parameter initialization
*/
#ifndef _RKAUDIO_SOURCE_FUNC_H_
#define _RKAUDIO_SOURCE_FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    #define MAX_CLIME_LENGTH_ENABLE 10

    // 源种类
    typedef enum SOURCE_TYPE {
        ClimeFreq = 0,
        DCInputEntry = 1,
        Oscillator = 2,
        VCO = 3,
        WhiteNoise = 4,
    }SourceType;

    typedef enum OSCILLATOR_TYPE {
        BeeqSource = 0,
        SawtoothWave = 1,
        SineTone = 2,
        SquareWave = 3,
        TriangleWave = 4,
    }OscillatorType;

    typedef enum SWITCH_STATUS {
        SOURCE_SWITCH_OFF = 0,
        SOURCE_SWITCH_ON = 1,
    }SwitchStatus;

    typedef struct Source_ {
        // --- 可调参数 ---
        void *stSource;
        SourceType SourceName;
        OscillatorType SubSourceName;
        SwitchStatus Switch;

        int out_scale;
        int sampleRate; // 采样率
    }Source;

    typedef struct ClimeFrequencySource_ {
        // --- 可调参数 ---
        SwitchStatus Switch;  //0 :OFF  1: ON
        char clime_end_flag;
        char clime_reset_flag;
        int maximum_time;   // 最大持续时间 ms
        int maximum_sample;
        int sample_index;
        int time_index;
        float phi;
        float delta_time;
        int *time_array;
        int *frequency_array;
        int *gain_array;
        int time_length;
        int frequency_length;
        int gain_length;

        int sampleRate; // 采样率
    }ClimeFrequencySource;

    typedef struct DCInputSource_ {
        // --- 可调参数 ---
        char fixedpoint_format; // 0 : 5.23; 1: 8.24; 目前214xx只支持32位即 1
        char integer_bit;
        char decimal_bit;

        SwitchStatus Switch;  //0 :OFF  1: ON
        float input_decimal;
        long input_hex;
        char DC_reset_flag;

        int sampleRate; // 采样率
    }DCInputSource;

    typedef struct OscillatorSource_ {
        // --- 可调参数 ---
        OscillatorType OscillatorSource;
        SwitchStatus Switch;  //0 :OFF  1: ON
        float Freqency;
        float phi;
        float delta_phi;
        char Oscillator_reset_flag;
        int sampleRate; // 采样率
    }OscillatorSource;

    void* Source_Init(int sampling_rate, int Out_bitPerSample, SourceType main_source, OscillatorType sub_source);
    int Source_Destroy(void* st);
    int Source_ReInit(void* st);

    //重新设置
    static inline void Source_ReSetParam(void* param, SourceType main_source)
    {
        Source* stSource = (Source*)param;
        switch (main_source)
        {
        case ClimeFreq:
        {
            ClimeFrequencySource *stClimeFrequency = (ClimeFrequencySource *)(stSource->stSource);
            int DefaultTimeArray[5] = { 0, 100, 500, 800, 1004 };
            int DefaultFreqArray[5] = { 1000, 5000, 12000, 9000, 4000 };
            int DefaultGainArray[5] = { -5, -5, -5, -5, -5 };

            stClimeFrequency->maximum_time = 1004; // 毫秒 ms
            stClimeFrequency->clime_reset_flag = 1;  //must set to 1

            stClimeFrequency->time_length = sizeof(DefaultTimeArray) / sizeof(*DefaultTimeArray);
            stClimeFrequency->frequency_length = sizeof(DefaultFreqArray) / sizeof(*DefaultFreqArray);
            stClimeFrequency->gain_length = sizeof(DefaultGainArray) / sizeof(*DefaultGainArray);

            memcpy(stClimeFrequency->time_array, DefaultTimeArray, stClimeFrequency->time_length * sizeof(int));
            memcpy(stClimeFrequency->frequency_array, DefaultFreqArray, stClimeFrequency->frequency_length * sizeof(int));
            memcpy(stClimeFrequency->gain_array, DefaultGainArray, stClimeFrequency->gain_length * sizeof(int));
            break;
        }
        case DCInputEntry:
        {
            DCInputSource* stDCInput = (DCInputSource*)(stSource->stSource);
            stDCInput->DC_reset_flag = 1;  //must set to 1
            stDCInput->input_decimal = 0.5f;
            break;
        }
        case Oscillator:
        {
            OscillatorSource* stOscillator = (OscillatorSource*)(stSource->stSource);
            stOscillator->Oscillator_reset_flag = 1; //must set to 1
            stOscillator->OscillatorSource = SineTone; //Oscillator : BeeqSource, SawtoothWave, SineTone, SquareWave, TriangleWave,
            stOscillator->Freqency = 10000.0f;
            break;
        }
        case VCO:
            break;
        case WhiteNoise:
            break;
        default:
            break;
        }
    }
    // 数据处理
    int Source_ProcessAudioSample(void* st, float *result, float accept_value);
    int Source_Switch(void* st, SwitchStatus status);

#ifdef __cplusplus
}
#endif

#endif    // _RKAUDIO_SOURCE_FUNC_H_
