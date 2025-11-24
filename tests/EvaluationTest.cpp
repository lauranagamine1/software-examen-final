#include <gtest/gtest.h>
#include "../include/Evaluation.h"

class EvaluationTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(EvaluationTest, DefaultConstructorInitializesCorrectly) {
    Evaluation eval;
    
    EXPECT_EQ(eval.getName(), "");
    EXPECT_DOUBLE_EQ(eval.getGrade(), 0.0);
    EXPECT_DOUBLE_EQ(eval.getWeightPercent(), 0.0);
}

TEST_F(EvaluationTest, ParameterizedConstructorInitializesCorrectly) {
    Evaluation eval("PC1", 15.5, 20.0);
    
    EXPECT_EQ(eval.getName(), "PC1");
    EXPECT_DOUBLE_EQ(eval.getGrade(), 15.5);
    EXPECT_DOUBLE_EQ(eval.getWeightPercent(), 20.0);
}

TEST_F(EvaluationTest, SettersWorkCorrectly) {
    Evaluation eval;
    
    eval.setName("Parcial");
    eval.setGrade(18.0);
    eval.setWeightPercent(30.0);
    
    EXPECT_EQ(eval.getName(), "Parcial");
    EXPECT_DOUBLE_EQ(eval.getGrade(), 18.0);
    EXPECT_DOUBLE_EQ(eval.getWeightPercent(), 30.0);
}

TEST_F(EvaluationTest, CalculateWeightedContributionIsCorrect) {
    Evaluation eval("PC1", 15.0, 20.0);
    
    double contribution = eval.calculateWeightedContribution();
    
    EXPECT_DOUBLE_EQ(contribution, 3.0);
}

TEST_F(EvaluationTest, WeightedContributionWithZeroWeight) {
    Evaluation eval("PC1", 15.0, 0.0);
    
    double contribution = eval.calculateWeightedContribution();
    
    EXPECT_DOUBLE_EQ(contribution, 0.0);
}

TEST_F(EvaluationTest, WeightedContributionWithMaxGrade) {
    Evaluation eval("Final", 20.0, 50.0);
    
    double contribution = eval.calculateWeightedContribution();
    
    EXPECT_DOUBLE_EQ(contribution, 10.0);
}
