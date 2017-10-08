#include <string>
//Constantes y Tipos
const int NUM_DIRS = 4;
const int DIM = 6;
const std::string NOMB_DIRS[NUM_DIRS] = {"Arriba","Derecha","Abajo","Izquierda"};
typedef enum tCelda{ NULA = 0, VACIA = 2, FICHA = 10 };
typedef enum tEstado{ BLOQUEO, GANA, JUGANDO };
typedef tCelda tTablero[DIM][DIM];
typedef struct{

	tTablero tablero;
	int filameta;
	int columnameta;
	int numBolas;
	int movimientos;
	tEstado estado;

}tMapa;
typedef struct{
	int fila;
	int columna;
	unsigned int direccion;
}tMovimiento;
typedef bool tPosibles[NUM_DIRS];
typedef struct{ int fila, columna; }tCoor;

const tCoor colindante[NUM_DIRS] = { { -1,0 }, { 0,1  }, { 1,0 }, { 0, -1 }, };//ARRIBA DERECHA ABAJO IZQUIERDA
const tCoor salto[NUM_DIRS] = { { -2,0 }, { 0, 2 }, { 2, 0 }, { 0, -2 } };//ARRIBA DERECHA ABAJO IZQUIERDA


//PROTOTIPOS
bool cargarTablero(tMapa /*SALIDA*/&mapa); //CARGAR
void ColorFondo(int color); //COLOR
void mostrarTablero(tMapa const &mapa); //MOSTRAR
void guardarTablero(tMapa &mapa); //GUARDAR
bool posibleMovimientos(tMapa const & mapa, tMovimiento movimiento, tPosibles/*SAL*/ posibles);
bool ejecutarMovimiento(tMapa &/*ENT SAL*/ mapa, tMovimiento const& movimiento);

//DEVUELVE SI LA CASILLA ESTA DENTRO DEL TABLERO
inline bool casillaExiste(tMapa const &mapa, tCoor coordenada){

	return coordenada.fila < DIM && coordenada.columna < DIM && mapa.tablero[coordenada.fila][coordenada.columna];

}

//DEVUELVE NULA, VACIA, FICHA SEGUN LO QUE HAYA EN EL TABLERO EN ESA POSICION.
inline tCelda tipoCasilla(tMapa mapa, tCoor coordenada){

	return mapa.tablero[coordenada.fila][coordenada.columna];
}
