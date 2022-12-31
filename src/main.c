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
  // mas antes destes, leitura de chaves e sua aplicação.

  // TODO FLAGS
  if (argc > 1)
  {
    // estruturas para uso dos programas,
    // preparadas de acordo com as flags
    list files = list_new();
    DIR *dir = NULL;
    struct dirent *entry;
    key key_input = key_empty();
    key key_output = key_empty();

    // loop de leitura de flags
    int counter = 0;
    while (counter < argc)
    {
      
      // -ki [input key]
      /// Altera a chave criptográfica de entrada
      if ( str_match("-ki", argv[counter]))
      {
        counter++;
        if (counter < argc)
        {
          if (key_input.length != 0 )
            key_free(key_input);

          key_input = key_new(argv[counter]);
          printf("\n Chave cadastrada: ");
          for(u_int i = 0; i < key_input.length; i++)
            printf("%c", key_input.keyword[i]);
        }

        else {
          printf("\n Chave de entrada inválida, abortando flag");
        }

        continue;
      } // -ki [key] end


      // -ko [output key
      /// Altera a chave criptográfica de saída
      if ( str_match("-ko", argv[counter]))
      {
        counter++;
        if (counter < argc)
        {
          if (key_output.length != 0)
            key_free(key_output);

          key_output = key_new(argv[counter]);
          printf("\n Chave cadastrada: ");
          for(u_int i = 0; i < key_output.length; i++)
            printf("%c", key_output.keyword[i]);
        }

        else {
          printf("\n Chave de saída inválida, abortando flag");
        }

        continue;
      } // -ko [key end

      
      // -f [files]
      /// recebe arquivos, verifica sua existência e armazena 
      /// os registros em uma lista (sem feature para diretórios)
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
        continue;
      } // -f [files] end
      counter ++;
    } //while end

memlib:
    if (files.len != 0)
      list_Free(&files);

    if (dir != NULL)
      closedir(dir);

    if (key_input.length != 0)
      key_free(key_input);

    if (key_output.length != 0)
      key_free(key_output);
  } //if argc end
   
  return 0;
}
