#Makefile for qti nfc drivers

include $(NFC_ROOT)/config/gki_nfc.conf

LINUXINCLUDE    += -I$(NFC_ROOT)/include/uapi/linux/nfc

LINUXINCLUDE   += -include $(NFC_ROOT)/config/gki_nfc_conf.h

LINUXINCLUDE   += -I$(NFC_ROOT)/../../../qcom/opensource/securemsm-kernel/smcinvoke/
LINUXINCLUDE   += -I$(NFC_ROOT)/../../../qcom/opensource/securemsm-kernel/linux/
LINUXINCLUDE   += -I$(NFC_ROOT)/../../../qcom/opensource/securemsm-kernel/include/linux/

obj-$(CONFIG_NXP_NFC_I2C) += nxp-nci.o

#source files
nxp-nci-objs += nfc/ese_cold_reset.o \
                nfc/common.o \
		nfc/common_nxp.o \
		nfc/common_qcom.o \
		nfc/i2c_drv.o

