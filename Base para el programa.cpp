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

int main() {
    Proceso* lista = NULL;
    int opcion, id, prioridad;
    string nombre;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Mostrar procesos\n";
        cout << "3. Eliminar proceso\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID: "; cin >> id;
                cout << "Ingrese nombre: "; cin.ignore(); getline(cin, nombre);
                cout << "Ingrese prioridad: "; cin >> prioridad;
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
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);

    return 0;
}

