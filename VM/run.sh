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
  -vga std \
