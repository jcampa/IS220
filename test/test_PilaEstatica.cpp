#include "gtest/gtest.h"

#include "Estructuras/Estaticas/PilaEstatica.hpp"

using namespace IS220::Estructuras::Estaticas;

TEST(PilaEstaticaTest, Basico) {
	PilaEstaticaBase<int, 5> pila;
	int val1 = 0xDEADBEEF;
	
	ASSERT_TRUE(pila.Vacia());
	
	ASSERT_FALSE(pila.Llena());
	
	ASSERT_FALSE(pila.Sacar(val1));
	
	ASSERT_EQ(val1, 0xDEADBEEF);
	
	for (int i = 1; i <= 5; ++i) {
		ASSERT_TRUE(pila.Poner(i));
		
		ASSERT_FALSE(pila.Vacia());
		
		if (i == 5) {
			ASSERT_TRUE(pila.Llena());
		} else {
			ASSERT_FALSE(pila.Llena());
		}
	}
	
	for (int i = 5; i >= 1; --i) {
		int val = 0;
		
		ASSERT_TRUE(pila.Sacar(val));
		
		ASSERT_EQ(val, i);
		
		ASSERT_FALSE(pila.Llena());
		
		if (i == 1) {
			ASSERT_TRUE(pila.Vacia());
		} else {
			ASSERT_FALSE(pila.Vacia());
		}
	}
}
