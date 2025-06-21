#include <iostream>
#include <string>
using namespace std;

// Estructura del nodo
struct Persona {
    int anioNacimiento;  //Guarda el aÃ±o ingresado
    string nombre; // El nombre de la persona
    Persona* izquierda; //Puntero al hijo o nodo que esta a la izquierda
    Persona* derecha; //Puntero al hijo o nodo que esta a la derecha
};

// FunciÃ³n para crear una nueva persona
Persona* crearPersona(int anio, string nombre) {
    Persona* nueva = new Persona; // Se crea un espacio para la siguiente persona
    nueva->anioNacimiento = anio; //Guarda un nuevo aÃ±o
    nueva->nombre = nombre; // Guarda nombre
    nueva->izquierda = NULL; // No deja nada al lado izquierdo
    nueva->derecha = NULL; //No deja nada al lado derecho
    return nueva; //Devuelve esa nueva persona para insertar en el arbol
}

// FunciÃ³n de Insertacion de Persona 
void insertarPersona(Persona*& raiz, int anio, string nombre) {
    if (raiz == NULL) {  //Condicion que si el Ã¡rbol esta vacio o se llego a un espacio libre, crea a la persona nueva
        raiz = crearPersona(anio, nombre);
    } else if (anio < raiz->anioNacimiento) { // Y si el aÃ±o es menor, se inserta a la persona a la izquierda, por asi decirlo a las personas viejas
        insertarPersona(raiz->izquierda, anio, nombre);
    } else if (anio > raiz->anioNacimiento) { // Y si el aÃ±o es mayor, se inserta a la persona a la derecha, siendo esta mÃ¡s joven.
        insertarPersona(raiz->derecha, anio, nombre);
    } else { //Si ya hay alguien con este mismo aÃ±o, no permitira agregar a esa persona
        cout << "Ya existe una persona con ese aÃ±o de nacimiento.\n"; // Y le tira un mensaje de que ya existe ese individuo
    }
}

// FunciÃ³n de Busqueda de Persona en el Arbol
bool buscarPersona(Persona* raiz, int anio) {
    if (raiz == NULL) return false;  // Si el Ã¡rbol estÃ¡ no se encuentra despues de buscar, no existe
    if (anio == raiz->anioNacimiento) {
    	cout<<"Persona encontrada: "<<raiz->nombre<<"("<<raiz->anioNacimiento<<")\n";
    	return true; // Si el aÃ±o ingresado coincide con el nodo, sÃ­ existe
	}
	
    else if (anio < raiz->anioNacimiento) return buscarPersona(raiz->izquierda, anio); // Si ve que es menor, busca por la izquierda
    else return buscarPersona(raiz->derecha, anio); // Si ve que es mayor, busca por la derecha
}
// Busca el nodo con el aÃ±o mas pequeÃ±o, empezando en un punto dado
Persona* encontrarMinimo(Persona* nodo) {
    while (nodo->izquierda != NULL) // Si existe alguien mas "viejo" sera a la izquierda
        nodo = nodo->izquierda; // Sigue avanzando a la izquierda
    return nodo; // Y retorna al mÃ¡s viejo encontrado
}

//Elimina a una persona del Ã¡rbol segun el aÃ±o ingresado
Persona* eliminarPersona(Persona* raiz, int anio) {
    if (raiz == NULL) return NULL; // Si el Ã¡rbol estÃ¡ vacio o no hay el nodo, n ose hace nada

    if (anio < raiz->anioNacimiento) { // Si el aÃ±o es , seguira buscando por izquierda
        raiz->izquierda = eliminarPersona(raiz->izquierda, anio);
    } else if (anio > raiz->anioNacimiento) {  // Si el aÃ±o es mayor, seguira buscando por la derecha
        raiz->derecha = eliminarPersona(raiz->derecha, anio);
    } else { //Si el aÃ±o coincide, ya se encontro a la persona a eliminar
        // Nodo encontrado
        string nombreEliminado = raiz->nombre;
        if (raiz->izquierda == NULL && raiz->derecha == NULL) { // En este caso si la persona no tiene hijos
        	cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [era hoja]\n";
            delete raiz; // Borra y libera espacio en la memoria
            
            return NULL; // Retorna NULL para quitar el nodo
        } else if (raiz->izquierda == NULL) { // En este caso, si tiene un hijo en la derecha
        	cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [tenía un hijo derecho]\n";
            Persona* temp = raiz->derecha; // Guarda al hijo derecho
            delete raiz; // Elimina el Nodo Raiz
            return temp; // Conecta el hijo derecho con el padre del nodo eliminado
        } else if (raiz->derecha == NULL) { // Ahora si solo  tiene hijo izquierdo
        	cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [tenía un hijo izquierdo]\n";
            Persona* temp = raiz->izquierda; // Guarda el hijo izquiero
            delete raiz; // Elimina el nodo raiz
            return temp; // Conectamos el hijo izquierdo con el padre del nodo eliminado
        } else { 
            // Si tiene dos hijos
            Persona* temp = encontrarMinimo(raiz->derecha); //Busca el nodo con el aÃ±o mÃ¡s pequeÃ±o del subÃ¡rbol derecho
            raiz->anioNacimiento = temp->anioNacimiento; //Remplaza los datos del nodo actual con los del sucesor
            raiz->nombre = temp->nombre;
            raiz->derecha = eliminarPersona(raiz->derecha, temp->anioNacimiento); // Elimina el sucesor que ya copiamos
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [tenía dos hijos, se reemplazó por " << temp->nombre << "]\n";
        }
    }
    return raiz; // Retorna la raiz modificada
}



// Recorrido INORDEN: Funcion de m?s antiguo a m?s reciente
void inorden(Persona* raiz) {
    if (raiz != NULL) { //En caso de que la raiz no este vacia
        inorden(raiz->izquierda); //Usando una llamada recursiva visita al hijo izquierdo
        cout << raiz->nombre << " \t(" << raiz->anioNacimiento << ")\n"; //Luego imprime el actual (raíz)
        inorden(raiz->derecha); //Usando una llamada recursiva visita al hijo derecho
    }
}

// Recorrido PREORDEN: Se usa para jerarquia generacional
void preorden(Persona* raiz) {
    if (raiz != NULL) {
        cout << raiz->nombre << " \t(" << raiz->anioNacimiento << ")\n"; //Primero imprime el actual (raíz)
        preorden(raiz->izquierda); //visita al hijo izquierdo
        preorden(raiz->derecha); //visita al hijo derecho
    }
}

// Recorrido POSTORDEN: Se usa para eliminaciones
void postorden(Persona* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda); //visita al hijo izquierdo
        postorden(raiz->derecha); //visita al hijo derecho
        cout << raiz->nombre << " \t(" << raiz->anioNacimiento << ")\n"; //Imprime el nodo actual
    }
}

//Mostrar jerarquÃ­a de forma visual
void mostrarJerarquia(Persona* raiz, int nivel = 0) {
    if (raiz != NULL) {
        mostrarJerarquia(raiz->derecha, nivel + 1); // Se muestra primero el subárbol derecho
        for (int i = 0; i < nivel; i++) cout << "   "; // Espaciado para representar visualmente el nivel jerárquico
        cout << "|--- " << raiz->nombre << " (" << raiz->anioNacimiento << ")\n"; // Se imprime el nodo actual con su indentación
        mostrarJerarquia(raiz->izquierda, nivel + 1); // Luego se muestra el subárbol izquierdo
    }
}


// Muestra el menú de opciones del programa. 
void menu() { 
    cout << "\n--- Ãrbol GenealÃ³gico (ABB) ---\n";
    cout << "1. Insertar persona\n";
    cout << "2. Buscar persona\n";
    cout << "3. Eliminar persona\n";
    cout << "4. Mostrar inorden\n";
    cout << "5. Mostrar preorden\n";
    cout << "6. Mostrar postorden\n";
    cout << "7. Visualizar jerarquÃ­a\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opciÃ³n: ";
}


int main() {
    setlocale(LC_CTYPE, "Spanish"); // Configura el idioma para mostrar correctamente caracteres en español
    Persona* raiz = NULL; // Puntero principal al árbol genealógico (raíz del ABB)
    int opcion, anio; // Variables para controlar el menú y capturar años
    string nombre; // Variable para capturar el nombre de la persona

    do {
        menu();
        cin >> opcion; // Captura la opción seleccionada por el usuario

        switch (opcion) { 
            case 1: // Inserción
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese aÃ±o de nacimiento: ";
                cin >> anio;
                insertarPersona(raiz, anio, nombre);
                break;
            case 2: // Búsqueda
                cout << "Ingrese aÃ±o a buscar: ";
                cin >> anio;
                if (!buscarPersona(raiz, anio))
                    cout << "No se encontró a la persona.\n";
                
                break;
            case 3: //  Eliminar una persona del árbol según su año de nacimiento
                cout << "Ingrese aÃ±o a eliminar: ";
                cin >> anio;
                raiz = eliminarPersona(raiz, anio);
                break;
            case 4: //  Mostrar el recorrido inorden (de más antiguo a más reciente)
                cout << "\n--- Recorrido Inorden (IRD - De mas antiguo a mas reciente) ---\n";
                inorden(raiz);
                break;
            case 5: // Mostrar el recorrido preorden (jerarquía generacional)
                cout << "\n--- Recorrido Preorden (RID - Jerarquia generacional) ---\n";
                preorden(raiz);
                break;
            case 6: // Mostrar el recorrido postorden (para eliminaciones o limpieza)
                cout << "\n--- Recorrido Postorden (IDR - Para eliminaciones) ---\n";
                postorden(raiz);
                break;
            case 7: // Mostrar visualmente la jerarquía del árbol genealógico
                cout << "\n--- VisualizaciÃ³n JerÃ¡rquica del Ãrbol ---\n";
                mostrarJerarquia(raiz);
                break;
            case 8: // Salir del programa
                cout << "Saliendo del programa.\n";
                break;
            default: // En caso de que se ingrese una opción que no está en el menú
                cout << "OpciÃ³n invÃ¡lida.\n";
        }
    } while (opcion != 8);

    return 0;
}

