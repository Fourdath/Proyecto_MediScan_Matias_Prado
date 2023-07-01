#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "list.h"


typedef struct List List;


typedef struct Sintoma {
    char nombre[100];
} Sintoma;

typedef struct Enfermedad {
    char nombre[100];
    List *sintomas;
    int cant_sintomas;
} Enfermedad;

typedef struct Alergia{
   char nombre[100];

}Alergia;

typedef struct EnfermedadPrevia{
   char nombre[100];

}EnfermedadPrevia;

typedef struct HistorialMedico {
    List *alergias;
    List *enfermedadesPrevias;
    int Cant_alergias;
    int Cant_enfer_prev;
} HistorialMedico;

typedef struct Paciente {
    char nombre[100];
    char rut[20];
    int edad;
    char sexo[10];
    int cant_Sintomas;
    List *sintomas;
    HistorialMedico historial;
} Paciente;

#endif // ESTRUCTURAS_H