#!/bin/bash

echo "========================================"
echo "   Generando cobertura de código"
echo "========================================"
echo ""

# Descargar Google Test si no existe
if [ ! -d "googletest" ]; then
    echo "Descargando Google Test..."
    git clone https://github.com/google/googletest.git
    echo ""
fi

echo "Compilando con cobertura habilitada..."
echo ""

# Compilar código fuente con cobertura
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/Evaluation.cpp -o src/Evaluation.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/Student.cpp -o src/Student.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/ExtraPointsPolicy.cpp -o src/ExtraPointsPolicy.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/PolicyManager.cpp -o src/PolicyManager.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/GradeCalculator.cpp -o src/GradeCalculator.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/InputValidator.cpp -o src/InputValidator.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c src/DisplayManager.cpp -o src/DisplayManager.o

# Compilar Google Test
g++ -std=c++17 -Igoogletest/googletest/include -Igoogletest/googletest \
    -c googletest/googletest/src/gtest-all.cc -o gtest-all.o

# Compilar tests
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c tests/EvaluationTest.cpp -o tests/EvaluationTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c tests/StudentTest.cpp -o tests/StudentTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c tests/ExtraPointsPolicyTest.cpp -o tests/ExtraPointsPolicyTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c tests/GradeCalculatorTest.cpp -o tests/GradeCalculatorTest.o
g++ -std=c++17 -Wall -Iinclude -Igoogletest/googletest/include --coverage \
    -c tests/test_main.cpp -o tests/test_main.o

# Enlazar con cobertura
g++ -o test_runner --coverage \
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
    echo "Ejecutando tests para generar datos de cobertura..."
    ./test_runner

    echo ""
    echo "========================================"
    echo "   Reporte de Cobertura"
    echo "========================================"
    echo ""

    # Generar reporte de cobertura con gcov
    gcov src/*.cpp

    echo ""
    echo "Archivos de cobertura generados (.gcov)"
    echo "Para ver el reporte completo, revisa los archivos .gcov"
    echo ""

    # Si lcov está instalado, generar reporte HTML
    if command -v lcov &> /dev/null; then
        echo "Generando reporte HTML con lcov..."
        lcov --capture --directory . --output-file coverage.info
        lcov --remove coverage.info '/usr/*' '*/googletest/*' --output-file coverage.info
        genhtml coverage.info --output-directory coverage_report
        echo ""
        echo "Reporte HTML generado en: coverage_report/index.html"
    fi
else
    echo ""
    echo "Error en la compilación."
fi
