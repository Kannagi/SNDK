#!/bin/sh

gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/main.c -o obj/src/main.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/option.c -o obj/src/option.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/tile.c -o obj/src/tile.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/load_write.c -o obj/src/load_write.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/other.c -o obj/src/other.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/palette.c -o obj/src/palette.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/snes.c -o obj/src/snes.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/pce.c -o obj/src/pce.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/neogeo.c -o obj/src/neogeo.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/blit.c -o obj/src/blit.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/sc16.c -o obj/src/sc16.o
gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/sc16x.c -o obj/src/sc16x.o

g++ -s   obj/src/main.o obj/src/option.o obj/src/tile.o obj/src/load_write.o obj/src/other.o obj/src/palette.o obj/src/snes.o obj/src/pce.o obj/src/neogeo.o obj/src/blit.o obj/src/sc16.o obj/src/sc16x.o  -o bin/retroconvert 


