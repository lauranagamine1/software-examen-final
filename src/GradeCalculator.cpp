#include "../include/GradeCalculator.h"
#include <algorithm>

// GradeCalculationResult implementation
GradeCalculationResult::GradeCalculationResult()
    : weightedAverage(0.0), afterPenalty(0.0), extraPointsApplied(0.0),
      finalGrade(0.0), penaltyApplied(false), extraPointsGranted(false),
      penaltyReason(""), extraPointsReason("") {}

void GradeCalculationResult::setWeightedAverage(double avg) {
    weightedAverage = avg;
}

void GradeCalculationResult::setAfterPenalty(double grade) {
    afterPenalty = grade;
}

void GradeCalculationResult::setExtraPointsApplied(double points) {
    extraPointsApplied = points;
}

void GradeCalculationResult::setFinalGrade(double grade) {
    finalGrade = grade;
}

void GradeCalculationResult::setPenaltyApplied(bool applied) {
    penaltyApplied = applied;
}

void GradeCalculationResult::setExtraPointsGranted(bool granted) {
    extraPointsGranted = granted;
}

void GradeCalculationResult::setPenaltyReason(const std::string& reason) {
    penaltyReason = reason;
}

void GradeCalculationResult::setExtraPointsReason(const std::string& reason) {
    extraPointsReason = reason;
}

double GradeCalculationResult::getWeightedAverage() const {
    return weightedAverage;
}

double GradeCalculationResult::getAfterPenalty() const {
    return afterPenalty;
}

double GradeCalculationResult::getExtraPointsApplied() const {
    return extraPointsApplied;
}

double GradeCalculationResult::getFinalGrade() const {
    return finalGrade;
}

bool GradeCalculationResult::isPenaltyApplied() const {
    return penaltyApplied;
}

bool GradeCalculationResult::areExtraPointsGranted() const {
    return extraPointsGranted;
}

std::string GradeCalculationResult::getPenaltyReason() const {
    return penaltyReason;
}

std::string GradeCalculationResult::getExtraPointsReason() const {
    return extraPointsReason;
}

// GradeCalculator implementation
GradeCalculator::GradeCalculator() {}

double GradeCalculator::calculateWeightedAverage(const Student& student) const {
    const auto& evaluations = student.getEvaluations();
    
    if (evaluations.empty()) {
        return 0.0;
    }
    
    double weightedSum = 0.0;
    double totalWeight = student.calculateTotalWeight();
    
    for (const auto& eval : evaluations) {
        weightedSum += eval.calculateWeightedContribution();
    }
    
    if (totalWeight > 0.0) {
        return (weightedSum / totalWeight) * 100.0;
    }
    
    return 0.0;
}

double GradeCalculator::applyAttendancePenalty(double baseGrade, 
                                              bool hasMinimumAttendance) const {
    if (!hasMinimumAttendance) {
        return 0.0;
    }
    return baseGrade;
}

GradeCalculationResult GradeCalculator::calculateFinalGrade(
    const Student& student, const ExtraPointsPolicy* policy) const {
    
    GradeCalculationResult result;
    
    // Paso 1: Calcular promedio ponderado
    double weightedAvg = calculateWeightedAverage(student);
    result.setWeightedAverage(weightedAvg);
    
    // Paso 2: Aplicar penalización por asistencia
    bool hasAttendance = student.getHasReachedMinimumAttendance();
    double afterPenalty = applyAttendancePenalty(weightedAvg, hasAttendance);
    result.setAfterPenalty(afterPenalty);
    
    if (!hasAttendance) {
        result.setPenaltyApplied(true);
        result.setPenaltyReason("No alcanzó la asistencia mínima requerida (70%)");
    }
    
    // Paso 3: Aplicar puntos extra si califica
    double extraPoints = 0.0;
    bool grantsExtra = false;
    
    if (policy != nullptr && policy->studentQualifies(afterPenalty, hasAttendance)) {
        extraPoints = policy->getExtraPointsAmount();
        grantsExtra = true;
        result.setExtraPointsReason(
            "Cumplió con nota mínima (" + 
            std::to_string(policy->getMinimumGradeRequired()) +
            ") y asistencia requerida"
        );
    }
    
    result.setExtraPointsApplied(extraPoints);
    result.setExtraPointsGranted(grantsExtra);
    
    // Paso 4: Calcular nota final (máximo 20)
    double finalGrade = std::min(MAX_GRADE, afterPenalty + extraPoints);
    result.setFinalGrade(finalGrade);
    
    return result;
}

bool GradeCalculator::hasPassedCourse(double finalGrade) const {
    return finalGrade >= PASSING_GRADE;
}
