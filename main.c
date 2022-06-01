#include <stdio.h>
#include <stdlib.h>
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

void cartel(String nombre_archivo){
	FILE * archivo = fopen(nombre_archivo, "r");
	String buffer;

	if (archivo==NULL){
		printf("Error al abrir el archivo %s", nombre_archivo);
	}else{
		while (!feof(archivo)){
			fgets(buffer,MAXIMA_LONGITUD_CADENA,archivo);
			printf("%s", buffer);
		}
		fclose(archivo);
	}
	fflush(stdin); getchar();
}

void clrscr(){
	system("cls");
}

void inicio(){
	cartel("Portada.txt");
	clrscr();
	cartel("Instrucciones.txt");
	clrscr();
}

void espacio(int n){
	int i;
	for(i=0;i<n;i++){
		printf("\n");
	}
	for(i=0;i<6;i++){
		printf("     ");
	}
}

void agregar_arbol(arbol a){
	static int cantidad = 0;
	String nuevo,actual,pregunta,res;
	espacio(2);
	printf("Que animal es?:  ");
	fflush(stdin); gets(nuevo);
	strcpy(actual, a->cadena);
	espacio(2);
	printf("Que lo diferencia del/de la %s?  ",actual);
	fflush(stdin); gets(pregunta);
	espacio(2);
	printf("En ese caso, el/la %s %s?  ", nuevo, pregunta);
	fflush(stdin); gets(res);
	strcpy(a->cadena, pregunta);

	if ((!strcmp(res, "Si"))||(!strcmp(res, "SI"))||(!strcmp(res, "si"))){
		a->der = nuevo_nodo(nuevo);
		a->izq = nuevo_nodo(actual);
		cantidad++;
	}else{
		if ((!strcmp(res, "No"))||(!strcmp(res, "NO"))||(!strcmp(res, "no"))){
			a->izq = nuevo_nodo(nuevo);
			a->der = nuevo_nodo(actual);
			cantidad++;
		}else{
			printf("Ingrese datos correctos\n");
		}
	}
}

void adivina(arbol a, String opc){
	if (a!=NULL){
		if ((a->der==NULL)&&(a->izq==NULL)){
			espacio(2);
			printf("El animal en el que esta pensando es : %s? ", a->cadena);
			scanf("%s", opc);
			if ((!strcmp(opc, "no"))||(!strcmp(opc, "NO"))||(!strcmp(opc, "No"))){
				agregar_arbol(a);
			}else{
				espacio(3);
				cartel("Gane.txt");
			}
		}else{
			espacio(2);
			printf("%s? ",a->cadena);
			scanf("%s", opc);
			if ((!strcmp(opc, "no"))||(!strcmp(opc, "NO"))||(!strcmp(opc, "No"))){
				adivina(a->izq,opc);
			}else{
				if ((!strcmp(opc, "si"))||(!strcmp(opc, "SI"))||(!strcmp(opc, "Si"))){
					adivina(a->der,opc);
				}
			}
		}
	}
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

int main(int argc, char const *argv[]){
	String opc;
	FILE * archivo;
	arbol a = inicializa();

	archivo = fopen("arbol.bin", "rb");
	if (archivo != NULL){
		leer_arbol(&a, archivo);
		fclose(archivo);
	}

	inicio();
	espacio(5);
	printf("Estas pensando en un animal? ");
	scanf("%s", opc);
	while ((!strcmp(opc, "si"))||(!strcmp(opc, "SI"))||(!strcmp(opc, "Si"))){
	    adivina(a,opc);
	    clrscr();
	    inicio();
	    espacio(5);
	    printf("Estas pensando en un animal? ");
		scanf("%s", opc);
	}

	archivo = fopen("arbol.bin", "wb");
	if (archivo != NULL){
		guardar_arbol(a, archivo);
		fclose(archivo);
	}

	eliminar_arbol(&a);

	return 0;
}
