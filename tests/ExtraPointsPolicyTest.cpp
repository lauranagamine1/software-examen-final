#include <gtest/gtest.h>
#include "../include/ExtraPointsPolicy.h"

class ExtraPointsPolicyTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(ExtraPointsPolicyTest, DefaultConstructorCreatesInactivePolicy) {
    ExtraPointsPolicy policy;
    
    EXPECT_EQ(policy.getAcademicYear(), "");
    EXPECT_FALSE(policy.getHasExtraPoints());
    EXPECT_DOUBLE_EQ(policy.getExtraPointsAmount(), 0.0);
    EXPECT_DOUBLE_EQ(policy.getMinimumGradeRequired(), 0.0);
    EXPECT_FALSE(policy.getRequiresMinimumAttendance());
}

TEST_F(ExtraPointsPolicyTest, ParameterizedConstructorSetsAllFields) {
    ExtraPointsPolicy policy("2025-1", true, 1.5, 10.5, true);
    
    EXPECT_EQ(policy.getAcademicYear(), "2025-1");
    EXPECT_TRUE(policy.getHasExtraPoints());
    EXPECT_DOUBLE_EQ(policy.getExtraPointsAmount(), 1.5);
    EXPECT_DOUBLE_EQ(policy.getMinimumGradeRequired(), 10.5);
    EXPECT_TRUE(policy.getRequiresMinimumAttendance());
}

TEST_F(ExtraPointsPolicyTest, StudentQualifiesWhenMeetsAllRequirements) {
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    bool qualifies = policy.studentQualifies(12.0, true);
    
    EXPECT_TRUE(qualifies);
}

TEST_F(ExtraPointsPolicyTest, StudentDoesNotQualifyWithLowGrade) {
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    bool qualifies = policy.studentQualifies(9.0, true);
    
    EXPECT_FALSE(qualifies);
}

TEST_F(ExtraPointsPolicyTest, StudentDoesNotQualifyWithoutAttendance) {
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    bool qualifies = policy.studentQualifies(12.0, false);
    
    EXPECT_FALSE(qualifies);
}

TEST_F(ExtraPointsPolicyTest, StudentDoesNotQualifyWhenPolicyInactive) {
    ExtraPointsPolicy policy("2024-2", false, 0.0, 0.0, false);
    
    bool qualifies = policy.studentQualifies(15.0, true);
    
    EXPECT_FALSE(qualifies);
}

TEST_F(ExtraPointsPolicyTest, StudentQualifiesWhenAttendanceNotRequired) {
    ExtraPointsPolicy policy("2025-2", true, 1.5, 11.0, false);
    
    bool qualifies = policy.studentQualifies(12.0, false);
    
    EXPECT_TRUE(qualifies);
}

TEST_F(ExtraPointsPolicyTest, StudentQualifiesWithExactMinimumGrade) {
    ExtraPointsPolicy policy("2025-1", true, 1.0, 10.5, true);
    
    bool qualifies = policy.studentQualifies(10.5, true);
    
    EXPECT_TRUE(qualifies);
}
