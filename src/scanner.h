#include <stdio.h>
#include "jg-groups/jg_strings.h"

// estrutura para guardar os argumentos 
typedef struct opt
{
    int len;
    char **args;
} opt;


// leitor do terminal para armazenar requisições
opt opt_scanner()
{
  char *output;
  
  { // leitura do terminal
    int counter = 0;
    int size = 10;
    bool space = 1;

    // aloca 10 espaços iniciais
    output = (char *) malloc(sizeof(char) * size);
    
    // lê o primeiro caractere (não pode ser espaço)
 
    // então lê até a quebra de linha 
    char input;
    while (EOF != (input = fgetc(stdin)) && input != '\n')
    {    
        // se existe um espaço final
        if ( space == 1)
        {
          // para que input seja lido, não pode ser um espaço também
          if (input != ' ')
          {
            output[counter] = input;
            space = 0;
            counter ++;
          }
        }

        else if (space == 0)
        {
          output[counter] = input;
          if (input == ' ')
            space = 1;
          
          counter++;
        } 

        // a cada 10 caracteres, alocamos + 10 de espaço
        if (counter == size)
        {
          size += 10;
          output = (char *) realloc(output, sizeof(char) * size);
        }
    }

    // arruma o tamanho certinho
    output = (char *) realloc(output, sizeof(char) * counter + 1);
    output[counter] = '\0';
  }

  // transformação da string em opt / args
  opt ret;
  
  ret.len = 0;
  ret.args = str_split(output, ' ');
  for (ret.len = 0; ret.args[ret.len] != NULL; ret.len++);  
  
  free(output);
  return ret;
}
