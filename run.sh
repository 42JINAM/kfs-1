#!/bin/bash
cd /workspace/src && make
cp /workspace/src/kfs-4.bin /workspace/output/kfs-4.bin
cp /workspace/src/kfs-4.bin /workspace/iso/boot/kfs-4.bin
cd ..
grub-mkrescue -o /workspace/output/kfs-4.iso iso

