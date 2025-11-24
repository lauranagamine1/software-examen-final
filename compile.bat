@echo off
echo Compilando el programa de calculo de notas...
echo.

g++ -std=c++17 -Wall -Iinclude ^
    main.cpp ^
    src/Evaluation.cpp ^
    src/Student.cpp ^
    src/ExtraPointsPolicy.cpp ^
    src/PolicyManager.cpp ^
    src/GradeCalculator.cpp ^
    src/InputValidator.cpp ^
    src/DisplayManager.cpp ^
    -o calculo_notas.exe

if %errorlevel% equ 0 (
    echo.
    echo Compilacion exitosa! Ejecutable creado: calculo_notas.exe
    echo.
    echo Para ejecutar el programa, use: calculo_notas.exe
) else (
    echo.
    echo Error en la compilacion.
)
pause
