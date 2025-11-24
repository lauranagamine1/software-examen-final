#ifndef EXTRAPOINTSPOLICY_H
#define EXTRAPOINTSPOLICY_H

#include <string>

/**
 * Representa la política de puntos extra para un año académico específico.
 * Responsabilidad: Encapsular las reglas de otorgamiento de puntos extra.
 * Alta cohesión: Solo maneja información relacionada con políticas de puntos extra.
 * Bajo acoplamiento: No depende de otras clases del dominio.
 */
class ExtraPointsPolicy {
private:
    std::string academicYear;
    bool hasExtraPoints;
    double extraPointsAmount;
    double minimumGradeRequired;
    bool requiresMinimumAttendance;

public:
    ExtraPointsPolicy();
    ExtraPointsPolicy(const std::string& year, bool hasExtra, double amount,
                     double minGrade, bool requiresAttendance);
    
    // Getters
    std::string getAcademicYear() const;
    bool getHasExtraPoints() const;
    double getExtraPointsAmount() const;
    double getMinimumGradeRequired() const;
    bool getRequiresMinimumAttendance() const;
    
    // Verifica si un estudiante califica para puntos extra según esta política
    bool studentQualifies(double currentGrade, bool hasMinimumAttendance) const;
};

#endif
