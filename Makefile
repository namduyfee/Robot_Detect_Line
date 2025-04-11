
.PHONY: clean build_GCC loadJlink loadSTlink

PRO_NAME := robot_line

PRO_DIR := .
OUT_DIR := $(PRO_DIR)/Output
EXE_DIR := $(PRO_DIR)/Bin
OUT_RTOS_DIR := $(PRO_DIR)/FreeRtos_CM3/Output

SRC_DIRS := $(PRO_DIR)/Application/Src
SRC_DIRS += $(wildcard $(PRO_DIR)/Driver/*/Src)
SRC_DIRS += $(wildcard $(PRO_DIR)/Application_User/*/Src)

INC_DIRS := $(wildcard $(PRO_DIR)/Driver/*/Inc)
INC_DIRS += $(PRO_DIR)/Application/Inc
INC_DIRS += $(wildcard $(PRO_DIR)/Application_User/*/Inc)
INC_DIRS += $(OUT_RTOS_DIR)/../include
INC_DIRS += $(OUT_RTOS_DIR)/../portable/GCC/ARM_CM3

INC_FILES_PATH := $(foreach dir,$(INC_DIRS),$(wildcard $(dir)/*.h))
SRC_FILES_PATH := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
LINK_FILE_PATH := $(PRO_DIR)/Linker/stm32f103c8t6.ld


INC_FILES := $(notdir $(INC_FILES_PATH))
SRC_FILES := $(notdir $(SRC_FILES_PATH))
OBJ_FILES := $(subst .c,.o,$(SRC_FILES))

OBJ_FILES_PATH := $(addprefix $(OUT_DIR)/, $(OBJ_FILES))
OBJ_FILES_RTOS := $(wildcard $(OUT_RTOS_DIR)/*.o)

COMPILER_DIR := D:/GCC_arm_msys2
CC           := $(COMPILER_DIR)/bin/arm-none-eabi-gcc
ASM          := $(COMPILER_DIR)/bin/arm-none-eabi-as
LD_GCC		 := $(COMPILER_DIR)/bin/arm-none-eabi-gcc

INC_DIRS_OPT := $(foreach dir, $(INC_DIRS), -I$(dir))
CC_OPT       := -mcpu=cortex-m3 -O0 -g -mfloat-abi=soft -std=gnu11 -mthumb $(INC_DIRS_OPT)

LD_GCC_OPT	 :=	-T $(LINK_FILE_PATH) -Wl,-Map,$(OUT_DIR)/$(PRO_NAME).map \
				-mcpu=cortex-m3 -mthumb -mfloat-abi=soft -nostartfiles -lc -lm -lgcc 

JLINK := C:/"Program Files"/SEGGER/JLink_V822/JLink.exe
FLASH_SCRIPT := $(PRO_DIR)/Jlink/Flash.jlink


vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)
vpath %.o $(OUT_DIR)

build_GCC: $(OBJ_FILES)
	$(LD_GCC) $(OBJ_FILES_RTOS) $(OBJ_FILES_PATH) -o $(EXE_DIR)/$(PRO_NAME).elf $(LD_GCC_OPT)
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex "$(EXE_DIR)/$(PRO_NAME).elf" "$(EXE_DIR)/$(PRO_NAME).hex"
	
%.o: %.c %.h
	$(CC) $< -c -o $(OUT_DIR)/$@ $(CC_OPT)
	echo "completed $@"
%.s: %.c 
	$(CC) $< -S -o $(OUT_DIR)/$@ $(CC_OPT)
	echo "completed $@"
%.i: %.c 
	$(CC) $< -E -o $(OUT_DIR)/$@ $(CC_OPT)
	echo "completed $@"	

loadSTlink: 
	$(PRO_DIR)/ST-LinkUtility/ST-LINK_CLI.exe -p "$(EXE_DIR)/$(PRO_NAME).hex" 0x08000000
	$(PRO_DIR)/ST-LinkUtility/ST-LINK_CLI.exe -rst

loadJlink: $(EXE_DIR)/$(PRO_NAME).hex
	$(JLINK) < $(FLASH_SCRIPT)

test: 
	$(COMPILER_DIR)/bin/arm-none-eabi-nm $(EXE_DIR)/$(PRO_NAME).elf | grep SysTick_Handler
	$(COMPILER_DIR)/bin/arm-none-eabi-nm $(EXE_DIR)/$(PRO_NAME).elf | grep SVC_Handler
	$(COMPILER_DIR)/bin/arm-none-eabi-nm $(EXE_DIR)/$(PRO_NAME).elf | grep PendSV_Handler
	$(COMPILER_DIR)/bin/arm-none-eabi-objdump -h $(EXE_DIR)/$(PRO_NAME).elf | grep isr_vector
#	$(COMPILER_DIR)/bin/arm-none-eabi-objdump -s -j .isr_vector $(EXE_DIR)/$(PRO_NAME).elf
printvalof-%: ; @echo $($(subst printvalof-,,$@))

print-%: ; @echo $(subst print-,,$@)

clean: ; rm -rf $(OUT_DIR)/* $(EXE_DIR)/*
