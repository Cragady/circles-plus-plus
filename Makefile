PROGRAM_FILES_TARGET := program_files.txt
# the shell function replaces all newline (& CRLF) chars with a single space
PROGRAM_FILES := $(shell cat $(PROGRAM_FILES_TARGET))
FILE_NAME_PARTIAL := circles
FILE_HOME := ./
# Empty assignment for no ext
FILE_EXT := .exe
FILE_NAME := $(FILE_NAME_PARTIAL)$(FILE_EXT)
OUT_OPTION := -o $(FILE_NAME)
G++_COMMAND_PARTIAL := g++ -std=c++17 -pedantic-errors
# INCLUDES_AND_LIBS := -I include -isystem lib/mingw-64 -L lib/mingw-64 -l opengl32 -l glfw3 -l gdi32
INCLUDES_AND_LIBS := -I include -L lib/mingw-64 -l glfw3 -l gdi32

all: circles-and-run

dependencies:
	cp -r modules/glm/glm include/

mingw-deps: dependencies
	cp libs-and-headers/mingw-misc/libstdc++-6.dll ./

# For windows build, use -mwindows, or -municode as an option
circles:
	$(G++_COMMAND_PARTIAL) src/main.cpp $(PROGRAM_FILES) $(OUT_OPTION) $(INCLUDES_AND_LIBS)

circles-wda:
	windres -i src/resource.rc -o resource.o
	$(G++_COMMAND_PARTIAL) src/win_main.cpp resource.o src/main.cpp $(PROGRAM_FILES) $(OUT_OPTION) -municode $(INCLUDES_AND_LIBS)

circles-and-run: circles
	./circles.exe


example:
	-$(G++_COMMAND_PARTIAL) src/example.cpp src/glad.c -o example.exe $(INCLUDES_AND_LIBS)

play:
	$(G++_COMMAND_PARTIAL) playground/main.cpp $(PROGRAM_FILES) -o playground.exe $(INCLUDES_AND_LIBS)
	./playground.exe

clean:
	-rm example.exe circles.exe playground.exe
