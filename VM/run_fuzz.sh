#!/usr/bin/env bash
set -x

qemu-system-x86_64 \
  -enable-kvm \
  -serial stdio \
  -soundhw hda \
  -hda $1 \
  -net user,hostfwd=tcp::2222-:22 \
  -net nic \
  -m 4G \
  -smp 4 \
  -cpu host,-rdtscp \
  -kernel "/home/oem/Desktop/workspace/linux-5.8/arch/x86/boot/bzImage" \
  -initrd "ubuntu-desktop/initrd.img-5.8.0-50-generic" \
  -append "root=/dev/mapper/ubuntu--vg-ubuntu--lv ro" 
 
   
   
