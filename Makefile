# Makefile where I learn how to make a Makefile
CC = g++
SRC = src/main.c \
	src/shader.c \
	src/gl_utils.c
TARGET = game
CFLAGS = -g
INC_DIR = -I ./lib/include
LIB_DIR = -L ./lib/
LOC_LIB = -lglfw3dll -lglew32
SYS_LIB = -lOpenGL32

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INC_DIR) $(SRC) -o $(TARGET) $(LIB_DIR) $(SYS_LIB) $(LOC_LIB)

.PHONY: clean
clean:
	rm ./$(TARGET).exe