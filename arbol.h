#ifndef ARBOL_FILE
#define ARBOL_FILE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXIMA_LONGITUD_CADENA 255

typedef char String[MAXIMA_LONGITUD_CADENA];

struct nodo{
	// Dato
	String cadena;
	// Ramas
	struct nodo *izq;
	struct nodo *der;
};

typedef struct nodo * arbol;

struct nodo * nuevo_nodo(String cadena);
arbol inicializa();
void eliminar_arbol(arbol * a);
void guardar_arbol(arbol a, FILE * archivo);
void leer_arbol(arbol * a, FILE * archivo);
void imprimir_arbol(arbol a);


#endif
