#!/bin/bash

echo "========================================"
echo "   Compilando y ejecutando tests"
echo "========================================"
echo ""

# Descargar Google Test si no existe
if [ ! -d "googletest" ]; then
    echo "Descargando Google Test..."
    git clone https://github.com/google/googletest.git
    echo ""
fi

echo "Compilando código fuente..."
echo ""

g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/Evaluation.cpp -o src/Evaluation.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/Student.cpp -o src/Student.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/ExtraPointsPolicy.cpp -o src/ExtraPointsPolicy.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/PolicyManager.cpp -o src/PolicyManager.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/GradeCalculator.cpp -o src/GradeCalculator.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/InputValidator.cpp -o src/InputValidator.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c src/DisplayManager.cpp -o src/DisplayManager.o

echo "Compilando Google Test..."
g++ -std=c++17 -Igoogletest/googletest/include -Igoogletest/googletest \
    -c googletest/googletest/src/gtest-all.cc -o gtest-all.o

echo "Compilando archivos de test..."
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c tests/EvaluationTest.cpp -o tests/EvaluationTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c tests/StudentTest.cpp -o tests/StudentTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c tests/ExtraPointsPolicyTest.cpp -o tests/ExtraPointsPolicyTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c tests/GradeCalculatorTest.cpp -o tests/GradeCalculatorTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include \
    -c tests/test_main.cpp -o tests/test_main.o

echo "Enlazando ejecutable de tests..."
g++ -o test_runner \
    src/Evaluation.o \
    src/Student.o \
    src/ExtraPointsPolicy.o \
    src/PolicyManager.o \
    src/GradeCalculator.o \
    src/InputValidator.o \
    src/DisplayManager.o \
    tests/EvaluationTest.o \
    tests/StudentTest.o \
    tests/ExtraPointsPolicyTest.o \
    tests/GradeCalculatorTest.o \
    tests/test_main.o \
    gtest-all.o \
    -lpthread

if [ $? -eq 0 ]; then
    echo ""
    echo "========================================"
    echo "   Ejecutando tests"
    echo "========================================"
    echo ""
    ./test_runner
    echo ""
    echo "Tests completados!"
else
    echo ""
    echo "Error en la compilación de tests."
fi
