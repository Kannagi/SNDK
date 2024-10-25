#rmake

#name executable
exe_name:bin/retroconvert

#command execute
cmd_execute:cd bin && ./retroconvert ship.png -sfc

#file .c or .cpp or folder : main.c;test.c , src;core;
add_folder:src

#--------compiler option------------
libdirs: 
includes:-Iinclude

#-O1 -O2 -O3 -Wall -Wextra -pedantic
options:-O1 -fomit-frame-pointer -Wall -Wextra -pedantic -Wno-unused-parameter
#-lnamelib 
libs:

cmd_precompiler:
cmd_compiler:$compiler $options $includes -c $file -o $object
cmd_linker:$linker -s $libdirs $object -o $exe_name $libs
cmd_postcompiler:

#--------compiler config------------
compilerc:gcc
compilercpp:g++
linker:g++