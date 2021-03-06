#pragma once

#include "../../defs.h"

#include <cstddef>

namespace IS220 { namespace Estructuras { namespace Base {

/*

Esta clase de ayuda emula (quizas no completamente) el comportamiento de:

	union {
		TDato m_region[UCapacidad];
	}

que es solo disponible en C++11, gracias a "unrestricted unions."

Se hace uso de esta facilidad en las estructuras de este proyecto para
evitar la inicializacion implicita de los N objetos dentro del array.
(Donde N = UCapacidad)

*/
template <typename TDato, std::size_t UCapacidad>
class RegionEstatica {
public:
	typedef TDato tipo_valor;
	typedef TDato& referencia;
	typedef const TDato& const_referencia;
	typedef TDato* puntero;
	typedef const TDato* const_puntero;
	
	inline referencia operator[] (std::size_t pos) NOEXCEPT {
		return * reinterpret_cast<puntero>(&m_region[pos * sizeof(tipo_valor)]);
	}
	
	inline CONSTEXPR const_referencia operator[] (std::size_t pos) const NOEXCEPT {
		return * reinterpret_cast<const_puntero>(&m_region[pos * sizeof(tipo_valor)]);
	}
	
	inline puntero data() NOEXCEPT {
		return & operator[](0);
	}
	
	inline CONSTEXPR const_puntero data() const NOEXCEPT {
		return & operator[](0);
	}
	
private:
	unsigned char m_region[UCapacidad * sizeof(tipo_valor)];
};

}}} // namespace IS220::Estructuras::Base
