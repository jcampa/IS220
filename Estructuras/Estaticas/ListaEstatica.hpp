#pragma once

#include "../../defs.h"
#include "../Base/RegionEstatica.hpp"

#include <algorithm>

namespace IS220 { namespace Estructuras { namespace Estaticas {
	
	template <typename TDato, size_t UCapacidad>
	class ListaEstaticaBase {
	public:
		typedef TDato tipo_valor;
		typedef TDato& referencia;
		typedef const TDato& const_referencia;
		
		typedef size_t iterador;
		
	private:
		struct nodo {
			tipo_valor m_dato;
			iterador m_siguiente;
		};
		
	public:
		static const iterador sin_pos = -1;
		
		ListaEstaticaBase()
			: m_it_lista(sin_pos), m_it_libre(0)
		{
			for (size_t i = 0; i < UCapacidad - 1; ++i) {
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
		
		bool Insertar(const_referencia obj, iterador it = sin_pos) {
			if (Llena()) {
				return false;
			}
			
			iterador nuevo = ObtenerNodo();
			
			new(&AccederNodo(nuevo)->m_dato) tipo_valor(obj);
			
			if (it == sin_pos) {
				AccederNodo(nuevo)->m_siguiente = m_it_lista;
				
				m_it_lista = nuevo;
			} else {
				AccederNodo(nuevo)->m_siguiente = Siguiente(it);
				
				AccederNodo(it)->m_siguiente = nuevo;
			}
			
			return true;
		}
		
		bool Eliminar(referencia ref, iterador it = sin_pos) {
			if (Vacia()) {
				return false;
			}
			
			iterador elim;
			
			if (it == sin_pos) {
				elim = m_it_lista;
				
				m_it_lista = Siguiente(elim);
			} else {
				elim = AccederNodo(it)->m_siguiente;
				
				AccederNodo(it)->m_siguiente = Siguiente(elim);
			}
			
			if (elim != sin_pos) {
				ref = MOVE(AccederNodo(elim)->m_dato);
				
				AccederNodo(elim)->m_dato.~tipo_valor();
				
				DevolverNodo(elim);
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
	};
	
	template <typename TDato>
	class ListaEstatica : public ListaEstaticaBase<TDato, 20> {
		//using ListaEstaticaBase::ListaEstaticaBase;
	};
	
}}}

