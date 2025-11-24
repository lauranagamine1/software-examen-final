#include <gtest/gtest.h>
#include "../include/GradeCalculator.h"
#include "../include/Student.h"
#include "../include/ExtraPointsPolicy.h"

class GradeCalculatorTest : public ::testing::Test {
protected:
    GradeCalculator calculator;
    Student student;
    
    void SetUp() override {
        student = Student("U202012345");
    }
};

TEST_F(GradeCalculatorTest, CalculateFinalGradeWithNoEvaluations) {
    student.setHasReachedMinimumAttendance(true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, nullptr);
    
    EXPECT_DOUBLE_EQ(result.getWeightedAverage(), 0.0);
    EXPECT_DOUBLE_EQ(result.getFinalGrade(), 0.0);
}

TEST_F(GradeCalculatorTest, CalculateWeightedAverageCorrectly) {
    Evaluation eval1("PC1", 15.0, 20.0);
    Evaluation eval2("PC2", 16.0, 30.0);
    Evaluation eval3("Final", 18.0, 50.0);
    
    student.addEvaluation(eval1);
    student.addEvaluation(eval2);
    student.addEvaluation(eval3);
    student.setHasReachedMinimumAttendance(true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, nullptr);
    
    EXPECT_NEAR(result.getWeightedAverage(), 16.8, 0.01);
}

TEST_F(GradeCalculatorTest, ApplyPenaltyWhenNoAttendance) {
    Evaluation eval("PC1", 18.0, 100.0);
    student.addEvaluation(eval);
    student.setHasReachedMinimumAttendance(false);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, nullptr);
    
    EXPECT_TRUE(result.isPenaltyApplied());
    EXPECT_DOUBLE_EQ(result.getAfterPenalty(), 0.0);
    EXPECT_DOUBLE_EQ(result.getFinalGrade(), 0.0);
}

TEST_F(GradeCalculatorTest, NoPenaltyWhenHasAttendance) {
    Evaluation eval("PC1", 15.0, 100.0);
    student.addEvaluation(eval);
    student.setHasReachedMinimumAttendance(true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, nullptr);
    
    EXPECT_FALSE(result.isPenaltyApplied());
    EXPECT_DOUBLE_EQ(result.getAfterPenalty(), 15.0);
}

TEST_F(GradeCalculatorTest, ApplyExtraPointsWhenQualifies) {
    Evaluation eval("PC1", 12.0, 100.0);
    student.addEvaluation(eval);
    student.setHasReachedMinimumAttendance(true);
    
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, &policy);
    
    EXPECT_TRUE(result.areExtraPointsGranted());
    EXPECT_DOUBLE_EQ(result.getExtraPointsApplied(), 1.0);
    EXPECT_DOUBLE_EQ(result.getFinalGrade(), 13.0);
}

TEST_F(GradeCalculatorTest, NoExtraPointsWhenDoesNotQualify) {
    Evaluation eval("PC1", 9.0, 100.0);
    student.addEvaluation(eval);
    student.setHasReachedMinimumAttendance(true);
    
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, &policy);
    
    EXPECT_FALSE(result.areExtraPointsGranted());
    EXPECT_DOUBLE_EQ(result.getExtraPointsApplied(), 0.0);
    EXPECT_DOUBLE_EQ(result.getFinalGrade(), 9.0);
}

TEST_F(GradeCalculatorTest, FinalGradeNeverExceeds20) {
    Evaluation eval("PC1", 19.5, 100.0);
    student.addEvaluation(eval);
    student.setHasReachedMinimumAttendance(true);
    
    ExtraPointsPolicy policy("2025-1", true, 1.5, 10.5, true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, &policy);
    
    EXPECT_DOUBLE_EQ(result.getFinalGrade(), 20.0);
}

TEST_F(GradeCalculatorTest, HasPassedCourseWithPassingGrade) {
    bool passed = calculator.hasPassedCourse(10.5);
    
    EXPECT_TRUE(passed);
}

TEST_F(GradeCalculatorTest, HasNotPassedCourseWithFailingGrade) {
    bool passed = calculator.hasPassedCourse(10.4);
    
    EXPECT_FALSE(passed);
}

TEST_F(GradeCalculatorTest, CompleteCalculationScenario) {
    Evaluation eval1("PC1", 14.0, 20.0);
    Evaluation eval2("PC2", 15.0, 20.0);
    Evaluation eval3("Parcial", 16.0, 30.0);
    Evaluation eval4("Final", 17.0, 30.0);
    
    student.addEvaluation(eval1);
    student.addEvaluation(eval2);
    student.addEvaluation(eval3);
    student.addEvaluation(eval4);
    student.setHasReachedMinimumAttendance(true);
    
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    GradeCalculationResult result = calculator.calculateFinalGrade(student, &policy);
    
    EXPECT_NEAR(result.getWeightedAverage(), 15.7, 0.1);
    EXPECT_FALSE(result.isPenaltyApplied());
    EXPECT_TRUE(result.areExtraPointsGranted());
    EXPECT_NEAR(result.getFinalGrade(), 16.7, 0.1);
}
