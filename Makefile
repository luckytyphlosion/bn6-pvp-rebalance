ROM_NAME = bn6f-pvp-rebalance.gba
PATCH_NAME := $(ROM_NAME:.gba=.bps)

TOOLCHAIN := $(DEVKITARM)
ifneq (,$(TOOLCHAIN))
ifneq ($(wildcard $(TOOLCHAIN)/bin),)
export PATH := $(TOOLCHAIN)/bin:$(PATH)
endif
endif

MODERNCC := arm-none-eabi-gcc
AS := arm-none-eabi-as
PATH_MODERNCC := PATH=$(TOOLCHAIN)/bin:PATH $(MODERNCC)
CC1 = $(shell $(PATH_MODERNCC) --print-prog-name=cc1) -quiet
CPP = gcc -E
CPPFLAGS = -iquote include -Wno-trigraphs

# build flags
CFLAGS = -mno-thumb-interwork -std=c11 -iquote include -Wno-trigraphs -mthumb -O2 -g -mcpu=arm7tdmi -mtune=arm7tdmi -march=armv4t -fno-toplevel-reorder -ffixed-r10 -ffixed-r12

CFLAGS_NO_INCLUDE = -mno-thumb-interwork -std=c11 -Wno-trigraphs -mthumb -O2 -g -mcpu=arm7tdmi -mtune=arm7tdmi -march=armv4t -fno-toplevel-reorder -ffixed-r10 -ffixed-r12

.FORCE:

# TODO: INTEGRATE SCAN INCLUDES

ifneq (,$(wildcard enable_training_mode.dump))
ENABLE_TRAINING_MODE := 1
else
ENABLE_TRAINING_MODE := 0
endif

all: $(ROM_NAME)

$(ROM_NAME): c_objs .FORCE
	rm -f "temp/ACDCTownScript.msg"
	rm -f "temp/ACDCTownScript.msg.lz"
	tools/TextPet.exe run-script gen_compressed_text.tps
	tools/TextPet.exe run-script gen_text.tps
	tools/armips.exe lzpad.s
	tools/lzss.exe -ewn "temp/ACDCTownScript.msg.lz"
	tools/armips.exe main.asm -equ ENABLE_TRAINING_MODE $(ENABLE_TRAINING_MODE) -sym "bn6f-training-mode.sym"

patch:
	tools/floating/flips.exe -c -b "bn6f.gba" $(ROM_NAME) $(PATCH_NAME)

c_objs: training-mode/main.o training-mode/main_data.o training-mode/xoshiro128pp.o common/common_main.o

common/common_main.o: common/common_main.c include/*.h
	$(MODERNCC) $(CFLAGS) -c -o common/common_main.o common/common_main.c

training-mode/main.o: training-mode/main.c include/*.h
	$(MODERNCC) $(CFLAGS) -c -o training-mode/main.o training-mode/main.c

training-mode/main_data.o: training-mode/main_data.c include/*.h
	$(MODERNCC) $(CFLAGS) -c -o training-mode/main_data.o training-mode/main_data.c

training-mode/xoshiro128pp.o: training-mode/xoshiro128pp.c include/xoshiro128pp.h
	$(MODERNCC) $(CFLAGS_NO_INCLUDE) -c -o training-mode/xoshiro128pp.o training-mode/xoshiro128pp.c

clean:
	rm -f *.o
	rm -f *.map
	rm -f *.elf
	# rm -f *.gba
	rm -f $(COMPRESSED_TEXT_ARCHIVES_DIR)/*.lz
	rm -f $(COMPRESSED_TEXT_ARCHIVES_DIR)/*.bin
