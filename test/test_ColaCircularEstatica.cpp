#include <gtest/gtest.h>

#include "../src/Estructuras/Estaticas/ColaCircularEstatica.hpp"

using namespace IS220::Estructuras::Estaticas;

TEST(ColaCircularEstaticaTest, ColaVacia) {
	ColaCircularEstaticaBase<int, 5> cola;
	
	ASSERT_TRUE(cola.Vacia());
	
	ASSERT_FALSE(cola.Llena());
	
	const int val_expected = 1992;
	int val_read = val_expected;
	
	ASSERT_FALSE(cola.Sacar(val_read));
	
	ASSERT_EQ(val_read, val_expected);
}
