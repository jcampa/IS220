#include "gtest/gtest.h"

#include "Estructuras/Base/RegionEstatica.hpp"

using namespace IS220::Estructuras::Base;

static int contador = 0;

TEST(RegionEstaticaTest, SizeofCoherente) {
	struct SizeofCoherente_t {
		int a, b;
		char c[14];
	};
	
	typedef RegionEstatica<SizeofCoherente_t, 10> region_t;
	
	const size_t sz_region = sizeof(region_t);
	const size_t sz_10item = 10 * sizeof(SizeofCoherente_t);
	
	ASSERT_EQ(sz_region, sz_10item) << "La estructura tiene sizeof() incoherente";
}

TEST(RegionEstaticaTest, NoInicializaDatos) {
	contador = 0;
	
	struct NoInicializaDatos_t {
		NoInicializaDatos_t() {
			++contador;
		}
	};
	
	RegionEstatica<NoInicializaDatos_t, 10> region;
	
	ASSERT_EQ(contador, 0) << "El contador no se debe modificar";
}

TEST(RegionEstaticaTest, PunterosCoherentes) {
	RegionEstatica<int, 10> region;
	
	for (int i = 0; i < 10; ++i) {
		ASSERT_EQ((int*) &region + i, &region[i])
			<< "Puntero de posicion " << i << " no concuerda";
	}
}
