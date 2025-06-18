//Codigo para las respuestas del informe parte 2
#include <iostream>
#include <string>
using namespace std;

// Estructura de un nodo del árbol
struct Persona {
    int anioNacimiento;
    string nombre;
    Persona* izquierda;
    Persona* derecha;
};

// Crear un nuevo nodo
	Persona* crearPersona(int anio, string nombre) {
	    Persona* nueva = new Persona;
	    nueva->anioNacimiento = anio;
	    nueva->nombre = nombre;
	    nueva->izquierda = NULL;
	    nueva->derecha = NULL;
	    return nueva;
	}

// Insertar una persona en el árbol
	void insertarPersona(Persona*& raiz, int anio, string nombre) {
	    if (raiz == NULL) {
	        raiz = crearPersona(anio, nombre);
	    } else if (anio < raiz->anioNacimiento) {
	        insertarPersona(raiz->izquierda, anio, nombre);
	    } else if (anio > raiz->anioNacimiento) {
	        insertarPersona(raiz->derecha, anio, nombre);
	    } else {
	        cout << "Ya existe una persona con ese año de nacimiento.\n";
	    }
	}
	
// Buscar una persona por año de nacimiento
	bool buscarPersona(Persona* raiz, int anio) {
	    if (raiz == NULL) return false;
	
	    if (anio == raiz->anioNacimiento) return true;
	    else if (anio < raiz->anioNacimiento) return buscarPersona(raiz->izquierda, anio);
	    else return buscarPersona(raiz->derecha, anio);
	}
	
//Eliminacion de una persona, solo en caso de una hoja:
	void eliminarHoja(Persona*& raiz, int anio) {
    if (raiz == NULL) return;
    
    if (anio < raiz->anioNacimiento) {
        eliminarHoja(raiz->izquierda, anio);
    } else if (anio > raiz->anioNacimiento) {
        eliminarHoja(raiz->derecha, anio);
    } else {
        // Verificamos si es hoja
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz;
            raiz = NULL;
            cout << "Persona eliminada correctamente.\n";
        } else {
            cout << "No se puede eliminar, no es una hoja.\n";
        	}
    	}
	}

// Recorrido INORDEN: Funcion de más antiguo a más reciente
	void inorden(Persona* raiz) {
	    if (raiz != NULL) {
	        inorden(raiz->izquierda);
	        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
	        inorden(raiz->derecha);
	    }
	}
// Recorrido PREORDEN: Se usa para jerarquía generacional
	void preorden(Persona* raiz) {
	    if (raiz != NULL) {
	        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
	        preorden(raiz->izquierda);
	        preorden(raiz->derecha);
	    }
	}
// Recorrido POSTORDEN: Se usa para eliminaciones
	void postorden(Persona* raiz) {
	    if (raiz != NULL) {
	        postorden(raiz->izquierda);
	        postorden(raiz->derecha);
	        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
	    }
	}
	
// Función principal para probar
	int main() {
	    setlocale(LC_CTYPE,"Spanish");
		Persona* raiz = NULL;
	    
	
	    // Inserción de miembros (civilización ficticia solo de ejemplo)
	    insertarPersona(raiz, 1950, "Apu");
	    insertarPersona(raiz, 1980, "Inti");
	    insertarPersona(raiz, 1930, "Manco");
	    insertarPersona(raiz, 1995, "Killa");
	    insertarPersona(raiz, 1970, "Sumaq");
	
	    cout << "\n<--- Árbol Genealógico (Cronológicamente) --->\n";
	    inorden(raiz);
	
	    cout << "\n<--- Buscar año 1980 --->\n";
	    if (buscarPersona(raiz, 1980)) cout << "Persona encontrada.\n";
	    else cout << "No se encontró a la persona.\n";
	
	    cout << "\n<--- Eliminar hoja con año 1995 --->\n";
	    eliminarHoja(raiz, 1995);
	
	    cout << "\n=== Árbol actualizado (Inorden) ===\n";
	    inorden(raiz);
	
	    cout << "\n=== Recorrido Preorden ===\n";
	    preorden(raiz);
	
	    cout << "\n=== Recorrido Postorden ===\n";
	    postorden(raiz);
	
	    return 0;
	}


