#ifndef _RKAUDIO_AGC_H_
#define _RKAUDIO_AGC_H_

#define AGC_LENGTH 8

#ifdef __cplusplus
extern "C" {
#endif
    typedef enum RKDPPro_
    {
        EN_Envelop = 1 << 0,
        EN_DRC = 1 << 1,
        EN_Limiter = 1 << 2,
    }RKDPPro;

    typedef enum RKDPEnable_
    {
        EN_Peak = 1 << 0,
        EN_Rms = 1 << 1,
        EN_Soft = 1 << 2,
    }RKDPEnable;

    typedef struct RKAGCParam_ {
        int                 model_en;
        int                 fs;
        int                 bit_rate;
        int                 point_len;
        float               RMS_TC;
        float               attack_time;
        float               hold_time;
        float               release_time;
        float               post_gain;
        int                 threhold;
        short int           * graph_x;
        short int           * graph_y;
    } RKAGCParam;

    RKAGCParam* rkstudio_agc_param_init(short* graph_x, short* graph_y);

    inline static  void rkstudio_agc_param_reset(void* Param_, short* graph_x, short* graph_y, int model_en, int Sampling_rate, int bit_rate, int point_len, float RMS_TC, float attack_time, float hold_time, float release_time, float post_gain,int threhold)
    {
        RKAGCParam* param = (RKAGCParam*)Param_;
        param->model_en = model_en;
        param->fs = Sampling_rate;
        param->bit_rate = bit_rate;
        param->point_len = point_len;
        param->RMS_TC = RMS_TC;
        param->attack_time = attack_time;
        param->hold_time = hold_time;
        param->release_time = release_time;
        param->post_gain = post_gain;
        param->graph_x = graph_x;
        param->graph_y = graph_y;
        param->threhold = threhold;
    };

    void* rkstudio_dp_init(int nChan, int bit_rate,int sampling_rate, void* param_);
    void rkstudio_DP_Process(void* st_ptr, float* pshwIn, float* pshwOut, int type);
    void rkstudio_dp_destory(void* st);


#ifdef __cplusplus
}
#endif

#endif

