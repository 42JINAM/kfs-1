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

NAME    := kfs-4
KERNEL  := $(NAME).bin
IMAGE   := $(NAME).iso

# ==============================
# Colors
# ==============================

CGREEN  := \033[32m
CYELLOW := \033[33m
CEND    := \033[0m

# ==============================
# Default Target
# ==============================

all:$(OUTPUT)/$(IMAGE)

# ==============================
# Build Rules
# ==============================

$(OUTPUT)/$(IMAGE): grub.cfg
	@echo "$(CYELLOW)[*] Creating ISO image...$(CEND)"
	rm -rf $(OUTDIR)
	mkdir -p $(OUTDIR)
	mkdir -p iso/boot/
	docker compose up --build
	@echo "$(CGREEN)[✓] $(IMAGE) created$(CEND)"


# ==============================
# Convenience Targets
# ==============================
build: $(OUTDIR)/$(IMAGE)
	@echo "$(CYELLOW)[*] Creating ISO image...$(CEND)"
	rm -rf $(OUTDIR)
	mkdir -p $(OUTDIR)
	mkdir -p iso/boot/
	docker compose up
	@echo "$(CGREEN)[✓] Build finished$(CEND)"

run: $(OUTDIR)/$(IMAGE)
	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU...$(CEND)"
	qemu-system-i386 -cdrom $(OUTDIR)/$(IMAGE)

# debug: $(IMAGE)
# 	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU in debug mode...$(CEND)"
# 	qemu-system-i386 -s -S -cdrom $(IMAGE)

clean:
	rm -rf $(OBJDIR) $(OUTDIR) *.o *.bin *.iso
	@echo "$(CGREEN)[✓] Cleaned all build artifacts$(CEND)"

re:		clean build
# ==============================
# Utility
# ==============================

.PHONY: all build run clean
