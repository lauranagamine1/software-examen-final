#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>

/**
 * Valida y procesa entradas del usuario desde la consola.
 * Responsabilidad: Centralizar la validación de entrada y manejo de errores.
 * Alta cohesión: Solo maneja operaciones de validación y entrada.
 * Bajo acoplamiento: No depende de clases del dominio, es una utilidad independiente.
 */
class InputValidator {
public:
    InputValidator();
    
    // Limpia el buffer de entrada cuando hay errores
    static void clearInputBuffer();
    
    // Valida que un número esté dentro de un rango específico
    static bool isInRange(double value, double min, double max);
    
    // Lee un número entero validado del usuario con reintentos
    static int readValidatedInt(const std::string& prompt, int min, int max);
    
    // Lee un número double validado del usuario con reintentos
    static double readValidatedDouble(const std::string& prompt, double min, double max);
    
    // Lee una línea de texto del usuario
    static std::string readLine(const std::string& prompt);
    
    // Lee una respuesta Si/No del usuario y retorna true si es Si
    static bool readYesNo(const std::string& prompt);
};

#endif
