@echo off

:: this command creates or validate the /bin dir
if not exist ".\bin" (
    echo creating the 'bin' directory
    mkdir "bin"
    if exist "bin/server.exe" del "bin/server.exe"
) else (
    echo 'bin' dir already exists
)

:: start compiling the server socket
echo compiling the server socket...
clang++ -std=c++23 -I src/include src/server/main.cpp src/server/server.cpp -o bin/server.exe -lws2_32
if errorLevel == 1 (
    echo there was an error during the compilation
    pause
    exit
)
echo server socket compiled successfully!

:: start the server socket
.\bin\server.exe

pause