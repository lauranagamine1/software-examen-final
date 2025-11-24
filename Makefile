# Makefile para el Sistema de Cálculo de Notas

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
TARGET = calculo_notas
SOURCES = main.cpp \
          src/Evaluation.cpp \
          src/Student.cpp \
          src/ExtraPointsPolicy.cpp \
          src/PolicyManager.cpp \
          src/GradeCalculator.cpp \
          src/InputValidator.cpp \
          src/DisplayManager.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Compilación exitosa! Ejecutable creado: $(TARGET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Archivos objeto y ejecutable eliminados"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
