#include <gtest/gtest.h>

#include "../src/Estructuras/Estaticas/ListaEstatica.hpp"

using namespace IS220::Estructuras::Estaticas;

TEST(ListaEstaticaTest, ListaVacia) {
	ListaEstaticaBase<int, 5> lista;
	
	ASSERT_TRUE(lista.Vacia());
	
	ASSERT_FALSE(lista.Llena());
	
	ASSERT_EQ(lista.Inicio(), lista.Fin());
	
	const int val_expected = 1992;
	int val_read = val_expected;
	
	ASSERT_FALSE(lista.Eliminar(val_read));
	
	ASSERT_EQ(val_expected, val_read);
}
