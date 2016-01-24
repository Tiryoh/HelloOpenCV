# Makefile
# Copyright (c) 2016 Tiryoh <tiryoh@gmail.com>
# 
# This software is released under the MIT License.

CC :=g++
CFLAGS :=-Wall `pkg-config opencv --cflags`
LDFLAGS :=`pkg-config opencv --libs`
SOURCES :=$(wildcard *.cpp)
EXECUTABLE :=$(SOURCES:.cpp=.out)

.PHONY:all
all:$(EXECUTABLE);

$(EXECUTABLE):$(@:.out=.cpp)
	$(CC) $(@:.out=.cpp) $(LDFLAGS) $(CFLAGS) -o $@

.PHONY:clean
clean:
	rm -rf $(EXECUTABLE)

.PHONY:rebuild
rebuild:clean all;
