#pragma once

#include "../../defs.h"
#include "../Interfaces/ICola.hpp"
#include "../Base/RegionEstatica.hpp"

#include <cstddef>
#include <utility>

namespace IS220 { namespace Estructuras { namespace Estaticas {
	
	template <typename TDato, std::size_t UCapacidad>
	class ColaEstaticaBase : public Interfaces::ICola<TDato> {
	public:
		typedef TDato tipo_valor;
		typedef TDato& referencia;
		typedef const TDato& const_referencia;
		
	private:
		struct resposicionar { };
		
	public:
		ColaEstaticaBase()
			: m_inicio(0), m_cantidad(0) { }
		
		inline bool Vacia() const {
			return m_cantidad == 0;
		}
		
		inline bool Llena() const {
			return m_cantidad == UCapacidad;
		}
		
		bool Poner(const_referencia obj) {
			if (Llena(resposicionar())) {
				return false;
			}
			
			const std::size_t pos = m_inicio + m_cantidad;
			
			m_allocator.construct(&m_datos[pos], obj);
			
			++m_cantidad;
			
			return true;
		}
		
		bool Sacar(referencia obj) {
			if (Vacia()) {
				return false;
			}
			
			const std::size_t pos = m_inicio;
			
			obj = MOVE(m_datos[pos]);
			
			m_allocator.destroy(&m_datos[pos]);
			
			++m_inicio;
			--m_cantidad;
			
			return true;
		}
		
	private:
		bool Llena(resposicionar) {
			if (Llena()) {
				return true;
			}
			
			if (m_inicio + m_cantidad < UCapacidad) {
				return false;
			}
			
			// ** C++11 **
			// (#include <algorithm>)
			// std::move(&m_datos[m_inicio], &m_datos[m_inicio + m_cantidad],
			//				&m_datos[0]);
			for (std::size_t i = 0; i < m_cantidad; ++i) {
				m_allocator.construct(&m_datos[i], MOVE(m_datos[i + m_inicio]));
				
				m_allocator.destroy(&m_datos[i + m_inicio]);
			}
			
			m_inicio = 0;
			
			return false;
		}
		
	private:
		Base::RegionEstatica<tipo_valor, UCapacidad> m_datos;
		
		std::size_t m_inicio;
		std::size_t m_cantidad;
		
		std::allocator<TDato> m_allocator;
	};
	
	template <typename TDato>
	class ColaEstatica : public ColaEstaticaBase<TDato, 20> {
		//using ColaEstaticaBase::ColaEstaticaBase;
	};
	
}}}

