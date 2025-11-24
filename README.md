# Sistema de Cálculo de Notas Finales - UTEC

Sistema implementado en C++ usando programación orientada a objetos para calcular la nota final de estudiantes considerando evaluaciones ponderadas, asistencia mínima y políticas de puntos extra.

## Descripción

Este programa permite a los docentes de Ingeniería de Software en UTEC:
- Registrar hasta 10 evaluaciones por estudiante con sus respectivas notas y pesos
- Verificar el cumplimiento de asistencia mínima
- Aplicar políticas de puntos extra según el año académico
- Calcular automáticamente la nota final con detalle completo del cálculo

## Arquitectura del Sistema

El sistema está diseñado con **bajo acoplamiento** y **alta cohesión**, siguiendo principios SOLID y buenas prácticas de POO.

### Estructura de Directorios

```
.
├── include/              # Archivos de cabecera (.h)
│   ├── Evaluation.h
│   ├── Student.h
│   ├── ExtraPointsPolicy.h
│   ├── PolicyManager.h
│   ├── GradeCalculator.h
│   ├── InputValidator.h
│   └── DisplayManager.h
├── src/                  # Implementaciones (.cpp)
│   ├── Evaluation.cpp
│   ├── Student.cpp
│   ├── ExtraPointsPolicy.cpp
│   ├── PolicyManager.cpp
│   ├── GradeCalculator.cpp
│   ├── InputValidator.cpp
│   └── DisplayManager.cpp
├── main.cpp              # Punto de entrada del programa
├── compile.bat           # Script de compilación para Windows
├── compile.sh            # Script de compilación para Linux/Mac
└── Makefile              # Makefile para compilación con make
```

### Clases y Responsabilidades

#### 1. Evaluation (Entidad del Dominio)
- **Responsabilidad**: Encapsular los datos de una evaluación individual
- **Atributos**: nombre, nota, peso porcentual
- **Métodos clave**: `calculateWeightedContribution()`
- **Acoplamiento**: Ninguno (clase independiente)
- **Cohesión**: Alta - solo maneja datos de evaluación

#### 2. Student (Entidad del Dominio)
- **Responsabilidad**: Gestionar información del estudiante y sus evaluaciones
- **Atributos**: código, evaluaciones, asistencia
- **Métodos clave**: `addEvaluation()`, `calculateTotalWeight()`
- **Acoplamiento**: Bajo - solo depende de Evaluation
- **Cohesión**: Alta - solo maneja datos del estudiante

#### 3. ExtraPointsPolicy (Entidad del Dominio)
- **Responsabilidad**: Encapsular reglas de otorgamiento de puntos extra
- **Atributos**: año académico, puntos, requisitos
- **Métodos clave**: `studentQualifies()`
- **Acoplamiento**: Ninguno (clase independiente)
- **Cohesión**: Alta - solo maneja políticas

#### 4. PolicyManager (Gestor de Colecciones)
- **Responsabilidad**: Gestionar colección de políticas de puntos extra
- **Métodos clave**: `findPolicyByYear()`, `addPolicy()`
- **Acoplamiento**: Bajo - solo depende de ExtraPointsPolicy
- **Cohesión**: Alta - solo gestiona políticas

#### 5. GradeCalculator (Lógica de Negocio)
- **Responsabilidad**: Centralizar toda la lógica de cálculo de notas
- **Métodos clave**: `calculateFinalGrade()`, `hasPassedCourse()`
- **Acoplamiento**: Medio - depende de Student y ExtraPointsPolicy (solo lectura)
- **Cohesión**: Alta - solo realiza cálculos de notas

#### 6. InputValidator (Utilidad)
- **Responsabilidad**: Validar y procesar entradas del usuario
- **Métodos clave**: `readValidatedInt()`, `readValidatedDouble()`, `readYesNo()`
- **Acoplamiento**: Ninguno (utilidad independiente)
- **Cohesión**: Alta - solo maneja validación de entrada

#### 7. DisplayManager (Presentación)
- **Responsabilidad**: Formatear y mostrar información en consola
- **Métodos clave**: `displayGradeCalculationDetail()`, `displayEvaluations()`
- **Acoplamiento**: Bajo - recibe objetos pero solo para lectura
- **Cohesión**: Alta - solo maneja visualización

### Principios de Diseño Aplicados

1. **Single Responsibility Principle**: Cada clase tiene una única responsabilidad bien definida
2. **Open/Closed Principle**: Las clases pueden extenderse sin modificar el código existente
3. **Dependency Inversion**: Las dependencias apuntan hacia abstracciones
4. **Separación de Concerns**: Lógica de negocio, presentación y validación están separadas
5. **Encapsulación**: Atributos privados con acceso controlado mediante getters/setters

## Requerimientos Funcionales Implementados

- **RF1**: Registro de estudiante por código
- **RF2**: Registro/Revisión de hasta 10 evaluaciones con validación de pesos
- **RF3**: Registro de asistencia mínima (hasReachedMinimumAttendance)
- **RF4**: Consulta de política de puntos extra por año académico
- **RF5**: Cálculo de nota final considerando:
  - Promedio ponderado de evaluaciones
  - Penalización por inasistencias (nota = 0 si no cumple asistencia)
  - Aplicación de puntos extra según política vigente
- **RF6**: Visualización detallada del cálculo paso a paso

## Requerimientos No Funcionales Implementados

- **RNF1**: Límite de 10 evaluaciones por estudiante usando `vector` con capacidad reservada
- **RNF2**: Diseño sin variables globales compartidas, preparado para hasta 50 usuarios concurrentes
- **RNF3**: Código modular y bien organizado con funciones específicas para cada tarea

## Compilación y Ejecución

### Opción 1: Usando scripts de compilación

#### En Windows:
```bash
compile.bat
calculo_notas.exe
```

#### En Linux/Mac:
```bash
chmod +x compile.sh
./compile.sh
./calculo_notas
```

### Opción 2: Usando Makefile

```bash
make              # Compila el proyecto
make run          # Compila y ejecuta
make clean        # Limpia archivos compilados
```

### Opción 3: Compilación manual

```bash
g++ -std=c++17 -Wall -Iinclude \
    main.cpp \
    src/Evaluation.cpp \
    src/Student.cpp \
    src/ExtraPointsPolicy.cpp \
    src/PolicyManager.cpp \
    src/GradeCalculator.cpp \
    src/InputValidator.cpp \
    src/DisplayManager.cpp \
    -o calculo_notas
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

El código está diseñado con:
- Sin variables globales compartidas
- Lógica de cálculo independiente del estado global
- Separación clara de responsabilidades
- Preparado para múltiples instancias simultáneas
- Soporte para hasta 50 usuarios concurrentes según RNF2

## Requisitos del Sistema

- Compilador C++ con soporte para C++17 o superior
- GCC/G++ 7.0+ o compatible
- Sistema operativo: Windows, Linux o macOS

## Mejoras de Diseño Implementadas

### Comparado con la versión anterior:

1. **Uso de Clases en lugar de Structs**: Encapsulación completa con atributos privados
2. **Separación en Archivos .h y .cpp**: Mejor organización y tiempos de compilación
3. **Bajo Acoplamiento**: Cada clase tiene dependencias mínimas y bien definidas
4. **Alta Cohesión**: Cada clase tiene una responsabilidad única y clara
5. **Comentarios Significativos**: Documentación clara de responsabilidades y propósito
6. **Facilidad de Mantenimiento**: Cambios en una clase no afectan innecesariamente a otras
7. **Facilidad de Testing**: Cada clase puede ser probada independientemente
8. **Escalabilidad**: Fácil agregar nuevas funcionalidades sin modificar código existente

## Diagrama de Dependencias

```
main.cpp
    |
    +-- Student (depende de Evaluation)
    +-- PolicyManager (depende de ExtraPointsPolicy)
    +-- GradeCalculator (depende de Student, ExtraPointsPolicy)
    +-- InputValidator (independiente)
    +-- DisplayManager (depende de Student, ExtraPointsPolicy, GradeCalculator)

ExtraPointsPolicy (independiente)
Evaluation (independiente)
```

## Soporte

Para dudas o problemas con el sistema, contactar al equipo de Ingeniería de Software de UTEC.
