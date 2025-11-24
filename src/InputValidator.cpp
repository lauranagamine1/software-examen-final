#include "../include/InputValidator.h"
#include <iostream>
#include <limits>

InputValidator::InputValidator() {}

void InputValidator::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool InputValidator::isInRange(double value, double min, double max) {
    return value >= min && value <= max;
}

int InputValidator::readValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    std::cout << prompt;
    
    while (!(std::cin >> value) || value < min || value > max) {
        std::cout << "Error: Ingrese un número válido entre " << min 
                  << " y " << max << ": ";
        clearInputBuffer();
    }
    clearInputBuffer();
    
    return value;
}

double InputValidator::readValidatedDouble(const std::string& prompt, 
                                          double min, double max) {
    double value;
    std::cout << prompt;
    
    while (!(std::cin >> value) || !isInRange(value, min, max)) {
        std::cout << "Error: Ingrese un valor válido entre " << min 
                  << " y " << max << ": ";
        clearInputBuffer();
    }
    clearInputBuffer();
    
    return value;
}

std::string InputValidator::readLine(const std::string& prompt) {
    std::string line;
    std::cout << prompt;
    std::getline(std::cin, line);
    return line;
}

bool InputValidator::readYesNo(const std::string& prompt) {
    char response;
    std::cout << prompt;
    
    while (!(std::cin >> response) || 
           (toupper(response) != 'S' && toupper(response) != 'N')) {
        std::cout << "Error: Ingrese 'S' para Sí o 'N' para No: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    
    return (toupper(response) == 'S');
}
