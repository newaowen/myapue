TARGET := libapue_common.a

INC := -I../inc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)


all: $(OBJS)
	@echo build static lib: $(TARGET)
	ar rcs $(TARGET) $(OBJS)

%.o: %.c
	@echo compiling $<
	gcc -c -g $< $(INC)

clean:
	rm -rf *.o
	rm -rf *.a
