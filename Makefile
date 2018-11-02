# ==================================================================================================
# Variables

# C++ compiler name
CXX = g++

# Compiler flags
CFLAGS = -std=c++14

# Debuguer flags
DFLAGS =

# Warning flags
WFLAGS = -Wall -Wextra
WFLAGS_EXTRA = -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
               -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs \
               -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
               -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef
# Linker flags
LFLAGS =

# Source files
SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Dependency files
DEP_DIR = deps
DEP_FILES = $(SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

# Object files
BUILD_DIR = build
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dummy warning files
WARNINGS = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.w)

# Executable name
EXEC = jellyfish

# Directory holding scene files
SCENE_DIR = scene

# Extra parameters to povray
POV_ARGS = +P
POV_DISP = -w800 -h450

# Frame to render
FRAME = 0

# ==================================================================================================
# Configuration

.PHONY: all release debug scene fast fancy mesh

# ==================================================================================================
# Main targets

debug: DFLAGS += -ggdb
debug: $(EXEC)

release: CFLAGS += -O3 -DNDEBUG
release: $(EXEC)

all: release

scene: scene_frame_$(FRAME).png

# ==================================================================================================
# Quality targets

# 144p
fast: POV_DISP = -w256 -h144
fast: scene

# 4K
fancy: POV_DISP = -w2048 -h1152
fancy: scene

# ==================================================================================================
# Main rules

# Build executable from object files
$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(DFLAGS) $(LFLAGS)

# Build object file from source file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CFLAGS) $(DFLAGS) $(WFLAGS)

# Create dependency files
$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -MM -MT '$(<:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)' $< -MF $@

# Include dependency files, without errors if they do not exist
NO_DEPS = clean clean-all warnings lint cppcheck-html doc package package-deb package-tar $(TEST_EXEC)
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NO_DEPS))))
        -include $(DEP_FILES)
endif

# ==================================================================================================
# Warnings target, output all g++ warnings without compiling
warnings: CFLAGS += -fsyntax-only
warnings: WFLAGS += $(WFLAGS_EXTRA)
warnings: $(WARNINGS)

# Output warnings
$(BUILD_DIR)/%.w: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CFLAGS) $(WFLAGS)

# ==================================================================================================
# Put the scene files together and render the scene

SCENE_INCS = mesh $(SCENE_DIR)/jellyfish_properties.inc $(SCENE_DIR)/scene.pov

mesh: $(EXEC)
	@mkdir -p $(SCENE_DIR)/build
	./$(EXEC) pov $(FRAME) 0 > $(SCENE_DIR)/build/jellyfish0.inc
	./$(EXEC) pov $(FRAME) 1 > $(SCENE_DIR)/build/jellyfish1.inc
	./$(EXEC) pov $(FRAME) 2 > $(SCENE_DIR)/build/jellyfish2.inc
	./$(EXEC) pov $(FRAME) 3 > $(SCENE_DIR)/build/jellyfish3.inc
	./$(EXEC) pov $(FRAME) 4 > $(SCENE_DIR)/build/jellyfish4.inc
	./$(EXEC) pov $(FRAME) 5 > $(SCENE_DIR)/build/jellyfish5.inc
	./$(EXEC) pov $(FRAME) 6 > $(SCENE_DIR)/build/jellyfish6.inc
	./$(EXEC) pov $(FRAME) 7 > $(SCENE_DIR)/build/jellyfish7.inc
	./$(EXEC) pov $(FRAME) 8 > $(SCENE_DIR)/build/jellyfish8.inc
	./$(EXEC) pov $(FRAME) 9 > $(SCENE_DIR)/build/jellyfish9.inc

scene_frame_$(FRAME).png: mesh
scene_frame_$(FRAME).png: $(SCENE_INCS)
	cd $(SCENE_DIR) && povray $(POV_DISP) $(POV_ARGS) -O../scene_frame_$(FRAME).png scene.pov

# ==================================================================================================
# Clean intermediate files (not final results like executables, documentation, packages,...)
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DEP_DIR)
	rm -rf $(SCENE_DIR)/build
	rm -rf *~

# Clean everything
clean-all: clean
	rm -rf $(EXEC)
	rm -rf scene.png
