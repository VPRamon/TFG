#!/bin/bash
set -x

/home/fuzz/fuzzer/fuzzer
wait $job 
nohup cat bug_report.txt
