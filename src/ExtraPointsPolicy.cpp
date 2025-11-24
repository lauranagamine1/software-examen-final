#include "../include/ExtraPointsPolicy.h"

ExtraPointsPolicy::ExtraPointsPolicy()
    : academicYear(""), hasExtraPoints(false), extraPointsAmount(0.0),
      minimumGradeRequired(0.0), requiresMinimumAttendance(false) {}

ExtraPointsPolicy::ExtraPointsPolicy(const std::string& year, bool hasExtra,
                                   double amount, double minGrade,
                                   bool requiresAttendance)
    : academicYear(year), hasExtraPoints(hasExtra), extraPointsAmount(amount),
      minimumGradeRequired(minGrade), requiresMinimumAttendance(requiresAttendance) {}

std::string ExtraPointsPolicy::getAcademicYear() const {
    return academicYear;
}

bool ExtraPointsPolicy::getHasExtraPoints() const {
    return hasExtraPoints;
}

double ExtraPointsPolicy::getExtraPointsAmount() const {
    return extraPointsAmount;
}

double ExtraPointsPolicy::getMinimumGradeRequired() const {
    return minimumGradeRequired;
}

bool ExtraPointsPolicy::getRequiresMinimumAttendance() const {
    return requiresMinimumAttendance;
}

bool ExtraPointsPolicy::studentQualifies(double currentGrade, 
                                        bool hasMinimumAttendance) const {
    if (!hasExtraPoints) {
        return false;
    }
    
    if (currentGrade < minimumGradeRequired) {
        return false;
    }
    
    if (requiresMinimumAttendance && !hasMinimumAttendance) {
        return false;
    }
    
    return true;
}
