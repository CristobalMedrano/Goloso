#Version 0.5.1 - 06-12-2018
#Makefile for Windows and Linux developed by Cristobal Medrano Alvarado.
#Makefile para Windows y Linux desarrollado por Cristobal Medrano Alvardo.

#Falta corregir la salida de archivos a otra carpeta.

#The operating system is checked.
#Se verifica el sistema operativo.
ifeq ($(OS),Windows_NT)
    OS_detected := Windows
else
    OS_detected := $(shell uname -s)
endif

#Select the variables to change depending on the OS.
#Se seleccionan las variables a cambiar dependiendo del SO. 

EXECUTABLE_NAME = goloso
ifeq ($(OS_detected), Windows)
	EXTENSION = .exe
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = $(EXECUTABLE)
	DEBUGEXECUTE = debug_$(EXECUTABLE)
    REMOVE = -del
	FILES = $(SOURCES)\*.o 

endif
ifeq ($(OS_detected), Linux)
	EXTENSION = .out
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = ./$(EXECUTABLE)
	DEBUGEXECUTE = ./debug_$(EXECUTABLE)
    REMOVE = -rm -f
	FILES = $(SOURCES)/*.o 
endif

#Modules and headers folders.
#Carpeta de modulos y cabeceras.
HEADERS = headers
SOURCES = sources
BUILD = build

#Variables
CC = gcc
OPTS = -Wall -g3 -I $(HEADERS)/
DEBUG = -D DEBUG

SRCS = $(wildcard $(SOURCES)/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
DOBJS = $(patsubst %.c,%_debug.o,$(SRCS))
MAIN = $(patsubst %.c,%.o,$(wildcard *.c))

.SILENT: all debug clean $(EXECUTABLE) debug_$(EXECUTABLE)
all: $(EXECUTABLE)

execute: $(EXECUTABLE)
	$(EXECUTABLE)

#debug_execute: debug_$(EXECUTABLE)
#	debug_$(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(MAIN)
	$(CC) -o $@ $^ 
	echo Compilation done. Executable: $(EXECUTE)

debug: debug_$(EXECUTABLE)

debug_$(EXECUTABLE): $(DOBJS) $(MAIN)
	$(CC) -o $@ $^ 
	echo Compilation done. Executable: $(DEBUGEXECUTE)

$(SOURCES)/%.o: $(SOURCES)/%.c
	$(CC) $(OPTS) -c -o $@ $<

$(SOURCES)/%_debug.o: $(SOURCES)/%.c
	$(CC) $(OPTS) $(DEBUG) -c -o $@ $<

%.o: %.c
	$(CC) $(OPTS) -c -o $@ $<

.PHONY: clean
clean:
	$(REMOVE) $(FILES) $(MAIN)
	$(REMOVE) $(EXECUTABLE) debug_$(EXECUTABLE)
	echo Full wipe.
