/**
  * Copyright (c) 2023 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include "hal_conf.h"

#ifdef HAL_USING_RPMSG_CMD

#include "hal_base.h"
#include "queue.h"
#include "middleware_conf.h"
#include "rpmsg_cmd.h"

#if defined(CPU0)
#define MASTER_EPT EPT_M1R0_SYSCMD
#elif defined(CPU2)
#define MASTER_EPT EPT_M1R2_SYSCMD
#elif defined(CPU3)
#define MASTER_EPT EPT_M1R3_SYSCMD
#else
#error "error: Undefined CPU id!"
#endif

#define REMOTE_EPT EPT_M2R_ADDR(MASTER_EPT)

static int32_t rpmsg_cmd_direct(void *priv, void *addr);

static struct rpmsg_cmd_info_t rpmsg_info;

/*
 * RPMsg ept callback
 *
 */
static int32_t remote_ept_cb(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    rpmsg_fmt_t *rpmsg_fmt = (rpmsg_fmt_t *)payload;
    struct rpmsg_cmd_info_t *info = (struct rpmsg_cmd_info_t *)priv;

    HAL_ASSERT(src == MASTER_EPT);

    switch (rpmsg_fmt->cmd) {
    case RPMSG_TYPE_DIRECT:
        rpmsg_cmd_direct(priv, rpmsg_fmt->addr);
        break;

    case RPMSG_TYPE_WORK:
    {
        /* push rpmsg_fmt->addr to queue */
        queue_t *rq = &info->rq;
        qdata_t qdat;
        qdat.size = payload_len - sizeof(uint32_t);      //size = payload_len - cmd size
        qdat.data = malloc(qdat.size);
        memcpy(qdat.data, &rpmsg_fmt->addr, qdat.size);
        queue_push(rq, &qdat);
        break;
    }

    case RPMSG_TYPE_QUERY:
    {
        /* pop data from queue */
        queue_t *wq = &info->wq;

        if (!queue_empty(wq)) {
            qdata_t *w_qdat = queue_front(wq);

            rpmsg_fmt_t rpmsg_data;
            rpmsg_data.cmd = rpmsg_fmt->cmd;
            rpmsg_data.addr = w_qdat->data;     //rpmsg_fmt->addr;

            if (w_qdat->data) {
                rpmsg_lite_send(info->instance, info->ept, MASTER_EPT, &rpmsg_data, sizeof(rpmsg_fmt_t), RL_BLOCK);
                free(w_qdat->data);
            }
            queue_pop(wq);
        }
        break;
    }

    default:
        HAL_ASSERT(0);
        break;
    }

    return RL_RELEASE;
}

/*
 * Initial rpmsg ept & command info
 *
 */
int rpmsg_cmd_init(void *param)
{
    struct rpmsg_cmd_info_t *info = &rpmsg_info;
    uint32_t master_id = MASTER_ID;
    uint32_t remote_id = HAL_CPU_TOPOLOGY_GetCurrentCpuId();

    memset(info, 0, sizeof(struct rpmsg_cmd_info_t));

    info->instance = rpmsg_remote_get_instance(master_id, remote_id);
    info->ept = rpmsg_lite_create_ept(info->instance, REMOTE_EPT, remote_ept_cb, info);

    queue_init(&info->rq);
    queue_init(&info->wq);

    return HAL_OK;
}

/*
 * RPMsg direct command process
 */
static int32_t rpmsg_cmd_direct(void *priv, void *param)
{
    rpmsg_cmd_t *info = (rpmsg_cmd_t *)priv;
    uint32_t *cmd = (uint32_t *)param;

    rpmsg_fmt_t rpmsg_data;

    rpmsg_data.cmd = RPMSG_TYPE_DIRECT;
    rpmsg_data.addr = param;

    switch (*cmd) {
    case RPMSG_CMD_GET_CPU_USAGE:
    {
        cpuusage_t *usage = (cpuusage_t *)param;
        usage->cmd = RPMSG_ACK_GET_CPU_USAGE;
        usage->data = HAL_GetCPUUsage();
        break;
    }
    default:
        break;
    }
    rpmsg_lite_send(info->instance, info->ept, MASTER_EPT, &rpmsg_data, sizeof(rpmsg_fmt_t), RL_BLOCK);

    return HAL_OK;
}

/*
 * RPMsg work(pop queue) command process
 */
int rpmsg_cmd_process(void *param)
{
    int ret = HAL_OK;
    struct rpmsg_cmd_info_t *info = &rpmsg_info;
    queue_t *rq = &info->rq;

    if (!queue_empty(rq)) {
        qdata_t *r_qdat = queue_front(rq);
        HAL_ASSERT(r_qdat->data);

        struct rpmsg_cmd_fmt_t *msg = (struct rpmsg_cmd_fmt_t *)r_qdat->data;
        switch (msg->cmd) {
        default:
            break;
        }

        if (r_qdat->data) {
            free(r_qdat->data);
        }
        queue_pop(rq);
    }

    return HAL_OK;
}

#endif
