COMPILER=gcc
C = c

#OUTPUT_PATH = ../../out/production/chapter2
EXEPATH =

INCLUDES = -I../inc
COPT = -O2
CCMD = gcc
OBJ  = o
# LIBS = -lgc
LIBS = -lapue_common -lpthread
LIBPATH = -L../lib
CPPFLAGS = $(COPT) -g $(INCLUDES)
LDFLAGS = $(LIBPATH) -g $(LIBS)
DEP = dep

OBJS := $(patsubst %.$(C),%.($OBJ),$(wildcard *.$(C)))
EXES := $(patsubst %.$(C),%,$(wildcard *.$(C)))

all:
	@echo build $(EXES)
	@for e in $(EXES);\
	do\
		$(CCMD) -o $(EXEPATH)$$e $$e.c $(CPPFLAGS) -static $(LDFLAGS);\
	done

%.$(OBJ):%.$(C)
	@echo compiling $(basename $<)...
	$(CCMD) -c $(CPPFLAGS) $< $@

clean:
	rm -rf *.$(OBJ) EXEPATH

rebuild: clean all
#
