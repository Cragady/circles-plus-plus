FILE_NAME_PARTIAL := circles
FILE_HOME := ./
# Empty assignment for no ext
FILE_EXT := .exe
FILE_NAME := $(FILE_NAME_PARTIAL)$(FILE_EXT)
OUT_OPTION := -o $(FILE_NAME)
G++_COMMAND_PARTIAL := g++ -std=c++17 -pedantic-errors
# INCLUDES_AND_LIBS := -I include -isystem lib/mingw-64 -L lib/mingw-64 -l opengl32 -l glfw3 -l gdi32
INCLUDES_AND_LIBS := -I include -L lib/mingw-64 -l glfw3 -l gdi32

circles:
	-$(G++_COMMAND_PARTIAL) src/main.cpp src/glad.c $(OUT_OPTION) $(INCLUDES_AND_LIBS)

example:
	-$(G++_COMMAND_PARTIAL) src/main.cpp src/glad.c -o example.exe $(INCLUDES_AND_LIBS)
