CXX = clang++
CXX_FLAGS = -std=c++17 -c
LINK_FLAGS = -lfmt

INCLUDE_FLAGS = -I./include

SRC_DIR = src/

all:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)table.cpp
