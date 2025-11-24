#include "../include/Evaluation.h"

Evaluation::Evaluation() : name(""), grade(0.0), weightPercent(0.0) {}

Evaluation::Evaluation(const std::string& name, double grade, double weightPercent)
    : name(name), grade(grade), weightPercent(weightPercent) {}

std::string Evaluation::getName() const {
    return name;
}

double Evaluation::getGrade() const {
    return grade;
}

double Evaluation::getWeightPercent() const {
    return weightPercent;
}

void Evaluation::setName(const std::string& name) {
    this->name = name;
}

void Evaluation::setGrade(double grade) {
    this->grade = grade;
}

void Evaluation::setWeightPercent(double weightPercent) {
    this->weightPercent = weightPercent;
}

double Evaluation::calculateWeightedContribution() const {
    return grade * (weightPercent / 100.0);
}
