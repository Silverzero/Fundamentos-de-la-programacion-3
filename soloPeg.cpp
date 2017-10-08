#include "soloPeg.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

//COLOR.
void ColorFondo(int color){

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

//CARGAR.
bool cargarTablero(tMapa &mapa){

	int tamaño, aux;
	ifstream archivo;
	string nombre;
	bool encontrado = false;
	/*cout << "Introduzca mapa a jugar: ";
	cin >> nombre;
	*/archivo.open("prueba.txt"/*nombre*/);
	if (archivo.is_open()){
		encontrado = true;
		archivo >> tamaño;

		if (tamaño == DIM){

			archivo >> mapa.numBolas;
			archivo >> mapa.filameta;
			archivo >> mapa.columnameta;
			for (int f = 0; f < tamaño; f++){
				for (int c = 0; c < tamaño; c++){
					archivo >> aux;
					mapa.tablero[f][c] = tCelda(aux);
					
				}
			}
			archivo >> mapa.movimientos;
		}
		else cout << "Tamaño no valido.";
	}
	archivo.close();

	return encontrado;
}

//MOSTRAR.
void mostrarTablero(tMapa const &mapa){

	cout << " ";
	for (int i = 0; i < DIM; i++) cout << i + 1 << " ";
	cout << endl;

	for (int f = 0; f < DIM; f++){
		cout << f + 1;
		for (int c = 0; c < DIM; c++){

			ColorFondo(mapa.tablero[f][c]);

			if (f == mapa.filameta && c == mapa.columnameta)cout << char(254);
			else cout << " ";
			ColorFondo(0);
			cout << " ";

		}
		cout << endl << endl;
	}
	cout << "Numero de movimientos: " << mapa.movimientos << endl;
}

//GUARDAR.
void guardarTablero(tMapa &mapa){

	ofstream archivo;
	/*cout << "Introduce nombre del archivo: ";
	string nombre;
	cin >> nombre;*/
	archivo.open("salida.txt"/*nombre*/);

	archivo << DIM << endl;
	archivo << mapa.numBolas << endl;
	archivo << mapa.filameta << endl;
	archivo << mapa.columnameta << endl;
	for (int f = 0; f < DIM; f++){
		for (int c = 0; c < DIM; c++){

			archivo << mapa.tablero[f][c];
			archivo << " ";

		}
		archivo << endl;

	}
	archivo << mapa.movimientos;

	archivo.close();

}

//POSIBLES MOVIMIENTOS QUE PODEMOS REALIZAR CON "X" FICHA.
bool posibleMovimientos(tMapa const & mapa, tMovimiento movimiento, tPosibles/*SAL*/ posibles){
	

	for (int i = 0; i < NUM_DIRS; i++){
		if (casillaExiste(mapa,{{movimiento.fila + salto[i].fila }, { movimiento.columna + salto[i].columna}}) &&
			mapa.tablero[movimiento.fila + colindante[i].fila][movimiento.columna + colindante[i].columna] == FICHA &&
			mapa.tablero[movimiento.fila + salto[i].fila][movimiento.columna + salto[i].columna] == VACIA){

			posibles[i] = true;

		}
		else posibles[i] = false;

	}

	return (posibles[0] || posibles[1] || posibles[2] || posibles[3] ) == true;
}

//EJECUCION DEL MOVIMIENTO Y ACTUALIZACION DEL TABLERO.
bool ejecutarMovimiento(tMapa &/*ENT SAL*/ mapa, tMovimiento const& movimiento){

	bool continuar = false;
	int i = movimiento.direccion;
	//Actualiza las Fichas del tablero.
	mapa.tablero[movimiento.fila][movimiento.columna] = VACIA;
	mapa.tablero[movimiento.fila + colindante[i].fila][movimiento.columna + colindante[i].columna] = VACIA;
	mapa.tablero[movimiento.fila + salto[i].fila][movimiento.columna + salto[i].columna] = FICHA;
	
	//Incrementa en numero de movimientos realizados.
	mapa.movimientos++;
	mapa.numBolas--;
	//Recalcular el estado del Juego:
	if (mapa.numBolas == 1 && mapa.tablero[mapa.filameta][mapa.columnameta] == FICHA) mapa.estado = GANA;
	else {
		tPosibles posibles;
		int i = 0;
		while (i < DIM && !continuar){
			int j = 0;
			while (j < DIM && !continuar){
				
				if (mapa.tablero[i][j]!=NULA && posibleMovimientos(mapa, { i, j, },posibles)) continuar = true;
				else j++;
			}//while J
			i++;
		}//while I
		if (i < DIM) mapa.estado = JUGANDO;
		else mapa.estado = BLOQUEO;
	}
	return continuar;
}



