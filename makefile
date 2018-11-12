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
UNIT_DIR= ./Unittest
RES_DIR= ./res
SRCS = $(shell find . -type f -name "*.c")
OBJS = $(patsubst %.c, $(RES_DIR)/%.o, $(notdir $(SRCS)))
VPATH= $(SRC_DIR):$(INC_DIR):$(UNIT_DIR)/source:$(UNIT_DIR)/include
INCS = $(patsubst %,-I%,$(subst :, ,$(VPATH)))


util: $(OBJS)
	mkdir -p ./bin
	gcc -o ./bin/util $(OBJS) $(CFLAGS) -lcunit -ggdb

./res/ring.o: ./source/ring.c ./include/ring.h
	mkdir -p ./res
	gcc -c -o ./res/ring.o ./source/ring.c -I./include -I./Unittest/include -lcunit -ggdb

./res/unittest.o: ./Unittest/source/unittest.c ./Unittest/include/unittest.h
	mkdir -p ./res
	gcc -c -o ./res/unittest.o ./Unittest/source/unittest.c -I./include -I./Unittest/include -lcunit -ggdb
#$(RES_DIR)/%.o: $(SRCS)#/%.c#$(INC_DIR)/%.h
#	mkdir -p ./res
#	gcc $(INCS) $(CFLAGS) -c -o "$@" "$<" -lcunit -ggdb

$(RES_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p ./res
	gcc $(INCS) $(CFLAGS) -c  -o "$@" "$<" -lcunit -ggdb

clean:
	rm -rf ./bin/*
	rm -rf ./res/*
