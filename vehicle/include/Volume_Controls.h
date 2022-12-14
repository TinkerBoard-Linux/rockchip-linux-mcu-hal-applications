#ifndef _VOLUME_CONTROLS_H_
#define _VOLUME_CONTROLS_H_
#ifdef __cplusplus
extern "C" {
#endif
    typedef enum VolumeType_ {
        Linear = 1 << 0,
        DB = 1 << 1,
        RC = 1 << 2
    }VolumeType;
    void Mute(float* in, float* out, int num_Channel, int On_Flag);
    void* Volume_Struct_init(int num_channel, int Sample_Rate, int model_en, int Slew_Rate, int value_number, float* value);
    void Volume_Control(void* st_ptr, float* in, float* out);
    void Volume_Struct_Reset(void* st_ptr, float* value);
    void Volume_Struct_destroy(void* st_ptr);

#ifdef __cplusplus
}
#endif

#endif

