#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Equipo {
	char nombre[24];
	int pts;
	float perdidos,ganados,empatados;
};
struct Equipo leeEquipos(struct Equipo e[10]);
void imprime(struct Equipo e);
void pregunta(struct Equipo e[10]);
void imprimeEquipos(struct Equipo e[10]);
float efectividad(struct Equipo e);
int main () {
	struct Equipo equipos[10];
	char ganador;
	leeEquipos(equipos);
	pregunta(equipos);
	imprimeEquipos(equipos);
	return 0;
}
struct Equipo leeEquipos(struct Equipo e[10]){
	FILE *tabla = NULL;
	int k;
	tabla = fopen("Resources/table.txt", "r");
	if (tabla == NULL){
		perror( "fopen failed" );
		exit(1);
	}
	for(k=0;k<10;k++)
		fscanf(tabla, "Equipo:%[^\t\n] Puntos:%d\nPartidos ganados:%f\nPartidos empatados:%f\nPartidos perdidos:%f\n\n",&e[k].nombre,&e[k].pts,&e[k].ganados,&e[k].empatados,&e[k].perdidos);
	fclose(tabla);
}
void imprime(struct Equipo e) {
	float efecti =efectividad(e);
	printf("\n\n\n%-10s tiene %03d pts  y una efectividad del %0.2f porciento \n", e.nombre,e.pts, efecti);
	printf("\nganados                 empatados                    perdidos\n");
	printf("\n   %0.0f                        %0.0f                            %0.0f\n", e.ganados,e.empatados,e.perdidos);
} 
float efectividad(struct Equipo e) {
	float efecti;
	efecti=(((e.ganados+e.empatados)/(e.ganados+e.empatados+e.perdidos))*100);
	return efecti;
}
void pregunta(struct Equipo e[10]){
	int x, loc, vis;
	char ganador;
	printf("\n\n");
	for(x=0;x<10;x++)
		printf("%s (%d)\n",e[x].nombre,x );
	printf("cual fue el equipo local? ");
	scanf("%d", &loc);
	printf("cual fue el equipo visitante? ");
	scanf("%d", &vis);
	getchar();
	printf("Quien gano el partido?  equipo local (l) ,visitnante (v) o empataron (e)\n");
	scanf("%c", &ganador);
	if(ganador=='v'||ganador=='V'){
		e[vis].ganados++;
		e[loc].perdidos++;
		e[vis].pts=e[vis].pts+3;
	}
	else if (ganador=='l'||ganador=='L'){
		e[vis].perdidos++;
		e[loc].ganados++;
		e[loc].pts=e[loc].pts+2;
	}
	else if (ganador=='e'||ganador=='E') {
		e[loc].empatados++;
		e[vis].empatados++;
		e[loc].pts++;
		e[vis].pts++;
	}
	else { 
		printf("ERROR RESULTADO INVALIDO");
		exit(0);
	}
}
void imprimeEquipos(struct Equipo e[10]){
	int x;
	struct Equipo temp;
	for (int i = 1; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (e[j].pts > e[i].pts) {
				temp = e[i];
				e[i] = e[j];
				e[j] = temp;
				}
			else if(e[j].pts == e[i].pts){
				if(e[j].perdidos < e[i].perdidos){
					temp = e[i];
					e[i] = e[j];
					e[j] = temp;
					}
				else if(e[j].perdidos == e[i].perdidos){
					if(e[j].ganados > e[i].ganados){
						temp = e[i];
						e[i] = e[j];
						e[j] = temp;
					}
				}
			}
		}
	}
	printf("\033[0;32m");
	imprime(e[9]);
	printf("\033[0m");
	for(x=8;x>0;x--){
		imprime(e[x]);
	}
	printf("\033[0;31m");
	imprime(e[0]);
	printf("\033[0m");
	printf("El equipo con mas puntos es\033[0;32m %s \033[0my el que tienen menos es\033[0;31m %s \033[0m\n",e[9].nombre,e[0].nombre);
}
