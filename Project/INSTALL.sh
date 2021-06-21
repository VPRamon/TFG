#!/bin/bash
set -x

cd src/
make clean
make

cd ../fuzzer_ssh/fuzzer
make
