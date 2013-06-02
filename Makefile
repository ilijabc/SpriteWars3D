#################################################################################
# Project: Jetman Game
# Author: Ilija Djukic
#
# Input variables:
#    TARGET
#    BUILD
#    PACKAGE
#################################################################################

CC := gcc
CPP := g++
RMDIR := rm -rf
MKDIR := mkdir -p

OUT_DIR := Out
OBJ_DIR := $(OUT_DIR)/obj
ONAME := $(OUT_DIR)/SpriteWars3D

#################################################################################
# Configuration
#################################################################################

ifneq ($(word 1,$(MAKECMDGOALS)),build)
	include Build/Config.mk
endif

#################################################################################
# Compiler settings
#################################################################################

INC_PATHS := -ISource/External -ISource/Frameworks
LIB_PATHS := 
LIBS := -lglfw

ifeq ($(BUILD),debug)
	OPT := -g -DDEBUG
else
	OPT := -Wall -O2
endif

#################################################################################
# Target settings
#################################################################################

ifeq ($(TARGET),linux)
	LIBS += -lm -ldl -lGL -lGLU -lXrandr
endif

ifeq ($(TARGET),mingw)
	LIBS += -lgdi32 -lglu32 -lopengl32
	SRC_RES += Source/Resources/resource.rc
	INC_PATHS += \
		-I./Prebuilt/GLFW/include
	LIB_PATHS += \
		-L./Prebuilt/GLFW/lib-mingw
endif

#################################################################################
# Source files
#################################################################################

include Build/Externals.mk
include Build/Frameworks.mk
ifneq ($(PACKAGE),)
	ONAME := $(OUT_DIR)/$(PACKAGE)
	include Build/Package_$(PACKAGE).mk
endif

#################################################################################
# Build rules
#################################################################################

CFLAGS := $(OPT) $(INC_PATHS) $(LIB_PATHS)
OBJS := $(foreach file, $(SRCS), $(OBJ_DIR)/$(strip $(basename $(file))).o)
RES := $(foreach file, $(SRC_RES), $(OBJ_DIR)/$(strip $(basename $(file))).res)

$(OBJ_DIR)/%.res: %.rc
	@echo Win32 Resource
	@-$(MKDIR) "$(@D)"
	@windres.exe -i $< -J rc -o $@ -O coff

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling $<
	@-$(MKDIR) "$(@D)"
	@$(CPP) -c $(CFLAGS) $(DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: %.cc
	@echo Compiling $<
	@-$(MKDIR) "$(@D)"
	@$(CPP) -c $(CFLAGS) $(DEFINES) -o $@ $<

$(OBJ_DIR)/%.o:  %.c
	@echo Compiling $<
	@-$(MKDIR) "$(@D)"
	@$(CC) -c $(CFLAGS) $(DEFINES) -o $@ $<

#################################################################################
# Build rules
#################################################################################

all: build

info:
	@echo ' ======================='
	@echo '  OUTPUT=$(ONAME)'
	@echo '  TARGET=$(TARGET)'
	@echo '  BUILD=$(BUILD)'
	@echo '  PACKAGE=$(PACKAGE)'
	@echo ' ======================='

build: info $(OBJS) $(RES)
	@$(CPP) $(CFLAGS) -o $(ONAME) $(OBJS) $(RES) $(LIBS)
	@echo 'Finished building target: $(ONAME)'

clean:
	-$(RMDIR) $(OUT_DIR)
	@echo 'Intermediate files removed'

run: build
	./$(ONAME)

help:
	@echo " "
	@echo " -----------------------------------------------------------------------------"
	@echo " Usage:"
	@echo " "
	@echo " make <rule>"
	@echo "   <rule>       :  all, build, clean, help"
	@echo " "
	@echo " For (rule = all) configuration is read from Config.mk, otherwise, config"
	@echo " variables must be set manualy."
	@echo " "
	@echo " make <rule> TARGET=<target> BUILD=<build> PACKAGE=<package>"
	@echo "   <target>     :  linux, mingw"
	@echo "   <build>      :  release, debug"
	@echo "   <package>    :  Test"
	@echo " -----------------------------------------------------------------------------"
