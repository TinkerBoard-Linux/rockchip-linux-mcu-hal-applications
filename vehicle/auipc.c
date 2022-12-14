/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2022 Rockchip Electronics Co., Ltd.
 */

#include "auipc.h"

static au_rpmsg_info *auipc_into = NULL;
static au_rpmsg_ept_map au_rpmsg_ept_map_table[3] =
{
    { MASTER_ID, REMOTE_ID0, AU_M1R0_RPMSG_BASE, AU_RPMSG_BLOCK_SIZE, M1R0_EPT0, EPT_M2R_ADDR(M1R0_EPT0), M1R0_EPT1, EPT_M2R_ADDR(M1R0_EPT1) },
    { MASTER_ID, REMOTE_ID1, AU_M1R2_RPMSG_BASE, AU_RPMSG_BLOCK_SIZE, M1R2_EPT0, EPT_M2R_ADDR(M1R2_EPT0), M1R2_EPT1, EPT_M2R_ADDR(M1R2_EPT1) },
    { MASTER_ID, REMOTE_ID2, AU_M1R3_RPMSG_BASE, AU_RPMSG_BLOCK_SIZE, M1R3_EPT0, EPT_M2R_ADDR(M1R3_EPT0), M1R3_EPT1, EPT_M2R_ADDR(M1R3_EPT1) },
};

static int32_t src_ept_rx_cb(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    au_rpmsg_info *info = (au_rpmsg_info *)priv;

    HAL_ASSERT(src == info->map->m_src_ept);

    info->src_msg.len = payload_len;
    info->src_msg.pdata = (char *)payload;

    return HAL_OK;
}

int32_t auipc_rpmsg_remote_read(char **data, uint32_t *size)
{
    au_rpmsg_info *info = auipc_into;
    au_rpmsg_cmd au_cmd;
    au_rpmsg_msg au_msg;
    char *pdata;
    uint32_t remain;
    int32_t ret;

    /* Wait master request */
    while(1) {
        __asm volatile ("cpsid i");
        memcpy(&au_msg, &info->src_msg, sizeof(au_rpmsg_msg));
        info->src_msg.len = 0;
        __asm volatile ("cpsie i");

        if (au_msg.len) {
            HAL_ASSERT(au_msg.len == sizeof(au_rpmsg_cmd));
            memcpy(&au_cmd, au_msg.pdata, sizeof(au_rpmsg_cmd));
            HAL_ASSERT(au_cmd.cmd == AUIPC_MSG_WQ);
            *size = au_cmd.parm[0];

            /* Send ack & buffer size to master*/
            au_cmd.cmd = AUIPC_MSG_WA;
            ret = rpmsg_lite_send(info->instance, info->src_ept, info->map->m_src_ept, (char *)&au_cmd, sizeof(au_rpmsg_cmd), RL_BLOCK);
            HAL_ASSERT(ret == RL_SUCCESS);
            break;
        }
    }

    remain = *size;
    *data = pdata = malloc(remain);
    HAL_ASSERT(pdata != NULL);

    /* Read data */
    while (remain) {
        __asm volatile ("cpsid i");
        memcpy(&au_msg, &info->src_msg, sizeof(au_rpmsg_msg));
        info->src_msg.len = 0;
        __asm volatile ("cpsie i");

        if (au_msg.len) {

            HAL_ASSERT(remain >= au_msg.len);
            memcpy(pdata, au_msg.pdata, au_msg.len);
            remain -= au_msg.len;
            pdata += au_msg.len;

            au_cmd.cmd = AUIPC_MSG_WD;
            ret = rpmsg_lite_send(info->instance, info->src_ept, info->map->m_src_ept, (char *)&au_cmd, sizeof(au_rpmsg_cmd), RL_BLOCK /*RL_FALSE*/);
            HAL_ASSERT(ret == RL_SUCCESS);
        }
    }

    return HAL_OK;
}

void auipc_rpmsg_remote_free(char *pbuf)
{
    free(pbuf);
}

static int32_t sink_ept_rx_cb(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    au_rpmsg_info *info = (au_rpmsg_info *)priv;

    HAL_ASSERT(src == info->map->m_sink_ept);

    info->sink_msg.len = payload_len;
    info->sink_msg.pdata = (char *)payload;

    return HAL_OK;
}

int32_t auipc_rpmsg_remote_write(char *pdata, uint32_t size)
{
    au_rpmsg_info *info = auipc_into;
    au_rpmsg_cmd au_cmd;
    au_rpmsg_msg au_msg;
    uint32_t len;
    int32_t ret;

    /* Wait master request */
    while(1) {
        __asm volatile ("cpsid i");
        memcpy(&au_msg, &info->sink_msg, sizeof(au_rpmsg_msg));
        info->sink_msg.len = 0;
        __asm volatile ("cpsie i");

        if (au_msg.len) {
            memcpy(&au_cmd, au_msg.pdata, sizeof(au_rpmsg_cmd) /*au_msg.len*/);
            HAL_ASSERT(sizeof(au_rpmsg_cmd) == au_msg.len);
            HAL_ASSERT(au_cmd.cmd == AUIPC_MSG_RQ);

            /* Send ack & buffer len to master*/
            au_cmd.cmd = AUIPC_MSG_RA;
            au_cmd.parm[0] = size;
            ret = rpmsg_lite_send(info->instance, info->sink_ept, info->map->m_sink_ept, (char *)&au_cmd, sizeof(au_rpmsg_cmd), RL_BLOCK /*RL_FALSE*/);
            HAL_ASSERT(ret == RL_SUCCESS);
            break;
        }
    }

    /* Write data */
    while (size) {
        // get continuou request
        __asm volatile ("cpsid i");
        memcpy(&au_msg, &info->sink_msg, sizeof(au_rpmsg_msg));
        info->sink_msg.len = 0;
        __asm volatile ("cpsie i");

        if (au_msg.len) {
            memcpy(&au_cmd, au_msg.pdata, au_msg.len);
            HAL_ASSERT(au_msg.len == sizeof(au_rpmsg_cmd));
            HAL_ASSERT(au_cmd.cmd == AUIPC_MSG_RD);
            len = au_cmd.parm[0];   // master paylod size
            HAL_ASSERT(len <= size);

            ret = rpmsg_lite_send(info->instance, info->sink_ept, info->map->m_sink_ept, pdata, len, RL_BLOCK /*RL_FALSE*/);
            HAL_ASSERT(ret == RL_SUCCESS);
            size  -= len;
            pdata += len;
        }
    }

    return HAL_OK;
}

void auipc_rpmsg_remote_init(void)
{
    uint32_t index, remote_id;
    au_rpmsg_info *info;

    HAL_ASSERT((AU_M1R3_RPMSG_BASE + AU_RPMSG_BLOCK_SIZE) <= AU_RPMSG_MEM_END);

    info = malloc(sizeof(struct au_rpmsg_info_t));
    HAL_ASSERT(info != NULL);
    memset(info, 0, sizeof(au_rpmsg_info));

    remote_id = HAL_CPU_TOPOLOGY_GetCurrentCpuId();
    for (index = 0; index < 3; index++) {
        if (au_rpmsg_ept_map_table[index].r_id == remote_id) {
            break;
        }
    }
    HAL_ASSERT(index < 3);
    info->map = &au_rpmsg_ept_map_table[index];

    info->instance = rpmsg_lite_remote_init((void *)info->map->base,
                                            RL_PLATFORM_SET_LINK_ID(info->map->m_id, info->map->r_id), RL_NO_FLAGS);
    HAL_ASSERT(info->instance != NULL);

    rpmsg_lite_wait_for_link_up(info->instance);

    info->sink_ept = rpmsg_lite_create_ept(info->instance, info->map->r_sink_ept, sink_ept_rx_cb, info);
    HAL_ASSERT(info->sink_ept != NULL);
    info->src_ept = rpmsg_lite_create_ept(info->instance, info->map->r_src_ept, src_ept_rx_cb, info);
    HAL_ASSERT(info->src_ept != NULL);

    auipc_into = info;
}

void auipc_rpmsg_remort_deinit(void)
{
    // Destroy...
    free(auipc_into);
}

#if 0   //test
void HAL_App_Init(void)
{
    char *pbuf;
    uint32_t len;
    int32_t ret;

    auipc_rpmsg_remote_init();

    while (1) {
        ret = auipc_rpmsg_remote_read(&pbuf, &len);
        HAL_ASSERT(pbuf != NULL);

        for (uint32_t i = 0; i < len; i++) {
            HAL_ASSERT(pbuf[i] == 0x55);
            pbuf[i] = 0xaa;
        }

        ret = auipc_rpmsg_remote_write(pbuf, len);
        HAL_ASSERT(ret == HAL_OK);

        auipc_rpmsg_remote_free(pbuf);
    }
}
#endif
