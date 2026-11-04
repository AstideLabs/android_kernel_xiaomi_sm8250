# Android makefile for nfc kernel modules

# Path to DLKM make scripts
ifeq ($(strip $(NFC_DLKM_ENABLED)),true)
DLKM_DIR          :=  $(TOP)/device/qcom/common/dlkm

LOCAL_PATH        := $(call my-dir)

include $(CLEAR_VARS)
ifeq ($(TARGET_ENABLE_PERIPHERAL_CONTROL), true)
  LOCAL_CFLAGS := -DNFC_SECURE_PERIPHERAL_ENABLED
  KBUILD_OPTIONS += KBUILD_EXTRA_SYMBOLS=$(PWD)/$(call intermediates-dir-for,DLKM,sec-module-symvers)/Module.symvers
  ifeq ($(TARGET_KERNEL_DLKM_SECURE_MSM_OVERRIDE), true)
    LOCAL_REQUIRED_MODULES := sec-module-symvers
    LOCAL_ADDITIONAL_DEPENDENCIES += $(call intermediates-dir-for,DLKM,sec-module-symvers)/Module.symvers
  endif
endif

LOCAL_CFLAGS      := -DCONFIG_NFC_BOB1
LOCAL_MODULE      := nxp-nci.ko
LOCAL_MODULE_PATH := $(KERNEL_MODULES_OUT)
LOCAL_SRC_FILES   := $(wildcard $(LOCAL_PATH)/**/*) $(wildcard $(LOCAL_PATH)/*)

LOCAL_MODULE_DDK_BUILD := true
include $(DLKM_DIR)/Build_external_kernelmodule.mk
endif
