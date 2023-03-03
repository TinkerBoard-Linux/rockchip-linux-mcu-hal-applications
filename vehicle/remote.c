/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd.
 */

#include "remote.h"
#include "middleware_conf.h"

static uint32_t Interrupt = 0;

static int32_t remote_ept_cb(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    memcpy((char *)priv, payload, payload_len);

    Interrupt = 1;

    return RL_RELEASE;
}

int aupipe_launch(void *arg)
{
    uint32_t send_buf[2], recv_buf[2];
    uint32_t remote_addr, lenght;

    struct rpmsg_lite_endpoint *ept;
    struct rpmsg_lite_instance *instance;

    instance = rpmsg_remote_get_instance(MASTER_ID, REMOTE_ID_0);

    ept = rpmsg_lite_create_ept(instance, EPT_M2R_ADDR(EPT_M1R0_ECNR), remote_ept_cb, &recv_buf);

    while (1)
    {
        if (Interrupt)
        {
            Interrupt = 0;

            switch (recv_buf[0])
            {
            case ECNR_INIT:
                send_buf[0] = ecnr_init(recv_buf[1]);
                break;
            case ECNR_DEINIT:
                send_buf[0] = ecnr_deinit(recv_buf[1]);
                break;
            case ECNR_PROCESS:
                send_buf[0] = ecnr_process(recv_buf[1], recv_buf[2]);
                break;
            default:
                break;
            }
            rpmsg_lite_send(instance, ept, EPT_M1R0_ECNR, send_buf, sizeof(send_buf), RL_BLOCK);
        }
        HAL_DelayUs(1);
    }

    return RL_RELEASE;
}

