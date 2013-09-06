#pragma once

#include "../../defs.h"
#include "../Base/RegionEstatica.hpp"

#include <utility>

namespace IS220 { namespace Estructuras { namespace Estaticas {
	
	template <typename TDato, std::size_t UCapacidad>
	class PilaEstaticaBase {
	public:
		typedef TDato tipo_valor;
		typedef TDato& referencia;
		typedef const TDato& const_referencia;
		
	public:
		PilaEstaticaBase()
			: m_cantidad(0u) { }
		
		inline bool Vacia() const {
			return m_cantidad == 0u;
		}
		
		inline bool Llena() const {
			return m_cantidad == UCapacidad;
		}
		
		bool Poner(const tipo_valor& obj) {
			if (Llena()) {
				return false;
			}
			
			const std::size_t pos = m_cantidad;
			
			new(&m_datos[pos]) tipo_valor(obj);
			
			++m_cantidad;
			
			return true;
		}
		
		bool Sacar(tipo_valor& obj) {
			if (Vacia()) {
				return false;
			}
			
			const std::size_t pos = m_cantidad - 1;
			
			obj = MOVE(m_datos[pos]);
			
			m_datos[pos].~tipo_valor();
			
			--m_cantidad;
			
			return true;
		}
		
	private:
		Base::RegionEstatica<tipo_valor, UCapacidad> m_datos;

		std::size_t m_cantidad;
	};
	
	template <typename TDato>
	class PilaEstatica : public PilaEstaticaBase<TDato, 20u> {
		//using PilaEstaticaBase::PilaEstaticaBase;
	};
	
}}}
