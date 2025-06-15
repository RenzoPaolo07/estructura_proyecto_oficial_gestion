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
