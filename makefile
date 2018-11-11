###################################
# Makefile for project 2          #
###################################
#Description: This is the makefile for Project 2
#Authors: Roberto Baquerizo, Vance Farren
#Tools: Make, gcc
#Links: https://www.gnu.org/software/make/manual/make.html
#
#
#


CFLAGS= -Wall -Werror -Wextra -g -std=c99


INC_DIR= ./include
SRC_DIR= ./source
RES_DIR= ./res
OBJS= $(patsubst ./source/%.c, ./res/%.o, $(shell find . -name "*.c"))

util: $(OBJS)
	mkdir -p ./bin
	gcc -o ./bin/util $(OBJS) $(CFLAGS) -lcunit -ggdb

$(RES_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	mkdir -p ./res 
	gcc -I$(INC_DIR) $(CFLAGS) -c -o "$@" "$<" -lcunit -ggdb

$(RES_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p ./res
	gcc -I$(INC_DIR) $(CFLAGS) -c  -o "$@" "$<" -lcunit -ggdb

clean: 
	rm -rf ./bin/*
	rm -rf ./res/*
