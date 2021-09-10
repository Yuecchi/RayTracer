CC		= g++
C_FILES = $(wildcard src/*.cpp)
O_FILES = $(C_FILES:src/%.cpp=build/%.o)
OUT		= bin/raytracer.exe
INCLUDE = -I include/
LIB		= lib/libglew32.a lib/libglfw3.a -lgdi32 -lopengl32
MARCH   ?=
ifeq ($(MARCH),)
	CFLAGS = -O2
else
	CFLAGS = -O2 -march=$(MARCH)
endif


.DEFAULT: all

all: $(O_FILES) | bin
	$(CC) $^ -o $(OUT) $(LIB)

build/%.o: src/%.cpp | build
	$(CC) $(INCLUDE) $(CFLAGS) -D GLEW_STATIC -c $^ -o $@ 

build:
	mkdir $@

bin:
	mkdir $@