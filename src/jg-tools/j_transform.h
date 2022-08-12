#ifndef CONV_H
#define CONV_H

// V 1.2

#include "j_math.h"
#include "j_strings.h"
#include <stdlib.h>

// Transforma um array de inteiros em uma string. Necessário liberar memória alocada.
char *array_str(int *array, int tam)
{
    char *aux = (char*)malloc(sizeof(char)*(tam+1));
    for (int i = 0; i < tam; i++)
        aux[i] = array[i] + '0';

    aux[tam] = '\0';
    return aux;
}

// Retorna uma string de um número. Necessário liberar memória alocada.
char *ret_str(int num)
{
    // aloca o espaço para o número
    int size    = int_log(num, 10);
    char *str   = (char*)malloc(sizeof(char)*(size+1));
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


// Retorna o valor correspondente unsigned de str1.
unsigned ret_uns(char *str1)
{
    int len = str_len(str1);
    u_int32_t ret = 0; int i = 0;
    while ( i < len)
    {
        ret *= 10;
        ret += str1[i] - '0';
        i++;
    }

    return ret;
}

// Retorna o valor correspondente inteiro de str1.
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
