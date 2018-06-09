@echo off
rem ChatNetwork Builder
title ChatNetwork
color 0a
cls

echo Compiling...
g++ main.cpp -o main.exe
echo Session Starting...
echo ------------------------
main.exe
del main.exe
echo ------------------------
echo Session ended.
@echo on