@echo off

rem "First run VsDevCmd.bat"
rem '/mnt/c/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/Common7/Tools/VsDevCmd.bat'
rem "Change environment to x64"
rem vcvarsall x64
rem "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64

rem Environment variables
set vcvarsall="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
set outdir=out
set outdll="%outdir%\ios.dll"

echo This should be run inside the context of 'VsDevCmd.bat'
echo .
echo To change environment, run 'vcvarsall.bat' script.
echo For instance:
echo %vcvarsall% x64
echo .
echo .
echo [+] Cleaning out output ('%outdir%') directory
if exist "%outdir%" rm %outdir%/*

echo [+] Compiling Library
cl ios.c /I include -link  -dll -out:"%outdll%"

echo [+] Enjoy: %outdll%

rem TODO: use this instead :
rem nmake 
