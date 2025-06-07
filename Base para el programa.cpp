#include <iostream>
#include <string>
using namespace std;

const int TAMANO_TABLA = 5;

struct Estudiante {
	int id;
	string nombre;
	bool ocupado;
};

int funcionHash(int id){
	return id % TAMANO_TABLA;
}

struct TablaHash {
	Estudiante tabla[TAMANO_TABLA];
};

void insertar (TablaHash& tablaHash, int id, string nombre){
	int indice = funcionHash(id);
	tablaHash.tabla[indice].id = id;
	tablaHash.tabla[indice].nombre=nombre;
	tablaHash.tabla[indice].ocupado = true;
	cout<<"Estudiante "<<nombre<<" insertado en el índice "<<indice<<endl;
}

string buscar(const TablaHash& tablaHash, int id){
	int indice = funcionHash(id);
	if (tablaHash.tabla[indice].ocupado && tablaHash.tabla[indice].id == id){
		return tablaHash.tabla[indice].nombre;
	}
	return "Estudiante no encontrado.";
}

void mostrar(const TablaHash& tablaHash){
	for (int i=0; i< TAMANO_TABLA; i++){
		if (tablaHash.tabla[i].ocupado){
			cout<<"Indice "<<i<<": ID: "<<tablaHash.tabla[i].id
				<<" -> "<<tablaHash.tabla[i].nombre<<endl;
		} else {
			cout<<"Indice "<<i<<": Vacio"<<endl;
		}
	}
}

void mostrarMenu(){
	cout<<"\n--- Menú de Opciones---\n";
	cout<<"1. Insertar estudiante\n";
	cout<<"2. Buscar estudiante\n";
	cout<<"3. Mostrar tabla hash\n";
	cout<<"4. Salir\n";
	cout<<"Elija una opcion: ";
}

int main(){
	setlocale(LC_CTYPE,"Spanish");
	TablaHash tablaHash={};
	
	int opcion;
	int id;
	string nombre;
	//Comentario de ppruebaaaaaaaa
	do {
		mostrarMenu();
		cin>>opcion;
		
		switch (opcion){
			case 1:
				cout<<"Ingrese el ID del estudiante: ";
				cin>> id;
				cin.ignore();
				cout<<"Ingrese el nombre del estudiante: ";
				getline(cin,nombre);
				insertar(tablaHash, id, nombre);
				break;
			case 2:
				cout<<"Ingrese el ID del estudiante a buscar: ";
				cin>>id;
				cout<<"Resultado de la busqueda: "<<buscar(tablaHash, id)<<endl;
				break;
			case 3:
				mostrar(tablaHash);
				break;
			case 4:
				cout<<"Hasta luego!"<<endl;
				break;
			default:
				cout<<"Opcion no válida. Intente nuevamente\n";
		}
	} while (opcion !=4);
	return 0;
}

