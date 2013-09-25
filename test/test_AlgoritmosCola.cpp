#include <gtest/gtest.h>

#include "../src/Algoritmos/Cola.hpp"
#include "../src/Estructuras/Estaticas/ColaEstatica.hpp"

#include <ctime>
#include <cstdlib>

using namespace IS220::Algoritmos;
using namespace IS220::Estructuras::Estaticas;
using namespace std;

// NOTA: test poco riguroso
TEST(AlgoritmosColaTest, OrdenarCola) {
	const int tam_cola = 100;
	ColaEstaticaBase<int, tam_cola> cola;
	
	srand(time(0));
	
	for (int i = 0; i < tam_cola; ++i) {
		cola.Poner(rand());
	}
	
	OrdenarCola(cola);
	
	int anterior = 0;
	
	for (int i = 0; i < tam_cola; ++i) {
		int actual;
		
		cola.Sacar(actual);
		
		ASSERT_LE(anterior, actual);
		
		anterior = actual;
	}
}
