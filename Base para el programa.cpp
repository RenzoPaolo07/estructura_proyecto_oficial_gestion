 //listas
#include <iostream>
#include <string>

using namespace std;

struct Proceso {
    int id; 
    string nombre;  
    int prioridad; //prioridad del 1 al 5
    float porcentajeMemoria; //porcentaje de memoria que ocupa el proceso
    Proceso* siguiente; //puntero al siguiente nodo
};


void insertarProceso(Proceso*& lista, int id, const string& nombre, int prioridad) {


    Proceso* nuevo = new Proceso; //Creacion de un nuevo nodo
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;

    nuevo->siguiente = NULL; //Se define que el puntero que apunta al siguiente nodo de "nuevo" apunta a nulo

    if (lista == NULL) {
        lista = nuevo; //si la lista esta vacia, el nodo nuevo se vuelve en el primero
    } else {
     //caso contrario recorremos toda la lista 
        Proceso* temp = lista; //el puntero temp apunta al inicio
        while (temp->siguiente != NULL) { //mientras el nodo siguiente a temp no sea nulo se repetira el bucle
            temp = temp->siguiente;
        }
     //al finaliar el bucle, temp apunta al final de la lista
        temp->siguiente = nuevo;// esto enlaza el nuevo nodo al final
    }
}

void mostrarProcesos(const Proceso* lista) {
    const Proceso* temp = lista; //se declara el puntero temp que recorrera la lista
    

    cout << "\nProcesos actuales:\n";
    while (temp != NULL) { // en este se recorre todos los nodos mostrando sus datos: id, nombre, prioridad
        cout << "ID: " << temp->id ;
        cout << " | Nombre: " << temp->nombre ;
        cout << " | Prioridad: " << temp->prioridad<<endl ;
        
        temp = temp->siguiente; //Avanamos al siguiente nodo en cada iteracion
    }

    
}

void eliminarProceso(Proceso*& lista, int id) {
    Proceso* actual = lista; //declaramos un puntero que recorrera la lista
    Proceso* anterior = NULL; //declaramos un puntero al nodo anterior que sera inicializara en NULL

    while (actual != NULL && actual->id != id) { 
        anterior = actual;
        actual = actual->siguiente;
    } //el bucle se repetira hasta encontrar el nodo con el ID buscado
     //el anterior se guardara como el actual y el puntero actual avanzara al siguiente  
 

    if (actual == NULL) { //si llegamos al final sin encontrar el ID se imprimira el siguiente mensaje
        cout << "Proceso no encontrado.\n";
        return;
    }

    if (anterior == NULL) { //En caso de que el nodo a eliminar esta al inicio
        lista = actual->siguiente;//el inicio de la lista pasa al siguiente nodo
    } else {
        anterior->siguiente = actual->siguiente; //el nodo anterior deja de apuntar al nodo actual y apunta al nodo siguiente del actual
    }

    delete actual; //eliminamos el nodo actual
    cout << "Proceso eliminado correctamente.\n";
}
Proceso* buscarProceso(Proceso* lista, int id) {
    Proceso* actual = lista;  // Creamos un puntero que apunta al inicio de la lista
    while (actual != NULL) { // recorremos la lista mientras no lleguemos al final
        if (actual->id == id) return actual; //Si encontramos el proceso con el ID buscado, devolvemos el nodo actual
        actual = actual->siguiente;
    }
    return NULL;  // devolvemos NULL, si llegamos al final y no se encontro el proceso 
}

void modificarPrioridad(Proceso* lista, int id, int nuevaPrioridad) {
    Proceso* p = buscarProceso(lista, id); //Utiliamos la funcion buscar proceso para encontrar el nodo con el id 
    if (p != NULL) { // Si el proceso fue encontrado modificamos la prioridad
        p->prioridad = nuevaPrioridad;
        cout << "Prioridad modificada correctamente.\n";
    } else {
        cout << "Proceso no encontrado.\n";
    }
}

//Colas
struct NodoCola {
    Proceso* proceso; // puntero a un proceso que está en la cola
    NodoCola* siguiente; //puntero al nodo siguiente
};

NodoCola* frente = NULL; //definimos un puntero global al primer nodo de la cola


void encolar(Proceso* p) {
    NodoCola* nuevo = new NodoCola; //creamos un nuevo nodo
    nuevo->proceso = p; //asignamos el proceso al nodo
    nuevo->siguiente = NULL; // inicialmente el nodo no apunta a otro

    if (frente == NULL || p->prioridad > frente->proceso->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
     // Si la cola esta vacia o el proceso tiene mayor prioridad que el primero entonces se inserta el nuevo nodo al inicio
    } else {
        NodoCola* actual = frente;
        while (actual->siguiente != NULL && p->prioridad <= actual->siguiente->proceso->prioridad) {
            actual = actual->siguiente;
        }
     //con el bucle while recorremos mientras no lleguemos al final y la prioridad del nuevo sea menor o igual
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo; // insertamos el nuevo nodo entre actual y su siguiente
    }
}


void ejecutarProceso() {
    if (frente == NULL) { //en caso la cola este vacia
        cout << "No hay procesos en la cola.\n";
        return;
    }
//mostramos la informacion del proceso
    cout << "Ejecutando proceso ID: " << frente->proceso->id
         << ", Nombre: " << frente->proceso->nombre << endl;

    NodoCola* temp = frente; //este puntero tempporal apunta al frene
    frente = frente->siguiente; //avanamos el frene al siguiente nodo
    delete temp; //eliminamos el nodo temporal ejecutado
}


void mostrarCola() {
    NodoCola* actual = frente; // Creamos un puntero para recorrer la cola desde el frente
    cout << "\nCola de procesos:\n";
    while (actual != NULL) {
        cout << "ID: " << actual->proceso->id;
        cout << ", Nombre: " << actual->proceso->nombre;
        cout << ", Prioridad: " << actual->proceso->prioridad << endl;
        actual = actual->siguiente;
    } //con el bucle se muestran los datos de cada proceso
}
//pilas
// Definimos la funcion que asignara memoria a un proceso usando pilas (Push)
void push(Proceso*& pila, int id, const string& nombre, int prioridad) {
    Proceso* nuevo = new Proceso; // Se crea un nuevo nodo de tipo Proceso
    nuevo->id = id;  // Se asigna los datos al nodo
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    
    cout << "Ingrese el porcentaje de memoria que usa el proceso: "; // Se solicita al usuario que ingrese el porcentaje de memoria que usará el proceso
    cin >> nuevo->porcentajeMemoria;

    nuevo->siguiente = pila; // El nuevo nodo se coloca al inicio de la pila
    pila = nuevo;

    cout << "Memoria asignada al proceso correctamente.\n"; // Muestra un mensaje de que la memoria se asignó correctamente
}

// Definimos la función que elimina el proceso más reciente (Pop)
void pop(Proceso*& pila) {
    if (pila == NULL) { // Si la pila está en blanco, se notifica al usuario con un mensaje
        cout << "No hay procesos en la pila de memoria.\n"; 
        return;
    }

    Proceso* temp = pila;  // El "temp" esta con el nodo que está en la cima
    pila = pila->siguiente; // Se actualiza la cima al siguiente nodo

    cout << "Memoria liberada del proceso:\n"; // Despues se muestran los datos del proceso eliminado
    cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Memoria: " << temp->porcentajeMemoria << "%\n";

    delete temp; // Tambien elimina el nodo de memoria
}

// Definimos la función que muestra el estado actual de la memoria
// Este va a recorrer la pila y sumar el total de memoria usada y luego mostrarla
void mostrarPila(Proceso* pila) {
    if (pila == NULL) {  // Verifica si la pila está vacía
        cout << "La pila de memoria esta vacia.\n";
        return; // Si no hay procesos termina la función
    }

    Proceso* temp = pila; // Se declara un puntero temporal para recorrer la pila
    float memoriaTotal = 0;  // Usa una variable para acumular el porcentaje total de memoria usada

    cout << "\n--- Estado actual de la memoria (Pila) ---\n";
    while (temp != NULL) { // Recorre cada nodo de la pila
        cout << "ID: " << temp->id << " | Nombre: " << temp->nombre  // Muestra los datos del proceso actual
             << " | Prioridad: " << temp->prioridad 
             << " | Memoria: " << temp->porcentajeMemoria << "%\n";
        memoriaTotal += temp->porcentajeMemoria; // Suma el porcentaje de memoria que usa este proceso
        temp = temp->siguiente; // Luego avanza al siguiente nodo en la pila
    }

    cout << "Memoria total en uso: " << memoriaTotal << "%\n"; // Muestra el total de memoria que se usa en un mensaje
    if (memoriaTotal > 100) {  // Y si el total supera el 100%, se lanza una advertencia
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
                cout << "Ingrese ID: "; cin >> id; cin.ignore(); //Ingresar ID, ignorando los espacio
                cout << "Ingrese nombre: "; getline(cin, nombre);
                
                do {
                    cout << "Ingrese prioridad del 1 al 5: ";
                    cin >> prioridad;
                    if (prioridad < 1 || prioridad > 5) {
                        cout << "La prioridad debe estar entre 1 y 5.\n";
                    }
                } while (prioridad < 1 || prioridad > 5); //el bucle do while pedira que ingreses la prioridad mientras no sea del 1 al 5
                insertarProceso(lista, id, nombre, prioridad); //llamamos a la funcion para insertar los procesos
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

