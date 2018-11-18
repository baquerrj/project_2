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

MAKE= /usr/bin/make
GCC= /usr/bin/gcc

INC_DIR= ./include
SRC_DIR= ./source
UNIT_DIR= ./Unittest
RES_DIR= ./res

SRCS = $(shell find . -type f -name "*.c")
OBJS = $(patsubst %.c, $(RES_DIR)/%.o, $(notdir $(SRCS)))
VPATH= $(INC_DIR):$(UNIT_DIR)/$(INC_DIR)
INCS = $(patsubst %,-I%,$(subst :, ,$(VPATH)))


util: $(OBJS)
	mkdir -p ./bin
	$(GCC) -o ./bin/util $(OBJS) $(CFLAGS) -lcunit -ggdb

./res/unittest.o: ./Unittest/source/unittest.c ./Unittest/include/unittest.h
	mkdir -p ./res
	$(GCC) $(CFLAGS) -c -o ./res/unittest.o ./Unittest/source/unittest.c -I./include -I./Unittest/include -lcunit -ggdb

$(RES_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	mkdir -p ./res
	$(GCC) $(INCS) $(CFLAGS) -c -o "$@" "$<" -lcunit -ggdb

$(RES_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p ./res
	$(GCC) $(INCS) $(CFLAGS) -c  -o "$@" "$<" -lcunit -ggdb

clean:
	rm -rf ./bin/*
	rm -rf ./res/*

debug:
	@echo $(INCS)
