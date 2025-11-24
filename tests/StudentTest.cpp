#include <gtest/gtest.h>
#include "../include/Student.h"

class StudentTest : public ::testing::Test {
protected:
    Student student;
    
    void SetUp() override {
        student = Student("U202012345");
    }
};

TEST_F(StudentTest, DefaultConstructorCreatesEmptyStudent) {
    Student emptyStudent;
    
    EXPECT_EQ(emptyStudent.getStudentCode(), "");
    EXPECT_EQ(emptyStudent.getEvaluationCount(), 0);
    EXPECT_FALSE(emptyStudent.getHasReachedMinimumAttendance());
}

TEST_F(StudentTest, ParameterizedConstructorSetsCode) {
    EXPECT_EQ(student.getStudentCode(), "U202012345");
}

TEST_F(StudentTest, SetStudentCodeWorks) {
    student.setStudentCode("U202099999");
    
    EXPECT_EQ(student.getStudentCode(), "U202099999");
}

TEST_F(StudentTest, AddEvaluationIncreasesCount) {
    Evaluation eval("PC1", 15.0, 20.0);
    
    bool added = student.addEvaluation(eval);
    
    EXPECT_TRUE(added);
    EXPECT_EQ(student.getEvaluationCount(), 1);
}

TEST_F(StudentTest, AddMultipleEvaluations) {
    Evaluation eval1("PC1", 15.0, 20.0);
    Evaluation eval2("PC2", 16.0, 20.0);
    Evaluation eval3("Parcial", 17.0, 30.0);
    
    student.addEvaluation(eval1);
    student.addEvaluation(eval2);
    student.addEvaluation(eval3);
    
    EXPECT_EQ(student.getEvaluationCount(), 3);
}

TEST_F(StudentTest, CannotAddMoreThanMaxEvaluations) {
    for (int i = 0; i < 10; i++) {
        Evaluation eval("Eval" + std::to_string(i), 15.0, 10.0);
        student.addEvaluation(eval);
    }
    
    EXPECT_TRUE(student.hasReachedMaxEvaluations());
    
    Evaluation extraEval("Extra", 15.0, 10.0);
    bool added = student.addEvaluation(extraEval);
    
    EXPECT_FALSE(added);
    EXPECT_EQ(student.getEvaluationCount(), 10);
}

TEST_F(StudentTest, ClearEvaluationsRemovesAll) {
    Evaluation eval1("PC1", 15.0, 20.0);
    Evaluation eval2("PC2", 16.0, 20.0);
    
    student.addEvaluation(eval1);
    student.addEvaluation(eval2);
    student.clearEvaluations();
    
    EXPECT_EQ(student.getEvaluationCount(), 0);
}

TEST_F(StudentTest, CalculateTotalWeightSumsCorrectly) {
    Evaluation eval1("PC1", 15.0, 20.0);
    Evaluation eval2("PC2", 16.0, 30.0);
    Evaluation eval3("Final", 18.0, 50.0);
    
    student.addEvaluation(eval1);
    student.addEvaluation(eval2);
    student.addEvaluation(eval3);
    
    double totalWeight = student.calculateTotalWeight();
    
    EXPECT_DOUBLE_EQ(totalWeight, 100.0);
}

TEST_F(StudentTest, SetAttendanceWorks) {
    student.setHasReachedMinimumAttendance(true);
    
    EXPECT_TRUE(student.getHasReachedMinimumAttendance());
    
    student.setHasReachedMinimumAttendance(false);
    
    EXPECT_FALSE(student.getHasReachedMinimumAttendance());
}

TEST_F(StudentTest, GetMaxEvaluationsReturns10) {
    EXPECT_EQ(student.getMaxEvaluations(), 10);
}
