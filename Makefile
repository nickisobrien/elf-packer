TARGET = packer

SRCDIR := src
INCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/*.c)
INC := $(wildcard $(SRCDIR)/*.h)
OBJ := $(src:.c=.o)
CC ?= gcc

LDFLAGS +=
CFLAGS +=

$(TARGET): $(SRC)
	echo $(CC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -I$(INC)

.PHONY: clean
clean:
	rm -f $(obj) myprog

re: clean $(TARGET)
