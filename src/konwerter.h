#ifndef KONWERTER
#define KONWERTER
#include<stdlib.h>
#include<stdio.h>
#include "jg-groups/jg_strings.h"

///!! VALORES MÁXIMOS PARA INTEIROS = 1.84e+19
///!! USO DE 64 BITS DE MEMÓRIA 
///
/// TODO em caso de criptografia de dados estruturados
/// (pacotes, arquivos), a estratégia é concatenar os bytes
/// (1 char = 1 byte = 8 bits) para o cálculo do konwerter, ou seja,
/// realizar os cálculos 

// chave de criptografia
typedef struct CHAVE
{
  u_int length;
  char *keyword;
} key; 


// array simples 
typedef struct ARRAY
{
  u_int length;
  u_int *nth;
} vec;


/// Gera um default binário
key key_binary()
{
  key ret;
  ret.length = 2;
  ret.keyword = (char *)malloc( sizeof(char) * ret.length);

  ret.keyword[0] = '0';
  ret.keyword[1] = '1';
  
  return ret;
}


/// Gera um default decimal
key key_decimal()
{
  key ret;
  ret.length = 10;
  ret.keyword = (char *) malloc(sizeof(char) * ret.length);

  for(int i = '0', j = 0; i <= '9'; i++, j++)
  {
    ret.keyword[j] = i;
  }
  
  return ret;
}


/// Gera uma nova chave específica
key key_new(char *keywords)
{
  key ret;
  ret.length = str_len(keywords);
  ret.keyword = str_copy(keywords);
  return ret; 
}

/// Gera uma nova chave vazia
key key_empty()
{
  key ret;
  ret.length = 0;
  ret.keyword = NULL;
  return ret;
}

/// Gera uma nova chave com carácteres ASCII
key key_ascii()
{
  key ret;
  ret.length = 256;
  ret.keyword = (char *) malloc(sizeof(char) * ret.length);
  // me parece que tem outra maneira de fazer isso
  for (u_int i = 0; i < ret.length; i++)
    ret.keyword[i] = i;

  return ret;
}

/// Compara duas chaves
/// retorna 0 se diferentes ou 1 se iguais
int key_compare(key key1, key key2)
{
  if (key1.length == key2.length)
  {
    for(u_int i = 0; i < key1.length; i++)
    {
      if (key1.keyword[i] != key2.keyword[i])
        return 0;
    }

    return 1;
  }

  return 0;
}


//libera a memória de uma chave
void key_free(key target)
{
  if (target.keyword != NULL)
  {
    free(target.keyword);
  }

  return;
}


// Recebe uma string e uma chave, e com base na chave
// retorna um vec (vetor) de inteiros respectivos da string (na base insys.length)
vec konwerter_decode(char *input, key insys)
{
  int length = str_len(input);
  vec ret;
  ret.length = length;
  ret.nth = (u_int *)malloc(sizeof(u_int) * length);

  for(u_int i = 0; i < ret.length; i++)
  {

    // extraimos o valor equivalente da chave do caractere no index "i"
    int index = -1;
    for(u_int  j = 0; j < insys.length; j++)
    {
      if (input[i] == insys.keyword[j]) index = j;
    }

    // não achou o caractere do input na chave, ou seja, impossível convertermos
    if (index == -1)
    {
      free(ret.nth);
      ret.length = 0;
      ret.nth = NULL;
      return ret;
    }

    else
    {
      ret.nth[i] = index;
    }
  }

  return ret;
}


// Recebe um vetor de inteiros e retorna uma 
// string com os caracteres correspondentes.
char *konwerter_encode(vec input, key outsys)
{ 
  if (input.length == 0 || input.nth == NULL)
    return NULL;

  char *ret = (char *) malloc(sizeof(char) * (input.length + 1));
  for(u_int i = 0; i < input.length; i++)
  {
    // erro 
    if (input.nth[i] >= outsys.length)
    {
      free(ret);
      return NULL;
    }

    ret[i] = outsys.keyword[input.nth[i]];
  }

  ret[input.length] = 0;
  return ret;
}


// Recebe um vec de inteiros, e transforma ele
// em um único inteiro em decimal (da BASE correspondente)
long int konwerter_dec( vec input, int base )
{
  if (input.length == 0 || input.nth == 0)
    return -1; // erro

  int index = input.length - 1;
  u_int64_t basis = 1;
  u_int64_t ret = 0;
  do
  {
    ret += input.nth[index] * basis;
    basis *= base;
  } while(index-- != 0);

  return ret;
}


/// Recebe um inteiro em decimal e transforma-o e
/// retorna um vec de inteiros correspondente.
vec konwerter_sys( u_int64_t input, int base)
{
  vec ret;
  ret.length = 0;
  u_int64_t aux;
  int index;

  if (base <= 1)
  { return ret; }


  // acha o tamanho do vetor
  aux = input;
  while(aux != 0)
  {
    aux /= base;
    ret.length += 1;
  }
  ret.nth = (u_int *) malloc(sizeof(u_int) * ret.length);

  // adicionamos os elementos
  aux = input;
  index = ret.length -1;
  while(aux != 0)
  {
    ret.nth[index] = aux % base;
    aux /= base;
    index --;
  }

  return ret;
}


// Função para mudar bases numéricas de acordo com uma chave dada
// Retorna o valor na base resultante
char *konwerter(char *input, key insys, key outsys)
{
  // checa se é redundante
  if (key_compare(insys, outsys))
  {
      return input;
  }

  // sistemas diferentes
  else
  {
    // transformamos input em inteiros trabalháveis
    vec aux_input = konwerter_decode(input, insys);
    if (aux_input.length == 0)
    {
      if (aux_input.nth != NULL)
        free(aux_input.nth);

      return NULL;
    }

    // mudamos a base de insys para decimal
    u_int64_t decimal = konwerter_dec(aux_input, insys.length);
    if (decimal < 0)
    {
      if (aux_input.nth != NULL)
        free(aux_input.nth);

      return NULL;
    }

    // mudamos a base de decimal para outsys
    vec aux_output = konwerter_sys(decimal, outsys.length);
    if (aux_output.length == 0)
    {
      if (aux_input.nth != NULL)
        free(aux_input.nth);
      
      if (aux_output.nth != NULL)
        free(aux_output.nth);
      
      return NULL;
    }
    
    char *ret = konwerter_encode(aux_output, outsys);
    
    free(aux_input.nth);
    free(aux_output.nth);
    return ret;

  }

  return NULL;
}

/*
int main(int argc, char **argv)
{
  key key1 = key_binary();
  key key2 = key_decimal();
  key key3 = key_new("01");
  key key4 = key_new("0123456789ABCDEF");
  if (argc <= 1) return 0;
  char *konwerted = konwerter(argv[1], key2, key1);
  printf("%s", konwerted);
  free(konwerted);

  key_free(key3);
  key_free(key1);
  key_free(key2);
  key_free(key4);
}*/

#endif
