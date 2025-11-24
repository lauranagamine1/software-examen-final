#ifndef EVALUATION_H
#define EVALUATION_H

#include <string>

/**
 * Representa una evaluación individual del estudiante.
 * Responsabilidad: Encapsular los datos de una evaluación (nombre, nota, peso).
 * Alta cohesión: Solo maneja datos relacionados con una evaluación.
 */
class Evaluation {
private:
    std::string name;
    double grade;
    double weightPercent;

public:
    Evaluation();
    Evaluation(const std::string& name, double grade, double weightPercent);
    
    // Getters
    std::string getName() const;
    double getGrade() const;
    double getWeightPercent() const;
    
    // Setters
    void setName(const std::string& name);
    void setGrade(double grade);
    void setWeightPercent(double weightPercent);
    
    // Calcula la contribución ponderada de esta evaluación al promedio final
    double calculateWeightedContribution() const;
};

#endif
