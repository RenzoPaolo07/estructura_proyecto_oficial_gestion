//Codigo para las respuestas del informe
	//Primero definimos la estructura Persona, que sera la base del arbol:
#include <iostream>
#include <string>
using namespace std;

struct Persona {
    int anioNacimiento;
    string nombre;
    Persona* izquierda;
    Persona* derecha;
};

//1. ¿Que informacion se debe almacenar en cada nodo? - Ejemplo:
	Persona* crearPersona(int anio, string nombre) {
	    Persona* nueva = new Persona;
	    nueva->anioNacimiento = anio;
	    nueva->nombre = nombre;
	    nueva->izquierda = NULL;
	    nueva->derecha = NULL;
	    return nueva;
	}

//2. ¿Como insertar y eliminar miembros del arbol sin romper su estructura? - Ejemplos:
	//Insercion:
	void insertarPersona(Persona*& raiz, int anio, string nombre) {
	    if (raiz == NULL) {
	        raiz = crearPersona(anio, nombre);
	    } else if (anio < raiz->anioNacimiento) {
	        insertarPersona(raiz->izquierda, anio, nombre);
	    } else if (anio > raiz->anioNacimiento) {
	        insertarPersona(raiz->derecha, anio, nombre);
	    } else {
	        cout << "Ya existe una persona con ese año.\n";
	    }
	}
	
	//Eliminacion solo en caso de una hoja:
	void eliminarHoja(Persona*& raiz, int anio) {
    if (raiz == NULL) return;
    
    if (anio < raiz->anioNacimiento) {
        eliminarHoja(raiz->izquierda, anio);
    } else if (anio > raiz->anioNacimiento) {
        eliminarHoja(raiz->derecha, anio);
    } else {
        // Solo eliminamos si es hoja
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz;
            raiz = NULL;
            cout << "Persona eliminada.\n";
        } else {
            cout << "No se puede eliminar, no es una hoja.\n";
        	}
    	}
	}

//3. ¿Que metodos permiten recorrer el arbol para visualizar la genealogia? - Ejemplos:
	//Inorden:
	void inorden(Persona* raiz) {
	    if (raiz != NULL) {
	        inorden(raiz->izquierda);
	        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
	        inorden(raiz->derecha);
	    }
	}
	//Preorden:
	void preorden(Persona* raiz) {
	    if (raiz != NULL) {
	        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
	        preorden(raiz->izquierda);
	        preorden(raiz->derecha);
	    }
	}
	//Postorden:
	void postorden(Persona* raiz) {
	    if (raiz != NULL) {
	        postorden(raiz->izquierda);
	        postorden(raiz->derecha);
	        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
	    }
	}
	
//4.¿Como determinar si un miembro pertenece a una rama especifica? - Ejemplo:
	bool buscarPersona(Persona* raiz, int anio) {
	    if (raiz == NULL) return false;
	
	    if (anio == raiz->anioNacimiento) return true;
	    else if (anio < raiz->anioNacimiento) return buscarPersona(raiz->izquierda, anio);
	    else return buscarPersona(raiz->derecha, anio);
	}

