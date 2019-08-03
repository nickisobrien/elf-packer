TARGET = packer

CC ?= gcc

SRCDIR := src
INCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(src:.c=.o)

LDFLAGS :=
CFLAGS :=

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -I$(INCDIR)

clean:
	rm -f $(OBJ) $(TARGET)

re: clean $(TARGET)

.PHONY: re clean
