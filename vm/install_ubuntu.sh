#!/usr/bin/env bash

qemu-img create -f qcow2 ubuntu-desktop/$2.img 20G

qemu-system-x86_64 \
  -enable-kvm \
  -serial stdio \
  -soundhw hda \
  -hda "ubuntu-desktop/$2.img" \
  -cdrom "$1" \
  -net user,hostfwd=tcp::2222-:22 \
  -net nic \
  -m 2G \
  -smp 4 \
  -vga std \