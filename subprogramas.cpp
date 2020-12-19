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
typedef enum {Amarillo, Azul, Rojo, Verde, Gris, Ninguno} tColor; // Amarillo = 0, Azul = 1, Rojo = 2, Verde = 3, Blanco = 4
typedef tColor tCasillas[NUMERO_DE_CASILLAS];

// Declaracion de funciones
void pausa(); // Pausa el programa para 
void cambiarTurno(int& turno); // Cambia el turno
void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, int& turno); // Inicializa las fichas en -1, las calles en Ninguno y el primer turno
void cambiarColor(tColor color); // Cambia el color de la terminal en Windows en funcion del tipo de color introducido
void tablero(const tJugadores jugadores, const tCasillas calle1, const tCasillas calle2); // Muestra el tablero

bool hayGanador(int finalJuagdores[4]); // Determina si alguno de los jugadores ha ganado
bool esSeguro(int casilla); // Determina si una casilla es segura
bool enCasa(tJugadores jugadores, tColor color); // Determina si un jugador tiene alguna ficha en casa
bool hayPuente(int casilla, const tCasillas calle1, const tCasillas calle2); // Determina si hay un puente en una casilla
bool todasEnMeta(const tJugadores jugadores, tColor color); // Determina si un jugador tiene todas sus casillas en meta

int tirarDado(); // Crea un numero aleatorio entre el 1 y el 6 
int cuantasEn(const tJugadores jugadores, int casilla, tColor color); // Devuelve el numero de fichas que tiene un jugador en una casilla
int colorAJugador(tColor color); // Devuelve el numero del jugador 
int zanataJugador(tColor jugador); // Devuelve la casilla de zanata de un jugador
int salidaJugador(tColor jugador); // Devuelve la casilla de salida de un jugador
int primeraEn(const tJugadores jugadores, int casilla, tColor color); // Devuleve el menor indice de las fichas del jugador en una casilla
int segundaEn(const tJugadores jugadores, int casilla, tColor color); // Devuelve el mayor indice de las fichas del jugador en una casilla

// PROBANDO FUNCIONES


// TERMINANDO DE PROBAR FUNCIONES


int main(){
    tJugadores jugadores;
    tCasillas calle1, calle2;
    int turno, jugador;
    int finalJugadores[4] = {0, 0, 0, 0};

    iniciar(jugadores, calle1, calle2, turno);

    int prueba;
    // COMIENZAN COMANDOS DE PRUEBA


    jugadores[Amarillo][0] = 108;
    jugadores[Amarillo][1] = 108;
    jugadores[Amarillo][2] = 108;
    jugadores[Amarillo][3] = 108;

    if(todasEnMeta(jugadores, Amarillo)){
        cout << "Si";
    }
    else cout << "no";
    
    //tablero(jugadores, calle1, calle2);

    // FINALIZAN COMANDOS DE PRUEBA

    // Bucle principal
    /*while (!hayGanador(finalJugadores)){
        cambiarTurno(turno);
        switch (turno){
        case 1:
            jugador = Amarillo;
            //JuegaJugador Amarillo J1
            break;
        
        case 2:
            jugador = Azul;
            //JuegaJugador Azul J2
            break;
        
        case 3:
            jugador = Rojo;
            //JuegaJugador Rojo J3
            break;
        
        case 4:
            jugador = Verde;
            //JuegaJugador Verde J4
            break;
        default:
            cout << "\n\nError de turno, por favor reinicie el programa\n\n";
            exit(0);
            break;
        }
        tablero(jugadores, calle1, calle2);        
    }*/


    return 0;
}

// VOIDS
void pausa(){ // FUNCIONA
   cout << "\n\nPulsa Intro para continuar...\n\n";
   cin.ignore();
}

void cambiarTurno(int& turno){ // FUNCIONA
    if(turno == 4){
        turno = 0;
    }
    turno++;
}

void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, int& turno){ // FUNCIONA
    srand(time(NULL));
    turno = 1 + rand() % (4-1);

    for (int i = 0; i < NUMERO_DE_JUGADORES; i++){
        for (int x = 0; x < NUMERO_DE_FICHAS; x++){
            jugadores[i][x] = -1;
        }
    }
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        calle1[i] = Ninguno;
        calle2[i] = Ninguno;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); // Pone el fondo en blanco

    cambiarColor(Gris);    
}

void cambiarColor(tColor color){ // FUNCIONA 
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
    
    case Gris:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;

    default:
        break;
    }
}

void tablero(const tJugadores jugadores, const tCasillas calle1, const tCasillas calle2){ // FUNCIONA
    int casilla, ficha;
    tColor jugador;

    cout << "\x1b[2J\x1b[H";
    cambiarColor(Gris);
    cout << endl;

    //Previos
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        cout << i / 10;
    }
    cout << endl;
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        cout << i % 10;
    }
    cout << endl;

    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        cout << ">";
    }
    cout << endl;

    // Calle2
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        cambiarColor(calle2[i]);
        if (calle2[i] != Ninguno){
            cout << segundaEn(jugadores, i, calle2[i]) + 1;
        }
        else {
            cout << " ";
        }
        cambiarColor(Gris);
    }
    cout << endl;

    // Mediana
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        if (esSeguro(i)){
            cout << "O";
        }
        else{
            cout << "-";
        }
    }
    cout << endl;

    // Calle1
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        cambiarColor(calle1[i]);
        if (calle1[i] != Ninguno){
            cout << segundaEn(jugadores, i, calle1[i]) + 1;
        }
        else {
            cout << " ";
        }
        cambiarColor(Gris);
    }
    cout << endl;

    jugador = Amarillo;
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++)
        if (i == zanataJugador(jugador)) {
            cambiarColor(jugador);
            cout << "V";
            cambiarColor(Gris);
        }
        else if (i == salidaJugador(jugador)) {
            cambiarColor(jugador);
            cout << "^";
            cambiarColor(Gris);
            jugador = tColor(int(jugador) + 1);
        }
        else
            cout << '>';
    cout << endl;

    for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
        casilla = 0;
        jugador = Amarillo;
        cambiarColor(jugador);
        while (casilla < NUMERO_DE_CASILLAS){
            if (casilla == zanataJugador(jugador)){
                ficha = primeraEn(jugadores, 101 + i, jugador);
                if (ficha != -1){
                    cout << ficha + 1;
                    if (cuantasEn(jugadores, 101 + i, jugador) > 1){
                        ficha = segundaEn(jugadores, 101 + i, jugador);
                        if (ficha != -1){
                            cout << ficha + 1;
                        }
                        else{
                            cout << "V";
                        }
                    }
                    else {
                        cout << "V";
                    }
                }
                else {
                    cout << "VV";
                }
                casilla++;
            }
            else if (casilla == salidaJugador(jugador)) {
                if (jugadores[jugador][i] == -1){
                    cout << i + 1;
                }
                else {
                    cout << "^";
                }
                jugador = tColor(int(jugador) + 1);
                cambiarColor(jugador);
            }
            else{
                cout << " ";
            }
            casilla++;
        }
        cout << endl;
   }
}

// INTS
int tirarDado(){ // FUNCIONA
	int dado = 0;
    srand(time(NULL));
	
    dado = 1 + rand() % (7-1);

	cout<<"El resultado de tu dado es: " << dado;
	
	return dado;
}

int cuantasEn(const tJugadores jugadores, int casilla, tColor color){ // FUNCIONA
    int contador = -1;
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        if (jugadores[color][i] == casilla) contador++;
    }
    return contador;
}

int colorAJugador(tColor color){ // FUNCIONA
    int jugador = color;
    return jugador + 1;
}

int zanataJugador(tColor jugador){ // FUNCIONA
    switch (jugador){
    case Amarillo:
        return 0;
        break;
    
    case Azul:
        return 17;
        break;

    case Rojo:
        return 34;
        break;

    case Verde:
        return 51;
        break;

    default:
        return 0;
        break;
    }
}

int salidaJugador(tColor jugador){ // FUNCIONA
    switch (jugador){
    case Amarillo:
        return 5;
        break;
        
    case Azul:
        return 22;
        break;
        
    case Rojo:
        return 39;
        break;
        
    case Verde:
        return 56;
        break;
        
    default:
        return 0;
        break;
    }
}

int primeraEn(const tJugadores jugadores, int casilla, tColor color){ // FUNCIONA
    for (int i = 0; i < NUMERO_DE_FICHAS; i++){
        if (jugadores[color][i] == casilla){
            return i;
        }
    }
    return -1;
}

int segundaEn(const tJugadores jugadores, int casilla, tColor color){ // FUNCIONA
    for (int i = 3; i >= 0; i--){
        if (jugadores[color][i] == casilla) {
            return i;
        }
    }
    return -1;
}

// BOOLS
bool hayGanador(int finalJugadores[4]){ // CREO QUE FUNCIONA
    for (int i = 0; i < NUMERO_DE_JUGADORES; i++){
        if (finalJugadores[i] == 1){
            return true;
        }
    }
    return false;
}

bool hayPuente(int casilla, const tCasillas calle1, const tCasillas calle2){ // FUNCIONA
    return calle1[casilla] != Ninguno && (calle1[casilla] == calle2[casilla]);
}

bool esSeguro(int casilla){ //FUNCIONA
    return casilla == 0 || casilla == 5 || casilla == 12 || casilla == 17 || casilla == 22 || casilla == 29 || casilla == 34 || casilla == 39 || casilla == 46 || casilla == 51 || casilla == 56 || casilla == 63;
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

bool todasEnMeta(const tJugadores jugadores, tColor color){ // FUNCIONA
    return jugadores[color][0] == 108 && jugadores[color][1] == 108 && jugadores[color][2] == 108 && jugadores[color][3] == 108;
}