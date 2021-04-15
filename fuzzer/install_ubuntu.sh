#!/usr/bin/env bash

qemu-system-x86_64 \
  -enable-kvm \
  -serial stdio \
  -soundhw hda \
  -hda "ubuntu-desktop/ubuntu.img" \
  -cdrom "iso/ubuntu-17.04-desktop-amd64.iso" \
  -net user,hostfwd=tcp::2222-:22 \
  -net nic \
  -m 2G \
  -smp 4 \
;