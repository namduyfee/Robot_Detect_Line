
.PHONY: clean build clean

HEAP_IMPLEMENTATION := heap_4.c  # <-- select a heap is used

# list heap_X.c
HEAP_SOURCES := heap_1.c heap_2.c heap_3.c heap_4.c heap_5.c


PRO_DIR		 := ..
FREERTOS_DIR := .
OUT_DIR 	 := $(FREERTOS_DIR)/Output


INC_DIRS := $(FREERTOS_DIR)/include
INC_DIRS += $(FREERTOS_DIR)/portable/GCC/ARM_CM3

SRC_DIRS := $(FREERTOS_DIR)
SRC_DIRS += $(FREERTOS_DIR)/portable/GCC/ARM_CM3
SRC_DIRS += $(FREERTOS_DIR)/portable/MemMang


INC_FILES_PATH := $(foreach dir,$(INC_DIRS),$(wildcard $(dir)/*.h))
SRC_FILES_PATH := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

INC_FILES := $(notdir $(INC_FILES_PATH))
SRC_FILES := $(notdir $(SRC_FILES_PATH))
# filter heap
SRC_FILES := $(filter-out $(filter-out $(HEAP_IMPLEMENTATION), $(HEAP_SOURCES)), $(SRC_FILES))

OBJ_FILES := $(subst .c,.o,$(SRC_FILES))

COMPILER_DIR := D:/GCC_arm_msys2
CC           := $(COMPILER_DIR)/bin/arm-none-eabi-gcc
ASM          := $(COMPILER_DIR)/bin/arm-none-eabi-as

INC_DIRS_OPT := $(foreach dir, $(INC_DIRS), -I$(dir))
CC_OPT       := -mcpu=cortex-m3 -O0 -g -mfloat-abi=soft -std=gnu11 -mthumb $(INC_DIRS_OPT)

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)

build: $(OBJ_FILES)

%.o: %.c
	$(CC) $< -c -o $(OUT_DIR)/$@ $(CC_OPT)
	echo "completed $@"
%.s: %.c 
	$(CC) $< -S -o $(OUT_DIR)/$@ $(CC_OPT)
	echo "completed $@"
%.i: %.c 
	$(CC) $< -E -o $(OUT_DIR)/$@ $(CC_OPT)
	echo "completed $@"	

printvalof-%: ; @echo $($(subst printvalof-,,$@))

print-%: ; @echo $(subst print-,,$@)

clean: ; rm -rf $(OUT_DIR)/*
