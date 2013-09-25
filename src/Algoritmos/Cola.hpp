#pragma once

namespace IS220 { namespace Algoritmos {

/*

Se implementa un algoritmo divide-and-conquer estilo quicksort.

*/
template <class TCola>
void OrdenarCola(TCola& cola) {
	if (cola.Vacia()) {
		return;
	}
	
	typedef typename TCola::tipo_valor TDato;
	
	TDato pivote;
	cola.Sacar(pivote);
	
	TCola menores, mayores;
	
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

}} // namespace IS220::Algoritmos
