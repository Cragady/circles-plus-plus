FILE_NAME_PARTIAL := circles
FILE_HOME := ./
# Empty assignment for no ext
FILE_EXT := .exe
FILE_NAME := $(FILE_NAME_PARTIAL)$(FILE_EXT)
OUT_OPTION := -o $(FILE_NAME)
G++_COMMAND_PARTIAL := g++ -std=c++17 -pedantic-errors
G++_TO_BIN := $(G++_COMMAND_PARTIAL) $(OUT_OPTION)

circles:
	-$(G++_TO_BIN) src/main.cpp
