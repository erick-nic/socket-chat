@echo off

SET INCLUDE_DIR=.\include

:: this command creates or validate the /bin dir
if not exist ".\bin" (
    echo creating the 'bin' directory
    mkdir "bin"
    if exist "bin/server.exe" del "bin/server.exe"
)

:: start compiling the server socket
echo compiling the server socket...
clang++ -std=c++23 -I %INCLUDE_DIR% src/server/main.cpp src/server/socket_handler/server.cpp -o bin/server.exe -lws2_32
if errorLevel == 1 (
    echo there was an error during the compilation
    pause
    exit
)
echo server socket compiled successfully!

:: start the server socket
.\bin\server.exe
pause