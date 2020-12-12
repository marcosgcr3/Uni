#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>

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
typedef enum {Amarillo, Azul, Rojo, Verde, Blanco} tColor; // Amarillo = 0, Azul = 1, Rojo = 2, Verde = 3, Blanco = 4

//Declaracion de funciones
void pausa();
void cambiarTurno(int& turno);
void tablero();
void iniciar(tJugadores jugadores);
void setColor(tColor color);

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


    cuantasEn2(jugadores, Amarillo, 3)
     

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

void setColor(tColor color){ // FUNCIONA 
    switch (color) {
    case Amarillo:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
        break;

    case Azul:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
        break;

    case Rojo:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        break;

    case Verde:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        break;

    case Blanco:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    default:
        break;
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


void tablero(tJugadores jugadores) { //Los colores de la consola lo hemos sacado de internet
	for (int x = 0; x < 68; x++){
		cout << x / 10;
	}
	cout<< "\n";
	for(int x = 0; x < 68; x++){
		cout << x % 10;

	}
	cout<< "\n";
    for (int x = 0; x < 68; x++){
    	cout << '>';
	
	
	}
	cout<< "\n";
    cout<< "\n";
    
    
    for (int x = 0; x <= 67; x++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (seguras(x)) {
			cout << "O";
		}

		else {
			cout << "-";
		}
	}
	cout << "\n";
	for (int x = 0; x <= 67; x++) {

        for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
            if (jugadores[Amarillo)[i] == x){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                cout << i;
            }
            
        }
    }
        if (pos2 == x) {
			if(j2 == 'V'){
				SetColor(Amarillo)
				cout<<j2;
			}
			else if (j2 == 'R'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
				cout<<j2;
			}
			else if ( j2 == 'A'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE);
				cout<<j2;
			}
			else if (j2 == 'M'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);
				cout<<j2;
			}
		}
		else {
			cout << " ";
		}
	}
	
	
	cout << "\n";
    
    for (int x = 0; x < 65; x++){

        if(x == 0){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);
            cout<< "V";
        }
        if(x == 49){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
            cout<<"V";
        }
        if(x == 16){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE);
            cout<<"V";

        }
        if(x == 32){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
            cout<<"V";
        }


        else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    	    cout << '>';
        }
	
	}
    cout<<"\n";
	
}
