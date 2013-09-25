#pragma once

#include "../../defs.h"
#include "../Base/RegionEstatica.hpp"

#include <cstddef>
#include <memory>
#include <utility>

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
	
	bool Poner(const_referencia obj) {
		if (Llena()) {
			return false;
		}
		
		const std::size_t pos = (m_inicio + m_cantidad) % UCapacidad;
		
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
		
		m_inicio = (m_inicio + 1) % UCapacidad;
		--m_cantidad;
		
		return true;
	}
	
private:
	Base::RegionEstatica<tipo_valor, UCapacidad> m_datos;
	
	std::size_t m_inicio;
	std::size_t m_cantidad;

	std::allocator<tipo_valor> m_allocator;
};

template <typename TDato>
class ColaCircularEstatica : public ColaCircularEstaticaBase<TDato, 20> {
	//using ColaCircularEstaticaBase::ColaCircularEstaticaBase;
};

}}} // namespace IS220::Estructuras::Estaticas
