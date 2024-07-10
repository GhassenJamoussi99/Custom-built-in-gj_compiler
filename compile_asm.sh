#!/bin/sh

gcc -g -o asm.out asm.s -no-pie -fPIE

./asm.out
