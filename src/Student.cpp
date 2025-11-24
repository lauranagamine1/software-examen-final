#include "../include/Student.h"

Student::Student() : studentCode(""), hasReachedMinimumAttendance(false) {
    evaluations.reserve(MAX_EVALUATIONS);
}

Student::Student(const std::string& code) 
    : studentCode(code), hasReachedMinimumAttendance(false) {
    evaluations.reserve(MAX_EVALUATIONS);
}

std::string Student::getStudentCode() const {
    return studentCode;
}

const std::vector<Evaluation>& Student::getEvaluations() const {
    return evaluations;
}

bool Student::getHasReachedMinimumAttendance() const {
    return hasReachedMinimumAttendance;
}

int Student::getMaxEvaluations() const {
    return MAX_EVALUATIONS;
}

void Student::setStudentCode(const std::string& code) {
    this->studentCode = code;
}

void Student::setHasReachedMinimumAttendance(bool hasAttendance) {
    this->hasReachedMinimumAttendance = hasAttendance;
}

bool Student::addEvaluation(const Evaluation& evaluation) {
    if (hasReachedMaxEvaluations()) {
        return false;
    }
    evaluations.push_back(evaluation);
    return true;
}

void Student::clearEvaluations() {
    evaluations.clear();
}

int Student::getEvaluationCount() const {
    return evaluations.size();
}

bool Student::hasReachedMaxEvaluations() const {
    return evaluations.size() >= MAX_EVALUATIONS;
}

double Student::calculateTotalWeight() const {
    double totalWeight = 0.0;
    for (const auto& eval : evaluations) {
        totalWeight += eval.getWeightPercent();
    }
    return totalWeight;
}
