.PHONY: all init build clean cleanall

DPF_PATH=DPF
NAME = d_talchorus

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	main.cpp

# --------------------------------------------------------------
# Do some magic

include $(DPF_PATH)/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifneq ($(MACOS_OR_WINDOWS),true)
TARGETS += ladspa
TARGETS += dssi
endif

TARGETS += lv2_dsp
TARGETS += vst

all: $(TARGETS)


# --------------------------------------------------------------
#  Additional rules by soerenbnoergaard
init:
	make -C DPF

# --------------------------------------------------------------
