/**
*  @file rkaudio_preprocess.h
*  @brief parameter initialization
*/
#ifndef _RKAUDIO_PREPROCESS_H_
#define _RKAUDIO_PREPROCESS_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum _RT_RET {
    RT_OK                      = 0,

    RT_ERR_BAD                 = -1,
    RT_ERR_UNKNOWN             = -2,
    RT_ERR_NULL_PTR            = -3,
    RT_ERR_MALLOC              = -4,
    RT_ERR_OPEN_FILE           = -5,
    RT_ERR_VALUE               = -6,
    RT_ERR_READ_BIT            = -7,
    RT_ERR_TIMEOUT             = -8,
    RT_ERR_UNIMPLIMENTED       = -9,
    RT_ERR_UNSUPPORT           = -10,
    RT_ERR_SUSPEND             = -11,
    RT_ERR_NO_BUFFER           = -12,
    RT_ERR_HW_UNSUPPORT        = -13,
    RT_ERR_RETRY               = -14,

    RT_ERR_BASE                = -64,

    /* The error in stream processing */
    RT_ERR_INIT                = RT_ERR_BASE - 1,
    RT_ERR_FATAL_THREAD        = RT_ERR_BASE - 2,
    RT_ERR_NOMEM               = RT_ERR_BASE - 3,
    RT_ERR_OUTOF_RANGE         = RT_ERR_BASE - 4,
    RT_ERR_END_OF_STREAM       = RT_ERR_BASE - 5,

    /* The error in list */
    RT_ERR_LIST_BASE           = -128,
    RT_ERR_LIST_EMPTY          = RT_ERR_LIST_BASE - 1,
    RT_ERR_LIST_FULL           = RT_ERR_LIST_BASE - 2,
    RT_ERR_LIST_OUTOF_RANGE    = RT_ERR_LIST_BASE - 3,
} RT_RET;

#include "source.h"
#include "basic_dsp.h"
#include "schematic_design.h"
#include "filter.h"
#include "mixers.h"
#include "muxes_demuxes.h"
#include "rkaudio_agc.h"
#include "Volume_Controls.h"
#include "level_detectors.h"
#include "lookup_tables.h"
#include "Loudness.h"
#include "look_up.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
