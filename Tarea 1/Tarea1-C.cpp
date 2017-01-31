#include <stdio.h>
#include <stdlib.h>

// Función que recibe un arreglo bidimensional que contiene una matriz
// junto con numero de filas y columas, y regresa la matriz traspuesta.
int **matrizTraspuesta(int filas, int columnas, int **matriz)
{
	// Declaramos matriz traspuesta, ahora filas serán columnas y viceversa.
	int nuevasFilas = columnas; int nuevasColumnas = filas;
	int **Traspuesta = 0;
	Traspuesta = new int*[nuevasFilas];

	for (int i = 0; i < nuevasFilas; ++i)
	{
		Traspuesta[i] = 0;
		Traspuesta[i] = new int[nuevasColumnas];
		for (int j = 0; j < nuevasColumnas; ++j)
		{
			Traspuesta[i][j] = matriz[j][i];
		}
	}

	return Traspuesta;
}

int main()
{
	// Declarando variables y pidiendo filas y columnas.
	int filas, columnas;
	printf("¿Cuántas filas tiene su matriz?: "); scanf("%d", &filas);
	printf("¿Cuántas columnas tiene su matriz?: "); scanf("%d", &columnas);

	// Declarando matriz y recibiendo valores.
	int **matriz = 0;
	matriz = new int*[filas];
	int contadorDisplay = 1;
	for (int i = 0; i < filas; ++i)
	{
		matriz[i] = 0;
		matriz[i] = new int[columnas];
		printf("Por favor, ingrese los %d numeros de la %d fila.\n", columnas, contadorDisplay);
		for (int j = 0; j < columnas; ++j)
		{
			scanf("%d", &matriz[i][j] );
		}
		contadorDisplay++;
	}printf("\n");

	
	// Ahora mandamos la matriz a la función para recibir la matriz traspuesta.
	int **matrizT = matrizTraspuesta(filas, columnas, matriz);
	if ( matrizT == 0)
	{
		printf("Hubo un error en la ejecución. No hay memoria disponible.\n");
	}

	// Tenemos la matriz traspuesta, ahora falta imprimir en pantalla.
	// Recordemos que en la traspuesta se invierten las filas y columnas.
	for (int i = 0; i < columnas; ++i)
	{
		for (int j = 0; j < filas; ++j)
		{
			printf("%d ", matrizT[i][j] );
		}
		printf("\n");
	}

	return 0;
}