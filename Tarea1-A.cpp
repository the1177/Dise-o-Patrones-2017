#include <stdio.h>
#include <stdlib.h>

// Funcion que junta dos arreglos y los guarda en un nuevo arreglo
// ordenados de menor a mayor. Se necesita especificar el tamaño de
// ambos arreglos cuando se llama la funcion. Usa apuntadores
int *juntarArreglos(int tamA, int tamB, int *arregloA, int *arregloB)
{
	int contador = 0;
	int tamTotal = tamA + tamB;
	int *arregloMaestro = 0;
	arregloMaestro = new int[tamTotal];

	// Guardando primer arreglo
	for (int i = 0; i < tamA; ++i)
	{
		arregloMaestro[contador] = arregloA[i];
		contador++;
	}

	// Guardando segundo arreglo
	for (int i = 0; i < tamB; ++i)
	{
		arregloMaestro[contador] = arregloB[i];
		contador++;
	}
	return arregloMaestro;
}

int main()
{
	// Declarando variables
	int tamA, tamB;

	// Ingresar tamaños de los dos arreglos
	printf("¿Qué tamaño tendrá el arreglo #1?:  "); scanf("%d", &tamA);
	printf("¿Qué tamaño tendrá el arreglo #2?:  "); scanf("%d", &tamB);
	printf("\n");

	// Ya podemos declarar arreglos
	int arregloA[tamA];
	int arregloB[tamB];

	// Ingresar los dos arreglos
	printf("Por favor, escriba el arreglo #1: ");
	for (int i = 0; i < tamA; ++i)
	{
		int current; scanf("%d", &current);
		arregloA[i] = current;
	}
	printf("Por favor, escriba el arreglo #2: ");
	for (int i = 0; i < tamB; ++i)
	{
		int current; scanf("%d", &current);
		arregloB[i] = current;
	}
	printf("\nProcesando arreglos... \n");
	printf("Arreglo resultante:  [ ");

	// Llamando a función
	int tamTotal = tamA + tamB;
	int *arregloFinal = juntarArreglos(tamA, tamB, arregloA, arregloB);

	// Acomodando arreglo final
	for (int i = 0; i < tamTotal; ++i)
	{
		for (int j = 0; j < (tamTotal-1); ++j)
		{
			if (arregloFinal[j] > arregloFinal[j+1])
			{
				int aux = arregloFinal[j];
				arregloFinal[j] = arregloFinal[j+1];
				arregloFinal[j+1] = aux;
			}
		}
	}

	// Imprimir arreglo final
	for (int i = 0; i < tamTotal; ++i)
	{
		printf("%d ", arregloFinal[i]);
	}

	printf(" ]\n");

	return 0;
}
