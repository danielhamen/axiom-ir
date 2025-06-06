CXX := g++
CXXFLAGS := -std=c++20 -Wall -Iinclude -MMD -MP
BUILD_DIR := build
SRC_DIR := lib
TARGET := axiom-ir

# Find all .cpp files in lib/ recursively
SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

# Main entry point
MAIN_SRC := axiom-ir.cpp
MAIN_OBJ := $(BUILD_DIR)/axiom-ir.o

# Final object list
ALL_OBJ := $(MAIN_OBJ) $(OBJ)

# Target rule
$(TARGET): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o in build/
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main file
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Include generated dependency files
-include $(DEP)
