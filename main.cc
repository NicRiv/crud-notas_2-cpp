#include <iostream>
#include <string>
// #include <fstream> // archivos
// #include <algorithm> // find
// #include <conio.h> // getch()

#include "funciones.h"

using namespace std;

/*
	BD: .txt
	Encriptar base de datos
	Color a la consola
	Implementacion de clases?
*/

void NP();
void MENU();
string tipear();

int main () {
	int input = -1;
	string val;
	int nota;

	NP();
	MENU();
	val = tipear();
	input = stoi(val);

	while (input != 0) {
		
		switch (input) {
			case 1:
				// head
				NP();
				MENU();
				// body
				crear_nota();
				// footer
				cout << "\n" << "<< [9] Menu, [0] Salir" << "\n";
				val = tipear();
				input = stoi(val);
				break;
			case 2:
				// head
				NP();
				MENU();
				// body
				ver_notas();
				// footer
				cout << "\n" <<"<< [9] Menu, [0] Salir" << "\n";
				val = tipear();
				input = stoi(val);
				break;
			case 3:
				// head
				NP();
				MENU();
				// body
				cout << "\n" << "Ingresar id de la nota" << "\n";
				val = tipear();
				nota = stoi(val);
				ver_nota(nota);
				// footer
				cout << "\n" << "<< [9] Menu, [0] Salir" << "\n";
				val = tipear();
				input = stoi(val);
				break;
			case 4:
				// head
				NP();
				MENU();
				// body
				cout << "\n" << "Ingresar id de la nota a editar" << "\n";
				val = tipear();
				nota = stoi(val);
				editar_nota(nota);
				// footer
				cout << "\n" << "<< [9] Menu, [0] Salir" << "\n";
				val = tipear();
				input = stoi(val);
				break;
			case 5:
				// head
				NP();
				MENU();
				// body
				cout << "\n" << "Ingresar id de la nota a borrar" << "\n";
				val = tipear();
				nota = stoi(val);
				borrar_nota(nota);
				cout << "\n" << "* La nota (" << nota << ") ha sido borrada *" << "\n";
				// footer
				cout << "\n" << "<< [9] Menu, [0] Salir" << "\n";
				val = tipear();
				input = stoi(val);
				break;
			case 9:
				// head
				NP();
				MENU();
				// footer
				val = tipear();
				input = stoi(val);
				break;
			default:
				cout << "\n" << "* Opcion no valida *" << "\n";
				cout << "\n" << "<< [9] Menu, [0] Salir" << "\n";
				val = tipear();
				input = stoi(val);
				break;
		}
	}

	return 0;
}

// Funciones

void NP () {
	cout << "\033[2J\033[H";	
}

string tipear () {
	string entrada;
	cout << "> ";
	getline(cin, entrada);
	return entrada;
}

void MENU () {
	cout << "---------------" << "\n";
	cout << "-----CRUD------" << "\n";
	cout << "---------------" << "\n";
	cout << "[1] Crear nota" << "\n";
	cout << "[2] Ver notas" << "\n";
	cout << "[3] Ver nota {ingresar id}" << "\n";
	cout << "[4] Editar nota" << "\n";
	cout << "[5] Borrar nota" << "\n";
	cout << "[0] Salir" << "\n";	
}