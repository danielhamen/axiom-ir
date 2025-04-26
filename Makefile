CXX = clang++
CXXFLAGS = -std=c++20 -O2
OUT = vm_runner

# Find all .cpp files
SRC = main.cpp $(shell find lib -name '*.cpp')

# Turn .cpp files into .o files
OBJ = $(SRC:.cpp=.o)

all: $(OUT)

# How to build the final executable
$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

# How to build each .o from each .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJ)
