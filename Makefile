# ==============================
# Compiler & Tools
# ==============================

# AS     := i686-elf-as
# AS      := gcc -m32 -x assembler
# CC      := i686-elf-gcc
# LD      := i686-elf-gcc
#
# CC      := gcc 
# LD      := gcc
#
# COMPILE_FLAGS := -m32 -ffreestanding -nostdlib -fno-pic -fno-asynchronous-unwind-tables -fno-unwind-tables
# LD_FLAGS = -m32 -ffreestanding -nostdlib -no-pie -Wl,--build-id=none

# ==============================
#
# Directories
# ==============================
#
# SRCDIR  := src
# OBJDIR  := objs
OUTDIR  := output
#
# ==============================
# Files
# ==============================

CFILES  := kernel terminal vga keyboard init switch_tab gdt printk interupt \
		   utils/memcpy \
		   utils/memset \
		   utils/strlen \
		   utils/printf \
		   utils/printf_format \
		   utils/hexdump \
		   utils/test_printf \
		   ascii/ascii_1_bonus \
		   ascii/ascii_2_bonus \
		   ascii/ascii_3_bonus \
		   ascii/ascii_4_bonus \
		   ascii/ascii_5_bonus \
		   ascii/ascii_bonus
SFILES  := boot gdt_flush set_interupt
SRCDIR = src

C_SRCS  := $(addprefix $(SRCDIR)/, $(addsuffix .c , $(CFILES)))
S_SRCS  := $(addprefix $(SRCDIR)/, $(addsuffix .s , $(SFILES)))
A_SRCS    := $(C_SRCS) $(S_SRCS)


NAME    := kfs-4
KERNEL  := $(NAME).bin
IMAGE   := $(NAME).iso
TARGET			:= $(OUTPUT)/$(IMAGE)
# ==============================
# Colors
# ==============================

CGREEN  := \033[32m
CYELLOW := \033[33m
CEND    := \033[0m

# ==============================
# Default Target
# ==============================

all:$(TARGET)

# ==============================
# Build Rules
# ==============================

run: $(TARGET) $(A_SRCS)
	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU...$(CEND)"
	qemu-system-i386 -cdrom $(OUTDIR)/$(IMAGE)

$(TARGET): grub.cfg $(A_SRCS)
	@echo "$(CYELLOW)[*] Creating ISO image...$(CEND)"
	rm -rf $(OUTDIR)
	mkdir -p $(OUTDIR)
	mkdir -p iso/boot/
	docker compose up --build
	@echo "$(CGREEN)[✓] $(IMAGE) created$(CEND)"


# ==============================
# Convenience Targets
# ==============================
build: $(TARGET) $(A_SRCS)
	@echo "$(CYELLOW)[*] Creating ISO image...$(CEND)"
	rm -rf $(OUTDIR)
	mkdir -p $(OUTDIR)
	# mkdir -p iso/boot/grub 
	docker compose up
	@echo "$(CGREEN)[✓] Build finished$(CEND)"

# debug: $(IMAGE)
# 	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU in debug mode...$(CEND)"
# 	qemu-system-i386 -s -S -cdrom $(IMAGE)

clean:
	rm -rf $(TARGET)
	cd src && make clean
	@echo "$(CGREEN)[✓] Cleaned all build artifacts$(CEND)"

re:		clean build
	# ==============================
# Utility
# ==============================

.PHONY: all build run clean
