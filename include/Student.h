#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Evaluation.h"

/**
 * Representa un estudiante con sus evaluaciones y asistencia.
 * Responsabilidad: Gestionar la información del estudiante y sus evaluaciones.
 * Alta cohesión: Solo maneja datos y operaciones relacionadas con el estudiante.
 * Bajo acoplamiento: Solo depende de Evaluation.
 */
class Student {
private:
    std::string studentCode;
    std::vector<Evaluation> evaluations;
    bool hasReachedMinimumAttendance;
    static const int MAX_EVALUATIONS = 10;

public:
    Student();
    explicit Student(const std::string& code);
    
    // Getters
    std::string getStudentCode() const;
    const std::vector<Evaluation>& getEvaluations() const;
    bool getHasReachedMinimumAttendance() const;
    int getMaxEvaluations() const;
    
    // Setters
    void setStudentCode(const std::string& code);
    void setHasReachedMinimumAttendance(bool hasAttendance);
    
    // Gestión de evaluaciones
    bool addEvaluation(const Evaluation& evaluation);
    void clearEvaluations();
    int getEvaluationCount() const;
    bool hasReachedMaxEvaluations() const;
    
    // Cálculos relacionados con las evaluaciones del estudiante
    double calculateTotalWeight() const;
};

#endif
