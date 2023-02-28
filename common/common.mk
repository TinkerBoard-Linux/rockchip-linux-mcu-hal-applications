#!/bin/sh

# SPDX-License-Identifier: BSD-3-Clause */

# Copyright (c) 2022 Rockchip Electronics Co., Ltd.

COMMON_PATH=$(HAL_PATH)/applications/common

INCLUDES += \
-I"$(COMMON_PATH)" \

SRC_DIRS += \
    $(COMMON_PATH) \
