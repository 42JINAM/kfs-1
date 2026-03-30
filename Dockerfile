FROM ubuntu:20.04

WORKDIR /workspace

RUN dpkg --add-architecture i386
RUN apt update && apt install -y libc6:i386 libstdc++6:i386 grub-pc-bin xorriso nasm make wget unzip vim


ENV PATH="/tmp/cross/bin:$PATH"

COPY install_compiler.sh /install_compiler.sh
RUN /install_compiler.sh 
#RUN cd /workspace/src && make
#RUN cp /workspace/src/kfs-4.bin /workspace/output/.
#RUN cp /workspace/src/kfs-4.bin /workspace/iso/boot/.

CMD ["./run.sh"]
#CMD ["tail", "-f", "/dev/null"]
#CMD ["grub-mkrescue", "-o", "/workspace/output/kfs-4.iso", "iso"]
