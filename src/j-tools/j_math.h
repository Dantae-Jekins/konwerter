#ifndef J_MATH_H
#define J_MATH_H
#include <math.h>

double _pi = 3.1415926;
// potênciação
int int_podniesc(int num1, int base)
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

// função rápida
int int_sqrpodniesc(int num1)
{
  return num1*num1;
}

int faotorial(int num1)
{
  int i = num1;
  num1  = 1;
  
  while(i > 1)
    num1 *= i--;

  return num1; 
}
int int_log(int num1, int base)
{
  int i;
  for (i = 1; num1 >= base; i++)
    num1 /= base;

  return i;
}

// diferença entre 2 pontos
int int_module(int num1, int num2)
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