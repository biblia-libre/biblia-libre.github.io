
BUILD_DIR := ./build
TARGET_DIR := .

GB_CURR_DIR := $(shell pwd)

TARGET := gen_bib_tex.elf

define POST_OPERS
	cp ./$(TARGET) ../DATA
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

SRC_INCDIRS := .

SOURCES := gen_bib_tex.cpp

default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
