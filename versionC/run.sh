#!/bin/sh
bin/clang -O1 --target=mos-snes -ffreestanding -nostdlib make.c -S
python3 stoh.py make.s make.egl
higueulc







