#include "../include/DisplayManager.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

DisplayManager::DisplayManager() {}

void DisplayManager::showHeader() const {
    std::cout << "========================================\n";
    std::cout << "   SISTEMA DE CÁLCULO DE NOTAS FINALES\n";
    std::cout << "   INGENIERÍA DE SOFTWARE - UTEC\n";
    std::cout << "========================================\n\n";
}

void DisplayManager::showSectionSeparator(const std::string& title) const {
    std::cout << "\n=== " << title << " ===\n";
}

void DisplayManager::displayEvaluations(const Student& student) const {
    showSectionSeparator("EVALUACIONES REGISTRADAS");
    
    std::cout << std::left << std::setw(20) << "Evaluación"
              << std::right << std::setw(10) << "Nota"
              << std::setw(12) << "Peso (%)" << "\n";
    std::cout << std::string(42, '-') << "\n";
    
    for (const auto& eval : student.getEvaluations()) {
        std::cout << std::left << std::setw(20) << eval.getName()
                  << std::right << std::setw(10) << std::fixed 
                  << std::setprecision(2) << eval.getGrade()
                  << std::setw(12) << std::fixed << std::setprecision(2) 
                  << eval.getWeightPercent() << "\n";
    }
}

void DisplayManager::displayPolicy(const ExtraPointsPolicy* policy) const {
    showSectionSeparator("POLÍTICA DE PUNTOS EXTRA");
    
    if (policy == nullptr) {
        std::cout << "No se encontró política para este año académico.\n";
        return;
    }
    
    std::cout << "Año académico: " << policy->getAcademicYear() << "\n";
    std::cout << "¿Hay puntos extra?: " 
              << (policy->getHasExtraPoints() ? "SÍ" : "NO") << "\n";
    
    if (policy->getHasExtraPoints()) {
        std::cout << "Puntos extra disponibles: " << std::fixed 
                  << std::setprecision(2) << policy->getExtraPointsAmount() << "\n";
        std::cout << "Nota mínima requerida: " << std::fixed 
                  << std::setprecision(2) << policy->getMinimumGradeRequired() << "\n";
        std::cout << "Requiere asistencia mínima: "
                  << (policy->getRequiresMinimumAttendance() ? "SÍ" : "NO") << "\n";
    }
}

void DisplayManager::displayGradeCalculationDetail(
    const Student& student,
    const GradeCalculationResult& result,
    const ExtraPointsPolicy* policy,
    bool passed) const {
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "       DETALLE DE CÁLCULO DE NOTA FINAL\n";
    std::cout << std::string(60, '=') << "\n\n";
    
    std::cout << "Estudiante: " << student.getStudentCode() << "\n\n";
    
    displayEvaluations(student);
    
    std::cout << "\n--- CÁLCULO PASO A PASO ---\n\n";
    
    // Paso 1: Promedio ponderado
    std::cout << "1. PROMEDIO PONDERADO DE EVALUACIONES:\n";
    for (const auto& eval : student.getEvaluations()) {
        double contribution = eval.calculateWeightedContribution();
        std::cout << "   " << std::left << std::setw(20) << eval.getName()
                  << ": " << std::fixed << std::setprecision(2) << eval.getGrade()
                  << " × " << eval.getWeightPercent() << "% = "
                  << contribution << "\n";
    }
    std::cout << "   " << std::string(50, '-') << "\n";
    std::cout << "   Promedio ponderado: " << std::fixed << std::setprecision(2)
              << result.getWeightedAverage() << "\n\n";
    
    // Paso 2: Penalización por asistencia
    std::cout << "2. VERIFICACIÓN DE ASISTENCIA:\n";
    std::cout << "   Asistencia mínima alcanzada: "
              << (student.getHasReachedMinimumAttendance() ? "SÍ" : "NO") << "\n";
    
    if (result.isPenaltyApplied()) {
        std::cout << "   PENALIZACIÓN APLICADA: Nota = 0.00\n";
        std::cout << "   Razón: " << result.getPenaltyReason() << "\n";
    } else {
        std::cout << "   Sin penalización aplicada\n";
    }
    std::cout << "   Nota después de penalización: " << std::fixed 
              << std::setprecision(2) << result.getAfterPenalty() << "\n\n";
    
    // Paso 3: Puntos extra
    std::cout << "3. APLICACIÓN DE PUNTOS EXTRA:\n";
    if (policy != nullptr && policy->getHasExtraPoints()) {
        std::cout << "   Política del año " << policy->getAcademicYear() << ":\n";
        std::cout << "   - Puntos disponibles: " << std::fixed 
                  << std::setprecision(2) << policy->getExtraPointsAmount() << "\n";
        std::cout << "   - Nota mínima requerida: " << std::fixed 
                  << std::setprecision(2) << policy->getMinimumGradeRequired() << "\n";
        std::cout << "   - Requiere asistencia: "
                  << (policy->getRequiresMinimumAttendance() ? "SÍ" : "NO") << "\n\n";
        
        if (result.areExtraPointsGranted()) {
            std::cout << "   PUNTOS EXTRA OTORGADOS: +" << std::fixed 
                      << std::setprecision(2) << result.getExtraPointsApplied() << "\n";
            std::cout << "   Razón: " << result.getExtraPointsReason() << "\n";
        } else {
            std::cout << "   No califica para puntos extra\n";
            if (result.getAfterPenalty() < policy->getMinimumGradeRequired()) {
                std::cout << "   Razón: Nota insuficiente (requiere al menos "
                          << std::fixed << std::setprecision(2) 
                          << policy->getMinimumGradeRequired() << ")\n";
            }
        }
    } else {
        std::cout << "   No hay política de puntos extra para este año\n";
    }
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "NOTA FINAL: " << std::fixed << std::setprecision(2) 
              << result.getFinalGrade();
    
    if (passed) {
        std::cout << " - APROBADO\n";
    } else {
        std::cout << " - DESAPROBADO\n";
    }
    std::cout << std::string(60, '=') << "\n";
}

void DisplayManager::showWarning(const std::string& message) const {
    std::cout << "ADVERTENCIA: " << message << "\n";
}

void DisplayManager::showInfo(const std::string& message) const {
    std::cout << message << "\n";
}
