/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/******************************************************************************
 * Copyright (C) 2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2022 NXP
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 ******************************************************************************/
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 ****************************************************************************/

#ifndef _UAPI_SN_UAPI_H_
#define _UAPI_SN_UAPI_H_

#include <linux/ioctl.h>

/* Ioctls
 * The type should be aligned with MW HAL definitions
 */

#define NFC_MAGIC			(0xE9)

#define NFC_SET_PWR			_IOW(NFC_MAGIC, 0x01, uint32_t)
#define ESE_SET_PWR			_IOW(NFC_MAGIC, 0x02, uint32_t)
#define ESE_GET_PWR			_IOR(NFC_MAGIC, 0x03, uint32_t)
#define NFC_SET_RESET_READ_PENDING	_IOW(NFC_MAGIC, 0x04, uint32_t)
#define NFC_GET_GPIO_STATUS		_IOR(NFC_MAGIC, 0x05, uint32_t)
#define NFC_SECURE_ZONE			_IOW(NFC_MAGIC, 0x0A, uint32_t)
#define ESE_COLD_RESET _IOWR(NFCC_MAGIC, 0x08, struct ese_ioctl_arg)

#endif
