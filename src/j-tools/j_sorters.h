#ifndef J_SORTERS_H
#define J_SORTERS_H
#include <stdio.h>
#include <stdlib.h>

void swap(int *str, int i, int j)
{
  int aux = str[i];
  str[i] = str[j];
  str[j] = aux;
}

void merge(int *v, int *aux, int siz, int ini)
{
  int mei = (siz+1)/2 + ini;
  int fim = siz       + ini;
  int dir = mei;
  int esq = ini;

  int i = ini;
  while ((esq < mei) && (dir < fim))
  {
    if (v[esq] < v[dir])
      aux[i++] = v[esq++];
    else
      aux[i++] = v[dir++];
  }
  while (dir < fim)
    aux[i++] = v[dir++];
  while (esq < mei)
    aux[i++] = v[esq++];

  for(i = ini; i < (siz+ini); i++)
    v[i] = aux[i];
}

void merge_recursion(int *array, int *aux, int siz, int ini)
{
  if (siz == 1)
    return;

  merge_recursion(array, aux, (siz+1)/2, ini);
  merge_recursion(array, aux, siz/2, ini+(siz+1)/2);
  merge(array, aux, siz, ini);
}

// Algoritmos de ordenação:

void merge_sort(int *array, int size)
{
  int *aux = (int*) malloc(sizeof(int)*size);
  merge_recursion(array, aux, size, 0);
  free(aux);  
}

void selection_sort(int *array, int size)
{
	int ordenado = 0;
  for (int i = 0; i < size-1; i++)
  { 
		for (int j = i + 1; j < size; j++ )    
			if (array[i] > array[j])
			{
				ordenado = 0;
				swap(array, i, j);
			}
	}
}

void bubble_sort(int *array, int size)
{
	int ordenado = 0;
  for (int i = 0; i < size-1; i++)
	{
    for(int j = 0; j < size-1-i; j++)
			if(array[j] > array[j+1])
    	{
				ordenado = 0;
        swap(array, j, j+1);
  	  }
	}
}
#endif