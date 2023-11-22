@echo off

setlocal

cd /d %~dp0
echo Compiling 'llarm.cpp' into 'llarm.exe'...
g++ llarm.cpp -O2 -static -Wl,--stack=256000000 -o llarm.exe
echo Compiling 'simpllar.cpp' into 'simpllar.exe'...
g++ simpllar.cpp -O2 -static -Wl,--stack=256000000 -o simpllar.exe
echo Done!

endlocal
