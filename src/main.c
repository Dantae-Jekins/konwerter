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
    key key_input = key_ascii();
    key key_output = key_ascii();
    bool keyi_alter = false;
    bool keyo_alter = false;

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
          for(int i = 0; i < key_input.length; i++)
            printf("%c", key_input.keyword[i]);

          keyi_alter = true;
        }

        else {
          printf("\n Chave de entrada inválida, abortando flag");
        }

      } // -ki [key] end


      // -ko [output key]
      /// Altera a chave criptográfica de saída
      else if ( str_match("-ko", argv[counter]))
      {
        counter++;
        if (counter < argc)
        {
          if (key_output.length != 0)
            key_free(key_output);

          key_output = key_new(argv[counter]);
          printf("\n Chave cadastrada: ");
          for(int i = 0; i < key_output.length; i++)
            printf("%c", key_output.keyword[i]);

          keyo_alter = true;
        }

        else {
          printf("\n Chave de saída inválida, abortando flag");
        }

      } // -ko [key end

      
      // -f [files]
      /// recebe arquivos, verifica sua existência e armazena 
      /// os registros em uma lista (sem feature para diretórios)
      else if( str_match("-f", argv[counter]))
      {
        dir = opendir("./");
        if (dir == NULL) goto memlib; 

        counter++;
        for(; counter < argc; counter++)
        {
          // checa se é o final ou se é outra flag
          if (argv[counter] == NULL || argv[counter][0] == '-')
          {
            counter--;
            break;
          }

          else
          {
            list_addFirst(&files, item_new(argv[counter]));
          }
        }
        

        // TODO MOVER ISSO PARA FORA DO ARGC.
        while((entry = readdir(dir)) != NULL) // while entries
        {
          // exclui diretórios (por enquanto)
          if (entry->d_type == 8)
          {
            // percorre a lista para cada entry
            snode node = list_Get(files);

            if (keyi_alter) printf("\n Chave de entrada inalterada");
            if (keyo_alter) printf("\n Chave de saída inalterada");

            while (node != NULL) // while nodes
            {
              // Arquivo existe
              if (str_match(entry->d_name, node->item.text))
              {
                printf("\n Criptografando arquivo : %s", entry->d_name);
                FILE *ptr = fopen(node->item.text, "r");
                if (ptr == NULL)
                  printf("\n Erro ao ler o arquivo");
                else
                {
                  int i = 0;
                  char buffer[8]; //8 bytes máximo
                  for (char ch = fgetc(ptr); ch != EOF; i++)
                  {
                    //TODO ler o arquivo e criptografar os dados nos 8 bytes
                  }
                }

                fclose(ptr);
              }
              node = list_Next();
              
            }
          }
        } 
      } // -f [files] end
      
      counter ++;
    } //while end

    // flags coletadas
    // se existem arquivos para serem tratados


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
