/**
  * Copyright (c) 2023 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#ifndef __RPMSG_CMD_H__
#define __RPMSG_CMD_H__

#include "hal_conf.h"

#ifdef HAL_USING_RPMSG_CMD

#include "middleware_conf.h"

/* RPMsg cmd data format */
struct rpmsg_cmd_info_t {
    struct rpmsg_lite_instance *instance;
    struct rpmsg_lite_endpoint *ept;
    queue_t rq;
    queue_t wq;
};
typedef struct rpmsg_cmd_info_t rpmsg_cmd_t;

/* Cpuusage cmd data format */
struct rpmsg_cmd_cpuusage_t {
    uint32_t cmd;
    uint32_t data;
};
typedef struct rpmsg_cmd_cpuusage_t cpuusage_t;

/* RPMSG CMD define */
#define RPMSG_ACK_GET_CPU_USAGE ((1UL << 1) + 0)
#define RPMSG_CMD_GET_CPU_USAGE ((1UL << 1) + 1)

/* RPMsg CMD API Functions */

#endif

#endif
