#ifndef POLICYMANAGER_H
#define POLICYMANAGER_H

#include <vector>
#include <string>
#include "ExtraPointsPolicy.h"

/**
 * Gestiona el conjunto de políticas de puntos extra para diferentes años académicos.
 * Responsabilidad: Almacenar y buscar políticas según el año académico.
 * Alta cohesión: Solo gestiona operaciones relacionadas con políticas.
 * Bajo acoplamiento: Depende únicamente de ExtraPointsPolicy.
 */
class PolicyManager {
private:
    std::vector<ExtraPointsPolicy> policies;
    
    void initializeDefaultPolicies();

public:
    PolicyManager();
    
    // Agrega una nueva política a la colección
    void addPolicy(const ExtraPointsPolicy& policy);
    
    // Busca y retorna una política según el año académico
    // Retorna nullptr si no se encuentra la política
    const ExtraPointsPolicy* findPolicyByYear(const std::string& year) const;
    
    // Verifica si existe una política para un año específico
    bool hasPolicyForYear(const std::string& year) const;
    
    // Obtiene todas las políticas disponibles
    const std::vector<ExtraPointsPolicy>& getAllPolicies() const;
};

#endif
