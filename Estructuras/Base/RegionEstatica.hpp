#pragma once

#include "../../defs.h"

#include <cstddef>

namespace IS220 { namespace Estructuras { namespace Base {
	
	template <typename TDato, std::size_t UCapacidad>
	class RegionEstatica {
	public:
		typedef TDato tipo_valor;
		typedef TDato& referencia;
		typedef const TDato& const_referencia;
		typedef TDato* puntero;
		typedef TDato* const_puntero;
		
		inline referencia operator[] (std::size_t pos) {
			return * reinterpret_cast<puntero>(&m_region[pos * sizeof(tipo_valor)]);
		}
		
		inline CONSTEXPR const_referencia operator[] (std::size_t pos) const {
			return * reinterpret_cast<const_puntero>(&m_region[pos * sizeof(tipo_valor)]);
		}
		
		inline operator puntero() {
			return & operator[](0);
		}
		
		inline CONSTEXPR operator const_puntero() const {
			return & operator[](0);
		}
		
	private:
		unsigned char m_region[UCapacidad * sizeof(tipo_valor)];
	};
	
}}}

