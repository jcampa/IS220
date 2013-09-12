#pragma once

#include "../Estructuras/Interfaces/ICola.hpp"
#include "../Estructuras/Estaticas/ColaEstatica.hpp"

namespace IS220 { namespace Algoritmos {
	
	/*
	
	Se implementa un algoritmo divide-and-conquer estilo quicksort.
	
	*/
	template <class TDato>
	void OrdenarCola(ICola<TDato>& cola) {
		if (cola.Vacia()) {
			return;
		}
		
		TDato pivote;
		cola.Sacar(pivote);
		
		// TODO: utilizar colas dinamicas
		ColaEstatica<TDato> menores, mayores;
		
		TDato elem;
		
		while (cola.Sacar(elem)) {
			if (elem < pivote) {
				menores.Poner(elem);
			} else {
				mayores.Poner(elem);
			}
		}
		
		OrdenarCola(menores);
		OrdenarCola(mayores);
		
		while (menores.Sacar(elem)) {
			cola.Poner(elem);
		}
		
		cola.Poner(pivote);
		
		while (mayores.Sacar(elem)) {
			cola.Poner(elem);
		}
	}
	
}}
