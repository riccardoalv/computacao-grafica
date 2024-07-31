# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIB_DIR = lib
ASSETS_DIR = assets

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable
EXECUTABLE = FreeGLUT_Animation

# Libraries
LIBS = -lGL -lGLU -lglut

# Make build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target
$(EXECUTABLE): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BUILD_DIR)/$(EXECUTABLE) $(LIBS)

# Object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean target
clean:
	rm -rf $(BUILD_DIR)/*

# Phony targets
.PHONY: clean
