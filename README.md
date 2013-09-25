IS220
=====

Estructuras y algoritmos para la clase IS220 de la Universidad Privada de Santa Cruz de la Sierra (UPSA).

Se distribuye este codigo con intenciones educativas. El autor no se responsabiliza del mal uso de dicho codigo.

Instrucciones (Windows + Visual Studio)
--

  * Descargar e instalar CMake (http://www.cmake.org/cmake/resources/software.html)
  * Descargar e instalar algun cliente Git (se recomienda http://windows.github.com/)
  * Clonar este repositorio
  * Navegar al directorio local del repositorio
  * Crear el directorio "build": `mkdir build`
  * Navegar al directorio creado: `cd build`
  * Correr CMake: `cmake ..`
  * Abrir "IS220.sln"
  * Compilar y correr el proyecto "IS220-test"

Si tiene git, cmake, devenv.exe en su PATH (recomendado):

	git clone https://github.com/Garciat/IS220.git
	cd IS220
	mkdir build
	cd build
	cmake ..
	devenv IS220.sln /Build
	.\test\Debug\IS220-test.exe

Instrucciones (Linux)
--

	git clone https://github.com/Garciat/IS220.git
	cd IS220
	mkdir build
	cd build
	cmake ..
	make
	make test

Notas
--

Testeado en:

  * Visual Studio 2012 Update 3
  * GCC 4.7.2
