# How to run
### 1. Install **i686-elf**

Linux
```
sh ./install_compiler.sh
```
Mac
```
brew install i686-elf-gcc
```

### 2. Build iso image
```
make
or
make build
```
### 3. Run iso image in QEMU
```
make run
```

# Desciption of each file
### Makefile
Automates compiling C/ASM sources, building the kernel, creating the ISO, and running it in QEMU.
### Dockerfile & docker-compose.yml
**Dockerfile**

Provides an isolated environment with GRUB and xorriso to build the bootable ISO.

**docker-compose.yml**

To be able to build and run Docker image at once.

### linker.ld
Custom [linker script](https://wiki.osdev.org/Linker_Scripts) specifying memory layout of the kernel.
#### Why do we need to use this?
Because ...

### grub.cfg
[GRUB](https://wiki.osdev.org/GRUB) configuration file for booting the kernel.


