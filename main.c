#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "hasmap.h"

#include "Estructuras.h"


// Solicitar texto al usuario
char* solicitarTexto() {
    char* texto = malloc(sizeof(char) * 100);
    
    //scanf("%s", texto);
    scanf("%100[^\n]s",texto);
    getchar();
    return texto;
}

// Solicitar entero al usuario
int solicitarEntero() {
    int entero;
    
    scanf("%d", &entero);
    getchar();
    return entero;
}

void exportar(Paciente *paciente){
  
  FILE *fp = fopen("base de datos2.csv", "a"); // Abre el archivo "base de datos2.csv" en modo de apertura para agregar datos al final
  //printf("xd");
  fprintf(fp,"%s,%s,%d,%s,%d",
    paciente->nombre,
    paciente->rut,
    paciente->edad,
    paciente->sexo,
    paciente->cant_Sintomas);
  
  EnfermedadPrevia *aux_enfe_prev = firstList(paciente->historial.enfermedadesPrevias); // Obtiene el primer elemento de la lista de enfermedades previas del paciente
  Alergia *aux_alergias = firstList(paciente->historial.alergias); // Obtiene el primer elemento de la lista de alergias del paciente
  Sintoma *aux_sintoma = firstList(paciente->sintomas); // Obtiene el primer elemento de la lista de síntomas del paciente  
  
  while(aux_sintoma != NULL){
    fprintf(fp,",%s",aux_sintoma->nombre); // Escribe el nombre del síntoma en el archivo
    aux_sintoma= nextList(paciente->sintomas); // Avanza al siguiente síntoma de la lista
  }
  fprintf(fp,",%d",paciente->historial.Cant_alergias); // Escribe la cantidad de alergias en el archivo
  while(aux_alergias != NULL){
    fprintf(fp,",%s",aux_alergias->nombre); // Escribe el nombre de la alergia en el archivo
    aux_alergias= nextList(paciente->historial.alergias); // Avanza a la siguiente alergia de la lista
  }
  fprintf(fp,",%d",paciente->historial.Cant_enfer_prev); // Escribe la cantidad de enfermedades previas en el archivo
  while(aux_enfe_prev != NULL){
    fprintf(fp,",%s",aux_enfe_prev->nombre); // Escribe el nombre de la enfermedad previa en el archivo
    aux_enfe_prev= nextList(paciente->historial.enfermedadesPrevias); // Avanza a la siguiente enfermedad previa de la lista
  }
  fprintf(fp,"\n"); // Escribe un salto de línea en el archivo para separar los registros
  fclose(fp); // Cierra el archivo
}


void agregarPaciente(HashMap *tablaHash, List *listaSintomas) {
    // Crear un nuevo paciente
    Paciente *paciente = (Paciente *)malloc(sizeof(Paciente));
    paciente->historial.alergias = createList();
    paciente->sintomas = createList();
    paciente->historial.enfermedadesPrevias = createList();

    printf("\033[1;36m"); // Establecer color azul brillante

    printf("\033[1;36m╔══════════════════════════════════════════════════╗");
    printf("\n\033[1;36m║               🏥 MediScan Hospital 🏥            ║");
    printf("\n\033[1;36m╠══════════════════════════════════════════════════╣");
    printf("\n\033[1;36m║          Usted ha elegido la opción 1:           ║");
    printf("\n\033[1;36m║             👤 Agregar Paciente 👤               ║");
    printf("\n\033[1;36m║                                                  ║");
    printf("\n\033[1;36m║ Por favor, ingrese los datos del paciente:       ║");
    printf("\n\033[1;36m║                                                  ║");

    printf("\033[1;37m"); // Establecer color blanco

    // Solicitar el nombre del paciente y asignarlo
    printf("\n\033[1;37m║ 📋 Nombre: ");
    strcpy(paciente->nombre, solicitarTexto());
    

    // Solicitar el rut del paciente y asignarlo
    printf("\033[1;37m║ 🔢 RUT: ");
    strcpy(paciente->rut, solicitarTexto());

    // Solicitar la edad del paciente y asignarla
    printf("\033[1;37m║ 🎂 Edad: ");
    paciente->edad = solicitarEntero();

    // Solicitar el sexo del paciente y asignarlo
    printf("\033[1;37m║ 🚹 Sexo: ");
    strcpy(paciente->sexo, solicitarTexto());

    printf("\033[1;36m║                                                  ║");
    printf("\n\033[1;36m║--------------------------------------------------║");
    printf("\n\033[1;36m║               🩺 Ingrese los Síntomas 🩺         ║");
    printf("\n\033[1;36m║--------------------------------------------------║");

    // Solicitar los síntomas del paciente y agregarlos a la lista de síntomas general
    int cont_sintoma;
    
    printf("\n\033[1;37m║ Ingrese la cantidad de síntomas: ");
    cont_sintoma = solicitarEntero();
    paciente->cant_Sintomas =cont_sintoma;  
    Sintoma *sintoma;

    for (int i = 0; i < cont_sintoma; i++) {
        sintoma = (Sintoma *)malloc(sizeof(Sintoma));
        printf("\033[1;37m║ Síntoma %i: ", i + 1);
        strcpy(sintoma->nombre, solicitarTexto());
        pushBack(paciente->sintomas, sintoma);
    }

    // Verificar si el paciente tiene alergias a fármacos
    int opcion;
    int cont_alergias;
    printf("\n\033[1;36m║--------------------------------------------------║");
    printf("\n\033[1;36m║ ¿El tiene alguna alergia a medicamentos? 🌡️       ║");
    printf("\n\033[1;36m║--------------------------------------------------║");
    printf("\n\033[1;37m║   [1] Sí");
    printf("\n\033[1;37m║   [2] No");
    //printf("\n033[1;37m║ Respuesta: ");
    printf("\n║ Respuesta: ");
    opcion = solicitarEntero();

    if (opcion == 1) {
        printf("\033[1;37m║ Ingrese numero de alergias: ");
        cont_alergias = solicitarEntero();
        paciente ->historial.Cant_alergias= cont_alergias;  
        Alergia *alergia_actual;

        for (int i = 0; i < cont_alergias; i++) {
            alergia_actual = (Alergia *)malloc(sizeof(Alergia));
            printf("\033[1;37m║ Ingrese el nombre  del fármaco %i: ", i + 1);
            strcpy(alergia_actual->nombre, solicitarTexto());
            pushBack(paciente->historial.alergias, alergia_actual);
        }
    }

    // Verificar si el paciente tiene enfermedades previas
    
    printf("\n\033[1;36m║--------------------------------------------------║");
    printf("\n\033[1;36m║ ¿El paciente tiene enfermedades previas? 📋      ║");
    printf("\n\033[1;36m║--------------------------------------------------║");
    printf("\n\033[1;37m║   [1] Sí");
    printf("\n\033[1;37m║   [2] No");
    printf("\n║ Respuesta: ");
    opcion = solicitarEntero();
    int cont_enf_prev;

    if (opcion == 1) {
        printf("\033[1;37m║ Ingrese numero de enfermedades previas: ");
        cont_enf_prev = solicitarEntero();
        paciente->historial.Cant_enfer_prev = cont_enf_prev;
        EnfermedadPrevia *enfermedad_actual;

        for (int i = 0; i < cont_enf_prev; i++) {
            enfermedad_actual = (EnfermedadPrevia *)malloc(sizeof(EnfermedadPrevia));
            printf("\033[1;37m║ Ingrese el nombre  de la enfermedad %i: ", i + 1);
            strcpy(enfermedad_actual->nombre, solicitarTexto());
            pushBack(paciente->historial.enfermedadesPrevias, enfermedad_actual);
        }
    }

    // Insertar el paciente en la tabla hash
    insertMap(tablaHash, paciente->rut, paciente);
    Paciente *p = searchMap(tablaHash, paciente->rut)->value;
    
    
    printf("\n\033[1;36m╚══════════════════════════════════════════════════╝\n\n");
    
    printf("\033[0m"); // Restablecer el color a los valores predeterminados
    printf("\033[1;32m╔═══════════════════════════════════════════════════════════╗\033[0m");
    printf("\n\033[1;32m║                                                           ║\033[0m");
    printf("\n\033[1;32m║                ✅ Paciente agregado correctamente ✅      ║\033[0m");
    printf("\n\033[1;32m║                                                           ║\033[0m");
    printf("\n\033[1;32m║    El paciente %s ha sido registrado exitosamente.     ║\033[0m", p->nombre);
    printf("\n\033[1;32m║                                                           ║\033[0m");
    printf("\n\033[1;32m╚═══════════════════════════════════════════════════════════╝\033[0m\n\n");

    exportar(paciente);
    
}

// Funcion para leer el k-esimo elemento de un string (separado por comas)
const char *get_csv_field(char *tmp, int k, char c) {
    // Variables locales
    int open_mark = 0; // Bandera para indicar si se está dentro de una marca de comillas
    char *ret = (char *)malloc(100 * sizeof(char)); // Se reserva memoria para el string de retorno
    int ini_i = 0, i = 0; // Variables para almacenar los índices inicial y actual del campo actual
    int j = 0; // Contador para seguir el número de campos procesados

    // Ciclo mientras no se alcance el final del string
    while (tmp[i + 1] != '\0') {

        // Verificar si el carácter actual es una comilla doble
        if (tmp[i] == '\"') {
            open_mark = 1 - open_mark; // Cambiar el valor de la bandera (abrir o cerrar la marca de comillas)
            if (open_mark)
                ini_i = i + 1; // Si se abre la marca de comillas, se actualiza el índice inicial del campo
            i++;
            continue;
        }

        // Si estamos dentro de una marca de comillas o el carácter actual no es el delimitador
        if (open_mark || tmp[i] != c) {
            // Si el contador de campos coincide con k, se copia el carácter al string de retorno
            if (k == j)
                ret[i - ini_i] = tmp[i];
            i++;
            continue;
        }

        // Si se encuentra el delimitador
        if (tmp[i] == c) {
            // Si el contador de campos coincide con k, se finaliza el string de retorno y se retorna
            if (k == j) {
                ret[i - ini_i] = 0;
                return ret;
            }
            j++; // Se incrementa el contador de campos
            ini_i = i + 1; // Se actualiza el índice inicial del campo para el próximo campo
        }

        i++; // Se incrementa el índice actual del string
    }

    // Cuando se alcanza el final del string, si el contador de campos coincide con k, se finaliza el string de retorno
    if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
    }

      
    return NULL;
}

void importar(HashMap *tablaHash_pacientes) {
    FILE *fp = fopen("base de datos2.csv", "r"); // Se abre el archivo CSV en modo lectura

    char linea[1024]; // Cadena para almacenar una línea completa del archivo
    char *aux;
    int cont;
    int i;
    Sintoma *sintoma;
    Alergia *alergias;
    EnfermedadPrevia *enfermedadesPrevias;

    fgets(linea, 1023, fp); // Se lee la primera línea del archivo y se descarta (cabecera)

    Paciente *paciente; // Puntero para almacenar la información del paciente

    while (fgets(linea, 1023, fp) != NULL) { // Mientras haya líneas por leer en el archivo

        paciente = (Paciente *)malloc(sizeof(Paciente)); // Se reserva memoria para el paciente
        paciente->historial.alergias = createList(); // Se crea una lista para almacenar las alergias del paciente
        paciente->sintomas = createList(); // Se crea una lista para almacenar los síntomas del paciente
        paciente->historial.enfermedadesPrevias = createList(); // Se crea una lista para almacenar las enfermedades previas del paciente

        // Se obtienen los datos del paciente de la línea actual del archivo CSV
        strcpy(paciente->nombre, get_csv_field(linea, 0, ',')); // Se obtiene el nombre
        strcpy(paciente->rut, get_csv_field(linea, 1, ',')); // Se obtiene el rut
        paciente->edad = atoi(get_csv_field(linea, 2, ',')); // Se obtiene la edad
        strcpy(paciente->sexo, get_csv_field(linea, 3, ',')); // Se obtiene el sexo

        // Se obtienen los síntomas del paciente
        cont = 5;
        paciente->cant_Sintomas = atoi(get_csv_field(linea, cont - 1, ',')); // Se obtiene la cantidad de síntomas

        for (int i = 0; i < paciente->cant_Sintomas; i++) {
            aux = get_csv_field(linea, cont + i, ',');
            sintoma = (Sintoma *)malloc(sizeof(Sintoma));
            strcpy(sintoma->nombre, aux); // Se obtiene y guarda cada síntoma
            pushBack(paciente->sintomas, sintoma); // Se agrega el síntoma a la lista de síntomas del paciente
        }

        // Se obtienen las alergias del paciente
        cont = paciente->cant_Sintomas + 6;
        paciente->historial.Cant_alergias = atoi(get_csv_field(linea, cont - 1, ',')); // Se obtiene la cantidad de alergias

        for (int i = 0; i < paciente->historial.Cant_alergias; i++) {
            aux = get_csv_field(linea, cont + i, ',');
            alergias = (Alergia *)malloc(sizeof(Alergia));
            strcpy(alergias->nombre, aux); // Se obtiene y guarda cada alergia
            pushBack(paciente->historial.alergias, alergias); // Se agrega la alergia a la lista de alergias del paciente
        }

        // Se obtienen las enfermedades previas del paciente
        cont = paciente->historial.Cant_alergias + paciente->cant_Sintomas + 7;
        paciente->historial.Cant_enfer_prev = atoi(get_csv_field(linea, cont - 1, ',')); // Se obtiene la cantidad de enfermedades previas

        for (int i = 0; i < paciente->historial.Cant_enfer_prev; i++) {
            aux = get_csv_field(linea, cont + i, ',');
            enfermedadesPrevias = (EnfermedadPrevia *)malloc(sizeof(EnfermedadPrevia));
            strcpy(enfermedadesPrevias->nombre, aux); // Se obtiene y guarda cada enfermedad previa
            pushBack(paciente->historial.enfermedadesPrevias, enfermedadesPrevias); // Se agrega la enfermedad previa a la lista de enfermedades previas del paciente
        }

        insertMap(tablaHash_pacientes, paciente->rut, paciente); // Se inserta el paciente en la tabla hash
        Paciente *p = searchMap(tablaHash_pacientes, paciente->rut)->value; // Se realiza una búsqueda para verificar la inserción correcta
    }

    fclose(fp); // Se cierra el archivo
}


void importar_base_enfermedades(List *listaEnfermedades) {
    FILE *fp = fopen("Base_enfermedades.csv", "r"); // Se abre el archivo CSV en modo lectura
    if (fp == NULL) {
        printf("Error al abrir el archivo Base_enfermedades.csv\n"); // Si no se puede abrir el archivo, se muestra un mensaje de error y se retorna
        return;
    }

    char linea[1024]; // Cadena para almacenar una línea completa del archivo
    char *aux;
    int cont;
    int i;
    Sintoma *sintoma;

    fgets(linea, 1023, fp); // Se lee la primera línea del archivo y se descarta (cabecera)

    Enfermedad *enfermedad; // Puntero para almacenar la información de la enfermedad

    while (fgets(linea, 1023, fp) != NULL) { // Mientras haya líneas por leer en el archivo

        enfermedad = (Enfermedad *)malloc(sizeof(Enfermedad)); // Se reserva memoria para la enfermedad
        enfermedad->sintomas = createList(); // Se crea una lista para almacenar los síntomas de la enfermedad

        strcpy(enfermedad->nombre, get_csv_field(linea, 0, ',')); // Se obtiene el nombre de la enfermedad

        cont = 1;
        aux = (char *)get_csv_field(linea, cont, ','); // Se obtiene el primer síntoma

        while (aux != NULL) { // Mientras haya síntomas por leer
            sintoma = (Sintoma *)malloc(sizeof(Sintoma));
            strcpy(sintoma->nombre, aux); // Se guarda el nombre del síntoma
            pushBack(enfermedad->sintomas, sintoma); // Se agrega el síntoma a la lista de síntomas de la enfermedad
            cont += 1;
            aux = (char *)get_csv_field(linea, cont, ','); // Se obtiene el siguiente síntoma
        }
        
        enfermedad->cant_sintomas = cont - 1; // Se actualiza la cantidad de síntomas de la enfermedad
        pushBack(listaEnfermedades, enfermedad); // Se agrega la enfermedad a la lista de enfermedades

    }

    fclose(fp); // Se cierra el archivo
}
void mostrar_base_enfermedades(List *listaEnfermedades) {
    Enfermedad *enfermedad;
    Sintoma *sintoma;
    enfermedad = firstList(listaEnfermedades); // Se obtiene el primer elemento de la lista de enfermedades

    printf("\033[1;34m");
    printf("╭───────────────────────────────────────────────────────╮\n");
    printf("│        ≋≋≋ BASE DE DATOS DE ENFERMEDADES ≋≋≋          │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");
    printf("\033[0m");
    
    while (enfermedad != NULL) { // Mientras haya enfermedades por mostrar
        printf("\033[1;33m");
        printf("❖ Enfermedad: %s\n", enfermedad->nombre); // Se muestra el nombre de la enfermedad
        printf("\033[0m");
        printf("\033[1;31m");
        printf("🌡️ Síntomas:\n");
        printf("\033[0m");
        
        sintoma = firstList(enfermedad->sintomas); // Se obtiene el primer síntoma de la enfermedad
        
        while (sintoma != NULL) { // Mientras haya síntomas por mostrar
            printf("  • %s\n", sintoma->nombre); // Se muestra el nombre del síntoma
            sintoma = nextList(enfermedad->sintomas); // Se obtiene el siguiente síntoma
        }
        
        printf("\n");
        enfermedad = nextList(listaEnfermedades); // Se obtiene la siguiente enfermedad
    }

    printf("\033[1;34m");
    printf("╭───────────────────────────────────────────────────────╮\n");
    printf("│            ◉◉◉ Fin de la Base de Datos ◉◉◉            │\n");
    printf("╰───────────────────────────────────────────────────────╯\n");
}



void comparar_sintomas(HashMap *tablaHash, List *listaEnfermedades) {
    Sintoma *sintoma_paciente;
    Sintoma *sintoma_de_enfermedad;
    Enfermedad *enfermedad;
    Paciente *paciente;
    HashMap *aciertos = createMap(150);
    int *cant_aciertos;
    char rut[20];
    printf("\033[1;34m");
    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                  ▄▄▄▄▄ ▄▄▄ ▄▄▄ ▄▄  ▄▄▄                │\n");
    printf("│                 ██▄▄▄▄ ▀▀ ▀▀ ▀▀ ██▄ ██                │\n");
    printf("│                 ██▀▀▀▀█▄    ▄█▀▀██▀▀██                │\n");
    printf("│                 ██     ██ ▄██ ██  ██                  │\n");
    printf("│                 ▀▀▀▄▄▄██▀ ██  ██  ██                  │\n");
    printf("│                 ▀▀▀▀▀▀   ▀▀  ▀▀  ▀▀                   │\n");
    printf("│                                                       │\n");
    printf("│                Diagnóstico del Paciente               │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");
    printf("\033[0m");
    printf("❖ Ingrese el RUT del paciente: ");
    scanf("%s", rut);

    if (searchMap(tablaHash, rut) != NULL) {
        paciente = searchMap(tablaHash, rut)->value;
    } else {
        printf("El paciente no se encuentra en la base de datos.\n");
        return;
    }

    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│             ≋≋≋ COMPARACIÓN DE SÍNTOMAS ≋≋≋          │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");

    sintoma_paciente = firstList(paciente->sintomas);
    while (sintoma_paciente != NULL) {
        enfermedad = firstList(listaEnfermedades);

        while (enfermedad != NULL) {
            sintoma_de_enfermedad = firstList(enfermedad->sintomas);
            bool Se_Encontro = false;

            while (sintoma_de_enfermedad != NULL) {
                if (strcmp(sintoma_de_enfermedad->nombre, sintoma_paciente->nombre) == 0) {
                    Se_Encontro = true;
                    break;
                }

                sintoma_de_enfermedad = nextList(enfermedad->sintomas);
            }

            if (Se_Encontro) {
                if (searchMap(aciertos, enfermedad->nombre) == NULL) {
                    cant_aciertos = malloc(sizeof(int));
                    *cant_aciertos = 1;

                    insertMap(aciertos, enfermedad->nombre, cant_aciertos);
                } else {
                    cant_aciertos = searchMap(aciertos, enfermedad->nombre)->value;
                    *cant_aciertos += 1;
                }
            }

            enfermedad = nextList(listaEnfermedades);
        }

        sintoma_paciente = nextList(paciente->sintomas);
    }

    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                  ▄▄▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄                   │\n");
    printf("│                 ██▄▄▄▄ ██ ██  ██                      │\n");
    printf("│                 ██▀▀▀▀▀▀▀▀██  ██                      │\n");
    printf("│                 ██        ██  ██                      │\n");
    printf("│                 ██        ██▄▄██                      │\n");
    printf("│                                                       │\n");
    printf("│               Resultado de la Comparación             │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");

    Pair *Porcentaje_aciertos = firstMap(aciertos);
    float Porcentaje;
    char *nombre_enfermedad;

    while (Porcentaje_aciertos != NULL) {
        nombre_enfermedad = Porcentaje_aciertos->key;
        cant_aciertos = Porcentaje_aciertos->value;
        enfermedad = firstList(listaEnfermedades);

        while (enfermedad != NULL) {
            if (strcmp(enfermedad->nombre, nombre_enfermedad) == 0) {
                break;
            }

            enfermedad = nextList(listaEnfermedades);
        }

        Porcentaje = (*cant_aciertos * 100) / enfermedad->cant_sintomas;

        printf("Enfermedad: %s\n", nombre_enfermedad);
        printf("Coincidencias: %d\n", *cant_aciertos);
        printf("Porcentaje de coincidencias: %.2f%%\n\n", Porcentaje);

        Porcentaje_aciertos = nextMap(aciertos);
    }

    printf("╭───────────────────────────────────────────────────────╮\n");
    printf("│            ◉◉◉ Fin de la Comparación ◉◉◉              │\n");
    printf("╰───────────────────────────────────────────────────────╯\n");

    // Liberar memoria de aciertos
    for (Pair *p = firstMap(aciertos); p != NULL; p = nextMap(aciertos)) {
        free(p->value);
    }
    
}

void mostrarPaciente(Paciente *pacientes, int cantidadPacientes) {
    printf("BASE DE DATOS DE PACIENTES:\n");
    printf("----------------------------\n");

    for (int i = 0; i < cantidadPacientes; i++) {
        Paciente paciente = pacientes[i];

        printf("Nombre: %s\n", paciente.nombre);
        printf("RUT: %s\n", paciente.rut);
        printf("Edad: %d\n", paciente.edad);
        printf("Sexo: %s\n", paciente.sexo);

        printf("Síntomas:\n");
        List *sintomas = paciente.sintomas;
        Node *sintomaNode = sintomas->head;
        while (sintomaNode != NULL) {
            Sintoma *sintoma = (Sintoma *)sintomaNode->data;
            printf("- %s\n", sintoma->nombre);
            sintomaNode = sintomaNode->next;
        }
        printf("Cantidad de síntomas: %d\n", paciente.cant_Sintomas);

        printf("Alergias:\n");
        List *alergias = paciente.historial.alergias;
        Node *alergiaNode = alergias->head;
        while (alergiaNode != NULL) {
            Alergia *alergia = (Alergia *)alergiaNode->data;
            printf("- %s\n", alergia->nombre);
            alergiaNode = alergiaNode->next;
        }
        printf("Cantidad de alergias: %d\n", paciente.historial.Cant_alergias);

        printf("Enfermedades previas:\n");
        List *enfermedadesPrevias = paciente.historial.enfermedadesPrevias;
        Node *enfermedadNode = enfermedadesPrevias->head;
        while (enfermedadNode != NULL) {
            EnfermedadPrevia *enfermedad = (EnfermedadPrevia *)enfermedadNode->data;
            printf("- %s\n", enfermedad->nombre);
            enfermedadNode = enfermedadNode->next;
        }
        printf("Cantidad de enfermedades previas: %d\n", paciente.historial.Cant_enfer_prev);

        printf("----------------------------\n");
    }
}





void obtenerEnfermedadYSintomas(char enfermedad[100], char sintomas[][100], int *cantidadSintomas) {
    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                ≋≋≋ OBTENER ENFERMEDAD ≋≋≋             │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");

    printf("Ingrese el nombre de la enfermedad: ");
    fgets(enfermedad, 100, stdin);
    // Eliminar el salto de línea al final del nombre de la enfermedad
    enfermedad[strlen(enfermedad) - 1] = '\0';

    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                ≋≋≋ OBTENER SÍNTOMAS ≋≋≋               │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");

    // Obtener la cantidad de síntomas que se ingresarán
    printf("Ingrese la cantidad de síntomas a ingresar: ");
    scanf("%d", cantidadSintomas);
    // Limpiar el búfer del teclado después de la entrada
    getchar();

    // Validar la cantidad de síntomas ingresados
    if (*cantidadSintomas < 1) {
        printf("Cantidad de síntomas inválida. Ingrese al menos 1 síntoma.\n");
        return;
    }

    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                      ≋≋≋ SÍNTOMAS ≋≋≋                 │\n");
    printf("╰───────────────────────────────────────────────────────╯\n\n");

    // Obtener los síntomas desde el usuario
    for (int i = 0; i < *cantidadSintomas; i++) {
        printf("Ingrese el Síntoma %d: ", i + 1);
        fgets(sintomas[i], 100, stdin);
        // Eliminar el salto de línea al final del síntoma
        sintomas[i][strlen(sintomas[i]) - 1] = '\0';
    }

    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                ◉◉◉ Fin de la Captura ◉◉◉              │\n");
    printf("╰───────────────────────────────────────────────────────╯\n");
}

void exportarEnfermedad(char enfermedad[100], char sintomas[][100], int cantidadSintomas) {
    FILE *fp = fopen("Base_enfermedades.csv", "a"); // Abre el archivo "Base_enfermedades.csv" en modo de escritura al final del archivo
    if (fp == NULL) { // Verifica si ocurrió un error al abrir el archivo
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Escribe los datos de la enfermedad y sus síntomas en el archivo CSV
    fprintf(fp, "%s", enfermedad);
    for (int i = 0; i < cantidadSintomas; i++) {
        if (strlen(sintomas[i]) > 0) {
            fprintf(fp, ",%s", sintomas[i]);
        } else {
            fprintf(fp, ",");
        }
    }
    for (int i = cantidadSintomas; i < 4; i++) {
        fprintf(fp, ",");
    }
    fprintf(fp, "\n");

    fclose(fp); // Cierra el archivo

    // Muestra un mensaje indicando que los datos se han exportado correctamente a la base de datos
    printf("\n╭───────────────────────────────────────────────────────╮\n");
    printf("│                                                       │\n");
    printf("│   ✨✨ Los datos se han exportado correctamente ✨✨  │\n");
    printf("│             a la base de datos.                       │\n");
    printf("│                                                       │\n");
    printf("╰───────────────────────────────────────────────────────╯\n");
}




int main() {
    // Crear la tabla hash y la lista de síntomas
    HashMap *tablaHash_pacientes = createMap(100);
    List *listaSintomas = createList();
    List *listaEnfermedades = createList();
    // Declarar la variable Paciente
    Paciente paciente;
// Obtener el nombre de la enfermedad y los síntomas desde el usuario
    char enfermedad[100];
    int cantidadSintomas;
    char sintomas[10][100];
    int opcion;
    do {
     // Imprimir menú de opciones  
    printf("\033[1;36m╔═════════════════════════════════════════════════════════════════════╗\n");
    printf("║                  !! Bienvenido a MediScan !!                        ║\n");
    printf("║                       MENÚ DE OPCIONES                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════╝\n");
    printf("║ \033[1;33mOpciones para paciente        \033[0m║  \033[1;33mOpciones base de conocimiento      \033[0m║\n");
    printf("╠═══════════════════════════════╣═════════════════════════════════════║\n");
    printf("║   \033[1;37m⑴ Agregar paciente          \033[0m║  (3) Mostrar base de enfermedades   ║\n");
    printf("║   \033[1;37m⑵ Diagnóstico e             \033[0m║  (4) Mostrar base de pacientes      ║\n");
    printf("║     información del paciente  ║  (5) Actualizar base de enfermedades║\n");
    printf("║                               ║                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════╝\n\033[0m");
    printf("\033[1;96m\nSeleccione una opción: \033[0m");
        
        
        opcion = solicitarEntero();

        switch (opcion) {
            case 1:
                agregarPaciente(tablaHash_pacientes, listaSintomas);
                break;
            case 2:
                importar_base_enfermedades(listaEnfermedades);
                importar(tablaHash_pacientes);
                comparar_sintomas(tablaHash_pacientes,listaEnfermedades);
                break;
            case 3 :
                
                
                importar_base_enfermedades(listaEnfermedades);

              
                mostrar_base_enfermedades(listaEnfermedades);
                break;
            case 4 :{
                importar(tablaHash_pacientes);
                int cantidadPacientes = getSize(tablaHash_pacientes);
                Paciente pacientes[cantidadPacientes];
                getValues(tablaHash_pacientes, (void **)pacientes);
                
                mostrarPaciente(pacientes, cantidadPacientes);                 
                break;
                
              }  
            case 5:
                obtenerEnfermedadYSintomas(enfermedad, sintomas, &cantidadSintomas);
              // Validar que se haya obtenido correctamente la enfermedad y los síntomas
                if (strlen(enfermedad) > 0 && cantidadSintomas > 0) {
                  // Exportar la enfermedad y los síntomas a la base de datos
                  exportarEnfermedad(enfermedad, sintomas, cantidadSintomas);    
                }
                break;          
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 6);

  return 0;
}
