#include "gtest/gtest.h"

#include "Estructuras/Estaticas/ColaEstatica.hpp"

using namespace IS220::Estructuras::Estaticas;

TEST(ColaEstaticaTest, Basico) {
	ColaEstaticaBase<int, 5> cola;
	int val1 = 0xDEADBEEF;
	
	ASSERT_TRUE(cola.Vacia());
	
	ASSERT_FALSE(cola.Llena());
	
	ASSERT_FALSE(cola.Sacar(val1));
	
	ASSERT_EQ(val1, 0xDEADBEEF);
	
	for (int i = 1; i <= 5; ++i) {
		ASSERT_TRUE(cola.Poner(i));
		
		ASSERT_FALSE(cola.Vacia());
		
		if (i == 5) {
			ASSERT_TRUE(cola.Llena());
		} else {
			ASSERT_FALSE(cola.Llena());
		}
	}
	
	for (int i = 1; i <= 5; ++i) {
		int val = 0;
		
		ASSERT_TRUE(cola.Sacar(val));
		
		ASSERT_EQ(val, i);
		
		ASSERT_FALSE(cola.Llena());
		
		if (i == 5) {
			ASSERT_TRUE(cola.Vacia());
		} else {
			ASSERT_FALSE(cola.Vacia());
		}
	}
}
