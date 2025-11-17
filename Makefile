#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
ifeq ($(shell uname), Darwin)
	OBJS = lib/stds/src/*.c src/*.c
else
	OBJS = lib/stds/src/*.c lib/stds/include/*.h src/*.c include/*.h
endif


#CC specifies which compiler we're using
CC = aarch64-linux-gnu-gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/sdk/usr/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/sdk/usr/lib

ifeq ($(OS), Windows_NT)
	INCLUDE_PATHS = -IC:\MinGW\include
endif 

ifeq ($(OS), Windows_NT)
	LIBRARY_PATHS = -LC:\MinGW\lib
endif

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresszzes all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Werror -g --sysroot=/sdk/aarch64-linux-gnu-7.5.0-linaro/aarch64-linux-gnu/libc

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = 0

ifeq ($(OS), Windows_NT)
	LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
else
	LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lfreetype -lmad -lz -lbz2 -lm
endif

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = build/Brick-Breaker/Game

#This is the target that compiles our executable
all : $(OBJS)
	mkdir -p build/Brick-Breaker
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	cp -r res build/Brick-Breaker/
	@if [ -f res/icon.png ]; then \
		cp res/icon.png build/Brick-Breaker/icon.png; \
		echo "Icon copied to build directory"; \
	else \
		echo "Warning: res/icon.png not found. Please create an icon for the app."; \
	fi
	@echo "Build complete. Game and resources copied to build/Brick-Breaker/"
