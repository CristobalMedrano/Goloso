#Version 0.7.0 - 31-12-2018
#Makefile for Windows and Linux developed by Cristobal Medrano Alvarado.
#Makefile para Windows y Linux desarrollado por Cristobal Medrano Alvardo.

# Archivo main para funcion principal, archivos de salida en build.

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
	FILES = $(BUILD)\*.o 

endif
ifeq ($(OS_detected), Linux)
	EXTENSION = .out
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = ./$(EXECUTABLE)
	DEBUGEXECUTE = ./debug_$(EXECUTABLE)
    REMOVE = -rm -f
	FILES = $(BUILD)/*.o 
endif

#Modules and headers folders.
#Carpeta de modulos y cabeceras.
HEADERS = include
SOURCES = src
BUILD = build

#Variables
CC = gcc
HDRS = $(HEADERS)/
BLDS = $(BUILD)/
OPTS = -Wall -g3 -I
DEBUG = -D DEBUG

SRCS = $(wildcard $(SOURCES)/*.c)
OBJS = $(subst $(SOURCES)/, $(BUILD)/,$(patsubst %.c,%.o,$(SRCS)))
DOBJS = $(subst $(SOURCES)/, $(BUILD)/,$(patsubst %.c,%_debug.o,$(SRCS)))
MAIN = main
DMAIN = $(MAIN)_debug

.SILENT: all debug clean $(EXECUTABLE) debug_$(EXECUTABLE)
all: $(EXECUTABLE)

# Normal compilation
$(EXECUTABLE): $(OBJS) $(BUILD)/$(MAIN).o
	$(CC) -o $@ $^ 
	echo Compilation done. Executable: $(EXECUTE)

$(BUILD)/%.o: $(SOURCES)/%.c
	$(CC) $(OPTS) $(HDRS) -c -o $@ $<

$(BUILD)/$(MAIN).o: $(MAIN).c
	$(CC) $(OPTS) $(HDRS) -c -o $(BUILD)/$(MAIN).o $(MAIN).c
# End normal compilation

# Debug compilation
debug: debug_$(EXECUTABLE)

debug_$(EXECUTABLE): $(DOBJS) $(BUILD)/$(DMAIN).o
	$(CC) -o $@ $^ 
	echo Compilation done. Executable: $(DEBUGEXECUTE)

$(BUILD)/%_debug.o: $(SOURCES)/%.c
	$(CC) $(OPTS) $(HDRS) $(DEBUG) -c -o $@ $<

$(BUILD)/$(DMAIN).o: $(MAIN).c
	$(CC) $(OPTS) $(HDRS) $(DEBUG) -c -o $(BUILD)/$(DMAIN).o $(MAIN).c
# End debug compilation.

#Default files compilation
#%.o: %.c
#	$(CC) $(OPTS) -c -o $@ $<

.PHONY: clean
clean:
	$(REMOVE) $(FILES)
	$(REMOVE) $(EXECUTABLE) debug_$(EXECUTABLE)
	echo Full wipe.
