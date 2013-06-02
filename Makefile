COMPILER=gcc

# todo: object files into output path, processing c / c++ files in the same time (?), nested directories for source files (?)
C = c
OUTPUT_PATH = out/production/
SOURCE_PATH = src/
EXEPATH = $(OUTPUT_PATH)
EXE = $(OUTPUT_PATH)myapue

ifeq ($(COMPILER), gcc)     #linux平台
  ifeq ($(OS),Windows_NT)
    OBJ = obj
  else
    OBJ = o
  endif
  COPT = -O2
  CCMD = gcc
  OBJFLAG = -o
  EXEFLAG = -o
# INCLUDES = -I../.includes
  INCLUDES = -I./src/inc
# LIBS = -lgc
  LIBS =
# LIBPATH = -L../gc/.libs
  LIBPATH =
  CPPFLAGS = $(COPT) -g $(INCLUDES)
  LDFLAGS = $(LIBPATH) -g $(LIBS)
  DEP = dep
else #windows平台
  OBJ = obj
  COPT = /O2
  CCMD = cl
  OBJFLAG = /Fo
  EXEFLAG = /Fe
# INCLUDES = /I..\\.includes
  INCLUDES =
# LIBS = ..\\.libs\\libgc.lib
  LIBS =
  CPPFLAGS = $(COPT) /DEBUG $(INCLUDES)
  LDFLAGS = /DEBUG
endif

OBJS := $(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH)*/*.$(C)))

%.$(OBJ):%.$(C)
	@echo $(OBJS)
	@echo Compiling $(basename $<)...
	$(CCMD) -c $(CPPFLAGS) $(CXXFLAGS) $< $(OBJFLAG)$@
	@echo Linking

all: $(OBJS)
	@echo Linking...
	@echo objs: $(OBJS)
	$(CCMD) $(LDFLAGS) $^ $(LIBS) $(EXEFLAG) $(EXEPATH)/$<

clean:
	rm -rf $(SOURCE_PATH)*.$(OBJ) $(EXE)

rebuild: clean all
#rebuild is not entirely correct
