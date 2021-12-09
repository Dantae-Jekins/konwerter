#ifndef J_WEKTORY_H
#define J_WEKTORY_H
#include <stdlib.h>
#include "j_math.h"

// retorna TAM elementos de array em outro vetor
int *copy_array(int *array, int tam)
{
    int *aux = (int*)malloc(sizeof(int)*tam);
    for(int i = 0; i < tam; i++)
        aux[i] = array[i];
    return aux;
}

// limpa um array de tam posições (seta para 0)
void clear_array(int *array, int tam)
{
    for (int i = 0; i < tam; i ++)
        array[i] = 0;
}

void invert_array(int *array, int tam)
{
    int *aux = copy_array(array, tam); tam--;
    for(int i = 0; i <= tam; i++)
          array[i] = aux[tam-i]; 

    free(aux);
}

// transforma um array de inteiros em uma string
char* to_str(int *array, int tam)
{
    char *aux = malloc(sizeof(char)*(tam+1));
    for (int i = 0; i < tam; i++)
        aux[i] = array[i] + '0';

    aux[tam] = '\0';
    return aux;
}

// retorna uma string de um número
char *ret_str(int num)
{
    // aloca o espaço para o número
    int size    = int_log(num, 10);
    char *str   = malloc(sizeof(char)*(size+1));
    str[size] = '\0';
    
    do
    {
        // num % 10 pega os primeiros digitos
        // num /= 10 diminui o tamanho de num
        size --;
        str[size] = num % 10 + '0'; 
        num /= 10;
    } while(size > 0);
    return str;
}


// retorna o valor correspondente unsigned de str1
unsigned ret_uns(char *str1)
{
    int len = str_len(str1);
    u_int32_t ret = 0; int i = 0;
    while ( i <= len)
    {
        ret *= 10;
        ret += str1[i] - '0';
    }

    return ret;
}

// retorna o valor correspondente inteiro de str1
int ret_int(char *str1)
{
    int neg = 0;
    if(str1[0] == '-')
        neg = 1;

    int len = str_len(str1);
    int ret = 0; int i = neg;
    
    while ( i < len )
    {
        ret *= 10;
        ret += str1[i] - '0';
        i++;
    }

    if (neg)
        return -ret;
    return ret;
}

#endif