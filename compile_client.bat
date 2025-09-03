@echo off

:: this command creates or validate the /bin dir
if not exist ".\bin" (
    echo creating the 'bin' directory
    mkdir "bin"
    if exist "bin/client.exe" del "bin/client.exe"
) else (
    echo 'bin' dir already exists
)

:: start compiling the client socket
echo compiling the client socket...
clang++ -I src/include src/client/_client.cpp -o bin/client.exe -lws2_32
if errorLevel == 1 (
    echo there was an error during the compilation
    pause
    exit
)
echo client socket compiled successfully!

:: start the client socket
.\bin\client.exe

pause