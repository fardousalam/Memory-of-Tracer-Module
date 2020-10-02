include ../Makefile.config

PROJECT = memory_main
OBJS    = $(PROJECT).o $(DEP_TB).o $(DEP_MOD).o $(DEP_TOP).o
DEP_TB  = memory_tb
DEP_MOD  = memory_top
DEP_TOP = memory


include ../Makefile.rules
