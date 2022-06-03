#include "arbol.h"

struct nodo * nuevo_nodo(String cadena){
	// Solicitar memoria
	size_t tamanioNodo = sizeof(struct nodo);
	struct nodo *nodo = (struct nodo *)malloc(tamanioNodo);
	// Asignar el dato e iniciar hojas
	strcpy(nodo->cadena, cadena);
	nodo->izq = nodo->der = NULL;
	return nodo;
}

arbol inicializa(){
	// arbol a = nuevo_nodo("Gorrion");
	arbol a = NULL;
	return a;
}

void eliminar_arbol(arbol * a){
	if (a != NULL){
		eliminar_arbol(&(*a)->izq);
		eliminar_arbol(&(*a)->der);
		free(a);
	}
}

void guardar_arbol(arbol a, FILE * archivo){
	if (a != NULL){
		fprintf(archivo, "%s\n", a->cadena);
		guardar_arbol(a->izq, archivo);
		guardar_arbol(a->der, archivo);
	}else{
		fprintf(archivo, "%s\n", "NULL");
	}
}

void leer_arbol(arbol * a, FILE * archivo){
	String cadena;
	fgets(cadena, MAXIMA_LONGITUD_CADENA, archivo);
	if (!feof(archivo)){
		cadena[strlen(cadena)-1] = '\0';
		// printf("leido: %s\n", cadena);
		if(strcmp(cadena, "NULL")){
			*a = nuevo_nodo(cadena);
			leer_arbol(&((*a)->izq), archivo);
			leer_arbol(&((*a)->der), archivo);
		}
	}
}

void imprimir_arbol(arbol a){
	if (a != NULL){
		printf("%s, ", a->cadena);
		imprimir_arbol(a->izq);
		imprimir_arbol(a->der);
	}
}