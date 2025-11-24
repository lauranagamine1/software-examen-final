#include "../include/PolicyManager.h"

PolicyManager::PolicyManager() {
    initializeDefaultPolicies();
}

void PolicyManager::initializeDefaultPolicies() {
    ExtraPointsPolicy policy2025_1("2025-1", true, 1.0, 10.5, true);
    ExtraPointsPolicy policy2025_2("2025-2", true, 1.5, 11.0, true);
    ExtraPointsPolicy policy2024_2("2024-2", false, 0.0, 0.0, false);
    
    policies.push_back(policy2025_1);
    policies.push_back(policy2025_2);
    policies.push_back(policy2024_2);
}

void PolicyManager::addPolicy(const ExtraPointsPolicy& policy) {
    policies.push_back(policy);
}

const ExtraPointsPolicy* PolicyManager::findPolicyByYear(const std::string& year) const {
    for (const auto& policy : policies) {
        if (policy.getAcademicYear() == year) {
            return &policy;
        }
    }
    return nullptr;
}

bool PolicyManager::hasPolicyForYear(const std::string& year) const {
    return findPolicyByYear(year) != nullptr;
}

const std::vector<ExtraPointsPolicy>& PolicyManager::getAllPolicies() const {
    return policies;
}
