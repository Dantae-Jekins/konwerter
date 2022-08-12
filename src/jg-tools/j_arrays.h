#ifndef J_WEKTORY_H
#define J_WEKTORY_H

// V 1.1

#include <stdlib.h>
#include "j_math.h" 
#include <time.h>


// Retorna TAM elementos de array em outro vetor. Necessário liberar memória alocada.
int *cpy_array(int *array, int tam)
{
    int *aux = (int*)malloc(sizeof(int)*tam);
    for(int i = 0; i < tam; i++)
        aux[i] = array[i];
    return aux;
}


// Limpa um array de tam posições (seta para 0)
void clr_array(int *array, int tam)
{
    for (int i = 0; i < tam; i ++)
        array[i] = 0;
}


// Inverte um array
void inv_array(int *array, int tam)
{
    int *aux = cpy_array(array, tam); tam--;
    for(int i = 0; i <= tam; i++)
          array[i] = aux[tam-i]; 

    free(aux);
}


// Preenche um array de valores aleatórios, para servir de sample.
void fill_array(int *array, int tam, int max, int min)
{
  int intervalo = max - min + 1;
  for (int i = 0; i < tam; i++)
    array[i] = (rand()%intervalo) + min;
  
}

#endif
