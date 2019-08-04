TARGET = packer

CC ?= gcc

SRCDIR := src
INCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:.c=.o)

STUBTARGET = stub

STUBDIR := $(SRCDIR)/stub

STUBSRC := $(wildcard $(STUBDIR)/*.c)

LDFLAGS :=
CFLAGS :=

all: $(TARGET) $(STUBTARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -I$(INCDIR)

$(STUBTARGET): $(STUBSRC)
	$(CC) $(CFLAGS) -static -c -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET) $(STUBTARGET)

re: clean all

.PHONY: re clean
