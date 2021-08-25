CXX = clang++
CXX_FLAGS = -std=c++17 -c
LINK_FLAGS = -lfmt

AR = ar

LIB_NAME = libquerycpp

INCLUDE_FLAGS = -I./include/

SRC_DIR = src/querycpp/

OUT_DIR = out/

all: column_build table_build query_build
	$(AR) -rv $(LIB_NAME).a query.o table.o column.o
	mkdir -p $(OUT_DIR){bin,include}
	mv $(LIB_NAME).a $(OUT_DIR)bin
	cp -r include/querycpp $(OUT_DIR)include

query_build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)query.cpp

table_build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)table.cpp

column_build:
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $(SRC_DIR)column.cpp


clean:
	rm *.o
