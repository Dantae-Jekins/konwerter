#ifndef KOWERTER
#define KONWERTER

#include <stdio.h>
#include <stdlib.h>
#include "j-tools/j_tools.h"


// Function to scan stdinput
void *scanner(char flag[], FILE *file)
{
  if (str_match(flag, "-f"))
  {
    printf("\n Flag not yet available");
    return NULL;
  }

  else if (str_match(flag, "-i"))
  {
    char reader;
    int halt = 1;
    int *output = malloc(sizeof(int));
    *output = 0; 

    while (EOF != (reader = fgetc(file)) && reader != '\n')
    {
      if (reader != '0' && halt != 0)
        halt = 0; // ignore starting zeros.

      if (halt != 1)
      {
        if (reader >= 48 && reader <= 57)
          reader -= 48;

        *output *= 10;
        *output += reader;
      }
    }

    return output;
  }

  else if (str_match(flag, "-c"))
  {

    int halt = 1;
    char *output;
    size_t counter = 0;
    output = malloc(sizeof(char) * 1);

    while (EOF != (output[counter] = fgetc(file)) && output[counter] != '\n')
    {
      if (output[counter] != '0' && halt != 0)
        halt = 0; //ignore starting zeros
                  //strings could actually take them, but i'll make a flag
                  //later on for this, currently it's mainly about reading hexa.

      if (halt != 1)
        output = realloc(output, sizeof(char) * ((counter += 1) + 1));
    }

    output[counter] = '\0';
    return output;
  }

  else
  {
    return NULL;
  }
}

// converte a base de um número para decimal
int to_dec(int input, int sys)
{
  char *aux = ret_str(input);
  int len   = str_len(aux) - 1;
  int dec = 0;

  // transforma em inteiros
  for (int i = 0; i <= len; i++)
    aux[i] -= '0'; 
 
  // extraimos o decimal
  for (int i = 0; i <= len; i++)
    dec += int_podniesc(sys, i) * aux[len - i];
  
  return dec;
}

// converte de um decimal para outro
int to_sys(int input, int sys)
{
  // descobrimos o tamanho que o novo resultado venha a ter
  int len = 0; 
  int aux = input;
  while (aux != 0)
  {
    len ++;
    aux /= sys;
  }

  // agora que sabemos o tamanho q vai ter
  int *var = malloc(sizeof(int)*len);
  int i = 0;
  while (input != 0)
  {
    var[i] = input % sys;
    input /= sys;
    i++;
  }

  // extraídos os restos basta inverter
  // e tirar o valor inteiro da string
  // um array não tem um ponto de parada
  invert_array(var, len);
  char *pre_ret = to_str(var, len);
  
  // por isso transformamos em uma str
  int ret = ret_int(pre_ret);
  free(pre_ret);
  free(var);

  return ret;
}

// Função para mudar bases numéricas
// altera o conteúdo de input como resultado.
void konwerter(void *input, int insys, int outsys)
{
  // Se não, checa se os sistemas não precisam de caracteres
  if (insys <= 10 && insys >= 2 && outsys <= 10 && outsys >= 2)
  {
    // Se sim, checa se o sys de entrada e o de saída são iguais
    if (insys == outsys)
      return;

      int *aux = (int *) input;

    // Se não, transforma a saída em decimal
    int  dec = to_dec(*aux, insys);
    // Se a saída for em decimal, retorna isto como string
    if (outsys == 10)
    {
      *aux = dec;
      return;
    }
    
    // Se não, transforma na respectiva base
    *aux  = to_sys(dec, outsys);
    return;
  }
  // Se estiver acima retorna NULL como erro.
  else
  {
    printf("\nkonwerter function - invalid arguments");
  }
}

void clearinput(void)
{
  while (getchar() != '\n');
}


int main(int argc, char *argv[])
{
  // no special commands
  if (argc == 1)
  {
    int osys; // i dont like declaring in 
    int sys;  // a single line :)
    int input;

    system("@cls||clear");
    /*
    printf( "\n Konwerter program"
            "\n This program only supports "
            "\n values within 32-bit limit "
            "\n (2147483647).\n"
            "\n Hexadecimal's only available"
            "\n in special flags mode, through"
            "\n the terminal.\n");

    printf( "\n------------------------------\n"
            "\n Select the input numeric system:  ");      
    scanf("%d", &sys);
    
    printf( " Select the output numeric system: ");
    scanf("%d", &osys);
    
    while(sys > 10 || sys < 2 || osys > 10 || sys < 2)
    {
      printf( "\n The only numeric systems available"
              "\n without special flags are within 10"
              "\n and 2, please select again:\n");
      printf( "\n------------------------------\n"
              "\n Select the input numeric system:  ");
      scanf("%d", &sys);

      printf(" Select the output numeric system: ");
      scanf("%d", &osys);
    }
    */
    sys = 2;
    osys = 4;   
    while(1)
    { 
    printf( "\n The number to konwert:\n ");
    scanf("%d", &input);

    konwerter(&input, sys, osys);
    printf("\n retorno : %d", input);
    }
  }
  else
  {
    printf("Testin");
  }
}
#endif
