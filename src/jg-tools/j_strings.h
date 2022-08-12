#ifndef J_STRINGS_H
#define J_STRINGS_H

// V 1.3

#include<stdlib.h>


// Retorna o tamano da string
int str_len(char *string)
{
    int i = 0;
    while(string[i]!='\0') 
      i++;

    return i;
}


// Retorna uma cópia de uma string. Necessário liberar a memoria alocada.
char *str_copy(char *string)
{
    int tam = str_len(string);
    char *aux = (char*)malloc(sizeof(int)*(1+tam));
    for (int i = 0; i <= tam; i++)
        aux[i] = string[i];
    
    aux[tam] = '\0'; //coloca ponto de parada
    return aux;
}

// Separa uma string. Necessário liberar a memória alocada.
// Retorna várias strings, termina com uma string NULL
char **str_split( char *str, char keyword)
{
  int slen = str_len(str);
  int string = 0;
  int last_key = 0;

  char **ret = (char **) malloc(sizeof( char *));
  ret[0] = (char *) malloc(sizeof(char) * slen);
  
  int i = 0;
  int j = 0;
  for (; str[i] != '\0'; i++)
  {
    if (str[i] != keyword)
    {
      ret[string][j] = str[i];
      j++;
    }

    else
    {
      // len = tamanho da leitura, contando keyword (i - last_key), + espaço nulo (+1)
      int len = i - last_key + 1; 
      
      // achou keyword então aloca direito o espaço da string no contexto
      ret[string] = (char *) realloc(ret[string], sizeof(char) * (len));
      ret[string][len- 1] = '\0';

      last_key = i; // incrementa a partida
      string ++;  // incrementa a string a ser lida
      j = 0;
       
      // e aloca mais um espaço para a próxima string
      ret = ( char ** ) realloc(ret, sizeof(char *) * (string + 1));
      ret[string] = (char *) malloc(sizeof(char) * ( slen - last_key));
    }
  } 

  // terminou o for, aloca o espaço final
  int len = i - last_key + 1; 
  ret[string] = (char *) realloc(ret[string], sizeof(char) * (len));
  ret[string][len- 1] = '\0';

  last_key = i; // incrementa a partida
  string ++;  // incrementa a string a ser lida
  
  ret = ( char ** ) realloc(ret, sizeof(char *) * (string + 1));
  ret[string] = NULL;

  return ret;
}


// Retorna duas strings somadas. Necessário liberar a memória alocada.
char *str_concac(char *str1, char *str2)
{
  // adquire os tamanhos
  int len1 = str_len(str1);
  int len2 = str_len(str2);
  int end = len1 + len2;

  // aloca
  char *ret = (char*)malloc(sizeof(char) * (end + 1));
  ret[end] = '\0';

  int i;
  // percorre str1 0 -> len1
  for (i = 0; i < len1; i++)
    ret[i] = str1[i]; 
  
  // percorre str2 i -> end
  for (int j = 0; i < end; i++, j++)
    ret[i] = str2[j];

  return ret;
}


// Retorna str cortado entre start e end. Necessário liberar memória alocada
char *str_crop(unsigned int start, unsigned int end, char *str1)
{ 

  int size = end-start+1;
  char *str2 = (char*)malloc(sizeof(char)*(size));
  
  int i = 0;
  while((str1[start] != '\0') && (end > start))
  {
    str2[i++] = str1[start++];
  } 

  str2[size-1] = '\0'; // coloca ponto de parada
  return str2;
}


// Move i elementos de str2 para str1
void str_mov(int i, char *str1, char *str2)
{
  int j = 0;
  while( j < i )
  {
    str1[j] = str2[j];
    j++;
  }  
}


// Verifica se str1 == str2
int str_match(char *str1, char *str2)
{
    int i = 0;
    do
    {
        if(str1[i] != str2[i])
            return 0; // retorna falso
        
    } while( (str1[i] != '\0') && (str2[i++] != '\0') );

    return 1;
}

#endif
