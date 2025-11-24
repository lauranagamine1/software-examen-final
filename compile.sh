#!/bin/bash

echo "Compilando el programa de cálculo de notas..."
echo ""

g++ -std=c++17 -Wall -Iinclude \
    main.cpp \
    src/Evaluation.cpp \
    src/Student.cpp \
    src/ExtraPointsPolicy.cpp \
    src/PolicyManager.cpp \
    src/GradeCalculator.cpp \
    src/InputValidator.cpp \
    src/DisplayManager.cpp \
    -o calculo_notas

if [ $? -eq 0 ]; then
    echo ""
    echo "Compilación exitosa! Ejecutable creado: calculo_notas"
    echo ""
    echo "Para ejecutar el programa, use: ./calculo_notas"
else
    echo ""
    echo "Error en la compilación."
fi
