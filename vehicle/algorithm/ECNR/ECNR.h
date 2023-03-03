/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd.
 */

#ifndef __ECNR_H__
#define __ECNR_H__

#include "middleware_conf.h"

#define IN_SIZE                768

int ecnr_init(uint32_t src_shmem_address);
int ecnr_deinit(uint32_t src_shmem_address);
int ecnr_process(uint32_t src_shmem_address, uint32_t dst_shmem_address);

#endif

