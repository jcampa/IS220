#pragma once

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

		referencia operator[] (std::size_t pos) {
			return * reinterpret_cast<puntero>(&m_region[pos * sizeof(tipo_valor)]);
		}

		const_referencia operator[] (std::size_t pos) const {
			return * reinterpret_cast<const_puntero>(&m_region[pos * sizeof(tipo_valor)]);
		}

		operator puntero() {
			return & operator[](0u);
		}

		operator const_puntero() const {
			return & operator[](0u);
		}

	private:
		unsigned char m_region[UCapacidad * sizeof(tipo_valor)];
	};

}}}
