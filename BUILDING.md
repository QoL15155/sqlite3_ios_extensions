Build Instructions
=======================

For more information see building instructions for [sqlite3.org](https://www.sqlite.org/howtocompile.html)


Directories
+ `include/` : Contains sqlite3 mandatory include files. Do NOT touch this folder!
+ `out/` : Compilation output

# Linux

``` sh
gcc -g -fPIC -shared ios.c -o ios.so
```

# Windows

Compiling on Windows with MSVC

``` shell
# Command Line run `VsDevCmd.bat
c:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat

# For 64-bit change environment
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat x64

# Compile the library. For example- ios extension:
cl ios.c /I include -link -dll -out:out\ios.dll
```

Another options is to use [Makefile](Makefile) - after configuring the environment as above. Note: *Makefile* will only work on Windows machines.