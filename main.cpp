#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================================
// ESTRUCTURAS Y CLASES
// ============================================================================

/**
 * Estructura que representa una evaluación individual
 */
struct Evaluation {
    string name;           // Nombre de la evaluación (PC1, Parcial, etc.)
    double grade;          // Nota obtenida (0-20)
    double weightPercent;  // Peso porcentual (0-100)

    Evaluation() : name(""), grade(0.0), weightPercent(0.0) {}

    Evaluation(const string& n, double g, double w)
        : name(n), grade(g), weightPercent(w) {}
};

/**
 * Estructura que almacena las evaluaciones de un estudiante
 * Máximo 10 evaluaciones según RNF1
 */
struct ExamsStudents {
    string studentCode;                    // Código del estudiante
    vector<Evaluation> evaluations;        // Lista de evaluaciones (max 10)
    bool hasReachedMinimumClasses;         // Si cumplió con asistencia mínima

    ExamsStudents() : studentCode(""), hasReachedMinimumClasses(false) {
        evaluations.reserve(10);  // Reservar espacio para máximo 10 evaluaciones
    }
};

/**
 * Estructura que representa la política de puntos extra por año académico
 */
struct ExtraPointsPolicy {
    string academicYear;           // Año académico (ej: "2025-1", "2025-2")
    bool hasExtraPoints;           // Si hay puntos extra disponibles
    double extraPointsAmount;      // Cantidad de puntos extra a otorgar
    double minimumGradeRequired;   // Nota mínima requerida para puntos extra
    bool requiresMinimumAttendance; // Si requiere asistencia mínima

    ExtraPointsPolicy()
        : academicYear(""), hasExtraPoints(false), extraPointsAmount(0.0),
          minimumGradeRequired(0.0), requiresMinimumAttendance(false) {}

    ExtraPointsPolicy(const string& year, bool hasExtra, double amount,
                     double minGrade, bool requiresAttendance)
        : academicYear(year), hasExtraPoints(hasExtra),
          extraPointsAmount(amount), minimumGradeRequired(minGrade),
          requiresMinimumAttendance(requiresAttendance) {}
};

/**
 * Colección de políticas de puntos extra por diferentes años
 */
struct AllYearsTeachers {
    vector<ExtraPointsPolicy> policies;

    // Buscar política para un año académico específico
    ExtraPointsPolicy* findPolicy(const string& year) {
        for (auto& policy : policies) {
            if (policy.academicYear == year) {
                return &policy;
            }
        }
        return nullptr;
    }

    // Agregar una nueva política
    void addPolicy(const ExtraPointsPolicy& policy) {
        policies.push_back(policy);
    }
};

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

/**
 * Limpia el buffer de entrada
 */
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Valida que un número esté en un rango específico
 */
bool isInRange(double value, double min, double max) {
    return value >= min && value <= max;
}

// ============================================================================
// RF2 - REGISTRO Y GESTIÓN DE EVALUACIONES
// ============================================================================

/**
 * Registra las evaluaciones de un estudiante
 * Cumple con RF2: Registro de hasta 10 evaluaciones
 */
void registerEvaluations(ExamsStudents& student) {
    int numEvaluations;

    cout << "\n=== REGISTRO DE EVALUACIONES ===\n";
    cout << "¿Cuántas evaluaciones desea registrar? (máximo 10): ";

    while (!(cin >> numEvaluations) || numEvaluations < 1 || numEvaluations > 10) {
        cout << "Error: Ingrese un número válido entre 1 y 10: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    student.evaluations.clear();
    double totalWeight = 0.0;

    for (int i = 0; i < numEvaluations; i++) {
        cout << "\n--- Evaluación " << (i + 1) << " ---\n";

        Evaluation eval;

        // Nombre de la evaluación
        cout << "Nombre de la evaluación: ";
        getline(cin, eval.name);

        // Nota obtenida
        cout << "Nota obtenida (0-20): ";
        while (!(cin >> eval.grade) || !isInRange(eval.grade, 0.0, 20.0)) {
            cout << "Error: Ingrese una nota válida entre 0 y 20: ";
            clearInputBuffer();
        }

        // Peso porcentual
        cout << "Peso porcentual (0-100): ";
        while (!(cin >> eval.weightPercent) || !isInRange(eval.weightPercent, 0.0, 100.0)) {
            cout << "Error: Ingrese un peso válido entre 0 y 100: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        totalWeight += eval.weightPercent;
        student.evaluations.push_back(eval);
    }

    // Validación opcional: verificar que los pesos sumen 100%
    cout << "\nPeso total de evaluaciones: " << fixed << setprecision(2)
         << totalWeight << "%\n";

    if (abs(totalWeight - 100.0) > 0.01) {
        cout << "ADVERTENCIA: Los pesos no suman exactamente 100%.\n";
        cout << "El cálculo se realizará con los pesos ingresados.\n";
    }
}

/**
 * Muestra las evaluaciones registradas
 */
void displayEvaluations(const ExamsStudents& student) {
    cout << "\n=== EVALUACIONES REGISTRADAS ===\n";
    cout << left << setw(20) << "Evaluación"
         << right << setw(10) << "Nota"
         << setw(12) << "Peso (%)" << "\n";
    cout << string(42, '-') << "\n";

    for (const auto& eval : student.evaluations) {
        cout << left << setw(20) << eval.name
             << right << setw(10) << fixed << setprecision(2) << eval.grade
             << setw(12) << fixed << setprecision(2) << eval.weightPercent << "\n";
    }
}

// ============================================================================
// RF3 - REGISTRO DE ASISTENCIA MÍNIMA
// ============================================================================

/**
 * Registra si el estudiante alcanzó la asistencia mínima
 * Cumple con RF3
 */
void registerAttendance(ExamsStudents& student) {
    char response;

    cout << "\n=== REGISTRO DE ASISTENCIA ===\n";
    cout << "¿El estudiante alcanzó la asistencia mínima requerida? (S/N): ";

    while (!(cin >> response) || (toupper(response) != 'S' && toupper(response) != 'N')) {
        cout << "Error: Ingrese 'S' para Sí o 'N' para No: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    student.hasReachedMinimumClasses = (toupper(response) == 'S');

    cout << "Asistencia registrada: "
         << (student.hasReachedMinimumClasses ? "CUMPLE" : "NO CUMPLE") << "\n";
}

// ============================================================================
// RF4 - POLÍTICA DE PUNTOS EXTRA
// ============================================================================

/**
 * Inicializa las políticas de puntos extra para diferentes años
 * Cumple con RF4
 */
void initializeExtraPointsPolicies(AllYearsTeachers& allYears) {
    // Política para 2025-1
    ExtraPointsPolicy policy2025_1(
        "2025-1",    // Año académico
        true,        // Tiene puntos extra
        1.0,         // 1 punto extra
        10.5,        // Requiere nota mínima de 10.5
        true         // Requiere asistencia mínima
    );

    // Política para 2025-2
    ExtraPointsPolicy policy2025_2(
        "2025-2",
        true,
        1.5,
        11.0,
        true
    );

    // Política para 2024-2 (sin puntos extra)
    ExtraPointsPolicy policy2024_2(
        "2024-2",
        false,
        0.0,
        0.0,
        false
    );

    allYears.addPolicy(policy2025_1);
    allYears.addPolicy(policy2025_2);
    allYears.addPolicy(policy2024_2);
}

/**
 * Muestra la política de puntos extra para un año académico
 */
void displayExtraPointsPolicy(const ExtraPointsPolicy* policy) {
    cout << "\n=== POLÍTICA DE PUNTOS EXTRA ===\n";

    if (policy == nullptr) {
        cout << "No se encontró política para este año académico.\n";
        return;
    }

    cout << "Año académico: " << policy->academicYear << "\n";
    cout << "¿Hay puntos extra?: " << (policy->hasExtraPoints ? "SÍ" : "NO") << "\n";

    if (policy->hasExtraPoints) {
        cout << "Puntos extra disponibles: " << fixed << setprecision(2)
             << policy->extraPointsAmount << "\n";
        cout << "Nota mínima requerida: " << fixed << setprecision(2)
             << policy->minimumGradeRequired << "\n";
        cout << "Requiere asistencia mínima: "
             << (policy->requiresMinimumAttendance ? "SÍ" : "NO") << "\n";
    }
}

// ============================================================================
// RF5 - CÁLCULO DE NOTA FINAL
// ============================================================================

/**
 * Calcula el promedio ponderado de las evaluaciones
 */
double calculateWeightedAverage(const ExamsStudents& student) {
    if (student.evaluations.empty()) {
        return 0.0;
    }

    double weightedSum = 0.0;
    double totalWeight = 0.0;

    for (const auto& eval : student.evaluations) {
        weightedSum += eval.grade * (eval.weightPercent / 100.0);
        totalWeight += eval.weightPercent;
    }

    // Si los pesos no suman 100%, normalizar
    if (totalWeight > 0.0) {
        return (weightedSum / totalWeight) * 100.0;
    }

    return 0.0;
}

/**
 * Aplica la penalización por inasistencias
 * Si no cumple con asistencia mínima, la nota final es 0
 */
double applyAttendancePenalty(double baseGrade, bool hasMinimumAttendance) {
    if (!hasMinimumAttendance) {
        return 0.0;  // Penalización total: desaprobado automático
    }
    return baseGrade;
}

/**
 * Determina si el estudiante califica para puntos extra
 */
bool qualifiesForExtraPoints(double currentGrade, bool hasMinimumAttendance,
                            const ExtraPointsPolicy* policy) {
    if (policy == nullptr || !policy->hasExtraPoints) {
        return false;
    }

    // Verificar si cumple con la nota mínima
    if (currentGrade < policy->minimumGradeRequired) {
        return false;
    }

    // Verificar si cumple con asistencia mínima (si es requerida)
    if (policy->requiresMinimumAttendance && !hasMinimumAttendance) {
        return false;
    }

    return true;
}

/**
 * Calcula la nota final del estudiante
 * Cumple con RF5: Considera promedio ponderado, penalización y puntos extra
 */
struct GradeCalculationResult {
    double weightedAverage;
    double afterPenalty;
    double extraPointsApplied;
    double finalGrade;
    bool penaltyApplied;
    bool extraPointsGranted;
    string penaltyReason;
    string extraPointsReason;
};

GradeCalculationResult calculateFinalGrade(const ExamsStudents& student,
                                          const ExtraPointsPolicy* policy) {
    GradeCalculationResult result;

    // 1. Calcular promedio ponderado
    result.weightedAverage = calculateWeightedAverage(student);

    // 2. Aplicar penalización por asistencia
    result.afterPenalty = applyAttendancePenalty(
        result.weightedAverage,
        student.hasReachedMinimumClasses
    );

    result.penaltyApplied = !student.hasReachedMinimumClasses;
    if (result.penaltyApplied) {
        result.penaltyReason = "No alcanzó la asistencia mínima requerida (70%)";
    }

    // 3. Aplicar puntos extra si califica
    result.extraPointsApplied = 0.0;
    result.extraPointsGranted = false;

    if (qualifiesForExtraPoints(result.afterPenalty,
                               student.hasReachedMinimumClasses,
                               policy)) {
        result.extraPointsApplied = policy->extraPointsAmount;
        result.extraPointsGranted = true;
        result.extraPointsReason = "Cumplió con nota mínima (" +
                                  to_string(policy->minimumGradeRequired) +
                                  ") y asistencia requerida";
    }

    // 4. Calcular nota final (máximo 20)
    result.finalGrade = min(20.0, result.afterPenalty + result.extraPointsApplied);

    return result;
}

// ============================================================================
// RF6 - VISUALIZACIÓN DEL DETALLE DE CÁLCULO
// ============================================================================

/**
 * Muestra el detalle completo del cálculo de la nota final
 * Cumple con RF6
 */
void displayGradeCalculationDetail(const ExamsStudents& student,
                                   const GradeCalculationResult& result,
                                   const ExtraPointsPolicy* policy) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "       DETALLE DE CÁLCULO DE NOTA FINAL\n";
    cout << string(60, '=') << "\n\n";

    cout << "Estudiante: " << student.studentCode << "\n\n";

    // Mostrar evaluaciones
    displayEvaluations(student);

    cout << "\n--- CÁLCULO PASO A PASO ---\n\n";

    // Paso 1: Promedio ponderado
    cout << "1. PROMEDIO PONDERADO DE EVALUACIONES:\n";
    for (const auto& eval : student.evaluations) {
        double contribution = eval.grade * (eval.weightPercent / 100.0);
        cout << "   " << left << setw(20) << eval.name
             << ": " << fixed << setprecision(2) << eval.grade
             << " × " << eval.weightPercent << "% = "
             << contribution << "\n";
    }
    cout << "   " << string(50, '-') << "\n";
    cout << "   Promedio ponderado: " << fixed << setprecision(2)
         << result.weightedAverage << "\n\n";

    // Paso 2: Penalización por asistencia
    cout << "2. VERIFICACIÓN DE ASISTENCIA:\n";
    cout << "   Asistencia mínima alcanzada: "
         << (student.hasReachedMinimumClasses ? "SÍ" : "NO") << "\n";

    if (result.penaltyApplied) {
        cout << "   PENALIZACIÓN APLICADA: Nota = 0.00\n";
        cout << "   Razón: " << result.penaltyReason << "\n";
    } else {
        cout << "   Sin penalización aplicada\n";
    }
    cout << "   Nota después de penalización: " << fixed << setprecision(2)
         << result.afterPenalty << "\n\n";

    // Paso 3: Puntos extra
    cout << "3. APLICACIÓN DE PUNTOS EXTRA:\n";
    if (policy != nullptr && policy->hasExtraPoints) {
        cout << "   Política del año " << policy->academicYear << ":\n";
        cout << "   - Puntos disponibles: " << fixed << setprecision(2)
             << policy->extraPointsAmount << "\n";
        cout << "   - Nota mínima requerida: " << fixed << setprecision(2)
             << policy->minimumGradeRequired << "\n";
        cout << "   - Requiere asistencia: "
             << (policy->requiresMinimumAttendance ? "SÍ" : "NO") << "\n\n";

        if (result.extraPointsGranted) {
            cout << "   PUNTOS EXTRA OTORGADOS: +" << fixed << setprecision(2)
                 << result.extraPointsApplied << "\n";
            cout << "   Razón: " << result.extraPointsReason << "\n";
        } else {
            cout << "   No califica para puntos extra\n";
            if (result.afterPenalty < policy->minimumGradeRequired) {
                cout << "   Razón: Nota insuficiente (requiere al menos "
                     << fixed << setprecision(2) << policy->minimumGradeRequired
                     << ")\n";
            }
        }
    } else {
        cout << "   No hay política de puntos extra para este año\n";
    }

    cout << "\n" << string(60, '=') << "\n";
    cout << "NOTA FINAL: " << fixed << setprecision(2) << result.finalGrade;

    // Indicar si aprobó o desaprobó
    if (result.finalGrade >= 10.5) {
        cout << " - APROBADO\n";
    } else {
        cout << " - DESAPROBADO\n";
    }
    cout << string(60, '=') << "\n";
}

// ============================================================================
// FUNCIÓN PRINCIPAL Y FLUJO DEL PROGRAMA
// ============================================================================

/**
 * Flujo principal del programa
 * Implementa el caso de uso descrito en los requerimientos
 */
int main() {
    // Inicializar políticas de puntos extra
    AllYearsTeachers allYears;
    initializeExtraPointsPolicies(allYears);

    cout << "========================================\n";
    cout << "   SISTEMA DE CÁLCULO DE NOTAS FINALES\n";
    cout << "   INGENIERÍA DE SOFTWARE - UTEC\n";
    cout << "========================================\n\n";

    bool continueProgram = true;

    while (continueProgram) {
        // Crear estructura para el estudiante
        ExamsStudents student;

        // RF1: Registro de estudiante
        cout << "\n--- IDENTIFICACIÓN DEL ESTUDIANTE ---\n";
        cout << "Ingrese el código del estudiante: ";
        getline(cin, student.studentCode);

        // RF2: Registro de evaluaciones
        registerEvaluations(student);

        // RF3: Registro de asistencia mínima
        registerAttendance(student);

        // RF4: Consulta de política de puntos extra
        string academicYear;
        cout << "\n--- CONSULTA DE POLÍTICA DE PUNTOS EXTRA ---\n";
        cout << "Ingrese el año académico (ej: 2025-1, 2025-2): ";
        getline(cin, academicYear);

        ExtraPointsPolicy* policy = allYears.findPolicy(academicYear);
        displayExtraPointsPolicy(policy);

        // RF5: Cálculo de nota final
        cout << "\n\nCalculando nota final...\n";
        GradeCalculationResult result = calculateFinalGrade(student, policy);

        // RF6: Visualización del detalle de cálculo
        displayGradeCalculationDetail(student, result, policy);

        // Preguntar si desea calcular otra nota
        cout << "\n¿Desea calcular la nota de otro estudiante? (S/N): ";
        char response;
        cin >> response;
        clearInputBuffer();

        continueProgram = (toupper(response) == 'S');
    }

    cout << "\n¡Gracias por usar el sistema de cálculo de notas!\n";
    cout << "Hasta pronto.\n\n";

    return 0;
}
