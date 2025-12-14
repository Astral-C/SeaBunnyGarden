BUILD_DIR=build
T3D_INST=$(shell realpath tiny3d)

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

N64_CFLAGS += -std=gnu2x -Os -Iinclude

src = src/entity.c src/main.c

all: bungarden.z64

$(BUILD_DIR)/bungarden.elf: $(src:%.c=$(BUILD_DIR)/%.o)

bungarden.z64: N64_ROM_TITLE="SeaBunny Garden"

clean:
	rm -rf $(BUILD_DIR) *.z64

build_lib:
	rm -rf $(BUILD_DIR) *.z64
	make -C $(T3D_INST)
	make all

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean