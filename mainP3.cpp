#include "soloPeg.h"
#include <iostream>
using namespace std;

//PROTOTIPOS
bool partida(tMapa &/*ENT SAL*/mapa);
bool leerMovimiento(tMapa const &mapa, tMovimiento &movimiento);


int main(){
	
	bool jugamos = true;
	tMapa mapa;
	mapa.estado = JUGANDO;
	if (cargarTablero(mapa)){
		while (jugamos){
			partida(mapa);
		}
	}
	

	guardarTablero(mapa);
}

bool partida(tMapa &/*ENT SAL*/mapa){
	
	tMovimiento movimiento;
	mostrarTablero(mapa);
	while (leerMovimiento(mapa, movimiento) && mapa.estado == JUGANDO)
		ejecutarMovimiento(mapa, movimiento);	
	
	return true;
}
//LEERMOS MOVIMIENTOS Y COMPROBAMOS INTEGRIDAD.
bool leerMovimiento(tMapa const &mapa, tMovimiento &movimiento){
	
	bool seguimos = false;
	tPosibles posibles;
	cout << "FICHA (fila y columna), o 0 para salir: ";
	cin >> movimiento.fila;
	if (movimiento.fila != 0){
		cin >> movimiento.columna;
		movimiento.fila = movimiento.fila - 1;
		movimiento.columna = movimiento.columna - 1;
		if (casillaExiste(mapa, { movimiento.fila, movimiento.columna }) && tipoCasilla(mapa, { movimiento.fila, movimiento.columna }) == FICHA){
			posibleMovimientos(mapa, movimiento, posibles);
			cout << "Selecciona direccion: " << endl;
			for (int i = 0; i < NUM_DIRS; i++){
				if (posibles[i])cout << "\t" << i + 1 << " - " << NOMB_DIRS[i] << endl;

			}
			cout << "Direccion: ";
			cin >> movimiento.direccion;
			movimiento.direccion = movimiento.direccion - 1;
			if (posibles[movimiento.direccion]) seguimos = true;

		}

	}
	return seguimos;
};



