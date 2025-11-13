#!/bin/sh

#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/main.c -o ob2/src/main.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/option.c -o ob2/src/option.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/tile.c -o ob2/src/tile.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/load_write.c -o ob2/src/load_write.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/other.c -o ob2/src/other.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/palette.c -o ob2/src/palette.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/snes.c -o ob2/src/snes.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/pce.c -o ob2/src/pce.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/neogeo.c -o ob2/src/neogeo.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/blit.c -o ob2/src/blit.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/sc16.c -o ob2/src/sc16.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/sc16x.c -o ob2/src/sc16x.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/neogeo_extract_fix.c -o ob2/src/neogeo_extract_fix.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/neogeo_extract.c -o ob2/src/neogeo_extract.o
#x86_64-w64-mingw32-gcc -O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/neogeo_fix.c -o ob2/src/neogeo_fix.o

x86_64-w64-mingw32-g++ -s   ob2/src/main.o ob2/src/option.o ob2/src/tile.o ob2/src/load_write.o ob2/src/other.o ob2/src/palette.o ob2/src/snes.o ob2/src/pce.o ob2/src/neogeo.o ob2/src/blit.o ob2/src/sc16.o ob2/src/sc16x.o ob2/src/neogeo_extract_fix.o ob2/src/neogeo_extract.o ob2/src/neogeo_fix.o  -o bin/retroconvert  --static


