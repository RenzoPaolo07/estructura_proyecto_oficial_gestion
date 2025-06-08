 //listas
#include <iostream>
#include <string>

using namespace std;

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    float porcentajeMemoria; 
    Proceso* siguiente;
};


void insertarProceso(Proceso*& lista, int id, const string& nombre, int prioridad) {
    Proceso* nuevo = new Proceso;
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;

    cout << "Ingrese el porcentaje de memoria que usa el proceso: ";
    cin >> nuevo->porcentajeMemoria;

    nuevo->siguiente = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        Proceso* temp = lista;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

void mostrarProcesos(const Proceso* lista) {
    const Proceso* temp = lista;
    float totalMemoria = 0;

    cout << "\nProcesos actuales:\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id ;
        cout << " | Nombre: " << temp->nombre ;
        cout << " | Prioridad: " << temp->prioridad ;
        cout << " | Memoria: " << temp->porcentajeMemoria << "%\n";
        totalMemoria += temp->porcentajeMemoria;
        temp = temp->siguiente;
    }

    cout << "Porcentaje de memoria total en uso: " << totalMemoria << "%\n";

    if (totalMemoria > 100.00) {
        cout << "\nNo hay suficiente espacio de memoria \n";
    }
}

void eliminarProceso(Proceso*& lista, int id) {
    Proceso* actual = lista;
    Proceso* anterior = NULL;

    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "Proceso no encontrado.\n";
        return;
    }

    if (anterior == NULL) {
        lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    cout << "Proceso eliminado correctamente.\n";
}
Proceso* buscarProceso(Proceso* lista, int id) {
    Proceso* actual = lista;
    while (actual != NULL) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void modificarPrioridad(Proceso* lista, int id, int nuevaPrioridad) {
    Proceso* p = buscarProceso(lista, id);
    if (p != NULL) {
        p->prioridad = nuevaPrioridad;
        cout << "Prioridad modificada correctamente.\n";
    } else {
        cout << "Proceso no encontrado.\n";
    }
}

//Colas
struct NodoCola {
    Proceso* proceso;
    NodoCola* siguiente;
};

NodoCola* frente = NULL;


void encolar(Proceso* p) {
    NodoCola* nuevo = new NodoCola;
    nuevo->proceso = p;
    nuevo->siguiente = NULL;

    if (frente == NULL || p->prioridad > frente->proceso->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
    } else {
        NodoCola* actual = frente;
        while (actual->siguiente != NULL && p->prioridad <= actual->siguiente->proceso->prioridad) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}


void ejecutarProceso() {
    if (frente == NULL) {
        cout << "No hay procesos en la cola.\n";
        return;
    }

    cout << "Ejecutando proceso ID: " << frente->proceso->id
         << ", Nombre: " << frente->proceso->nombre << endl;

    NodoCola* temp = frente;
    frente = frente->siguiente;
    delete temp;
}


void mostrarCola() {
    NodoCola* actual = frente;
    cout << "\nCola de procesos:\n";
    while (actual != NULL) {
        cout << "ID: " << actual->proceso->id;
        cout << ", Nombre: " << actual->proceso->nombre;
        cout << ", Prioridad: " << actual->proceso->prioridad << endl;
        actual = actual->siguiente;
    }
}
//pilas
void push(Proceso*& pila, int id, const string& nombre, int prioridad) {
    Proceso* nuevo = new Proceso;
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    
    cout << "Ingrese el porcentaje de memoria que usa el proceso: ";
    cin >> nuevo->porcentajeMemoria;

    nuevo->siguiente = pila;
    pila = nuevo;

    cout << "Memoria asignada al proceso correctamente.\n";
}

void pop(Proceso*& pila) {
    if (pila == NULL) {
        cout << "No hay procesos en la pila de memoria.\n";
        return;
    }

    Proceso* temp = pila;
    pila = pila->siguiente;

    cout << "Memoria liberada del proceso:\n";
    cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Memoria: " << temp->porcentajeMemoria << "%\n";

    delete temp;
}

void mostrarPila(Proceso* pila) {
    if (pila == NULL) {
        cout << "La pila de memoria esta vacia.\n";
        return;
    }

    Proceso* temp = pila;
    float memoriaTotal = 0;

    cout << "\n--- Estado actual de la memoria (Pila) ---\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id << " | Nombre: " << temp->nombre 
             << " | Prioridad: " << temp->prioridad 
             << " | Memoria: " << temp->porcentajeMemoria << "%\n";
        memoriaTotal += temp->porcentajeMemoria;
        temp = temp->siguiente;
    }

    cout << "Memoria total en uso: " << memoriaTotal << "%\n";
    if (memoriaTotal > 100) {
        cout << "Advertencia: Memoria excedida.\n";
    }
}
int main() {
    Proceso* lista = NULL;
    Proceso* pilaMemoria = NULL;
    int opcion, id, prioridad;
    string nombre;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Mostrar procesos\n";
        cout << "3. Eliminar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Encolar proceso\n";
        cout << "6. Ejecutar proceso\n";
        cout << "7. Mostrar cola\n";
        cout << "8. Asignar memoria a proceso (push)\n";
        cout << "9. Liberar memoria del ultimo proceso (pop)\n";
        cout << "10. Mostrar pila de memoria\n";
        cout << "11. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID: "; cin >> id; cin.ignore();
                cout << "Ingrese nombre: "; getline(cin, nombre);
                
                do {
                    cout << "Ingrese prioridad del 1 al 5: ";
                    cin >> prioridad;
                    if (prioridad < 1 || prioridad > 5) {
                        cout << "La prioridad debe estar entre 1 y 5.\n";
                    }
                } while (prioridad < 1 || prioridad > 5);
                insertarProceso(lista, id, nombre, prioridad);
                mostrarProcesos(lista);
                break;
            case 2:
                mostrarProcesos(lista);
                break;
            case 3:
                cout << "Ingrese el ID del proceso a eliminar: ";
                cin >> id;
                eliminarProceso(lista, id);
                break;
            case 4:
                cout << "Ingrese ID del proceso a modificar: ";
                cin >> id;
                cout << "Ingrese nueva prioridad: ";
                cin >> prioridad;
                modificarPrioridad(lista, id, prioridad);
                break;
            case 5: {
                cout << "ID del proceso a encolar: ";
                cin >> id;
                Proceso* p = buscarProceso(lista, id);
                if (p != NULL)
                    encolar(p);
                else
                    cout << "Proceso no encontrado.\n";
                break;
            }
            case 6:
                ejecutarProceso();
                break;
            case 7:
                mostrarCola();
                break;
            case 8:
                
                push(pilaMemoria, id, nombre, prioridad);
                break;
            case 9:
                pop(pilaMemoria);
                break;
            case 10:
                mostrarPila(pilaMemoria);
                break;
            case 11:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 11);

    return 0;
}

