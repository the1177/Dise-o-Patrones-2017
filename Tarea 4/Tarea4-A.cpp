#include <stdio.h>
#include <string.h>

/*********************	TAREA #4 - Juego de la vida  ****************************

	

*********************************************************************************/

// Definición de valores máximos del plano.
#define T 10
#define MAX 20

// Estructura autómata
// ( - ) representa un espacio muerto
// ( # ) representa un espacio vivo
struct PlanoVida
{
	char Plano[MAX][MAX];
};

// Estructura de linea de tiempo de autómatas
struct LineaTiempoCircular
{
	PlanoVida TiempoPlano[T];
	int last;
};


// Prototipos de funciones
void ImprimeError(int num);
PlanoVida *CrearPlano(int *errorHandler);
void ImprimePlano(PlanoVida *PlanoImprimir);
LineaTiempoCircular *CrearTiempo(PlanoVida *PrimerPlano);
PlanoVida *Dios(PlanoVida *PlanoBusqueda);
void InQueque(PlanoVida *PlanoIn, LineaTiempoCircular *Tiempo);
PlanoVida DeQueue(LineaTiempoCircular *Tiempo);


int main()
{
	// Inicializando variables
	int *error = 0;
	PlanoVida *PlanoActual = CrearPlano(error);
	
	// Instrucciones
	printf("===================================================\n");
	printf("||               JUEGO DE LA VIDA                ||\n");
	printf("||             Por Jacob Elías Torres            ||\n");
	printf("===================================================\n\n");
	printf("Bienvenido al juego de la vida.\n");
	printf("Por favor indíca cuántos elementos vivos habrá.\n");
	printf("VIVOS; "); int vivos; scanf("%d", &vivos);

	// Verificar que sea entero positivo dentro de los límites
	while (vivos < 0 || vivos > 400)
	{
		printf("\nNúmero de elementos vivos incorrecto.\n");
		printf("Por favor ingresa valor entre 0 - 400; ");
		printf("VIVOS; "); scanf("%d", &vivos);
	}
	printf("Correcto. Habrá %d elementos vivos.\n", vivos );
	ImprimePlano(PlanoActual);

	// Ingresar posición de elementos vivos e imprimir plano actual.
	for (int i = 1; i < vivos+1; ++i)
	{
		//ImprimePlano(PlanoActual);
		printf("Indica la posición del elemento #%d. (FILA COLUMNA); ", i );
		char fila; int columna; scanf(" %c %d", &fila, &columna);
		PlanoActual -> Plano[fila-65][columna-1] = '#';
	}	ImprimePlano(PlanoActual);

	// Comienza ciclo del juego de la vida
	printf("======================================================================\n");
	printf("\n\n"); printf("Elementos agregados. Todo listo para comenzar.\n");
	printf("Instrucciones; Oprima 0 para avanzar de cuadro, 9 para terminar.\n");
	int current; 
	LineaTiempoCircular *Tiempo = CrearTiempo(PlanoActual);

	// 0 - Siguiente cuadro || 9 - Terminar
	while (current != 9)
	{
		scanf("%d", &current);
		ImprimePlano(PlanoActual);
		printf("Instrucciones; Oprima 0 para avanzar de cuadro, 9 para terminar.\n");
		PlanoActual = Dios(PlanoActual);
		InQueque(PlanoActual, Tiempo);
	}

	printf("Programa terminado.\n");
	return 0;
}
// ----------------------  Funciones  -----------------------

// Función para imprimir mensaje de error
void ImprimeError(int num)
{
	const char *cadena[] = {"Hubo un error inesperado","Memoria insuficiente.","Cola Llena"};
	printf("ERROR; %s\n", *cadena[num] );
	return;
}

// Función para inicializar Plano de la vida
PlanoVida *CrearPlano(int *errorHandler)
{
	PlanoVida *NuevoPlano = new PlanoVida;
	if ( (NuevoPlano = new PlanoVida) == NULL )
	{
		ImprimeError(1);
		*errorHandler = 1;
		return NuevoPlano;
	}
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			NuevoPlano -> Plano[i][j] = '-';
		}
	}
	return NuevoPlano;
}

// Función para crear linea de tiempo de autómatas
LineaTiempoCircular *CrearTiempo(PlanoVida *PrimerPlano)
{
	LineaTiempoCircular *NuevaLineaDelTiempo = new LineaTiempoCircular;
	if ( (NuevaLineaDelTiempo = new LineaTiempoCircular) == NULL )
	{
		ImprimeError(1);
		return NuevaLineaDelTiempo;
	}
	NuevaLineaDelTiempo -> TiempoPlano[0] = *PrimerPlano;
	NuevaLineaDelTiempo -> last = 0;
	return NuevaLineaDelTiempo;
}

// Función todopoderosa que da y quita vida.
// Revisa los cuadros del plano y búsca coincidencias en las reglas;
// CASILLA VIVA;
// 		1 - De 0 a 1 vecinos vivo = MUERE
// 		2 - De 4 a 8 vecinos vivos = MUERE
// 		3 - De 2 a 3 vecinos vivos = SOBREVIVE
// CASILLA MUERTA;
//		1 - Solo con 3 vecinos vivos = NACE
PlanoVida *Dios(PlanoVida *PlanoBusqueda)
{
	PlanoVida *DIOS = CrearPlano(0);
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			int vecinos = 0;

			// Busqueda en cuadrantes de arriba
			if(PlanoBusqueda -> Plano[(i%20)-1][(j%20)-1] == '#'){vecinos++;}
			if(PlanoBusqueda -> Plano[(i%20)-1][(j%20)] == '#'){vecinos++;}
			if(PlanoBusqueda -> Plano[(i%20)-1][(j%20)+1] == '#'){vecinos++;}

			// Busqueda en laterales
			if(PlanoBusqueda -> Plano[(i%20)][(j%20)-1] == '#'){vecinos++;}
			if(PlanoBusqueda -> Plano[(i%20)][(j%20)+1] == '#'){vecinos++;}

			// Busqueda en cuadrantes de abajo
			if(PlanoBusqueda -> Plano[(i%20)+1][(j%20)-1] == '#'){vecinos++;}
			if(PlanoBusqueda -> Plano[(i%20)+1][(j%20)] == '#'){vecinos++;}
			if(PlanoBusqueda -> Plano[(i%20)+1][(j%20)+1] == '#'){vecinos++;}


			// Aplicando reglas
				// Si ACTUAL está vivo
			if(PlanoBusqueda -> Plano[(i%20)][(j%20)] == '#')
			{
				// Regla 1
				if(vecinos == 0 || vecinos == 1)
				{
					DIOS -> Plano[(i%20)][(j%20)] == '-';
				}
				// Regla 2
				if (vecinos >= 4 && vecinos <= 8)
				{
					DIOS -> Plano[(i%20)][(j%20)] == '-';
				}
				// Regla 3
				if(vecinos == 2 || vecinos == 3)
				{
					DIOS -> Plano[(i%20)][(j%20)] = '#';
				}
			}
				// Si ACTUAL está muerto
			if(PlanoBusqueda -> Plano[(i%20)][(j%20)] == '-')
			{
				if (vecinos == 3)
				{
					DIOS -> Plano[(i%20)][(j%20)] = '#';
				}
			}
		}
	}
	return DIOS;
}

// Función para meter planos al tiempo
void InQueque(PlanoVida *PlanoIn, LineaTiempoCircular *Tiempo)
{
	if ( (Tiempo -> last) > T)
	{
		ImprimeError(2);
		return;
	}
	int LST = Tiempo -> last % T;
	Tiempo -> TiempoPlano[LST++] = *PlanoIn;
	Tiempo -> last = LST++;
	return;
}

// Función para sacar planos del tiempo
PlanoVida DeQueue(LineaTiempoCircular *Tiempo)
{
	if ( (Tiempo -> last) < 0)
	{
		ImprimeError(0);
		PlanoVida PlanoBasura;
		return PlanoBasura;
	}
	Tiempo -> last = (Tiempo -> last)-1;
	return (Tiempo -> TiempoPlano[Tiempo -> last]);
}


// Función para imprimir mi elegante plano de la vida ;-)
void ImprimePlano(PlanoVida *PlanoImprimir)
{
	printf("\n");
	printf("======================================================================\n");
	printf("======================================================================\n");
	printf("======= 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20  ==\n");
	printf("======================================================================\n");
	for (int i = 0; i < MAX; ++i)
	{
		printf("== %c ==", 65+i );
		for (int j = 0; j < MAX; ++j)
		{
			printf(" %c ", PlanoImprimir -> Plano[i][j]);
		}
		printf(" ==\n");
	}
	printf("======================================================================\n");
	printf("======================================================================\n\n");
}