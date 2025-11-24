# Sistema de Cálculo de Notas Finales - UTEC

Sistema implementado en C++ para calcular la nota final de estudiantes considerando evaluaciones ponderadas, asistencia mínima y políticas de puntos extra.

## Descripción

Este programa permite a los docentes de Ingeniería de Software en UTEC:
- Registrar hasta 10 evaluaciones por estudiante con sus respectivas notas y pesos
- Verificar el cumplimiento de asistencia mínima
- Aplicar políticas de puntos extra según el año académico
- Calcular automáticamente la nota final con detalle completo del cálculo

## Requerimientos Funcionales Implementados

- **RF1**: Registro de estudiante por código
- **RF2**: Registro/Revisión de hasta 10 evaluaciones con validación de pesos
- **RF3**: Registro de asistencia mínima (hasReachedMinimumClasses)
- **RF4**: Consulta de política de puntos extra por año académico (allYearsTeachers)
- **RF5**: Cálculo de nota final considerando:
  - Promedio ponderado de evaluaciones
  - Penalización por inasistencias (nota = 0 si no cumple asistencia)
  - Aplicación de puntos extra según política vigente
- **RF6**: Visualización detallada del cálculo paso a paso

## Requerimientos No Funcionales Implementados

- **RNF1**: Límite de 10 evaluaciones por estudiante usando `vector` con capacidad reservada
- **RNF2**: Diseño sin variables globales compartidas, preparado para hasta 50 usuarios concurrentes
- **RNF3**: Código modular y bien organizado con funciones específicas para cada tarea

## Estructura del Código

### Estructuras de Datos
- `Evaluation`: Representa una evaluación individual (nombre, nota, peso)
- `ExamsStudents`: Almacena las evaluaciones y asistencia de un estudiante
- `ExtraPointsPolicy`: Define políticas de puntos extra por año académico
- `AllYearsTeachers`: Colección de políticas para diferentes años

### Funciones Principales
- `registerEvaluations()`: Registro de evaluaciones con validación
- `registerAttendance()`: Registro de asistencia mínima
- `calculateWeightedAverage()`: Cálculo del promedio ponderado
- `applyAttendancePenalty()`: Aplicación de penalización por inasistencias
- `qualifiesForExtraPoints()`: Verificación de elegibilidad para puntos extra
- `calculateFinalGrade()`: Cálculo completo de nota final
- `displayGradeCalculationDetail()`: Visualización detallada del cálculo

## Compilación y Ejecución

### En Windows:
```bash
# Compilar
compile.bat

# O manualmente:
g++ -std=c++17 -Wall -o calculo_notas.exe main.cpp

# Ejecutar
calculo_notas.exe
```

### En Linux/Mac:
```bash
# Dar permisos de ejecución al script
chmod +x compile.sh

# Compilar
./compile.sh

# O manualmente:
g++ -std=c++17 -Wall -o calculo_notas main.cpp

# Ejecutar
./calculo_notas
```

## Uso del Programa

1. **Inicio**: El programa solicita el código del estudiante
2. **Evaluaciones**: Registra cada evaluación con:
   - Nombre (PC1, Parcial, Final, etc.)
   - Nota obtenida (0-20)
   - Peso porcentual (0-100%)
3. **Asistencia**: Indica si cumplió con la asistencia mínima (S/N)
4. **Año Académico**: Ingresa el año académico para consultar política de puntos extra (ej: 2025-1)
5. **Resultado**: El sistema calcula y muestra:
   - Promedio ponderado
   - Penalizaciones aplicadas
   - Puntos extra otorgados
   - Nota final con detalle completo

## Ejemplo de Uso

```
Código de estudiante: U202012345

Evaluaciones:
- PC1: 15.0 (20%)
- PC2: 14.0 (20%)
- Parcial: 16.0 (30%)
- Final: 17.0 (30%)

Asistencia mínima: SÍ
Año académico: 2025-1

RESULTADO:
Promedio ponderado: 15.60
Penalización: Ninguna
Puntos extra: +1.0 (cumple requisitos)
NOTA FINAL: 16.60 - APROBADO
```

## Políticas de Puntos Extra Predefinidas

### 2025-1
- Puntos extra: 1.0
- Nota mínima: 10.5
- Requiere asistencia: SÍ

### 2025-2
- Puntos extra: 1.5
- Nota mínima: 11.0
- Requiere asistencia: SÍ

### 2024-2
- Sin puntos extra disponibles

## Reglas Importantes

1. **Asistencia Mínima**: Si el estudiante NO alcanza la asistencia mínima (70%), su nota final será 0 automáticamente, sin importar sus calificaciones.

2. **Puntos Extra**: Solo se otorgan si el estudiante:
   - Alcanza la nota mínima requerida
   - Cumple con la asistencia mínima (si es requerida por la política)

3. **Nota Máxima**: La nota final no puede exceder 20 puntos, incluso con puntos extra.

4. **Aprobación**: Se requiere una nota final de al menos 10.5 para aprobar el curso.

## Validaciones Implementadas

- Notas en rango válido (0-20)
- Pesos porcentuales válidos (0-100%)
- Máximo 10 evaluaciones por estudiante
- Advertencia si los pesos no suman exactamente 100%
- Validación de entradas de usuario con manejo de errores

## Diseño para Concurrencia

El código está diseñado sin variables globales compartidas y con lógica independiente, permitiendo:
- Múltiples instancias del programa ejecutándose simultáneamente
- Preparación para implementación multi-hilo en el futuro
- Soporte para hasta 50 usuarios concurrentes según RNF2


## Notas Técnicas

- Los cálculos usan precisión de punto flotante con formato de 2 decimales

