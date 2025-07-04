CC = gcc
CLANG = -Wall -Wextra -Werror 

DIR = ../build
TARGET = $(DIR)/pong

create_pong: $(TARGET)

$(TARGET): pong.c
	$(CC) $(CLANG) $^ -o $@