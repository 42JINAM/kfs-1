# ==============================
# Compiler & Tools
# ==============================

# AS     := i686-elf-as
AS      := nasm
CC      := i686-elf-gcc
LD      := i686-elf-gcc

# ==============================
# Directories
# ==============================

SRCDIR  := ./
OBJDIR  := objs
OUTDIR  := output

# ==============================
# Files
# ==============================

NAME    := kfs-4
KERNEL  := $(NAME).bin
IMAGE   := $(NAME).iso

CFILES  := kernel terminal vga keyboard init switch_tab gdt printk interupt pic\
		   utils/memcpy \
		   utils/memset \
		   utils/strlen \
		   utils/printf \
		   utils/printf_format \
		   utils/hexdump \
		   utils/test_printf \
		   utils/register\
		   ascii/ascii_1_bonus \
		   ascii/ascii_2_bonus \
		   ascii/ascii_3_bonus \
		   ascii/ascii_4_bonus \
		   ascii/ascii_5_bonus \
		   ascii/ascii_bonus
SFILES  := boot gdt_flush set_interupt

C_OBJS  := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(CFILES)))
S_OBJS  := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SFILES)))
OBJS    := $(C_OBJS) $(S_OBJS)

# ==============================
# Colors
# ==============================

CGREEN  := \033[32m
CYELLOW := \033[33m
CEND    := \033[0m

# ==============================
# Default Target
# ==============================

all: $(KERNEL)

# ==============================
# Build Rules
# ==============================

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -fno-omit-frame-pointer -fno-builtin -nostdlib -nodefaultlibs -ffreestanding -O2 -nostdlib -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	$(AS) -f elf $< -o $@

$(KERNEL): $(OBJS) linker.ld
	$(LD) -nostdlib -ffreestanding -O2 -T linker.ld -o $@ $(OBJS) -lgcc
	@echo "$(CGREEN)[✓] $(KERNEL) created$(CEND)"
# ==============================
# Convenience Targets
# ==============================
# debug: $(IMAGE)
# 	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU in debug mode...$(CEND)"
# 	qemu-system-i386 -s -S -cdrom $(IMAGE)

clean:
	rm -rf $(OBJDIR) $(OUTDIR) $(KERNEL) $(IMAGE)

	@echo "$(CGREEN)[✓] Cleaned all build artifacts$(CEND)"

re:		clean build
# ==============================
# Utility
# ==============================
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/utils
	mkdir -p $(OBJDIR)/ascii
	@echo "$(CGREEN)[✓] $(OBJDIR) directory created$(CEND)"

.PHONY: all build run clean
