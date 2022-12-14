/**
  * Copyright (c) 2022 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#ifndef __AUPIC_H__
#define __AUPIC_H__

#include <stdlib.h>
#include "hal_bsp.h"
#include "hal_base.h"
#include "rpmsg_lite.h"

typedef struct au_rpmsg_info_t au_rpmsg_info;
typedef struct au_rpmsg_ept_map_t au_rpmsg_ept_map;
typedef struct au_rpmsg_cmd_t au_rpmsg_cmd;
typedef struct au_rpmsg_msg_t au_rpmsg_msg;

#define AUIPC_MSG_RQ 0x00005251UL               //'RQ' read request
#define AUIPC_MSG_RD 0x00005244UL               //'RQ' read data
#define AUIPC_MSG_RA 0x00005241UL               //'RQ' read ack
#define AUIPC_MSG_WQ 0x00005751UL               //'RQ' write request
#define AUIPC_MSG_WD 0x00005744UL               //'RQ' write data
#define AUIPC_MSG_WA 0x00005741UL               //'RQ' write ack

// Cpu id
#define MASTER_ID  ((uint32_t)1)
#define REMOTE_ID0 ((uint32_t)0)
#define REMOTE_ID1 ((uint32_t)2)
#define REMOTE_ID2 ((uint32_t)3)

#define EPT_M2R_ADDR(addr) (addr + VRING_SIZE)
#define EPT_R2M_ADDR(addr) (addr - VRING_SIZE)

// Define endpoint number
#define M1R0_EPT0 0UL
#define M1R0_EPT1 1UL
#define M1R2_EPT0 0UL
#define M1R2_EPT1 1UL
#define M1R3_EPT0 0UL
#define M1R3_EPT1 1UL

// Define rpmsg share memorys
extern uint32_t __share_rpmsg_start__[];
extern uint32_t __share_rpmsg_end__[];
#define AU_RPMSG_MEM_BASE ((uint32_t)&__share_rpmsg_start__)
#define AU_RPMSG_MEM_END  ((uint32_t)&__share_rpmsg_end__)

#define AU_RPMSG_BLOCK_SIZE (2UL * RL_VRING_OVERHEAD)
#define AU_M1R0_RPMSG_BASE  (AU_RPMSG_MEM_BASE + 0 * AU_RPMSG_BLOCK_SIZE)
#define AU_M1R2_RPMSG_BASE  (AU_RPMSG_MEM_BASE + 1 * AU_RPMSG_BLOCK_SIZE)
#define AU_M1R3_RPMSG_BASE  (AU_RPMSG_MEM_BASE + 2 * AU_RPMSG_BLOCK_SIZE)

struct au_rpmsg_ept_map_t {
    uint32_t m_id;          // master cpu id
    uint32_t r_id;          // remote cpu id
    uint32_t base;          // share memory base addr
    uint32_t size;          // share memory size
    uint32_t m_sink_ept;    // sink master endpoint
    uint32_t r_sink_ept;    // sink remote endpoint
    uint32_t m_src_ept;     // src master endpoint
    uint32_t r_src_ept;     // src remote endpoint
};

struct au_rpmsg_msg_t {
    uint32_t len;
    char *pdata;
};

struct au_rpmsg_cmd_t {
    uint32_t cmd;           // cmd
    uint32_t parm[2];       // parm
};

struct au_rpmsg_info_t {
    struct rpmsg_lite_instance *instance;
    struct rpmsg_lite_endpoint *sink_ept;   // sink ept
    struct rpmsg_lite_endpoint *src_ept;    // src ept
    struct au_rpmsg_ept_map_t *map;
    struct au_rpmsg_msg_t sink_msg;
    struct au_rpmsg_msg_t src_msg;
    void * private;
};

int32_t auipc_rpmsg_remote_read(char **data, uint32_t *size);
int32_t auipc_rpmsg_remote_write(char *pdata, uint32_t size);
void auipc_rpmsg_remote_free(char *pbuf);
void auipc_rpmsg_remote_init(void);

#endif
