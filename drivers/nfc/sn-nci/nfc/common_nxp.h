/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2019-2021 NXP
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ******************************************************************************/
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 ******************************************************************************/

#ifndef _COMMON_QCOM_H_
#define _COMMON_QCOM_H_

#define NCI_RESET_CMD_LEN			(4)
#define NCI_RESET_RSP_LEN			(4)
#define NCI_CORE_RESET_CMD_OID		(0x0)
#define NCI_CORE_RESET_CMD_PAYLOAD_LEN	(0x1)
#define NCI_CORE_RESET_KEEP_CONFIG	(0x0)
#define NCI_RESET_NTF_LEN			(13)

/*command response timeout*/
#define NCI_CMD_RSP_TIMEOUT_MS             (2000)	//2s

#define SN1XX_ROM_VER               0x01
#define SN1xx_MAJOR_VER             0x10
#define SN220_ROM_VER               0x01
#define SN220_MAJOR_VER             0x01
#define SN300_ROM_VER               0x02
#define SN300_MAJOR_VER             0x20
#define FW_ROM_CODE_VER_OFFSET      4
#define FW_MAJOR_VER_OFFSET         7
#define GET_VERSION_RSP_CHIP_TYPE_OFFSET	3
#define GET_VERSION_RSP_MINOR_VERSION_OFFSET	6
#define DL_GET_VERSION_CMD_LEN      (8)
#define DL_GET_VERSION_RSP_LEN_1    (12)	/* SN110 */
#define DL_GET_VERSION_RSP_LEN_2    (20)	/* SN220 */
#define DL_GET_VERSION_CMD_PAYLOAD_LEN      (4)
#define DL_GET_VERSION_CMD_ID		(0xF1)
#define DL_GET_VERSION_CMD_CRC_1	(0x6E)
#define DL_GET_VERSION_CMD_CRC_2	(0xEF)

#define DL_RESET_CMD_LEN                (8)
#define DL_GET_SESSION_STATE_CMD_LEN    (8)
#define DL_GET_SESSION_STATE_RSP_LEN    (8)
#define DL_GET_SESSION_STATE_CMD_PAYLOAD_LEN    (4)
#define DL_GET_SESSION_CMD_ID			(0xF2)
#define DL_GET_SESSION_CMD_CRC_1		(0xF5)
#define DL_GET_SESSION_CMD_CRC_2		(0x33)
#define GET_SESSION_STS_OFF             (3)
#define NFCC_SESSION_STS_CLOSED         (0x0)

/* Below offsets should be subtracted from NCI header length + payload length */

#define NFC_CHIP_TYPE_OFF		(4)
#define NFC_FW_MINOR_OFF		(1)


enum chip_types {
	CHIP_SN1XX = 0x01,
	CHIP_SN220 = 0x02,
	CHIP_SN300 = 0xd3,
	CHIP_UNKNOWN = 0xFF,
};

#endif //_COMMON_QCOM_H_
