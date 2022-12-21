/**
  * Copyright (c) 2022 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "skv_ulity.h"
#include "rkaudio_preprocess.h"

#define ALGO_BUFFER_FRAME_UINT_WIDTH                4

enum
{
    /* filter algorithm module */
    ALGO_FILTERS_INIT = 0,
    ALGO_FILTERS_DEINIT,
    ALGO_FILTERS_PROCESS,
    /* loudness algorithm module */
    ALGO_LOUDNESS_INIT,
    ALGO_LOUDNESS_DEINIT,
    ALGO_LOUDNESS_PROCESS,
    /* volume control algorithm module */
    ALGO_VOLUME_CONTROL_INIT,
    ALGO_VOLUME_CONTROL_DEINIT,
    ALGO_VOLUME_CONTROL_PROCESS,
};

typedef struct args_frame_info
{
    uint32_t algo_type;
    uint32_t args_addr;

    uint32_t function;
    uint32_t channels;
    uint32_t samplebits;
    uint32_t samplerate;
    uint32_t periodsize;
}ArgsFrameInfo;

#endif

