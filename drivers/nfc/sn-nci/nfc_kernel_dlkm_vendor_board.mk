# Build NFC kernel driver
NFC_DLKM_ENABLED := false

########## Check and set local DLKM flag based on system-wide global flags ##########
ifeq ($(TARGET_KERNEL_DLKM_DISABLE), true)
  ifeq ($(TARGET_KERNEL_DLKM_NFC_OVERRIDE), true)
    NFC_DLKM_ENABLED := true
  endif
else
  NFC_DLKM_ENABLED := true
endif

########## Build kernel module based on local DLKM flag status ##########
ifeq ($(NFC_DLKM_ENABLED), true)
ifeq ($(call is-board-platform-in-list, sun canoe lahaina parrot bengal chora malabar shikra taro),true)
  BOARD_VENDOR_KERNEL_MODULES += $(KERNEL_MODULES_OUT)/nxp-nci.ko
endif
endif

ifeq ($(call is-board-platform-in-list, blair parrot chora malabar taro),true)
TARGET_ENABLE_PERIPHERAL_CONTROL := false
endif
