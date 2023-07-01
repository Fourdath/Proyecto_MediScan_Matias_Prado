#include "Estructuras.h"

typedef struct {
    char alergias[100];
    ListaEnfermedades enfermedades;
} HistorialMedico;

typedef struct {
    char nombre[100];
    int edad;
    char sexo[10];
    ListaSintomas sintomas;
    HistorialMedico historial;
} Paciente;

typedef struct {
    char nombre[100];
    ListaSintomas sintomas;
} Enfermedad;

typedef struct nodoSintoma {
    Sintoma sintoma;
    struct nodoSintoma* siguiente;
} NodoSintoma;

typedef struct {
    NodoSintoma* primero;
    NodoSintoma* ultimo;
} ListaSintomas;
