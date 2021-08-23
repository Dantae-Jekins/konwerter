#include <stdio.h>
#include <stdlib.h>

// Function to compare strings
int cmpStr(char str1[], char str2[])
{
  int x = 0;
  for (int i = 0; str1[i] != '\0'; i++)
  {
    //printf("\nReading cmpstr; index: %d", i);
    if (str1[i] != str2[i])
    {
      x = 1;
      break;
    }
  }
  return x;
}

// Função pra elevar o número
int podniesc(int num, int i)
{
  if (i == 0)
    return 1;

  else if (i == 1)
    return num;

  else if (i > 1)
  {
    int carry = num;
    while (i > 1)
    {
      num *= carry;
      i--;
    }
    return num;
  }

  return -1; // error
}

// Função logaritmica
int lg(int base, int num)
{
  int i;
  for (i = 1; num > base; i++)
    num /= base;

  return i;
}

// Function to transform a integer into an array
int *array(int integer, int size)
{
  int *carry = malloc(sizeof(int) * size);
  while (size > 0)
  {
    carry[size - 1] = integer % 10;
    integer /= 10;
    size--;
  }

  return carry;
}

// Função que serve para sinalizar erros no programa.
int error(int code)
{
  printf("testing");
}

// Function to scan stdinput
void *scanner(char flag[], FILE *file)
{
  if (cmpStr(flag, "-f") == 0)
  {
    printf("\n Flag not yet available");
    return NULL;
  }

  else if (cmpStr(flag, "-i") == 0)
  {
    char reader;
    int halt = 1;
    int *output = malloc(sizeof(int));
    *output = 0; // goddanm initialize issues

    while (EOF != (reader = fgetc(file)) && reader != '\n')
    {
      if (reader != '0' && halt != 0)
        halt = 0; // ignore starting zeros.

      if (halt != 1)
      {
        if (reader >= 48 && reader <= 57)
          reader -= 48;
        else
          error(1);

        *output *= 10;
        *output += reader;
      }
    }

    return output;
  }

  else if (cmpStr(flag, "-c") == 0)
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
    error(2);
    return NULL;
  }
}

// Function to change numeric bases
void *konwerter(void *input, int insys, int outsys, char *flag)
{

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Modo especial? (sistemas acima de decimal, ou codificados)
  if (flag == NULL)
  {

    // Se não, checa se os sistemas realmente estão de acordo
    if (insys <= 10 && insys >= 2 && outsys <= 10 && outsys >= 2)
    {
      // Se sim, checa se o sys de entrada e o de saída são iguais
      if (insys == outsys)
        return input;

      // Se são diferentes deve-se realizar as operações
      else
      {
        int *carry = input;
        int *decimal = malloc(sizeof(int) * 1); // musi byc wskaznik wracac
        *decimal = 0;
        // Checa se o sistema de entrada é 10
        if (insys != 10)
        {
          // Se não devemos transformar este em decimal
          int size = lg(10, *carry);
          int *integer = array(*carry, size);
          for (int i = 1; i <= size; i++)
          {
            *decimal += integer[size - i] * podniesc(insys, i - 1);
          }
          free(integer);
          // Se o sistema de saída é decimal
          // basta retornar o decimal gerado
          if (outsys == 10)
            return decimal;
        }
        // Se o sistema veio como decimal basta transferir ele.
        else
          *decimal = *carry;

        // Agora que temos o decimal basta transformar este
        // na base desejada.

        *carry = 0;
        int module = 1;
        while (*decimal >= outsys)
        {
          *carry += (*decimal % outsys) * module; // adere o módulo
          *decimal /= outsys;
          module *= 10; //multiplica o próximo módulo por 10*+
        }

        *carry += *decimal * module; // último dígito.
        return carry;
      }
    }
    // Se estiver acima retorna NULL como erro.
    else
      return NULL;
  }

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Se a flag estiver definida como especial, deve-se realizar
  // as operações conforme ela determina, um README será criado
  // para instruir sobre seu funcionamento.
  else
  {
    return NULL;
  }
}

void clearinput(void)
{
  while (getchar() != '\n')
    ;
}


int main(int argc, char *argv[])
{
  // no special commands
  if (argc == 1)
  {
    int osys; // i dont like declaring into 
    int sys;  // a single line :)
    int input;

    system("@cls||clear");

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

    printf( "\n The number to konwert:\n ");
    scanf("%d", &input);


    konwerter(&input, sys, osys, NULL);

    printf(" \n Your number in base %d system: \n %d\n ", osys, input);
  }
  else
  {
    printf("Testin");
  }
}
