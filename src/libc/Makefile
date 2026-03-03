#!/usr/bin/make -f
# src/libc/Makefile - kfs libc 빌드 (OBJDIR + CFILES 백슬래시 스타일)

OBJDIR := objs
SRCDIR := src

CC := i686-elf-gcc
AR := i686-elf-ar

CFLAGS := -ffreestanding -Wall -Wextra -nostdinc -nostdlib -fno-builtin \
          -m32 -Iinclude -g

CFILES = strlen \
         memset \
         memcpy \
         stdlib

SFILES = 

C_OBJCS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(CFILES)))
S_OBJCS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SFILES)))

LIB := libkfs.a

.PHONY: all clean lib install

all: lib

lib: $(LIB)

$(LIB): $(C_OBJCS) $(S_OBJCS)
	@echo "  AR    $(LIB)"
	$(AR) rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "  CC    $<"
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	@echo "  AS    $<"
	i686-elf-as $< -o $@

install: $(LIB)
	@echo "  INSTALL  $(LIB)"
	cp $(LIB) ../../

clean:
	@echo "  CLEAN"
	rm -rf $(OBJDIR) $(LIB)

.PHONY: all lib clean install
