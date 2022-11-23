#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <dirent.h>
#include "jg-groups/jg_strings.h"
#include "konwerter.h"

// main
int main(int argc, char **argv)
{ 
  //TODO TESTES DE REDE

  //TODO
  // 1. estabelecer um módulo de comunicação na rede para recebimento e criptografia/descriptografia de dados
  // 2. estabelecer um módulo para leitura de arquivos e criptografia dos mesmos:w

  // TODO FLAGS
  if (argc > 1)
  { 
    // estruturas para uso dos programas,
    // preparadas de acordo com as flags
    list files = list_new();
    DIR *dir = NULL;
    struct dirent *entry;

    // loop de leitura de flags
    int counter = 0;
    while (counter < argc)
    {

      // -f [files]
      if( str_match("-f", argv[counter]))
      {
        dir = opendir("./");
        if (dir == NULL) goto memlib; 

        counter++;
        for(; counter < argc; counter++)
        {
          // checa se é o final ou se é outra flag
          if (argv[counter] == NULL || argv[counter][0] == '-')
            break;

          else
          {
            list_addFirst(&files, item_new(argv[counter]));
          }
        }
        
        while((entry = readdir(dir)) != NULL) // while entries
        {
          // exclui diretórios (por enquanto)
          if (entry->d_type == 8)
          {
            // percorre a lista para cada entry
            snode node = list_Get(files);
            while (node != NULL) // while nodes
            {
              // Arquivo existe
              if (str_match(entry->d_name, node->item.text))
              {
                printf("\n Criptografando arquivo : %s", entry->d_name);
              }
              node = list_Next();
              
            }
          }
        } 
      } // -f [files] end

      counter ++;
    } //while end

memlib:
    list_Free(&files);
    closedir(dir);
  } //if argc end
   
  return 0;
}
