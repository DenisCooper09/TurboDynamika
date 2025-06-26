SOURCES := \
    src/memory.c \
    src/startup.c \
    src/main.c \
    src/interrupts.c

CFLAGS ?= \
    -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -Wconversion \
    -fno-common -ffunction-sections -fdata-sections \
    -mcpu=cortex-m4 -mthumb \
    -g3 -Os \
    $(EXTRA_CFLAGS)

LDFLAGS ?= \
    -Tlinker/link.ld \
    -nostartfiles \
    -nostdlib \
    -Wl,--gc-sections \
    -Wl,-Map=$@.map

BUILD_DIRECTORY := build

OBJECTS := $(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(SOURCES))

ELF := $(BUILD_DIRECTORY)/firmware.elf
BIN := $(BUILD_DIRECTORY)/firmware.bin

all: $(BIN)

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $(ELF) $(BIN)

$(ELF): $(OBJECTS)
	arm-none-eabi-gcc $(LDFLAGS) $(OBJECTS) -o $(ELF)

$(BUILD_DIRECTORY)/%.o: %.c
	@mkdir -p $(dir $@)
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

flash: $(BIN)
	st-flash --reset write $(BIN) 0x08000000

ifeq ($(OS), Windows_NT)
  RM = cmd /C rmdir /S /Q
else
  RM = rm -rf
endif

clean:
	$(RM) $(BUILD_DIRECTORY)

.PHONY: all flash clean
