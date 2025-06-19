#include <iostream>
#include <string>
using namespace std;

// Estructura del nodo
struct Persona {
    int anioNacimiento;
    string nombre;
    Persona* izquierda;
    Persona* derecha;
};


Persona* crearPersona(int anio, string nombre) {
    Persona* nueva = new Persona;
    nueva->anioNacimiento = anio;
    nueva->nombre = nombre;
    nueva->izquierda = NULL;
    nueva->derecha = NULL;
    return nueva;
}


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


bool buscarPersona(Persona* raiz, int anio) {
    if (raiz == NULL) return false;
    if (anio == raiz->anioNacimiento) return true;
    else if (anio < raiz->anioNacimiento) return buscarPersona(raiz->izquierda, anio);
    else return buscarPersona(raiz->derecha, anio);
}

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



// Recorrido INORDEN: Funcion de m?s antiguo a m?s reciente
void inorden(Persona* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
        inorden(raiz->derecha);
    }
}

// Recorrido PREORDEN: Se usa para jerarqu?a generacional
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

//Mostrar jerarquía de forma visual
void mostrarJerarquia(Persona* raiz, int nivel = 0) {
    if (raiz != NULL) {
        mostrarJerarquia(raiz->derecha, nivel + 1);
        for (int i = 0; i < nivel; i++) cout << "   ";
        cout << "|-- " << raiz->nombre << " (" << raiz->anioNacimiento << ")\n";
        mostrarJerarquia(raiz->izquierda, nivel + 1);
    }
}

// Menú 
void menu() {
    cout << "\n--- Árbol Genealógico (ABB) ---\n";
    cout << "1. Insertar persona\n";
    cout << "2. Buscar persona\n";
    cout << "3. Eliminar hoja\n";
    cout << "4. Mostrar inorden\n";
    cout << "5. Mostrar preorden\n";
    cout << "6. Mostrar postorden\n";
    cout << "7. Visualizar jerarquía\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opción: ";
}


int main() {
    setlocale(LC_CTYPE, "Spanish");
    Persona* raiz = NULL;
    int opcion, anio;
    string nombre;

    do {
        menu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese año de nacimiento: ";
                cin >> anio;
                insertarPersona(raiz, anio, nombre);
                break;
            case 2:
                cout << "Ingrese año a buscar: ";
                cin >> anio;
                if (buscarPersona(raiz, anio))
                    cout << "Persona encontrada.\n";
                else
                    cout << "No se encontró a la persona.\n";
                break;
            case 3:
                cout << "Ingrese año a eliminar (solo si es hoja): ";
                cin >> anio;
                eliminarHoja(raiz, anio);
                break;
            case 4:
                cout << "\n--- Recorrido Inorden (IRD) ---\n";
                inorden(raiz);
                break;
            case 5:
                cout << "\n--- Recorrido Preorden (RID) ---\n";
                preorden(raiz);
                break;
            case 6:
                cout << "\n--- Recorrido Postorden (IDR) ---\n";
                postorden(raiz);
                break;
            case 7:
                cout << "\n--- Visualización Jerárquica del Árbol ---\n";
                mostrarJerarquia(raiz);
                break;
            case 8:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}

