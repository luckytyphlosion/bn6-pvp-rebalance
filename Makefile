ROM = bn6f-training-mode.gba

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

all: $(ROM)

$(ROM): main.o main_data.o xoshiro128pp.o .FORCE
	rm -f "temp/ACDCTownScript.msg"
	rm -f "temp/ACDCTownScript.msg.lz"
	tools/TextPet.exe run-script gen_compressed_text.tps
	tools/TextPet.exe run-script gen_text.tps
	tools/armips.exe lzpad.s
	tools/lzss.exe -ewn "temp/ACDCTownScript.msg.lz"
	tools/armips.exe src.asm -sym "bn6f-training-mode.sym"

patch:
	tools/floating/flips.exe -c -b "bn6f.gba" "bn6f-training-mode.gba" "bn6f-training-mode.bps"

#@$(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) -o - - | cat - <(echo -e ".text\n\t.align\t2, 0") | 

main.o: main.c include/*.h
	$(MODERNCC) $(CFLAGS) -c -o main.o main.c

main_data.o: main_data.c include/*.h
	$(MODERNCC) $(CFLAGS) -c -o main_data.o main_data.c

xoshiro128pp.o: xoshiro128pp.c include/xoshiro128pp.h
	$(MODERNCC) $(CFLAGS_NO_INCLUDE) -c -o xoshiro128pp.o xoshiro128pp.c

clean:
	rm -f *.o
	rm -f *.map
	rm -f *.elf
	# rm -f *.gba
	rm -f $(COMPRESSED_TEXT_ARCHIVES_DIR)/*.lz
	rm -f $(COMPRESSED_TEXT_ARCHIVES_DIR)/*.bin
