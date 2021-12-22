#ifndef KONWERTER
#define KONWERTER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jg-tools/jg_strings.h"
#include "scanner.h"

struct CHAVE
{
  int key_len;
  int use_len;
  char *keyword;
} key;


// seta a chave para o default, que é alfabética
void init_key()
{
  // letras maiúsculas 65 - 90
  // letras minúsculas 97 - 122
  // default = '0'..'9' 'A' .. 'Z' = 35 termos

  // qual é o tamanho total da chave
  key.key_len = 36;
  
  // qual é o tamanho a ser usado (hexa = 16)
  key.use_len = 35;

  key.keyword = malloc( sizeof(char) * key.key_len);
  for (int i = 0; i <= 9; i++)
      key.keyword[i] = '0' + i;
 
  for (int i = 0; i <= 25; i++)
    key.keyword[i + 10] = 'A' + i; 
}


// converte de uma letra para seu inteiro equivalente
int keyword_int( char val )
{
  for ( int i = 0; i <= key.use_len; i++)
  {
    if ( key.keyword[i] == val )
      return i;
  }
  
  printf(" CARACTERE NÃO VÁLIDO SENDO USADO : %c\n", val);
  printf(" CHAVE SENDO USADA PARA A OPERAÇÃO:\n >> ");
  for (int i = 0; i <= key.use_len; i++) printf("%c", key.keyword[i]);
  printf("\n TAMANHO: %d  ::  USADOS: %d \n", key.key_len, key.use_len);
  printf("\n ::TERMINANDO PROGRAMA PARA EVITAR PROBLEMAS::\n\n");
  exit(1);
}


// converte de um inteiro para seu char equivalente na tabela
char keyword_val( int val )
{
  if ( val <= key.use_len)
    return key.keyword[val];
  
  printf(" VALOR NÃO VÁLIDO SENDO USADO     : %d\n", val);
  printf(" CHAVE SENDO USADA PARA A OPERAÇÃO:\n >> ");
  for (int i = 0; i <= key.use_len; i++) printf("%c", key.keyword[i]);
  printf("\n TAMANHO: %d  ::  USADOS: %d \n", key.key_len, key.use_len);
  printf("\n ::TERMINANDO PROGRAMA PARA EVITAR PROBLEMAS::\n\n");
  exit(1);
}


// converte a base de um número para decimal
char *to_dec(char *input, int sys)
{
  key.use_len = sys;
  
  unsigned len  = str_len(input) - 1;
  int *aux = malloc(sizeof(int) * len+1);
  unsigned long dec = 0;
  // transforma em inteiros
  for (int i = 0; i <= len; i++)
  {
    aux[i] = keyword_int(input[i]);
  }

  // extraimos o decimal
  for (int i = 0; i <= len; i++)
    dec += int_pow(sys, i) * aux[len - i];

  free(aux); 
  return ret_str(dec);
}


// converte um decimal para outro sistema
char *to_sys(char *input, int sys)
{
  key.use_len = sys;
  
  // descobrimos o tamanho que o novo resultado venha a ter
  unsigned aux = ret_uns(input); 
  unsigned len = 0;
  // descobre quantas vezes venha a se transformar em inteiro
  while (aux != 0)
  {
    len ++;
    aux /= sys;
  }

  // agora que sabemos o tamanho que venha ter
  int *var = malloc(sizeof(int)*len);
  aux = ret_uns(input);
  int i = 0;
  while (aux != 0)
  {
    var[i] = aux % sys;
    aux /= sys;
    i++;
  }

  // extraídos os restos basta inverter,
  // transformarmos em string
  // e aplicarmos a chave de conversão
  inv_array(var, len); 
  char *ret = malloc(sizeof(char)*(len+1));
  for (i = 0; i < len; i++)
    ret[i] = keyword_val(var[i]);

  ret[i] = 0;

  free(var);
  return ret;
}


// Função para mudar bases numéricas de acordo com uma chave dada
// retorna o valor resultante 
char *konwerter(char *input, int insys, int outsys, char flag)
{
  // se estamos convertendo um arquivo
  if ( flag == 'f')
  {

  }
  
  // se estamos convertendo um valor solitário
  else if ( flag == 'v')
  {
    // se insys não é um decimal
    char *aux;
    if ( insys != 10 )
    {
      // transformamos para decimal
      // e retornamos se for necessário
      // apenas isto
      aux = to_dec(input, insys); 
      if ( outsys == 10 )
        return aux;
    }

      // se o sistema de saída não é decimal
      char *ret = to_sys(aux, outsys);
      free(aux); 
      return ret;
  }

  else
  {
    printf("\n konwerter: tipo %c não tratado", flag);
  }
}


// Função para eliminar a quebra do stdin
void clearinput(void)
{
  while (getchar() != '\n');
}


int main(int argc, char *argv[])
{
  // no special commands
  init_key();

  if (argc == 1)
  { 
    char *input  = input = scanner('s', stdin);
    char *result = konwerter(input, 2, 16, 'v');
    printf("%s", result);
    free(input);
    free(result); 
  }
}
#endif
