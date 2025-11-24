#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Student.h"
#include "ExtraPointsPolicy.h"
#include "GradeCalculator.h"

/**
 * Gestiona toda la presentación de información en la consola.
 * Responsabilidad: Formatear y mostrar información al usuario.
 * Alta cohesión: Solo maneja operaciones de presentación/visualización.
 * Bajo acoplamiento: Recibe objetos del dominio pero no los modifica,
 * solo los lee para presentar información.
 */
class DisplayManager {
public:
    DisplayManager();
    
    // Muestra el encabezado principal del programa
    void showHeader() const;
    
    // Muestra un separador de sección
    void showSectionSeparator(const std::string& title) const;
    
    // Muestra las evaluaciones de un estudiante en formato tabla
    void displayEvaluations(const Student& student) const;
    
    // Muestra información de una política de puntos extra
    void displayPolicy(const ExtraPointsPolicy* policy) const;
    
    // Muestra el detalle completo del cálculo de nota final
    void displayGradeCalculationDetail(const Student& student,
                                      const GradeCalculationResult& result,
                                      const ExtraPointsPolicy* policy,
                                      bool passed) const;
    
    // Muestra un mensaje de advertencia
    void showWarning(const std::string& message) const;
    
    // Muestra un mensaje de información
    void showInfo(const std::string& message) const;
};

#endif
