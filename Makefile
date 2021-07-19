CXX = clang++
CXX_FLAGS = -std=c++17 -c
LINK_FLAGS = -lfmt

LIB_NAME = libquerycpp

INCLUDE_FLAGS = -I./include/querycpp

SRC_DIR = src/querycpp/

OUT_DIR = out/

all: column_build table_build query_build
	$(CXX) $(CXX_FLAGS) query.o table.o column.o -o $(LIB_NAME).a $(LINK_FLAGS)
	mkdir -p $(OUT_DIR){bin,include}
#	mv $(LIB_NAME) $(OUT_DIR)bin
	cp -r include/querycpp $(OUT_DIR)include

query_build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)query.cpp

table_build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)table.cpp

column_build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)column.cpp


clean:
	rm *.o
