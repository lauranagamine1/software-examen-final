#include <iostream>
#include <iomanip>
#include <cmath>
#include "include/Student.h"
#include "include/Evaluation.h"
#include "include/PolicyManager.h"
#include "include/GradeCalculator.h"
#include "include/InputValidator.h"
#include "include/DisplayManager.h"

/**
 * Registra las evaluaciones de un estudiante mediante entrada por consola.
 * Permite al usuario ingresar hasta el máximo de evaluaciones permitidas.
 */
void registerStudentEvaluations(Student& student, const InputValidator& validator,
                               const DisplayManager& display) {
    display.showSectionSeparator("REGISTRO DE EVALUACIONES");
    
    int numEvaluations = validator.readValidatedInt(
        "¿Cuántas evaluaciones desea registrar? (máximo " + 
        std::to_string(student.getMaxEvaluations()) + "): ",
        1, student.getMaxEvaluations()
    );
    
    student.clearEvaluations();
    
    for (int i = 0; i < numEvaluations; i++) {
        std::cout << "\n--- Evaluación " << (i + 1) << " ---\n";
        
        std::string name = validator.readLine("Nombre de la evaluación: ");
        double grade = validator.readValidatedDouble("Nota obtenida (0-20): ", 0.0, 20.0);
        double weight = validator.readValidatedDouble("Peso porcentual (0-100): ", 0.0, 100.0);
        
        Evaluation eval(name, grade, weight);
        student.addEvaluation(eval);
    }
    
    double totalWeight = student.calculateTotalWeight();
    std::cout << "\nPeso total de evaluaciones: " << std::fixed 
              << std::setprecision(2) << totalWeight << "%\n";
    
    if (std::abs(totalWeight - 100.0) > 0.01) {
        display.showWarning("Los pesos no suman exactamente 100%. "
                          "El cálculo se realizará con los pesos ingresados.");
    }
}

/**
 * Registra si el estudiante cumplió con la asistencia mínima.
 */
void registerStudentAttendance(Student& student, const InputValidator& validator,
                              const DisplayManager& display) {
    display.showSectionSeparator("REGISTRO DE ASISTENCIA");
    
    bool hasAttendance = validator.readYesNo(
        "¿El estudiante alcanzó la asistencia mínima requerida? (S/N): "
    );
    
    student.setHasReachedMinimumAttendance(hasAttendance);
    
    std::cout << "Asistencia registrada: " 
              << (hasAttendance ? "CUMPLE" : "NO CUMPLE") << "\n";
}

/**
 * Procesa el cálculo de nota final para un estudiante.
 * Implementa el flujo principal del caso de uso.
 */
void processStudentGrade(PolicyManager& policyManager, 
                        const InputValidator& validator,
                        const DisplayManager& display) {
    Student student;
    
    // RF1: Registro de estudiante
    display.showSectionSeparator("IDENTIFICACIÓN DEL ESTUDIANTE");
    std::string code = validator.readLine("Ingrese el código del estudiante: ");
    student.setStudentCode(code);
    
    // RF2: Registro de evaluaciones
    registerStudentEvaluations(student, validator, display);
    
    // RF3: Registro de asistencia mínima
    registerStudentAttendance(student, validator, display);
    
    // RF4: Consulta de política de puntos extra
    display.showSectionSeparator("CONSULTA DE POLÍTICA DE PUNTOS EXTRA");
    std::string academicYear = validator.readLine(
        "Ingrese el año académico (ej: 2025-1, 2025-2): "
    );
    
    const ExtraPointsPolicy* policy = policyManager.findPolicyByYear(academicYear);
    display.displayPolicy(policy);
    
    // RF5: Cálculo de nota final
    std::cout << "\n\nCalculando nota final...\n";
    
    GradeCalculator calculator;
    GradeCalculationResult result = calculator.calculateFinalGrade(student, policy);
    bool passed = calculator.hasPassedCourse(result.getFinalGrade());
    
    // RF6: Visualización del detalle de cálculo
    display.displayGradeCalculationDetail(student, result, policy, passed);
}

/**
 * Función principal del programa.
 * Coordina el flujo general del sistema.
 */
int main() {
    PolicyManager policyManager;
    InputValidator validator;
    DisplayManager display;
    
    display.showHeader();
    
    bool continueProgram = true;
    
    while (continueProgram) {
        processStudentGrade(policyManager, validator, display);
        
        std::cout << "\n¿Desea calcular la nota de otro estudiante? (S/N): ";
        continueProgram = validator.readYesNo("");
    }
    
    std::cout << "\n¡Gracias por usar el sistema de cálculo de notas!\n";
    std::cout << "Hasta pronto.\n\n";
    
    return 0;
}
