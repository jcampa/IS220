#pragma once

#include "../../defs.h"
#include "../Interfaces/ICola.hpp"
#include "../Base/RegionEstatica.hpp"

#include <algorithm>

namespace IS220 { namespace Estructuras { namespace Estaticas {
	
	template <typename TDato, std::size_t UCapacidad>
	class ColaCircularEstaticaBase : public Interfaces::ICola<TDato> {
	public:
		typedef TDato tipo_valor;
		typedef TDato& referencia;
		typedef const TDato& const_referencia;
		
	public:
		ColaCircularEstaticaBase()
			: m_inicio(0), m_cantidad(0) { }
		
		inline bool Vacia() const {
			return m_cantidad == 0;
		}
		
		inline bool Llena() const {
			return m_cantidad == UCapacidad;
		}
		
		bool Poner(const tipo_valor& obj) {
			if (Llena()) {
				return false;
			}
			
			const std::size_t pos = (m_inicio + m_cantidad) % UCapacidad;
			
			new(&m_datos[pos]) tipo_valor(obj);
			
			++m_cantidad;
			
			return true;
		}
		
		bool Sacar(tipo_valor& obj) {
			if (Vacia()) {
				return false;
			}
			
			const std::size_t pos = m_inicio;
			
			obj = MOVE(m_datos[pos]);
			
			m_datos[pos].~tipo_valor();
			
			m_inicio = (m_inicio + 1) % UCapacidad;
			--m_cantidad;
			
			return true;
		}
		
	private:
		Base::RegionEstatica<tipo_valor, UCapacidad> m_datos;
		
		std::size_t m_inicio;
		std::size_t m_cantidad;
	};
	
	template <typename TDato>
	class ColaCircularEstatica : public ColaCircularEstaticaBase<TDato, 20> {
		//using ColaCircularEstaticaBase::ColaCircularEstaticaBase;
	};
	
}}}

