#pragma once

#include "../../defs.h"
#include "../Base/RegionEstatica.hpp"

#include <cstddef>
#include <memory>
#include <utility>

namespace IS220 { namespace Estructuras { namespace Estaticas {

template <typename TDato, std::size_t UCapacidad>
class PilaEstaticaBase {
public:
	typedef TDato tipo_valor;
	typedef TDato& referencia;
	typedef const TDato& const_referencia;
	typedef TDato* puntero;
	typedef const TDato* const_puntero;
	
public:
	PilaEstaticaBase()
		: m_cantidad(0) { }
	
	inline bool Vacia() const {
		return m_cantidad == 0;
	}
	
	inline bool Llena() const {
		return m_cantidad == UCapacidad;
	}
	
	bool Poner(tipo_valor obj) {
		if (Llena()) {
			return false;
		}
		
		const std::size_t pos = m_cantidad;
		
		m_allocator.construct(&m_datos[pos], MOVE(obj));
		
		++m_cantidad;
		
		return true;
	}
	
	bool Sacar(referencia obj) {
		if (Vacia()) {
			return false;
		}
		
		const std::size_t pos = m_cantidad - 1;
		
		obj = MOVE(m_datos[pos]);
		
		m_allocator.destroy(&m_datos[pos]);
		
		--m_cantidad;
		
		return true;
	}
	
private:
	Base::RegionEstatica<tipo_valor, UCapacidad> m_datos;

	std::size_t m_cantidad;
	
	std::allocator<tipo_valor> m_allocator;
};

template <typename TDato>
class PilaEstatica : public PilaEstaticaBase<TDato, 20> {
	//using PilaEstaticaBase::PilaEstaticaBase;
};

}}} // namespace IS220::Estructuras::Estaticas
