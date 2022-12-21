#!/bin/sh

# SPDX-License-Identifier: BSD-3-Clause */

# Copyright (c) 2022 Rockchip Electronics Co., Ltd.

AUDIO_ALGORITHM_PATH=$(HAL_PATH)/applications/vehicle

INCLUDES += \
-I"$(AUDIO_ALGORITHM_PATH)" \
-I"$(AUDIO_ALGORITHM_PATH)/include" \
-I"$(AUDIO_ALGORITHM_PATH)/algorithm/Volume_Control" \

SRC_DIRS += \
    $(AUDIO_ALGORITHM_PATH) \
    $(AUDIO_ALGORITHM_PATH)/algorithm/Volume_Control \

LDFLAGS += \
    $(AUDIO_ALGORITHM_PATH)/lib/librk_studio.a \
