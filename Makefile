CXX=g++
AR=ar
BUILD_DIR=./build
LIB_DIR=./lib
BUILD_ARGS=-I./include/ -L/usr/lib -lraylib -lm

libName=Splash

all: library

library: compile
	@echo "Creating static library $(LIB_DIR)/lib$(libName).a"
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $(LIB_DIR)/lib$(libName).a $(BUILD_DIR)/$(libName).o

compile: directories ./src/$(libName).cpp ./include/$(libName).h
	@echo "Compiling $< to $(BUILD_DIR)/$(libName).o"
	$(CXX) -c ./src/$(libName).cpp -o $(BUILD_DIR)/$(libName).o $(BUILD_ARGS)

directories:
	@echo "Creating build directories..."
	@mkdir -p $(BUILD_DIR)

clean:
	@echo "Cleaning artifacts..."
	rm -rf $(BUILD_DIR) 
	rm -rf $(LIB_DIR)
