/**
  * Copyright (c) 2022 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include "auipc.h"
#include "volume_control.h"

void HAL_App_Init(void)
{
    int ret;
    uint32_t algo_type;

    char *inbuffer, *outbuffer;
    uint32_t inlength, outlength;

    auipc_rpmsg_remote_init();

    while (1)
    {
        auipc_rpmsg_remote_read(&inbuffer, &inlength);
        HAL_ASSERT(inbuffer != NULL);

        memcpy(&algo_type, inbuffer, ALGO_BUFFER_FRAME_UINT_WIDTH);
        switch(algo_type)
        {
            case ALGO_VOLUME_CONTROL_INIT:
                ret = volume_control_init(inbuffer, &outbuffer, &outlength);
                break;
            case ALGO_VOLUME_CONTROL_DEINIT:
                ret = volume_control_deinit(inbuffer, &outbuffer, &outlength);
                break;
            case ALGO_VOLUME_CONTROL_PROCESS:
                ret = volume_control_process(inbuffer, &outbuffer, &outlength);
                break;
            default:
                break;
        }
        if (outbuffer && outlength)
        {
            ret = auipc_rpmsg_remote_write(outbuffer, outlength);
        }
        free(inbuffer);
        if (outbuffer)
        {
            free(outbuffer);
        }
    }
}

