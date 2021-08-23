#include <stdio.h>
#include <stdlib.h>





int *readInput()
{
  FILE *file = stdin;
  int *num;
  size_t size = 2, count = 0;

  num = malloc(sizeof(int) * size);

  while (EOF != (num[count] = fgetc(file)) && num[count] != '\n')
  {

    if (count + 1 == size)
    {

      num = realloc(num, sizeof(int) * (size += 1));

    }
    count++;
  }

  num[count] = -1;
  return num;
}

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

void *scanner(char flag[], FILE *file)
{
  if (cmpStr(flag, "-f") == 0)
  {
    char **output = NULL;
    return output;
    printf("\n Flag not yet available");
  }

  else if (cmpStr(flag, "-i") == 0)
  {
    char reader;
    int *output = malloc(sizeof(int));
    *output = 0; // goddanm initialize issues

    while (EOF != (reader = fgetc(file)) && reader != '\n')
    {
      if (reader >= 48 && reader <= 57)
        reader -= 48;
      //else
        //error(01); not ready yet
      output *= 10;
      *output += reader;
    }
    return output;
  }

  else if (cmpStr(flag, "-c") == 0)
  {

    char *output;
    size_t size = 1, counter = 0;
    output = malloc(sizeof(char) * size);

    while (EOF != (output[counter] = fgetc(file)) && output[counter] != '\n')
    {
      counter++;

      if (counter == size)
        output = realloc(output, sizeof(char) * (size += 1));
    }
    output[counter] = '\0';
    return output;
  }

  return NULL;
}

int arraySum(int *array, int size)
{
  int sum = 0;
  for (size_t i = 1, j = size; j > 0; i *= 10, j--, size--)
    sum += array[j - 1] * i;
  
  return sum;
}

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
}

int lg(int base, int num)
{

  int i;
  for (i = 1; num > base; i++)
    num /= base;

  return i;
}


int *integerValue(int flag, int *input)
{

  int wait = 0;
  int size = 0;

  while (input[wait] == 0)
    wait++;

  while (input[size] != -1)
    size++;

  size -= wait;

  if (wait > 0)
  {
    int *carry;
    carry = malloc(sizeof(int) * size + 1);
    for (size_t i = 0, j = wait; i <= size; i++, j++)
      carry[i] = input[j];
    
    input = carry;
  }

  if (flag == 0)
  {

    for (size_t i = 0; input[i] != -1; i++)
    {
      if (input[i] >= 48 && input[i] <= 57)
        input[i] -= 48;                     

      else if (input[i] >= 65 && input[i] <= 70)
        input[i] -= 55;

    }
  }
 
  else if (flag == 1)
  {
    for (size_t i = 0; input[i] != -1; i++)
    {
      if (input[i] >= 0 && input[i] <= 9)
        input[i] += 48;

      else if (input[i] >= 10 && input[i] <= 15)
        input[i] += 55;

    }
  }

  return input;
}

int *decKonwerter(int flag, int sys, int *input)
{

  int *output;
  int size = 0;
  int dec = 0;
  int hex = 0;

  while (input[size] != -1)
    size++;

  if (flag == 0)
  {

    dec = arraySum(input, size);
    size = 0;
    int carry = dec;
    while (carry >= sys)
    {

      carry /= sys;
      size++;
    }

    output = malloc(sizeof(int) * (size + 2));
    output[size + 1] = -1;
    for (carry = dec; size >= 0; size--)
    {
      output[size] = carry % sys;
      carry /= sys;
    }

    if (sys > 10)
      output = integerValue(1, output);

  }

  else if (flag == 1)
  {

    for (int i = size - 1, j = 0; i >= 0; i--, j++)
      dec += input[i] * podniesc(sys, j);



    size = lg(10, dec);                    
    output = malloc(sizeof(int) * size + 1); 
    output[size] = -1;                      
    for (int i = size - 1; i >= 0; i--, dec /= 10)
      output[i] = dec % 10;
      
  }
  else
  {
    printf("ERROR, função decOct FLAG INVÁLIDA");
  }

  return output;
}


void clearinput(void)
{
  while (getchar() != '\n')
    ;
}


void main()
{
  int base;
  int *bin = NULL, *oct = NULL, *dec = NULL, *hex = NULL;

  printf("\n\n Conversor hex/dec/oct/bin\n --------------------------------------------");
  printf("\n\n Por favor informe a base do valor de entrada: \n [0]-Hexa  [1]-Deci  [2]-Octa  [3]-Bin \n ");

  do
  {
    scanf("%d", &base);
    if (base != 0 && base != 1 && base != 2 && base != 3)
      printf("\n Este número não corresponde a uma base, insira um correto");

  } while (base != 0 && base != 1 && base != 2 && base != 3);

  clearinput();

  printf("\n\n Base do valor de entrada selecionada: ");

  switch (base)
  {
  case 0:

    printf(" Hexadecimal\n Insira o valor: ");

    hex = readInput();
    if (hex == NULL)
    {
      printf("ERRO HEX==NULL");
      break;
    }

    printf("\n hex : ");
    for (size_t i = 0; hex[i] != -1; i++)
      printf("%c", hex[i]);

    //converte em decimal
    dec = decKonwerter(1, 16,hex=integerValue(0,hex));
    printf("\n dec : ");
    for (size_t i = 0; dec[i] != -1; i++)
      printf("%d", dec[i]);

    //converte em binário
    bin = decKonwerter(0, 2, dec);
    printf("\n bin : ");
    for (size_t i = 0; bin[i] != -1; i++)
      printf("%d", bin[i]);

    //converte em octal
    oct = decKonwerter(0, 8, dec);
    printf("\n oct : ");
    for (size_t i = 0; oct[i] != -1; i++)
      printf("%d", oct[i]);
    break;

  case 1:

    printf(" Decimal\n Insira o valor: ");

    //Lê em decimal
    dec = integerValue(0, readInput());
    if (dec == NULL)
    {
      printf("ERRO DEC==NULL");
      break;
    }
    printf("\n dec : ");
    for (size_t i = 0; dec[i] != -1; i++)
      printf("%d", dec[i]);

    //converte em hexadecimal
    hex = decKonwerter(0, 16, dec);
    printf("\n hex : ");
    for (size_t i = 0; hex[i] != -1; i++)
      printf("%c", hex[i]);

    //converte em binário
    bin = decKonwerter(0, 2, dec);
    printf("\n bin : ");
    for (size_t i = 0; bin[i] != -1; i++)
      printf("%d", bin[i]);

    //converte em octal
    oct = decKonwerter(0, 8, dec);
    printf("\n oct : ");
    for (size_t i = 0; oct[i] != -1; i++)
      printf("%d", oct[i]);

    break;

  case 2:

    printf(" Octal\n Insira o valor: ");

    //lê em octal
    oct = integerValue(0, readInput());
    if (oct == NULL)
    {
      printf("ERRO OCT==NULL");
      break;
    }
    printf("\n oct : ");
    for (size_t i = 0; oct[i] != -1; i++)
      printf("%d", oct[i]);

    //converte em decimal
    dec = decKonwerter(1, 8, oct);
    printf("\n dec : ");
    for (size_t i = 0; dec[i] != -1; i++)
      printf("%d", dec[i]);

    //converte em hexadecimal
    hex = decKonwerter(0, 16, dec);
    printf("\n hex : ");
    for (size_t i = 0; hex[i] != -1; i++)
      printf("%c", hex[i]);

    //converte em binário
    bin = decKonwerter(0, 2, dec);
    printf("\n bin : ");
    for (size_t i = 0; bin[i] != -1; i++)
      printf("%d", bin[i]);

    break;

  case 3:

    printf(" Binário\n Insira o valor: ");

    //lê em binário
    bin = integerValue(0, readInput());
    if (bin == NULL)
    {
      printf("ERRO BIN==NULL");
      break;
    }
    printf("\n bin : ");
    for (size_t i = 0; bin[i] != -1; i++)
      printf("%d", bin[i]);

    //converte em decimal
    dec = decKonwerter(1, 2, bin);
    printf("\n dec : ");
    for (size_t i = 0; dec[i] != -1; i++)
      printf("%d", dec[i]);

    //converte em hexadecimal
    hex = decKonwerter(0, 16, dec);
    printf("\n hex : ");
    for (size_t i = 0; hex[i] != -1; i++)
      printf("%c", hex[i]);

    //converte em octal
    oct = decKonwerter(0, 8, dec);
    printf("\n oct : ");
    for (size_t i = 0; oct[i] != -1; i++)
      printf("%d", oct[i]);

    break;

  default:
    printf(" ERRO CASE=()");
  }

  printf("\n\n");
}
