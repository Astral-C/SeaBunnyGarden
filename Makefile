BUILD_DIR=build
T3D_INST=$(shell realpath tiny3d)

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

N64_CFLAGS += -std=gnu2x -Os -Iinclude

src = src/util.c src/camera.c src/test.c src/world.c src/gamestate.c src/menu.c src/tidepool.c src/entity.c src/main.c

assets_png = $(wildcard assets/*.png)
assets_gltf = $(wildcard assets/*.glb)
assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_gltf:%.glb=%.t3dm)))

all: bungarden.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"

filesystem/%.t3dm: assets/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o filesystem $@

$(BUILD_DIR)/bungarden.dfs: $(assets_conv)
$(BUILD_DIR)/bungarden.elf: $(src:%.c=$(BUILD_DIR)/%.o)

bungarden.z64: N64_ROM_TITLE="SeaBunny Garden"
bungarden.z64: $(BUILD_DIR)/bungarden.dfs

clean:
	rm -rf $(BUILD_DIR) *.z64
	rm -rf filesystem

build_lib:
	rm -rf $(BUILD_DIR) *.z64
	make -C $(T3D_INST)
	make all

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean