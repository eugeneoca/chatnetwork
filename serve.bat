@echo off
rem ChatNetwork Server Builder
title ChatNetwork Server
color 0a
cls

echo Compiling...
g++ server.cpp -o server.exe -lwsock32
echo Session Starting...
echo ------------------------
server.exe
del server.exe
echo ------------------------
echo Session ended.
@echo on