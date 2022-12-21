#include "hal_base.h"
#include "volume_control.h"

int volume_control_init(char *inbuffer, char **outbuffer, uint32_t *outlength)
{
    uint32_t ret;
    VolumeArgs *volargs = (VolumeArgs *)inbuffer;;
    VolumeHandle *volhandle = malloc(sizeof(VolumeHandle));

    memcpy(&volhandle->volargs, inbuffer, volargs->offset);

    volhandle->volargs.volume_value = malloc(volargs->size);
    memcpy(volhandle->volargs.volume_value, (inbuffer + volargs->offset), volargs->size);

    switch(volargs->args.function)
    {
        case FUNC_VOLUME_MUTE:
            /* volume control mute function does not need to be initialized */
            volhandle->st_volume = NULL;
            ret = HAL_TRUE;
            break;
        case FUNC_VOLUME_CTRL:
            volhandle->st_volume = Volume_Struct_init(volhandle->volargs.args.channels, volhandle->volargs.args.samplerate,\
                                   volhandle->volargs.model_en, volhandle->volargs.slew_rate, volhandle->volargs.value_num,\
                                                                                            volhandle->volargs.volume_value);
            ret = HAL_TRUE;
            break;
        default:
            ret = HAL_FALSE;
            break;
    }

    *outlength = 2 * sizeof(uint32_t);
    *outbuffer = malloc(*outlength);

    volargs->args.args_addr = (uint32_t)volhandle;

    memcpy(*outbuffer, &volargs->args, *outlength);

    return ret;
}

int volume_control_process(char *inbuffer, char **outbuffer, uint32_t *outlength)
{
    uint32_t ret;
    uint32_t offset;
    char *temp_inbuffer;
    char *temp_outbuffer;
    VolumeHandle *volhandle = NULL;
    VolumeArgs *volargs = (VolumeArgs *)inbuffer;
    volhandle = volargs->args.args_addr;

    offset = 2 * ALGO_BUFFER_FRAME_UINT_WIDTH;
    *outlength = volhandle->volargs.args.periodsize * volhandle->volargs.args.channels *\
                                               (volhandle->volargs.args.samplebits >> 3);

    /* Skip Frame Header */
    temp_inbuffer = inbuffer + offset;
    /* Include Frame Header */
    temp_outbuffer = (char *)malloc(*outlength + offset);
    /* request for memory space required by algorithm */
    SKV_BYTE* in = (SKV_BYTE*)temp_inbuffer;
    SKV_BYTE* out = (SKV_BYTE*)(temp_outbuffer + offset);

    float* data_in = (float*)malloc(volhandle->volargs.args.periodsize *\
                                    volhandle->volargs.args.channels * sizeof(float));
    float* data_out = (float*)malloc(volhandle->volargs.args.periodsize *\
                                     volhandle->volargs.args.channels * sizeof(float));

    skv_bytes2floats(in, data_in, volhandle->volargs.args.channels * volhandle->volargs.args.periodsize,\
                                                                  volhandle->volargs.args.samplebits, 0);

    switch(volhandle->volargs.args.function)
    {
        case FUNC_VOLUME_MUTE:
            for (int i = 0; i < volhandle->volargs.args.periodsize; i++)
            {
                Mute(data_in + volhandle->volargs.args.channels * i, data_out + volhandle->volargs.args.channels * i,\
                                                       volhandle->volargs.args.channels, volhandle->volargs.on_flag);
            }
            ret = HAL_TRUE;
            break;
        case FUNC_VOLUME_CTRL:
            for (int i = 0; i < volhandle->volargs.args.periodsize; i++)
            {
                Volume_Control(volhandle->st_volume, data_in + volhandle->volargs.args.channels * i,\
                                                    data_out + volhandle->volargs.args.channels * i);
            }
            ret = HAL_TRUE;
            break;
        default:
            ret = HAL_FALSE;
            break;
    }

    skv_floats2bytes(data_out, out, volhandle->volargs.args.channels * volhandle->volargs.args.periodsize,\
                                                                    volhandle->volargs.args.samplebits, 0);

    *outlength = *outlength + offset;
    *outbuffer = (char *)temp_outbuffer;
    memcpy(*outbuffer, &volargs->args.algo_type, ALGO_BUFFER_FRAME_UINT_WIDTH);
    memcpy(*outbuffer + ALGO_BUFFER_FRAME_UINT_WIDTH, &volargs->args.args_addr, ALGO_BUFFER_FRAME_UINT_WIDTH);

    free(data_in);
    free(data_out);

    return ret;
}

int volume_control_deinit(char *inbuffer, char **outbuffer, uint32_t *outlength)
{
    uint32_t ret;
    VolumeHandle *volhandle;
    VolumeArgs *volargs = (VolumeArgs *)inbuffer;

    volhandle = volargs->args.args_addr;

    Volume_Struct_destroy(volhandle->st_volume);

    if (volhandle->volargs.args.function == FUNC_VOLUME_CTRL)
    {
        free(volhandle->volargs.volume_value);
    }
    free(volhandle);

    *outlength = 0;
    *outbuffer = NULL;

    ret = HAL_TRUE;

    return ret;
}
