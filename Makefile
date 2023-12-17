# 
# Note: This Makefile currently only works on Windows machine
#
# Run: `nmake`
#

# Environment Variables
OUT_DIR = out
PROG = ios

# Compilation
CC = cl
FLAGS = /I include -link  -dll

SRC = src/$(PROG).c
TARGET = $(OUT_DIR)/$(PROG).dll

# Shell Commands
RM = rm

all: clean compile_win

compile_win:
	echo {+] Compiling $(TARGET)
	$(CC) $(SRC) $(FLAGS) -out:"$(TARGET)"

clean:
	echo "[+] Cleaning output directory ($(OUT_DIR))
	$(RM) -f $(OUT_DIR)/*
