#!/usr/bin/env bash
set -x

qemu-system-x86_64 \
  -enable-kvm \
  -soundhw hda \
  -hda "ubuntu-desktop/ubuntu.img" \
  -net user,hostfwd=tcp::2222-:22 \
  -net nic \
  -m 2G \
  -smp 4 \
  -kernel "kernel/linux-4.10/arch/x86/boot/bzImage" \
  -append "console=ttyS0 root=/dev/sda1 nokaslr" \
  -initrd "ubuntu-desktop/initrd.img-4.10.0-19-generic" \
  -nographic \
  -s \
  -S \
  
