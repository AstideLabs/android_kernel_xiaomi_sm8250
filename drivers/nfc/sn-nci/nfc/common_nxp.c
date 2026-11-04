// SPDX-License-Identifier: GPL-2.0-only
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
#include "common.h"
#include "common_nxp.h"

/**
 * get_nfcc_chip_type_dl() - get chip type in fw download command;
 * @nfc_dev:    nfc device data structure
 *
 * Perform get version command and determine chip
 * type from response.
 *
 * @Return:  enum chip_types value
 *
 */
static enum chip_types get_nfcc_chip_type_dl(struct nfc_dev *nfc_dev)
{
	int ret = 0;
	uint8_t *cmd = nfc_dev->write_kbuf;
	uint8_t *rsp = nfc_dev->read_kbuf;
	enum chip_types chip_type = CHIP_UNKNOWN;

	*cmd++ = DL_CMD;
	*cmd++ = DL_GET_VERSION_CMD_PAYLOAD_LEN;
	*cmd++ = DL_GET_VERSION_CMD_ID;
	*cmd++ = DL_PAYLOAD_BYTE_ZERO;
	*cmd++ = DL_PAYLOAD_BYTE_ZERO;
	*cmd++ = DL_PAYLOAD_BYTE_ZERO;
	*cmd++ = DL_GET_VERSION_CMD_CRC_1;
	*cmd++ = DL_GET_VERSION_CMD_CRC_2;

	pr_debug("NxpDrv: %s:Sending GET_VERSION cmd of size = %d\n", __func__, DL_GET_VERSION_CMD_LEN);
	ret = nfc_dev->nfc_write(nfc_dev, nfc_dev->write_kbuf, DL_GET_VERSION_CMD_LEN,
									MAX_RETRY_COUNT);
	if (ret <= 0) {
		pr_err("NxpDrv: %s: - nfc get version cmd error ret %d\n", __func__, ret);
		goto err;
	}
	memset(rsp, 0x00, DL_GET_VERSION_RSP_LEN_2);
	pr_debug("NxpDrv: %s:Reading response of GET_VERSION cmd\n", __func__);
	ret = nfc_dev->nfc_read(nfc_dev, rsp, DL_GET_VERSION_RSP_LEN_2, NCI_CMD_RSP_TIMEOUT_MS);
	if (ret <= 0) {
		pr_err("NxpDrv: %s: - nfc get version rsp error ret %d\n", __func__, ret);
		goto err;
	}
	if (rsp[0] == FW_MSG_CMD_RSP && ret >= DL_GET_VERSION_RSP_LEN_2) {

		nfc_dev->fw_major_version = rsp[FW_MAJOR_VER_OFFSET];

		if (rsp[FW_ROM_CODE_VER_OFFSET] == SN1XX_ROM_VER &&
			rsp[FW_MAJOR_VER_OFFSET] == SN1xx_MAJOR_VER)
			chip_type = CHIP_SN1XX;
		else if (rsp[FW_ROM_CODE_VER_OFFSET] == SN220_ROM_VER &&
			rsp[FW_MAJOR_VER_OFFSET] == SN220_MAJOR_VER)
			chip_type = CHIP_SN220;

		pr_debug("NxpDrv: %s:NFC Chip Type 0x%02x Rom Version 0x%02x FW Minor 0x%02x Major 0x%02x\n",
			__func__, rsp[GET_VERSION_RSP_CHIP_TYPE_OFFSET],
					rsp[FW_ROM_CODE_VER_OFFSET],
					rsp[GET_VERSION_RSP_MINOR_VERSION_OFFSET],
					rsp[FW_MAJOR_VER_OFFSET]);

		nfc_dev->nqx_info.info.chip_type = rsp[GET_VERSION_RSP_CHIP_TYPE_OFFSET];
		nfc_dev->nqx_info.info.rom_version = rsp[FW_ROM_CODE_VER_OFFSET];
		nfc_dev->nqx_info.info.fw_minor = rsp[GET_VERSION_RSP_MINOR_VERSION_OFFSET];
		nfc_dev->nqx_info.info.fw_major = rsp[FW_MAJOR_VER_OFFSET];
	}
err:
	return chip_type;
}

/**
 * get_nfcc_session_state_dl() - gets the session state
 * @nfc_dev:    nfc device data structure
 *
 * Performs get session command and determine
 * the nfcc state based on session status.
 *
 * @Return     nfcc state based on session status.
 *             NFC_STATE_FW_TEARED if sessionis not closed
 *             NFC_STATE_FW_DWL if session closed
 *             NFC_STATE_UNKNOWN in error cases.
 */
enum nfc_state_flags get_nfcc_session_state_dl(struct nfc_dev *nfc_dev)
{
	int ret = 0;
	uint8_t *cmd = nfc_dev->write_kbuf;
	uint8_t *rsp = nfc_dev->read_kbuf;
	enum nfc_state_flags nfc_state = NFC_STATE_UNKNOWN;

	*cmd++ = DL_CMD;
	*cmd++ = DL_GET_SESSION_STATE_CMD_PAYLOAD_LEN;
	*cmd++ = DL_GET_SESSION_CMD_ID;
	*cmd++ = DL_PAYLOAD_BYTE_ZERO;
	*cmd++ = DL_PAYLOAD_BYTE_ZERO;
	*cmd++ = DL_PAYLOAD_BYTE_ZERO;
	*cmd++ = DL_GET_SESSION_CMD_CRC_1;
	*cmd++ = DL_GET_SESSION_CMD_CRC_2;

	pr_debug("NxpDrv: %s:Sending GET_SESSION_STATE cmd of size = %d\n", __func__,
						DL_GET_SESSION_STATE_CMD_LEN);
	ret = nfc_dev->nfc_write(nfc_dev, nfc_dev->write_kbuf, DL_GET_SESSION_STATE_CMD_LEN,
						MAX_RETRY_COUNT);
	if (ret <= 0) {
		pr_err("NxpDrv: %s: - nfc get session cmd error ret %d\n", __func__, ret);
		goto err;
	}
	memset(rsp, 0x00, DL_GET_SESSION_STATE_RSP_LEN);
	pr_debug("NxpDrv: %s:Reading response of GET_SESSION_STATE cmd\n", __func__);
	ret = nfc_dev->nfc_read(nfc_dev, rsp, DL_GET_SESSION_STATE_RSP_LEN, NCI_CMD_RSP_TIMEOUT_MS);
	if (ret <= 0) {
		pr_err("NxpDrv: %s: - nfc get session rsp error ret %d\n", __func__, ret);
		goto err;
	}
	if (rsp[0] != FW_MSG_CMD_RSP) {
		pr_err("NxpDrv: %s: - nfc invalid get session state rsp\n", __func__);
		goto err;
	}
	pr_debug("NxpDrv: Response bytes are %02x%02x%02x%02x%02x%02x%02x%02x\n",
		rsp[0], rsp[1], rsp[2], rsp[3], rsp[4], rsp[5], rsp[6], rsp[7]);
	/*verify fw in non-teared state */
	if (rsp[GET_SESSION_STS_OFF] != NFCC_SESSION_STS_CLOSED) {
		pr_err("NxpDrv: %s NFCC booted in FW teared state\n", __func__);
		nfc_state = NFC_STATE_FW_TEARED;
	} else {
		pr_info("NxpDrv: %s NFCC booted in FW DN mode\n", __func__);
		nfc_state = NFC_STATE_FW_DWL;
	}
err:
	return nfc_state;
}

/**
 * get_nfcc_chip_type() - get nfcc chip type in nci mode.
 * @nfc_dev:   nfc device data structure.
 *
 * Function to perform nci core reset and extract
 * chip type from the response.
 *
 * @Return:  enum chip_types value
 *
 */
static enum chip_types get_nfcc_chip_type(struct nfc_dev *nfc_dev)
{
	int ret = 0;
	uint8_t major_version = 0;
	uint8_t rom_version = 0;
	uint8_t *cmd = nfc_dev->write_kbuf;
	uint8_t *rsp = nfc_dev->read_kbuf;
	enum chip_types chip_type = CHIP_UNKNOWN;

	*cmd++ = NCI_CMD;
	*cmd++ = NCI_CORE_RESET_CMD_OID;
	*cmd++ = NCI_CORE_RESET_CMD_PAYLOAD_LEN;
	*cmd++ = NCI_CORE_RESET_KEEP_CONFIG;

	pr_debug("NxpDrv: %s:Sending NCI Core Reset cmd of size = %d\n", __func__, NCI_RESET_CMD_LEN);
	ret = nfc_dev->nfc_write(nfc_dev, nfc_dev->write_kbuf, NCI_RESET_CMD_LEN, NO_RETRY);
	if (ret <= 0) {
		pr_err("NxpDrv: %s: - nfc nci core reset cmd error ret %d\n", __func__, ret);
		goto err;
	}

	/* to flush out debug NTF this delay is required */
	usleep_range(NCI_RESET_RESP_READ_DELAY, NCI_RESET_RESP_READ_DELAY + 100);
	nfc_dev->nfc_enable_intr(nfc_dev);

	memset(rsp, 0x00, NCI_RESET_RSP_LEN);
	pr_debug("NxpDrv: %s:Reading NCI Core Reset rsp\n", __func__);
	ret = nfc_dev->nfc_read(nfc_dev, rsp, NCI_RESET_RSP_LEN, NCI_CMD_RSP_TIMEOUT_MS);
	if (ret <= 0) {
		pr_err("NxpDrv: %s: - nfc nci core reset rsp error ret %d\n", __func__, ret);
		goto err_disable_intr;
	}

	pr_debug("NxpDrv: %s: nci core reset response 0x%02x%02x%02x%02x\n",
		__func__, rsp[0], rsp[1], rsp[2], rsp[3]);
	if (rsp[0] != NCI_RSP) {
		/* reset response failed response*/
		pr_err("NxpDrv: %s invalid nci core reset response\n", __func__);
		goto err_disable_intr;
	}

	memset(rsp, 0x00, NCI_RESET_NTF_LEN);
	/* read nci rest response ntf */
	ret = nfc_dev->nfc_read(nfc_dev, rsp, NCI_RESET_NTF_LEN, NCI_CMD_RSP_TIMEOUT_MS);
	if (ret <= 0) {
		pr_err("NxpDrv: %s - nfc nci rest rsp ntf error status %d\n", __func__, ret);
		goto err_disable_intr;
	}

	if (rsp[0] == NCI_NTF) {
		/* read version info from NCI Reset Notification */
		rom_version = rsp[NCI_HDR_LEN + rsp[NCI_PAYLOAD_LEN_IDX] - 3];
		major_version = rsp[NCI_HDR_LEN + rsp[NCI_PAYLOAD_LEN_IDX] - 2];
		/* determine chip type based on version info */
		if (rom_version == SN1XX_ROM_VER && major_version == SN1xx_MAJOR_VER)
			chip_type = CHIP_SN1XX;
		else if (rom_version == SN220_ROM_VER && major_version == SN220_MAJOR_VER)
			chip_type = CHIP_SN220;
		else if (rom_version == SN300_ROM_VER && major_version == SN300_MAJOR_VER)
			chip_type = CHIP_SN300;

		pr_debug("NxpDrv: %s:NCI  Core Reset ntf 0x%02x%02x%02x%02x\n",
			__func__, rsp[0], rsp[1], rsp[2], rsp[3]);

		nfc_dev->nqx_info.info.chip_type = rsp[NCI_HDR_LEN + rsp[NCI_PAYLOAD_LEN_IDX] -
									NFC_CHIP_TYPE_OFF];
		nfc_dev->nqx_info.info.rom_version = rom_version;
		nfc_dev->nqx_info.info.fw_major = major_version;
		nfc_dev->nqx_info.info.fw_minor = rsp[NCI_HDR_LEN + rsp[NCI_PAYLOAD_LEN_IDX] -
									NFC_FW_MINOR_OFF];
	}
err_disable_intr:
	nfc_dev->nfc_disable_intr(nfc_dev);
err:
	return chip_type;
}

/**
 * validate_download_gpio() - validate download gpio.
 * @nfc_dev: nfc_dev device data structure.
 * @chip_type: chip type of the platform.
 *
 * Validates dwnld gpio should configured for supported and
 * should not be configured for unsupported platform.
 *
 * @Return:  true if gpio validation successful ortherwise
 *           false if validation fails.
 */
static bool validate_download_gpio(struct nfc_dev *nfc_dev, enum chip_types chip_type)
{
	bool status = false;
	struct platform_gpio *nfc_gpio;

	if (nfc_dev == NULL) {
		pr_err("NxpDrv: %s nfc devices structure is null\n", __func__);
		return status;
	}

	nfc_gpio = &nfc_dev->configs.gpio;
	if (chip_type == CHIP_SN1XX) {
		/* gpio should be configured for SN1xx */
		status = gpio_is_valid(nfc_gpio->dwl_req);
	} else if ((chip_type == CHIP_SN220) || (chip_type == CHIP_SN300)) {
		/* gpio should not be configured for SN220, SN300 */
		nfc_gpio->dwl_req = -EINVAL;
		status = true;
	}
	return status;
}

/* Check for availability of NFC controller hardware */
int nfcc_hw_check(struct nfc_dev *nfc_dev)
{
	int ret = 0;
	enum nfc_state_flags nfc_state = NFC_STATE_UNKNOWN;
	enum chip_types chip_type = CHIP_UNKNOWN;
	struct platform_gpio *nfc_gpio = &nfc_dev->configs.gpio;

	/*get fw version in nci mode*/
	gpio_set_ven(nfc_dev, 1);
	gpio_set_ven(nfc_dev, 0);
	gpio_set_ven(nfc_dev, 1);
	chip_type = get_nfcc_chip_type(nfc_dev);

	/*get fw version in fw dwl mode*/
	if (chip_type == CHIP_UNKNOWN) {
		nfc_dev->nfc_enable_intr(nfc_dev);
		/*Chip is unknown, initially assume with fw dwl pin enabled*/
		set_valid_gpio(nfc_gpio->dwl_req, 1);
		gpio_set_ven(nfc_dev, 0);
		gpio_set_ven(nfc_dev, 1);
		chip_type = get_nfcc_chip_type_dl(nfc_dev);
		/*get the state of nfcc normal/teared in fw dwl mode*/
	} else {
		nfc_state = NFC_STATE_NCI;
	}

	/*validate gpio config required as per the chip*/
	if (!validate_download_gpio(nfc_dev, chip_type)) {
		pr_info("NxpDrv: %s gpio validation fail\n", __func__);
		ret = -ENXIO;
		goto err;
	}

	/*check whether the NFCC is in FW DN or Teared state*/
	if (nfc_state != NFC_STATE_NCI)
		nfc_state = get_nfcc_session_state_dl(nfc_dev);

	/*nfcc state specific operations */
	switch (nfc_state) {
	case NFC_STATE_FW_TEARED:
		pr_warn("NxpDrv: %s: - NFCC FW Teared State\n", __func__);
             break;
	case NFC_STATE_FW_DWL:
	case NFC_STATE_NCI:
	     break;
	case NFC_STATE_UNKNOWN:
	default:
		ret = -ENXIO;
		pr_err("NxpDrv: %s: - NFCC HW not available\n", __func__);
		goto err;
	}
	nfc_dev->nfc_state = nfc_state;
err:
	nfc_dev->nfc_disable_intr(nfc_dev);
	set_valid_gpio(nfc_gpio->dwl_req, 0);
	gpio_set_ven(nfc_dev, 0);
	gpio_set_ven(nfc_dev, 1);
	nfc_dev->nfc_ven_enabled = true;
	return ret;
}
