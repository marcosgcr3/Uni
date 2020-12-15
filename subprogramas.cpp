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
typedef tColor tCasillas[68];

//Declaracion de funciones
void pausa(); // Pausa el programa para 
void cambiarTurno(int& turno); // Cambia el turno
void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, int& turno); // Inicializa las posiciones de todos los jugadores en -1
void cambiarColor(tColor color); // Cambia el color de la terminal en Windows en funcion del tipo de color introducido

bool hayGanador(int finalJuagdores[4]); // Determina si alguno de los jugadores ha ganado
bool esSeguro(int casilla); // Determina si una casilla es segura
bool enCasa(tJugadores jugadores, tColor color); // Determina si un jugador tiene alguna ficha en casa
bool hayPuente(int casilla, tCasillas calle1, tCasillas calle2); // Determina si hay un puente en una casilla

int tirarDado(); // Crea un numero aleatorio entre el 1 y el 6 
int cuantasEn(tJugadores jugadores, int casilla, tColor color); // Devuelve el numero de fichas que tiene un jugador en una casilla
int colorAJugador(tColor color); // Devuelve el numero del jugador 
int zanataJugador(tColor jugador); // Devuelve el numero de la zanata de jugador

//PROBANDO FUNCIONES
/*void tablero(const tJugadores jugadores, tCasillas calle1, tCasillas calle2){
    int casilla, ficha, jugador;
    cout << "\x1b[2J\x1b[H";
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++)
      cout << i / 10;
   cout << endl;
   for (int i = 0; i < NUMERO_DE_CASILLAS; i++)
      cout << i % 10;
   cout << endl;
   // Borde superior...
   for (int i = 0; i < NUMERO_DE_CASILLAS; i++)
      cout << '>';
   cout << endl;
   for (int i = 0; i < NUMERO_DE_CASILLAS; i++) {
      setColor(calle2[i]);
      if (calle2[i] != Ninguno)
         //cout << primeraEn(jugadores[colorAJugador(calle2[i])], i) + 1;
      else
         cout << ' ';
      setColor(Gris);
}*/


/*void tablero(const tCasillas calle1, const tCasillas calle2) { //Los colores de la consola lo hemos sacado de internet
    for (int x = 0; x < NUMERO_DE_CASILLAS; x++) {
        cout << x / 10;
    }
    cout << "\n";
    for (int x = 0; x < NUMERO_DE_CASILLAS; x++) {
        cout << x % 10;
    }
    cout << "\n";
    for (int x = 0; x < NUMERO_DE_CASILLAS; x++) {
        cout << '>';
    }
    cout << "\n";
    cout << "\n";
    
    //Falta otro carril  CALLE2
    
    for(int x = 0; x < NUMERO_DE_CASILLAS; x++){ //Carril Central
        if(esSeguro(x)){
            cout << "O";
        }
        else cout << "-";
    }
    cout << "\n";
    //calle1
    for (int x = 0; x < NUMERO_DE_CASILLAS; x++) {
        for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
            if (jugadores[Amarillo][i] == x){
            cambiarColor(Amarillo);
            cout << i;
            cambiarColor(Blanco);
            }
        }
        for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
            if (jugadores[Azul][i] == x){
            cambiarColor(Azul);
            cout << i;
            cambiarColor(Blanco);
            }
        }
        for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
            if (jugadores[Rojo][i] == x){
            cambiarColor(Rojo);
            cout << i;
            cambiarColor(Blanco);
            }
        }
        for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
            if (jugadores[Verde][i] == x){
            cambiarColor(Verde);
            cout << i;
            cambiarColor(Blanco);
            }
        }
    }
    cout << "\n";/*
    for (int x = 0; x <= 67; x++) {
        for (int i = 0; i < NUMERO_DE_FICHAS; i++) {
            if (jugadores[Amarillo)[i] == x){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            cout << i;
            }
        }
    }
    if (pos2 == x) {
        if (j2 == 'V') {
            //SetColor(Amarillo)
                cout << j2;
        }
        else if (j2 == 'R') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            cout << j2;
        }
        else if (j2 == 'A') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            cout << j2;
        }
        else if (j2 == 'M') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            cout << j2;
        }
    }
    else {
        cout << " ";
    }
    for (int x = 0; x < 65; x++) {
        if (x == 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "V";
        }
        if (x == 49) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            cout << "V";
        }
        if (x == 16) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            cout << "V";
        }
        if (x == 32) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            cout << "V";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << '>';
        }
    }*/

//TERMINANDO DE PROBAR FUNCIONES


int main(){
    tJugadores jugadores;
    tCasillas calle1, calle2;
    int turno, jugador;
    int finalJugadores[4] = {0, 0, 0, 0};
    
    jugadores[Amarillo][0] = -1;
    jugadores[Amarillo][1] = -1;
    jugadores[Amarillo][2] = 1;
    jugadores[Amarillo][3] = 1;
    jugadores[Azul][1] = 6;
    jugadores[Verde][3] = 8;

    cuantasEn(jugadores, -1, Amarillo);
    
    jugador = colorAJugador(Amarillo);
    cout << jugador;

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

void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, int& turno){
    srand(time(NULL));
    turno = 1 + rand() % (4-1);

    for (int i = 0; i < NUMERO_DE_JUGADORES; i++){
        for (int x = 0; x < NUMERO_DE_CASILLAS; x++){
            jugadores[i][x] = -1;
        }
    }
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        calle1[i] = Ninguno;
        calle2[i] = Ninguno;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE, BACKGROUND_GREEN, BACKGROUND_RED); // Pone el fondo en blanco

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

void aCasa(tJugadores jugadores, int casilla, tCasillas calle1, tCasillas calle2){ //NO FUNCIONA
    // jugadores[calle2[casilla]][]
}

//Declaracion Ints
int tirarDado(){ //FUNCIONA
	int dado = 0;
    srand(time(NULL));
	
    dado = 1 + rand() % (7-1);

	cout<<"El resultado de tu dado es: " << dado;
	
	return dado;
}

int cuantasEn(tJugadores jugadores, int casilla, tColor color){ //FUNCIONA
    int contador = -1;
    for (int i = 0; i < NUMERO_DE_CASILLAS; i++){
        if (jugadores[color][i] == casilla) contador++;
    }
    return contador;
}

int colorAJugador(tColor color){
    int jugador = color;
    return jugador + 1;
}

int zanataJugador(tColor jugador){
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
        break;
    }
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

bool hayPuente(int casilla, tCasillas calle1, tCasillas calle2){ //ESTO HAY QUE VERLO
    return calle1[casilla] != Ninguno && calle2[casilla] != Ninguno;
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
