#ifndef J_MATH_H
#define J_MATH_H

// V 1.1

#include <math.h>


// Extrai um número elevado à uma base
int int_pow(int num1, int base)
{
    int aux = num1;
    if ((base == 0) || (num1 == 1))
        return 1;

    else if (base == 1)
        return num1;

    while(base > 1)
    {
        aux *= num1;
        base--;
    }

    return aux;
}


// Extrai o quadrado de um número
int int_sqr(int num1)
{
  return num1*num1;
}


// Extrai o fatorial de um número
int int_fat(int num1)
{
  int i = num1;
  num1  = 1;
  
  while(i > 1)
    num1 *= i--;

  return num1; 
}


// Extrai o logaritmo como inteiro
int int_log(int num1, int base)
{
  int i;
  for (i = 1; num1 >= base; i++)
    num1 /= base;

  return i;
}


// Diferença entre 2 pontos
int int_mod(int num1, int num2)
{
  if (num2 > num1)
  {
    num2 -= num1;
    return num2;
  }

  num1 -= num2;
  return num1;
}

#endif
