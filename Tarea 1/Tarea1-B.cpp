#include <stdio.h>
#include <stdlib.h>

// Función que busca un arreglo en un arreglo de arreglos
// y regresa valor 0 si se encontró arreglo en arreglos o
// cualquier otro número en caso contrario.
int arregloEnArreglos(int numeroArreglos, int **arreglosComparar, int *tamArreglos, int *arreglo, int tam)
{
	// Variable para llevar control de búsqueda
	int encontrado = 0;

	// Comparamos primero los tamaños, en caso de no encontrar
	// coincidencia, terminar la comparación. 
	for (int i = 0; i < numeroArreglos; ++i)
	{
		if (tamArreglos[i] == tam)
		{
			// Se encontró coincidencia, comparar elementos
			int coincidencias = 0;
			for (int j = 0; j < tamArreglos[i]; ++j)
			{
				for (int h = 0; h < tam; ++h)
				{
					if ( arreglosComparar[i][j] == arreglo[h] )
					{
						coincidencias++;
					}
				}
			}
			if (coincidencias == tam)
			{
				return encontrado;
			}
		}
	}
	encontrado++; 
	return encontrado;
}

int main()
{
	// Preguntamos cuantos conjuntos tendremos
	printf("¿Cuántos conjuntos tendremos?:  ");
	int numeroArreglos; scanf("%d", &numeroArreglos);

	// Guardamos los tamaños de los arreglos
	int *tamArreglos = 0;
	tamArreglos = new int[numeroArreglos];
	for (int i = 0; i < numeroArreglos; ++i)
	{
		printf("Ingrese tamaño de arreglo índice #%d: ", i );
		scanf("%d", &tamArreglos[i] );
	}

	// Ahora pediremos los arreglos, sabiendo de antemano los tamaños
	int **arreglosComparar = 0;
	arreglosComparar = new int*[numeroArreglos];
	for (int i = 0; i < numeroArreglos; ++i)
	{
		arreglosComparar[i] = new int[tamArreglos[i]];
		printf("Por favor, ingrese %d valores del arreglo índice %d: ", tamArreglos[i], i );
		for (int j = 0; j < tamArreglos[i]; ++j)
		{
			scanf("%d", &arreglosComparar[i][j] );
		}
	}
	
	// Pediremos el tamaño del arreglo a comparar
	printf("Por favor, ingrese el tamaño del arreglo para comparar: ");
	int tam; scanf("%d", &tam);

	// Ahora pedimos el arreglo
	printf("Ingrese los %d valores del arreglo: ", tam);
	int *arreglo = 0;
	arreglo = new int[tam]; 
	for (int i = 0; i < tam; ++i)
	{
		int current; scanf("%d", &arreglo[i]);
	}
	printf("\n");

	// Ya que tenemos todo, mandamos a nuestra función todo para comparar.
	int respuesta = arregloEnArreglos(numeroArreglos, arreglosComparar, tamArreglos, arreglo, tam);
	if (respuesta == 0)
	{
		printf("Arreglo encontrado.\n");
	}
	else
	{
		printf("Arreglo NO encontrado.\n");
	}
	return 0;
}