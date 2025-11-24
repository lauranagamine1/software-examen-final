# Backend Simple - Spring Boot con SonarQube

Backend simple en Java 17 con Spring Boot y Maven, integrado con SonarQube para análisis de código.

## Requisitos

- Docker y Docker Compose
- Java 17 (para desarrollo local)
- Maven 3.x (para desarrollo local)

## Estructura del Proyecto

```
.
├── src/
│   └── main/
│       ├── java/com/example/backend/
│       │   ├── BackendApplication.java
│       │   └── controller/
│       │       └── HelloController.java
│       └── resources/
│           └── application.properties
├── docker-compose.yml
├── Dockerfile
├── .env
└── pom.xml
```

## Configuración

Las variables de entorno están en el archivo `.env`:

```properties
# PostgreSQL Configuration
POSTGRES_DB=sonarqube
POSTGRES_USER=sonar
POSTGRES_PASSWORD=sonar123

# Spring Boot Configuration
SERVER_PORT=8080

# SonarQube Configuration
SONAR_PROJECT_KEY=backend-simple
SONAR_PROJECT_NAME=Backend Simple
SONAR_HOST_URL=http://localhost:9000
```

## Levantar los Servicios

### 1. Iniciar todos los servicios

```bash
docker-compose up -d
```

Esto levantará:
- PostgreSQL (puerto 5432)
- SonarQube (puerto 9000)
- Backend Spring Boot (puerto 8080)

### 2. Verificar el estado

```bash
docker-compose ps
```

### 3. Ver logs

```bash
docker-compose logs -f backend
docker-compose logs -f sonarqube
```

## Uso

### Endpoint disponible

**GET** `/api/hello`

Devuelve: `"hola mundo"`

**Ejemplo con curl:**

```bash
curl http://localhost:8080/api/hello
```

**Ejemplo con navegador:**

```
http://localhost:8080/api/hello
```

## SonarQube

### Acceso a SonarQube

1. Abre tu navegador en: `http://localhost:9000`
2. Credenciales por defecto:
   - Usuario: `admin`
   - Contraseña: `admin` (te pedirá cambiarla)

### Analizar el código con SonarQube

#### Opción 1: Desde el contenedor

```bash
docker exec -it backend-simple mvn clean verify sonar:sonar \
  -Dsonar.projectKey=backend-simple \
  -Dsonar.host.url=http://sonarqube:9000 \
  -Dsonar.login=<tu-token>
```

#### Opción 2: Desde tu máquina local

```bash
mvn clean verify sonar:sonar \
  -Dsonar.projectKey=backend-simple \
  -Dsonar.host.url=http://localhost:9000 \
  -Dsonar.login=<tu-token>
```

### Generar token en SonarQube

1. Ve a: `http://localhost:9000/account/security`
2. Genera un nuevo token
3. Usa ese token en el comando `-Dsonar.login=<tu-token>`

## Desarrollo Local

### Compilar y ejecutar sin Docker

```bash
mvn clean install
mvn spring-boot:run
```

### Ejecutar tests

```bash
mvn test
```

### Generar reporte de cobertura (JaCoCo)

```bash
mvn clean test jacoco:report
```

El reporte estará en: `target/site/jacoco/index.html`

## Detener los Servicios

```bash
docker-compose down
```

Para eliminar también los volúmenes:

```bash
docker-compose down -v
```

## Comandos Útiles

### Reconstruir el backend

```bash
docker-compose up -d --build backend
```

### Ver logs en tiempo real

```bash
docker-compose logs -f
```

### Reiniciar un servicio específico

```bash
docker-compose restart backend
```

## Notas

- La primera vez que inicies SonarQube tardará algunos minutos en estar disponible
- El backend esperará a que SonarQube esté listo antes de iniciarse (healthcheck)
- Los datos de PostgreSQL y SonarQube se persisten en volúmenes de Docker
