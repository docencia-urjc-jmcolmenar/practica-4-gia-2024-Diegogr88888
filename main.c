#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANIO_LISTA 100
#define MAXCHAR 50


enum Agenda{
    Listado = 1,
    Nueva_Persona = 2,
    Borrar_Persona = 3,
    Guardar_Agenda = 4,
    Salir = 0
};


enum TipoContacto{
    FAVORITO,
    CONOCIDO,
    TRABAJO
};


typedef struct {
    char nombre[MAXCHAR];
    char apellidos[MAXCHAR];
    int telefono;
    int edad;
    enum TipoContacto tipo;
}TipoPersona;


char *imprimirContacto(enum TipoContacto tipo){
    switch (tipo) {
        case FAVORITO: return "Favorito";
        case CONOCIDO: return "Conocido";
        case TRABAJO: return "Trabajo";
    }
}

void mostrarListado(TipoPersona *personas, int numPersonas){
    for (int i = 0; i < numPersonas; ++i) {
        printf("%i; %s; %s; %i; %i; %s;\n",i+1, personas[i].nombre, personas[i].apellidos, personas[i].telefono, personas[i].edad,
               imprimirContacto(personas[i].tipo));
    }
}

void NuevaPersona(TipoPersona *personas, int numPersonas){
    printf("Dame el nombre de la persona\n");
    scanf("%s", personas[numPersonas-1].nombre);
    printf("Dame el apellido de la persona\n");
    scanf("%s", personas[numPersonas-1].apellidos);
    printf("Dame el telefono de la persona\n");
    scanf("%i", &personas[numPersonas-1].telefono);
    printf("Dame la edad de la persona\n");
    scanf("%i", &personas[numPersonas-1].edad);
    printf("Dame el tipo de contacto que es la persona\n");
    printf("\t[0] = Favorito\n");
    printf("\t[1] = Conocido\n");
    printf("\t[2] = Trabajo\n");
    scanf("%i", &personas[numPersonas-1].tipo);

}

void BorrarPersona(TipoPersona *personas, int *numPersonas){
    int elec, seg;
    printf("Que contacto quieres borrar:\n ");
    mostrarListado(personas, *numPersonas);
    printf("Di el numero de la persona que desea borrar:\n ");
    scanf("%i", &elec);
    printf("¿Estas seguro? \n"
           "\t[1] Si.\n"
           "\t[2] No.\n");
    scanf("%i", &seg);
    if (seg == 1){
        for (int i = (elec - 1); i < *numPersonas; ++i) {
            personas[i] = personas[i+1];
        }
    }
    (*numPersonas)--;
    printf("\n");
    mostrarListado(personas, *numPersonas);
    printf("\n");

}

#define NOMBRE 1000

int GuardarAgenda(TipoPersona *personas, int numPersonas){
    char NombreFichero[NOMBRE];
    char linea[10000];
    int seguro;
    int opcion;

    printf("Dame un nombre del fichero terminado en .txt:\n");
    scanf("%s", NombreFichero);
    FILE *fichero = fopen(NombreFichero, "r");
    if (fichero != NULL){
        printf("Ya existe. ¿Quieres sobreescribirlo?\n");
        printf("\t[0] SI\n");
        printf("\t[1] NO\n");
        scanf("%i", &seguro);
        while(seguro == 1){
            fclose(fichero);
            printf("¿Quieres salir o poner otro nombre?\n");
            printf("\t[1] Salir\n");
            printf("\t[2] Poner nombre\n");
            scanf("%i", &opcion);
            if (opcion == 1){
                return 0;
            }else{
                printf("Dame un nombre terminado en .txt\n");
                gets(NombreFichero);
                fichero = fopen(NombreFichero, "r");
            }
        }
    }

    fichero = fopen(NombreFichero, "w");
    for (int i = 0; i < numPersonas; ++i) {
        fprintf(fichero, "%i %s %s %i %i %s", i + 1, personas[i].nombre, personas[i].apellidos,
                personas[i].telefono, personas[i].edad,
                imprimirContacto(personas[i].tipo));
        printf("\n");

    }
    fclose(fichero);
    fichero = fopen(NombreFichero, "r");
    while(!feof(fichero)){
        fgets(linea, 20, fichero);
        printf("%s", linea);
    }
}


int main() {
    int num = 1;
    int numPersonas = 0;
    int *fichero;
    TipoPersona *personas = malloc(sizeof(TipoPersona) * TAMANIO_LISTA);
    if (personas == NULL){
        printf("No hay memoria");
        return -1;
    }

//    strcpy(personas[0].nombre, "Alberto");
//    strcpy(personas[0].apellidos, "Garcia");
//    personas[0].edad = 30;
//    personas[0].telefono = 6550284;
//    personas[0].tipo = CONOCIDO;
//    numPersonas++;

    while (num != 0) {
        printf("1-Listado de personas\n");
        printf("2-Nueva persona\n");
        printf("3-Borrar persona\n");
        printf("4-Guardar agenda en fichero\n");
        printf("5-\n");
        printf("0-Salir\n");
        printf("Elige una opcion:\n");
        scanf("%i", &num);


        switch (num) {
            case Listado:
                printf("Has elegido la opcion listado\n");
                mostrarListado(personas, numPersonas);
                break;
            case Nueva_Persona:
                printf("Has elegido la opcion nueva personas\n");
                numPersonas++;
                NuevaPersona(personas, numPersonas);
                mostrarListado(personas, numPersonas);
                break;
            case Borrar_Persona:
                printf("Has elegido la opcion borrar personas\n");
                BorrarPersona(personas, &numPersonas);
                //mostrarListado(personas, numPersonas);
                break;
            case Salir:
                printf("Has elegido la opcion salir\n");
                mostrarListado(personas, numPersonas);
                num = 0;
                break;
            case Guardar_Agenda:
                GuardarAgenda(personas, numPersonas);
                printf("%i\n", fichero);
                break;
            default:
                printf("No has elegido ninguna de las opciones que se pueden elegir\n");
        }
    }

    free(personas);
    return 0;
}
