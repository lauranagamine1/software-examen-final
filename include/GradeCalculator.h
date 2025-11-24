#ifndef GRADECALCULATOR_H
#define GRADECALCULATOR_H

#include "Student.h"
#include "ExtraPointsPolicy.h"

/**
 * Resultado detallado del cálculo de la nota final.
 * Contiene información paso a paso del proceso de cálculo.
 */
class GradeCalculationResult {
private:
    double weightedAverage;
    double afterPenalty;
    double extraPointsApplied;
    double finalGrade;
    bool penaltyApplied;
    bool extraPointsGranted;
    std::string penaltyReason;
    std::string extraPointsReason;

public:
    GradeCalculationResult();
    
    // Setters para construir el resultado
    void setWeightedAverage(double avg);
    void setAfterPenalty(double grade);
    void setExtraPointsApplied(double points);
    void setFinalGrade(double grade);
    void setPenaltyApplied(bool applied);
    void setExtraPointsGranted(bool granted);
    void setPenaltyReason(const std::string& reason);
    void setExtraPointsReason(const std::string& reason);
    
    // Getters para acceder al resultado
    double getWeightedAverage() const;
    double getAfterPenalty() const;
    double getExtraPointsApplied() const;
    double getFinalGrade() const;
    bool isPenaltyApplied() const;
    bool areExtraPointsGranted() const;
    std::string getPenaltyReason() const;
    std::string getExtraPointsReason() const;
};

/**
 * Calcula la nota final de un estudiante aplicando todas las reglas del sistema.
 * Responsabilidad: Centralizar la lógica de cálculo de notas.
 * Alta cohesión: Solo se encarga de cálculos relacionados con notas.
 * Bajo acoplamiento: Depende de Student y ExtraPointsPolicy, pero no los modifica.
 */
class GradeCalculator {
private:
    static constexpr double MAX_GRADE = 20.0;
    static constexpr double PASSING_GRADE = 10.5;
    
    // Calcula el promedio ponderado de las evaluaciones del estudiante
    double calculateWeightedAverage(const Student& student) const;
    
    // Aplica la penalización por no cumplir con asistencia mínima
    double applyAttendancePenalty(double baseGrade, bool hasMinimumAttendance) const;

public:
    GradeCalculator();
    
    // Calcula la nota final del estudiante considerando todas las reglas
    GradeCalculationResult calculateFinalGrade(const Student& student,
                                              const ExtraPointsPolicy* policy) const;
    
    // Verifica si el estudiante aprobó según la nota final
    bool hasPassedCourse(double finalGrade) const;
};

#endif
