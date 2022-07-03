// Definiciones
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Remplazo de la funcion substr()
string sub_cadena (string cadena, int m, int M); // declaracion
int buscar (string cadena, string palabra); // declaracion, remplazo find()


// FUNCIONES

void crear_nota() {
	// LEER DB
	ifstream db;
	db.open("DB.txt");

	// Si falla abrir archivo
	if (db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	string ln_id;
	getline(db, ln_id);
	int ID = stoi(ln_id);

	string linea, datos;
	datos += to_string(ID+1) + "\n"; // genera id

	while (getline(db, linea)) {
		if(linea[0] != ID) {
			datos += linea + "\n";
		}
	}

	db.close();

	// CREAR NUEVA NOTA
	string titulo, contenido, nueva_nota;

	string clave_id = ";id:";
	string clave_tit = ";titulo:";
	string clave_cont = ";contenido:";

	cout << "Ingresar Titulo: ";
	getline(cin, titulo);

	cout << "Ingresar contenido: ";
	getline(cin, contenido);

	nueva_nota = clave_id + to_string(ID+1) + clave_tit + titulo + clave_cont + contenido;

	datos += nueva_nota;

	// GUARDAR N_DB
	ofstream n_db;
	n_db.open("DB.txt");
	// Si falla abrir archivo
	if (n_db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}
	n_db << datos;
	n_db.close();
}

void ver_notas() {
	ifstream db;
	db.open("DB.txt");

	// Si falla abrir archivo
	if (db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	string linea;
	string clave_id = ";id:";
	string clave_tit = ";titulo:";
	string clave_cont = ";contenido:";
	uint16_t p_id, p_tit, p_cont;
	int ID;
	string TIT, CONT;

	while (getline(db, linea)) {
		// primera linea la salto
		if (linea.length() > 5) {
			cout << "------------------" << "\n";

			p_id = buscar(linea, clave_id);
			p_tit = buscar(linea, clave_tit);
			p_cont = buscar(linea, clave_cont);

			// _id
			int m_I = p_id + clave_id.length();
			int M_I = p_tit;
			ID = stoi(sub_cadena(linea, m_I, M_I));
			cout <<"_id:  " << ID << "\n";

			// titulo
			int m_T = p_tit + clave_tit.length();
			int M_T = p_cont;
			TIT = sub_cadena(linea, m_T, M_T);
			cout << "TITULO:  " << TIT << "\n";

			// contenido
			int m_C = p_cont + clave_cont.length();
			int M_C = linea.length();
			CONT = sub_cadena(linea, m_C, M_C);
			cout << "CONTENIDO:  " << CONT << "\n" ;

			cout << "==================" << "\n";
		}
	}

	db.close();
}

void ver_nota(uint32_t nota) {
	ifstream db;
	db.open("DB.txt");

	// Si falla abrir archivo
	if (db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	string linea;
	string clave_id = ";id:";
	string clave_tit = ";titulo:";
	string clave_cont = ";contenido:";
	uint16_t p_id, p_tit, p_cont;
	int ID;
	string TIT, CONT;

	while (getline(db, linea)) {
		if (linea.length() > 5) {
			p_id = linea.find(clave_id);
			p_tit = linea.find(clave_tit);
			p_cont = linea.find(clave_cont);
			// id
			ID = stoi(linea.substr(p_id + clave_id.length(), p_tit - (p_id + clave_id.length())));


			if (ID == nota) {
				cout << "------------------" <<endl;

				// muestra id
				cout <<"_id:  " << ID<<endl;

				// titulo
				TIT = linea.substr(p_tit + clave_tit.length(), p_cont - (p_tit + clave_tit.length()));
				cout << "TITULO:  " << TIT << endl;

				// contenido
				CONT = linea.substr(p_cont + clave_cont.length(), linea.length() - (p_cont + clave_cont.length()));
				cout << "CONTENIDO:  " << CONT << endl ;

				cout << "==================" << endl;
			}
		}
	}

	db.close();		
}

void editar_nota(uint32_t nota) {
	ifstream db;
	db.open("DB.txt");

	// Si falla abrir archivo
	if (db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	string ln_id;
	getline(db, ln_id);
	int ID = stoi(ln_id);

	string linea, datos;
	datos += to_string(ID) + "\n"; // genera id

	string clave_id = ";id:";
	int p_id, id_nota;

	string clave_tit = ";titulo:";
	string clave_cont = ";contenido:";
	uint16_t p_tit, p_cont;
	string TIT, CONT;

	while (getline(db, linea)) {
		p_id = buscar(linea, clave_id);
		p_tit = buscar(linea, clave_tit);
		p_cont = buscar(linea, clave_cont);

		int m_I = p_id + clave_id.length();
		int M_I = p_tit;
		id_nota = stoi(sub_cadena(linea, m_I, M_I));

		if (id_nota != nota)
			datos += linea + "\n";
		else {
			// rescatar datos de tit y cont,
			int m_T = p_tit + clave_tit.length();
			int M_T = p_cont;
			TIT = sub_cadena(linea, m_T, M_T);

			// contenido
			int m_C = p_cont + clave_cont.length();
			int M_C = linea.length();
			CONT = sub_cadena(linea, m_C, M_C);
		}
	}
	db.close();

	// CREAR NUEVA NOTA
	string titulo, contenido, nueva_nota;

	cout << "Ingresar Titulo: ";
	// cin >> titulo;
	getline(cin, titulo);
	if (titulo.length() == 0) titulo = TIT;

	cout << "Ingresar contenido: ";
	getline(cin, contenido);
	if (contenido.length() == 0) contenido = CONT;

	nueva_nota = clave_id + to_string(nota) + clave_tit + titulo + clave_cont + contenido;

	datos += nueva_nota;

	// GUARDAR N_DB
	ofstream n_db;
	n_db.open("DB.txt");

	// Si falla abrir archivo
	if (n_db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	n_db << datos;
	n_db.close();
}

void borrar_nota(uint32_t nota) {
	// Obtener db
	ifstream db;

	db.open("DB.txt");
	// Si falla abrir archivo
	if (db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	string linea;
	string nueva_db;

	string clave_id = ";id:";
	string clave_tit = ";titulo:";
	uint16_t p_id, p_tit;
	int ID;

	// int n_id;
	getline(db, linea);
	// n_id = stoi(linea);

	nueva_db += linea + "\n";

	while (getline(db, linea)) {
		// ID = stoi(linea.substr(p_id + clave_id.length(), p_tit - (p_id + clave_id.length())));
		p_id = buscar(linea, clave_id);
		p_tit = buscar(linea, clave_tit);
		int m_I = p_id + clave_id.length();
		int M_I = p_tit;
		ID = stoi(sub_cadena(linea, m_I, M_I));

		if(ID != nota) {
			nueva_db += linea + "\n";
		}
	}

	db.close();

	// Nueva DB
	ofstream n_db;
	n_db.open("DB.txt");
	// Si falla abrir archivo
	if (n_db.fail()) {
		cerr << "Error al abrir base de datos" << endl;
		exit(1);
	}

	n_db << nueva_db;
	n_db.close();
}

// Remplazo de substr()
string sub_cadena (string cadena, int m, int M) {
	// Definicion
	string subcadena;

	for (int i = m; i < M; i++) {
		subcadena += cadena[i];
	}

	return subcadena;
}

int buscar (string cadena, string palabra) {
	int count_p = 0;
	int pos_p;

	for (int i = 0; i < cadena.length(); i++) {
		if (count_p > palabra.length()-1)
			break;
		else { 
			if (cadena[i] == palabra[count_p]) {
				if (count_p == 0) pos_p = i;
				count_p++;
			}
			else {
				count_p = 0;
				pos_p = -1;
				continue;
			}
		}
	}

	return pos_p;
}