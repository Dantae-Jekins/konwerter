#ifndef J_WEKTORY_H
#define J_WEKTORY_H

// V.1

#include <stdlib.h>
#include "j_math.h"

// retorna TAM elementos de array em outro vetor
int *cpy_array(int *array, int tam)
{
    int *aux = (int*)malloc(sizeof(int)*tam);
    for(int i = 0; i < tam; i++)
        aux[i] = array[i];
    return aux;
}

// limpa um array de tam posições (seta para 0)
void clr_array(int *array, int tam)
{
    for (int i = 0; i < tam; i ++)
        array[i] = 0;
}

void inv_array(int *array, int tam)
{
    int *aux = cpy_array(array, tam); tam--;
    for(int i = 0; i <= tam; i++)
          array[i] = aux[tam-i]; 

    free(aux);
}

#endif