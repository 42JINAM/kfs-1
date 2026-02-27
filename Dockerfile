FROM ubuntu:22.04

WORKDIR /workspace

RUN apt update && apt install -y grub-pc-bin xorriso

RUN mkdir -p /workspace/isodir/boot/grub

COPY kfs-1.bin /workspace/isodir/boot/kfs-1.bin
COPY grub.cfg /workspace/isodir/boot/grub/grub.cfg

CMD ["grub-mkrescue", "-o", "/workspace/output/kfs-1.iso", "isodir"]
