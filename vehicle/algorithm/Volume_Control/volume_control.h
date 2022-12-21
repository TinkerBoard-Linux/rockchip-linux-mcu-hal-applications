#ifndef __VOLUME_CONTROL_H__
#define __VOLUME_CONTROL_H__

#include "algorithm.h"
#include "Volume_Controls.h"

typedef struct volume_args VolumeArgs;
typedef struct volume_handle VolumeHandle;

enum
{
    FUNC_VOLUME_MUTE = 0,
    FUNC_VOLUME_CTRL,
    FUNC_VOLUME_MAX,
};

struct volume_args
{
    ArgsFrameInfo args;

    uint32_t on_flag;

    uint32_t model_en;
    uint32_t slew_rate;
    uint32_t value_num;
    uint32_t size;
    uint32_t offset;
    float *volume_value;
};

struct volume_handle
{
    void *st_volume;
    VolumeArgs volargs;
};

int volume_control_init(char *inbuffer, char **outbuffer, uint32_t *outlength);
int volume_control_deinit(char *inbuffer, char **outbuffer, uint32_t *outlength);
int volume_control_process(char *inbuffer, char **outbuffer, uint32_t *outlength);

#endif