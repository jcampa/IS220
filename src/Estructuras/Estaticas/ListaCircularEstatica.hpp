#pragma once

#include "../../defs.h"
#include "../Base/RegionEstatica.hpp"
#include "../Interfaces/IListaCircular.hpp"

#include <cstddef>
#include <memory>
#include <utility>

namespace IS220 { namespace Estructuras { namespace Estaticas {

template <typename TDato, std::size_t UCapacidad>
class ListaCircularEstaticaBase {
public:
	typedef TDato tipo_valor;
	typedef TDato& referencia;
	typedef const TDato& const_referencia;
	
	typedef std::size_t iterador;
	
private:
	struct nodo {
		tipo_valor m_dato;
		iterador m_siguiente;
	};
	
public:
	static const iterador sin_pos = -1;
	
	ListaCircularEstaticaBase()
		: m_it_lista(sin_pos), m_it_libre(0)
	{
		for (std::size_t i = 0; i < UCapacidad - 1; ++i) {
			m_datos[i].m_siguiente = i + 1;
		}
		
		m_datos[UCapacidad - 1].m_siguiente = sin_pos;
	}
	
	inline bool Vacia() const {
		return m_it_lista == sin_pos;
	}
	
	inline bool Llena() const {
		return m_it_libre == sin_pos;
	}
	
	inline iterador Inicio() const {
		if (Vacia()) {
			return sin_pos;
		}
		
		return AccederNodo(m_it_lista)->m_siguiente;
	}
	
	inline iterador Fin() const {
		return m_it_lista;
	}
	
	// Comportamiento indefinido para it == sin_pos
	inline referencia Acceder(iterador it) {
		return AccederNodo(it)->m_dato;
	}
	
	// Comportamiento indefinido para it == sin_pos
	inline iterador Siguiente(iterador it) {
		return AccederNodo(it)->m_siguiente;
	}
	
	bool Insertar(const_referencia obj, iterador it = sin_pos) {
		if (Llena()) {
			return false;
		}
		
		if (it == sin_pos) {
			it = m_it_lista;
		}
		
		iterador nuevo = ObtenerNodo();
		
		m_allocator.construct(&AccederNodo(nuevo)->m_dato, obj);
		
		if (AccederNodo(it)->m_siguiente == m_it_lista) {
			m_it_lista = nuevo;
		}
		
		AccederNodo(nuevo)->m_siguiente = AccederNodo(it)->m_siguiente;
		AccederNodo(it)->m_siguiente = nuevo;
		
		return true;
	}
	
	bool Eliminar(referencia ref, iterador it = sin_pos) {
		if (Vacia()) {
			return false;
		}
		
		if (it == sin_pos) {
			it = m_it_lista;
		}
		
		iterador elim = AccederNodo(it)->m_siguiente;
		
		ref = MOVE(AccederNodo(elim)->m_dato);
		
		m_allocator.destroy(&AccederNodo(it)->m_dato);
		
		AccederNodo(it)->m_siguiente = AccederNodo(elim)->m_siguiente;
		
		if (elim == it) {
			m_it_lista = sin_pos;
		} else if (elim == m_it_lista) {
			m_it_lista = AccederNodo(it)->m_siguiente;
		}
		
		DevolverNodo(elim);
		
		return true;
	}
	
private:
	inline nodo* AccederNodo(iterador it) {
		return &m_datos[it];
	}
	
	inline const nodo* AccederNodo(iterador it) const {
		return &m_datos[it];
	}
	
	iterador ObtenerNodo() {
		iterador it = m_it_libre;
		
		m_it_libre = Siguiente(m_it_libre);
		
		return it;
	}
	
	void DevolverNodo(iterador it) {
		AccederNodo(it)->m_siguiente = m_it_libre;
		
		m_it_libre = it;
	}
	
private:
	Base::RegionEstatica<nodo, UCapacidad> m_datos;
	
	iterador m_it_lista;
	iterador m_it_libre;

	std::allocator<tipo_valor> m_allocator;
};

template <typename TDato>
class ListaCircularEstatica : public ListaCircularEstaticaBase<TDato, 20> {
	//using ListaCircularEstaticaBase::ListaCircularEstaticaBase;
};

}}} // namespace IS220::Estructuras::Estaticas
