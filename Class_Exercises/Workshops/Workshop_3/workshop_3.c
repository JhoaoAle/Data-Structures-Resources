#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101
#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_GENRE 50
#define MAX_COMMENT 200


typedef struct Libro {
    char titulo[MAX_TITLE];
    char autor[MAX_AUTHOR];
    int volumenDistribucion;
    int calificacion;
    char disciplina[MAX_GENRE];
    char comentarios[MAX_COMMENT];

    struct Libro* nextAutor;
    struct Libro* nextDisciplina;
} Libro;



Libro* tablaAutores[TABLE_SIZE];

Libro* tablaDisciplinas[TABLE_SIZE];


unsigned int hash(const char* str) {
    unsigned int hash = 0;

    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }

    return hash % TABLE_SIZE;
}


Libro* crearLibro(
    const char* titulo,
    const char* autor,
    int volumen,
    int calificacion,
    const char* disciplina,
    const char* comentarios
) {
    Libro* nuevo = (Libro*) malloc(sizeof(Libro));

    strcpy(nuevo->titulo, titulo);
    strcpy(nuevo->autor, autor);
    nuevo->volumenDistribucion = volumen;
    nuevo->calificacion = calificacion;
    strcpy(nuevo->disciplina, disciplina);
    strcpy(nuevo->comentarios, comentarios);

    nuevo->nextAutor = NULL;
    nuevo->nextDisciplina = NULL;

    return nuevo;
}


void insertarLibro(Libro* libro) {
    unsigned int indexAutor = hash(libro->autor);
    libro->nextAutor = tablaAutores[indexAutor];
    tablaAutores[indexAutor] = libro;

    unsigned int indexDisciplina = hash(libro->disciplina);
    libro->nextDisciplina = tablaDisciplinas[indexDisciplina];
    tablaDisciplinas[indexDisciplina] = libro;
}

Libro* mejorLibroPorAutor(const char* autor) {

    unsigned int index = hash(autor);

    Libro* actual = tablaAutores[index];
    Libro* mejor = NULL;

    while (actual != NULL) {

        if (strcmp(actual->autor, autor) == 0) {

            if (mejor == NULL ||
                actual->calificacion > mejor->calificacion) {

                mejor = actual;
            }
        }

        actual = actual->nextAutor;
    }

    return mejor;
}

void rankingPorDisciplina(const char* disciplina) {

    unsigned int index = hash(disciplina);

    Libro* lista[100];
    int cantidad = 0;

    Libro* actual = tablaDisciplinas[index];

    while (actual != NULL) {

        if (strcmp(actual->disciplina, disciplina) == 0) {
            lista[cantidad++] = actual;
        }

        actual = actual->nextDisciplina;
    }

    for (int i = 0; i < cantidad - 1; i++) {

        for (int j = i + 1; j < cantidad; j++) {

            if (lista[j]->volumenDistribucion >
                lista[i]->volumenDistribucion) {

                Libro* temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    printf("\nRanking de %s\n", disciplina);

    for (int i = 0; i < cantidad; i++) {

        printf(
            "%d. %s | Autor: %s | Ventas: %d\n",
            i + 1,
            lista[i]->titulo,
            lista[i]->autor,
            lista[i]->volumenDistribucion
        );
    }
}

int main() {

    for (int i = 0; i < TABLE_SIZE; i++) {
        tablaAutores[i] = NULL;
        tablaDisciplinas[i] = NULL;
    }

    Libro* l1 = crearLibro(
        "Cien años de soledad",
        "Gabriel Garcia Marquez",
        500000,
        10,
        "Realismo magico",
        "Obra maestra latinoamericana"
    );

    Libro* l2 = crearLibro(
        "El amor en los tiempos del colera",
        "Gabriel Garcia Marquez",
        300000,
        9,
        "Realismo magico",
        "Historia de amor clasica"
    );

    Libro* l3 = crearLibro(
        "Dune",
        "Frank Herbert",
        700000,
        10,
        "Ciencia ficcion",
        "Clasico de ciencia ficcion"
    );

    Libro* l4 = crearLibro(
        "Neuromancer",
        "William Gibson",
        250000,
        9,
        "Ciencia ficcion",
        "Fundador del cyberpunk"
    );


    insertarLibro(l1);
    insertarLibro(l2);
    insertarLibro(l3);
    insertarLibro(l4);

    Libro* mejor = mejorLibroPorAutor("Gabriel Garcia Marquez");

    if (mejor != NULL) {

        printf("=== Recomendacion Premium ===\n");

        printf("Titulo: %s\n", mejor->titulo);
        printf("Autor: %s\n", mejor->autor);
        printf("Calificacion: %d\n", mejor->calificacion);
    }


    rankingPorDisciplina("Ciencia ficcion");

    return 0;
}