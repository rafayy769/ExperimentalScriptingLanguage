SRC = src
INC = include
TARGET = bin/program

# Compiler
CC = g++
CFLAGS = -Wall -g -std=c++11

all:
	$(CC) $(CFLAGS) $(SRC)/*.cpp -o $(TARGET)

out:
	$(TARGET)