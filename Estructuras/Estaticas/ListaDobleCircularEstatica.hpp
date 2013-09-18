#pragma once

#include "../../defs.h"
#include "../Base/RegionEstatica.hpp"

#include <cstddef>
#include <utility>

namespace IS220 { namespace Estructuras { namespace Estaticas {
	
	template <typename TDato, std::size_t UCapacidad>
	class ListaDobleCircularEstaticaBase {
	public:
		typedef TDato tipo_valor;
		typedef TDato& referencia;
		typedef const TDato& const_referencia;
		
		typedef std::size_t iterador;
		
		static const iterador sin_pos = -1;
		
	private:
		struct nodo {
			iterador m_anterior;
			iterador m_siguiente;
			tipo_valor m_dato;
			
			nodo() :
				m_anterior(sin_pos), m_siguiente(sin_pos) { }
		};
		
	public:
		ListaDobleCircularEstaticaBase()
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
			return m_it_lista;
		}
		
		inline iterador Fin() const {
			return sin_pos;
		}
		
		// Comportamiento indefinido para it == sin_pos
		inline referencia Acceder(iterador it) {
			return AccederNodo(it)->m_dato;
		}
		
		// Comportamiento indefinido para it == sin_pos
		inline iterador Siguiente(iterador it) {
			return AccederNodo(it)->m_siguiente;
		}
		
		bool InsertarIzquierda(const_referencia obj, iterador it = sin_pos) {
			if (Llena()) {
				return false;
			}
			
			iterador nuevo = ObtenerNodo();
			
			new(&AccederNodo(nuevo)->m_dato) tipo_valor(obj);
			
			if (m_it_lista == sin_pos) {
				m_it_lista = nuevo;
			}
			
			if (it == sin_pos) {
				it = m_it_lista;
			}
			
			AccederNodo(nuevo)->m_siguiente = it;
			AccederNodo(nuevo)->m_anterior = AccederNodo(it)->m_anterior;
			AccederNodo(it)->m_anterior = nuevo;
			AccederNodo(AccederNodo(nuevo)->m_anterior)->m_siguiente = nuevo;
			
			if (it == m_it_lista) {
				m_it_lista = nuevo;
			}
			
			return true;
		}
		
		bool InsertarDerecha(const_referencia obj, iterador it = sin_pos) {
			if (Llena()) {
				return false;
			}
			
			if (it == sin_pos) {
				return InsertarIzquierda(obj, it);
			}
			
			iterador nuevo = ObtenerNodo();
			
			new(&AccederNodo(nuevo)->m_dato) tipo_valor(obj);
			
			AccederNodo(nuevo)->m_anterior = it;
			AccederNodo(nuevo)->m_siguiente = AccederNodo(it)->m_siguiente;
			AccederNodo(it)->m_siguiente = nuevo;
			AccederNodo(AccederNodo(nuevo)->m_siguiente)->m_anterior = nuevo;
			
			if (AccederNodo(nuevo)->m_siguiente == m_it_lista) {
				m_it_lista = nuevo;
			}
			
			return true;
		}
		
		bool Eliminar(referencia ref, iterador it = sin_pos) {
			if (Vacia()) {
				return false;
			}
			
			if (it == sin_pos) {
				it = m_it_lista;
			}
			
			ref = MOVE(AccederNodo(it)->m_dato);
			
			AccederNodo(it)->m_dato.~tipo_valor();
			
			iterador anterior, siguiente;
			
			anterior = AccederNodo(it)->m_anterior;
			siguiente = AccederNodo(it)->m_siguiente;
			
			if (anterior != sin_pos) {
				AccederNodo(anterior)->m_siguiente = siguiente;
			}
			
			if (siguiente != sin_pos) {
				AccederNodo(siguiente)->m_anterior = anterior;
			}
			
			if (it == m_it_lista) {
				m_it_lista = siguiente;
			}
			
			if (anterior == siguiente) {
				m_it_lista = sin_pos;
			}
			
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
			
			// "nueva" instancia de tipo <nodo>
			new(AccederNodo(it)) nodo();
			
			return it;
		}
		
		void DevolverNodo(iterador it) {
			AccederNodo(it)->m_siguiente = m_it_libre;
			
			// destruir la instancia
			AccederNodo(it)->~nodo();
			
			m_it_libre = it;
		}
		
	private:
		Base::RegionEstatica<nodo, UCapacidad> m_datos;
		
		iterador m_it_lista;
		iterador m_it_libre;
	};
	
	template <typename TDato>
	class ListaDobleCircularEstatica : public ListaDobeEstaticaBase<TDato, 20> {
		//using ListaDobleCircularEstaticaBase::ListaDobleCircularEstaticaBase;
	};
	
}}}

