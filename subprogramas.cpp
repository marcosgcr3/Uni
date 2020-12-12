#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

//Declaracion de constantes
const int NUMERO_DE_FICHAS = 4;
const int NUMERO_DE_JUGADORES = 4;
const int NUMERO_DE_CASILLAS = 68;

//Declaracion de tipos
typedef int tJugadores[NUMERO_DE_JUGADORES][NUMERO_DE_FICHAS];
/*
[F1,F2,F3,F4] //Fichas del Amarillo
[F1,F2,F3,F4] //Fichas del Azul
[F1,F2,F3,F4] //Fichas del Rojo
[F1,F2,F3,F4] //Fichas del Verde
*/
typedef enum {Amarillo, Azul, Rojo, Verde} tColor; // Amarillo = 0, Azul = 1, Rojo = 2, Verde = 3

//Declaracion de funciones
void pausa();
void cambiarTurno(int& turno);
void tablero();
void iniciar(tJugadores jugadores);

bool hayGanador(int finalJuagdores[4]);
bool esSeguro(int casilla);
bool enCasa(tJugadores jugadores, tColor color);
bool hayPuente(tJugadores jugadores, int casilla);

int tirarDado();
int cuantasEn(tJugadores jugadores, int casilla);

//PROBANDO FUNCIONES



int main(){
    tJugadores jugadores;

    int turno = 4; //Iniciado en 4 para que al cambiar de turno al principio comience en el 1

    int finalJugadores[4] = {0, 0, 0, 0};

    bool inicioJ1, inicioJ2, inicioJ3, inicioJ4;
    bool finalJ1 = 0, finalJ2 = 0, finalJ3 = 0, finalJ4 = 0;

    iniciar(jugadores);

    jugadores[Rojo][1] = 2;
    jugadores[Rojo][2] = 2;

    if (hayPuente(jugadores, 2)){
        cout << "Si";
    }

    /*while (!hayGanador(finalJugadores)){
        cambiarTurno(turno);

        switch (turno){
        case 1:
            //JuegaJugador Amarillo J1
            break;
        
        case 2:
            //JuegaJugador Azul J2
            break;
        
        case 3:
            //JuegaJugador Rojo J3
            break;
        
        case 4:
            //JuegaJugador Verde J4
            break;

        default:
            cout << "\n\nError de turno, por favor reinicie el programa\n\n";
            exit(0);
            break;
        }

        tablero();        
    }*/


    return 0;
}

//Declaracion Voids
void pausa(){ //FUNCIONA
   cout << "\n\nPulsa Intro para continuar...\n\n";
   cin.ignore();
}

void cambiarTurno(int& turno){ // FUNCIONA
    if(turno == 4){
        turno = 0;
    }
    turno++;
}

void iniciar(tJugadores jugadores){ // FUNCIONA
    for (int i = 0; i < NUMERO_DE_JUGADORES; i++){
        for (int x = 0; x < NUMERO_DE_CASILLAS; x++){
            jugadores[i][x] = -1;
        }
    }
}

//Declaracion Ints
int tirarDado(){ //FUNCIONA

	int dado, resultado = 0;
    srand(time(NULL));
	
    dado = 1 + rand() % (7-1);

	cout<<"El resultado de tu dado es: " << dado;
	
	resultado += dado;

	if (dado == 6) {
		cout << "\nEnhorabuena, vuelves a tirar\n";
		
        pausa();

        dado = 1 + rand() % (7-1);
        cout<<"El resultado de tu dado es: " << dado;

		resultado += dado;

		if (dado == 6) {
			cout << "\nOtro 6 madre mia, estas onfire. Anda vuelves a tirar\n";
			
            pausa();

            dado = 1 + rand() % (7-1);
            cout<<"El resultado de tu dado es: " << dado;

			resultado += dado;

			if (dado == 6) {
				cout << "A tu casa";
				resultado = 0;
			}
		}
	}

	return resultado;
}

int cuantasEn(tJugadores jugadores, int casilla){
    int contador = 0;
    for (int i = 0; i < NUMERO_DE_JUGADORES; i++){
        for (int x = 0; x < NUMERO_DE_CASILLAS; x++){
            if (jugadores[i][x] == casilla){
                contador++;
            }
        }
    }
    cout << contador;
    return contador;
}


//Declaracion Bools
bool hayGanador(int finalJugadores[4]){
    for (int i = 0; i < NUMERO_DE_JUGADORES; i++){
        if (finalJugadores[i] == 1){
            return true;
        }
    }
    return false;
}

bool esSeguro(int casilla){ //FUNCIONA
	if (casilla == 0 || casilla == 5 || casilla == 12 || casilla == 17 || casilla == 22 || casilla == 29 || casilla == 34 || casilla == 39 || casilla == 46 || casilla == 51 || casilla == 56 || casilla == 63) {
		return true;
	}
	else {
		return false;
	}
}

bool enCasa(tJugadores jugador, tColor color){ // FUNCIONA
    for (int x = 0; x < 4; x++){
        if (jugador[color][x] == -1){
            cout << "Esta en casa";
            return true;
        }
    }
    return false;
}

bool hayPuente(tJugadores jugadores, int casilla){ // NO FUNCIONA
    if (cuantasEn(jugadores, casilla) == 2){
        return true;
    }

    return false;
}