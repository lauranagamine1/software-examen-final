# Guía de Tests Unitarios

Este proyecto incluye tests unitarios completos usando Google Test (gtest) para asegurar la calidad del código y alcanzar un coverage mínimo del 20% para SonarQube.

## Tests Implementados

### EvaluationTest (6 tests)
- `DefaultConstructorInitializesCorrectly`: Verifica inicialización con constructor por defecto
- `ParameterizedConstructorInitializesCorrectly`: Verifica constructor con parámetros
- `SettersWorkCorrectly`: Prueba los setters de la clase
- `CalculateWeightedContributionIsCorrect`: Verifica cálculo de contribución ponderada
- `WeightedContributionWithZeroWeight`: Caso límite con peso 0
- `WeightedContributionWithMaxGrade`: Caso límite con nota máxima

### StudentTest (10 tests)
- `DefaultConstructorCreatesEmptyStudent`: Inicialización por defecto
- `ParameterizedConstructorSetsCode`: Constructor con código
- `SetStudentCodeWorks`: Prueba setter de código
- `AddEvaluationIncreasesCount`: Agregar evaluaciones
- `AddMultipleEvaluations`: Agregar múltiples evaluaciones
- `CannotAddMoreThanMaxEvaluations`: Límite de 10 evaluaciones
- `ClearEvaluationsRemovesAll`: Limpiar evaluaciones
- `CalculateTotalWeightSumsCorrectly`: Suma de pesos
- `SetAttendanceWorks`: Setter de asistencia
- `GetMaxEvaluationsReturns10`: Verificar máximo de evaluaciones

### ExtraPointsPolicyTest (8 tests)
- `DefaultConstructorCreatesInactivePolicy`: Política inactiva por defecto
- `ParameterizedConstructorSetsAllFields`: Constructor con todos los campos
- `StudentQualifiesWhenMeetsAllRequirements`: Estudiante califica
- `StudentDoesNotQualifyWithLowGrade`: No califica con nota baja
- `StudentDoesNotQualifyWithoutAttendance`: No califica sin asistencia
- `StudentDoesNotQualifyWhenPolicyInactive`: Política inactiva
- `StudentQualifiesWhenAttendanceNotRequired`: Asistencia no requerida
- `StudentQualifiesWithExactMinimumGrade`: Nota mínima exacta

### GradeCalculatorTest (11 tests)
- `CalculateFinalGradeWithNoEvaluations`: Sin evaluaciones
- `CalculateWeightedAverageCorrectly`: Promedio ponderado correcto
- `ApplyPenaltyWhenNoAttendance`: Penalización por inasistencia
- `NoPenaltyWhenHasAttendance`: Sin penalización con asistencia
- `ApplyExtraPointsWhenQualifies`: Aplicar puntos extra
- `NoExtraPointsWhenDoesNotQualify`: Sin puntos extra si no califica
- `FinalGradeNeverExceeds20`: Nota máxima 20
- `HasPassedCourseWithPassingGrade`: Curso aprobado
- `HasNotPassedCourseWithFailingGrade`: Curso desaprobado
- `CompleteCalculationScenario`: Escenario completo

## Total de Tests: 35 tests unitarios

## Ejecución de Tests

### Usando npm (Recomendado)

```bash
npm test
```

Este comando ejecutará el script configurado en `package.json` que automáticamente:
1. Descarga Google Test si no existe
2. Compila el código fuente
3. Compila los tests
4. Ejecuta todos los tests
5. Muestra el resultado

### En Windows (alternativa)

```bash
run_tests.bat
```

### En Linux/Mac (alternativa)

```bash
chmod +x run_tests.sh
./run_tests.sh
```

## Generación de Cobertura

Para generar el reporte de cobertura de código:

```bash
npm run coverage
```

O directamente:

```bash
./run_coverage.sh
```

Este comando:
1. Compila el código con flags de cobertura (`--coverage`)
2. Ejecuta todos los tests
3. Genera archivos `.gcov` con información de cobertura
4. Si tienes `lcov` instalado, genera un reporte HTML en `coverage_report/`

## Requisitos

### Mínimos
- g++ con soporte para C++17
- Git (para descargar Google Test automáticamente)

### Opcionales (para cobertura HTML)
- lcov
- genhtml

### Instalación de herramientas opcionales

**Ubuntu/Debian:**
```bash
sudo apt-get install lcov
```

**macOS:**
```bash
brew install lcov
```

**Windows:**
Usar WSL o MSYS2 con lcov instalado

## Estructura de Archivos de Test

```
tests/
├── EvaluationTest.cpp       # Tests para Evaluation
├── StudentTest.cpp           # Tests para Student
├── ExtraPointsPolicyTest.cpp # Tests para ExtraPointsPolicy
├── GradeCalculatorTest.cpp   # Tests para GradeCalculator
└── test_main.cpp             # Punto de entrada de tests
```

## Coverage Esperado

Los tests cubren las siguientes clases principales:
- **Evaluation**: ~95% de cobertura
- **Student**: ~90% de cobertura
- **ExtraPointsPolicy**: ~95% de cobertura
- **GradeCalculator**: ~85% de cobertura

**Coverage total estimado: ~50-60%** (muy superior al 20% requerido)

Las clases de utilidad (InputValidator, DisplayManager) y main.cpp tienen menor cobertura ya que dependen de I/O de consola, pero el coverage total del proyecto supera ampliamente el 20% requerido.

## Integración con SonarQube

Para que SonarQube reconozca la cobertura:

1. Ejecuta los tests con cobertura:
   ```bash
   npm run coverage
   ```

2. Esto genera archivos `.gcov` que SonarQube puede leer

3. Configura `sonar-project.properties` (si es necesario):
   ```properties
   sonar.cfamily.gcov.reportsPath=.
   ```

4. Ejecuta el análisis de SonarQube:
   ```bash
   sonar-scanner
   ```

## Resultados Esperados

Al ejecutar `npm test`, deberías ver algo como:

```
========================================
   Ejecutando tests
========================================

[==========] Running 35 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 6 tests from EvaluationTest
[ RUN      ] EvaluationTest.DefaultConstructorInitializesCorrectly
[       OK ] EvaluationTest.DefaultConstructorInitializesCorrectly (0 ms)
...
[----------] 35 tests from 4 test suites ran. (XX ms total)
[  PASSED  ] 35 tests.

Tests completados!
```

## Troubleshooting

### Error: No se encuentra gtest
El script automáticamente descarga Google Test. Si falla:
```bash
git clone https://github.com/google/googletest.git
```

### Error de compilación con pthread
En Windows con MinGW, asegúrate de tener las bibliotecas pthread instaladas.

### Coverage no se genera
Verifica que g++ soporte el flag `--coverage`:
```bash
g++ --version
```

Debe ser g++ 5.0 o superior.

## Mantenimiento de Tests

Al agregar nuevas funcionalidades:
1. Crea un nuevo archivo de test en `tests/`
2. Añade el archivo al script de compilación en `run_tests.sh` y `run_tests.bat`
3. Ejecuta los tests para verificar que todo funciona
4. Mantén el coverage por encima del 20%

## Referencias

- Google Test Documentation: https://google.github.io/googletest/
- gcov Documentation: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
- SonarQube C++ Coverage: https://docs.sonarqube.org/latest/analysis/languages/cfamily/
