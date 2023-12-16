@echo off

rem "First run VsDevCmd.bat"
rem '/mnt/c/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/Common7/Tools/VsDevCmd.bat'
rem Environment variables
set vcvarsall="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
set outdir="out"
set outdll="%outdir%\ios.dll"

rm %outdll%
mkdir %outdir%
rem vcvarsall x64 - change environment to x64
@REM "%vcvarsall%" x64
"%vcvarsall%" x64
rem "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
rem cl ios.c /I include -link  -dll -out:ios.dll
echo "out: %outdll%"
cl ios.c /I include -link  -dll -out:"%outdll%"

rem TODO: use this instead :
rem nmake 