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

## Boot Process: From BIOS to Kernel (Simple Explanation)

This is a simplified explanation of how a computer goes from powering on to running an operating system kernel.

---

### 1. BIOS

**BIOS (Basic Input/Output System)** is firmware stored on the motherboard.

When the computer powers on, the BIOS runs first.

What it does:

* Checks hardware (RAM, CPU, keyboard, disks) — this is called **POST**.
* Finds a bootable device (hard drive, USB, etc.).
* Loads the **first sector of that device** into memory.

The BIOS then transfers control to the program it loaded.

This program is called the **bootloader**.

---

### 2. Bootloader (Real Mode)

The bootloader starts in **Real Mode**, which is the CPU's default mode after reset.

Real Mode characteristics:

* 16-bit mode
* Can only access **1 MB of memory**
* No memory protection
* Uses BIOS interrupts for hardware access

The bootloader's job:

* Prepare the system for the operating system
* Load the kernel into memory
* Switch the CPU to **Protected Mode**

Before switching modes, it must set up memory segmentation using the **GDT**.

---

### 3. Create GDT

**GDT (Global Descriptor Table)** defines how memory segments are structured.

Each entry in the GDT describes:

* Base address of a segment
* Size of the segment
* Access permissions (code/data, privilege level, etc.)

Typical minimal GDT contains:

* Null descriptor
* Code segment
* Data segment

Example layout:

| Entry | Purpose             |
| ----- | ------------------- |
| 0     | Null (required)     |
| 1     | Kernel Code Segment |
| 2     | Kernel Data Segment |

This table tells the CPU how to interpret memory addresses once Protected Mode starts.

---

### 4. Load GDT (`lgdt`)

After creating the GDT, the bootloader loads it using the **LGDT instruction**.

`lgdt` loads a structure containing:

* The **size of the GDT**
* The **memory address of the GDT**

Example concept:

```
lgdt [gdt_descriptor]
```

Now the CPU knows where the GDT is located in memory.

---

### 5. Enable Protected Mode (`CR0.PE = 1`)

To switch CPU modes, the bootloader sets the **PE (Protection Enable)** bit in the **CR0 control register**.

Conceptually:

```
CR0 |= 1
```

This tells the CPU:

> "Start operating in Protected Mode."

However, the CPU does not fully switch until a **far jump** occurs.

---

### 6. Far Jump

A **far jump** reloads the **Code Segment register (CS)** with a selector from the GDT.

Example idea:

```
jmp CODE_SEGMENT:protected_mode_entry
```

This step is required because:

* It flushes the CPU pipeline
* It loads the new **segment descriptor**

After this jump, the CPU officially runs in **Protected Mode**.

---

### 7. Protected Mode Starts

The CPU is now in **32-bit Protected Mode**.

Advantages compared to Real Mode:

* Access to **4 GB of memory**
* Memory protection
* Hardware privilege levels (rings)
* Advanced segmentation
* Paging support

However, the segment registers still contain old values from Real Mode.

They must be reinitialized.

---

### 8. Initialize Segment Registers

The kernel or bootloader sets all segment registers to the correct GDT selectors.

Registers updated:

* `DS` (Data Segment)
* `ES`
* `FS`
* `GS`
* `SS` (Stack Segment)

Example idea:

```
mov ax, DATA_SEG
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
```

Now memory accesses use the correct segment descriptors.

---

### 9. Run Kernel

Finally, the bootloader jumps to the **kernel entry point**.

Example concept:

```
call kernel_main
```

From here, the **operating system kernel** takes control.

The kernel can now:

* Set up **paging**
* Initialize **drivers**
* Manage **memory**
* Start **process scheduling**

At this point, the operating system begins running.

---

# Summary

```
BIOS
 ↓
Bootloader (Real Mode)
 ↓
Create GDT
 ↓
Load GDT (lgdt)
 ↓
Enable Protected Mode (CR0.PE = 1)
 ↓
Far Jump
 ↓
Protected Mode Starts
 ↓
Initialize Segment Registers
 ↓
Run Kernel
```

This is the basic process used by many **x86 operating systems** when booting.


## Useful link
[I/O handling](https://wiki.osdev.org/Inline_Assembly/Examples)

### keyboard input
[memory segment](https://www.geeksforgeeks.org/computer-organization-architecture/memory-segmentation-8086-microprocessor/)


[Receiving Bytes From Device/s](https://wiki.osdev.org/index.php?title=I8042_PS/2_Controller)

[Keyboard](https://osdev.jsren.co.uk/input-output/keyboard)

[Cursor](https://wiki.osdev.org/Text_Mode_Cursor)