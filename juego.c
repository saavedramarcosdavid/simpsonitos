#include "juego.h"

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