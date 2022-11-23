#ifndef J_LINKEDLIST_H
#define J_LINKEDLIST_H

// V 1.2

#include<stdlib.h>
#include<stdbool.h>
#include "./j_strings.h"
#include "./j_transform.h"
#include "./j_strings.h"

// Estrutura do conteúdo de um node
struct Item
{
  char *text;
};


// Estrutura node
struct Node
{
    struct Node *next;
    struct Node *prev;
    struct Item item;
} typedef * snode; 


// Estrura da lista ligada
typedef struct 
{
    snode ini;
    snode end;
    int len;
} list;

// valor para realizar extrações da lista
snode __j_ptrItem = NULL;

// -------------------------------------------------------------- //
// FUNÇÕES SUJEITAS A MUDANÇA, NECESSÁRIO ADAPTAR DE PROJETO PARA PROJETO

// Cria um novo item
// mudando os conteúdos de struct Item, se torna necessário
// também mudar esta função
struct Item item_new( char *text )
{
  struct Item ret;
  ret.text = str_copy(text);
  return ret;
}


// Função para comparar itens, 
// mudando os conteúdos de struct Item, se torna necessário
// também mudar esta função.
bool __item_Compare(struct Item i1, struct Item i2)
{
  if (str_match(i1.text, i2.text))
    return true;

  return false;
}


// Função para transformar itens em string,
// mudando os conteúdos de struct Item, se torna necessário 
// também mudar esta função
char * __item_toString(struct Item i1)
{
  char *ret;
  ret = str_copy(i1.text);

  return ret;
}


// Função que retorna uma cópia de item,
// necessário saber um pouco mais sobre C para usar isto corretamente
struct Item __item_Copy(struct Item value)
{
  // criação
  struct Item ret;

  // ret = value; só após C90 
  ret.text = value.text;

  return ret;
  
  // EM CASO DE PONTEIRO!
  /*

  Item { 
    char * pointer;
  }

  Item __item_Copy( char * pointer ) {
    // criação
    Item ret;

    ret.pointer = pointer !!!!!!!! ERRADO !!!!!!!!!
    // você está criando uma cópia do ponteiro, não do conteúdo,
    // faça uma função para copiar os conteúdos do ponteiro você mesmo
  }
  */
}


// Transforma a lista em uma string, útil para printagem
// É necessário liberar a memória
char *list_toString( list target)
{

  // Checa se está vazia
  if (target.ini == NULL)
  {
    return str_copy("{ null }");
  }

  else
  {
    // prepara o retorno
    char *ret = "{ ";
    char *value = NULL;

    // 2 strings para possibilitar free
    char *str1 = str_copy( ret );
    char *str2 = NULL;

    // percorre
    snode This = target.ini;
    while (1)
    {
      // libera value
      if ( value != NULL )
        free(value);

      value = __item_toString(This->item);

      // concatena e libera a string anterior
      str2 = str_concac(str1, value);
      free(str1);
      str1 = str2;

      // vê se é o fim
      if (This->next == NULL)
      {
        str2 = str_concac(str1, " }");
        free(str1);
        free(value);
        return str2;
      }

      // se não adiciona uma vírgula
      str2 = str_concac(str1, ", ");
      free(str1);
      str1 = str2;

      This = This->next;
    }
  } 
}






// ------------------------------------------------------------- //
/// FUNÇÕES NÃO SUJEITAS A MUDANÇA, NÃO TOQUE, SÓ EM CASO DE BUG

//Cria uma nova lista e retorna
list list_new()
{
  list ret;
  ret.len = 0;
  ret.ini = NULL;
  ret.end = NULL;
  return ret;
}


// Adiciona um elemento ao inicio da lista
// é necessário liberar a memória
void list_addFirst(list * target, struct Item value)
{
  snode new_n = (snode) malloc(sizeof( struct Node ));
  new_n->item = __item_Copy(value);
  new_n->prev = NULL;
  new_n->next = NULL;

  if ( target->len == 0 )
  {
    target->ini = new_n;
    target->end = new_n;
    target->len = 1;
    return;
  }

  target->len += 1;
  
  snode aux = target->ini;
  target->ini = new_n;

  new_n->next = aux;
  aux->prev = new_n;
}


// Adiciona um elemento ao final da lista
// é necessário liberar a memória
void list_addLast(list * target, struct Item value)
{
  snode new_n = (snode) malloc(sizeof( struct Node ));
  new_n->item = __item_Copy(value);
  new_n->prev = NULL;
  new_n->next = NULL;

  if ( target->len == 0 )
  {
    target->ini = new_n;
    target->end = new_n;
    target->len = 1;
    return;
  }

  target->len += 1;
  
  snode aux = target->end;
  target->end = new_n;
  
  aux->next = new_n;
  new_n->prev = aux;
}


// Função para remover um nó com um nó como parâmetro
// O nó DEVE existir na lista, não é uma função de busca
void list_nodeRemove(list *target, snode node)
{
  snode parent = node->prev;
  snode child = node->next;
  
  // faz o antecessor se conectar ao sucessor
  if (parent != NULL)
    parent->next = child;

  else
    target->ini = child;

  
  // faz o sucessor se conectar ao antecessor
  if (child != NULL)
    child->prev = parent;

  else
    target->end = parent;

  target->len -= 1;
  free(node->item.text);
  free(node);
}


// Função para remover um nó com uma estrutura como parâmetro
// Retorna true se foi removido com sucesso
bool list_itemRemove( list * target, struct Item value) 
{
  // checa o tamanho da lista
  if (target->len == 0) return false; 
  
  if (target->len == 1 ) 
  {
    if (__item_Compare( target->ini->item, value))
    {
      list_nodeRemove( target, target->ini );
      return true;
    }
    else return false;
  }

  // exitem mais de dois elementos:
  snode parent = (snode) target;
  while(parent->next != NULL)
  {
    if (__item_Compare( target->ini->item, value))
    {
      list_nodeRemove( target, parent->next);
      return true;
    }

    // movimenta
    parent = parent->next;
  } 
  
  return false;
}


// Retorna a quantidade de elementos da lista
int list_Count( list target )
{
  if (target.ini == NULL)
    return 0;
  
  snode current = target.ini;
  int count = 1;
  while ( current->next != NULL )
  {
    current = current->next;
    count += 1;
  }

  return count;
}

// Inicia o ponteiro para extração dos itens
snode list_Get( list target )
{
  __j_ptrItem = target.ini;
  return __j_ptrItem;
}

// Extrai o próximo elemento da lista
snode list_Next()
{
  if(__j_ptrItem == NULL) return NULL;
  __j_ptrItem = __j_ptrItem->next;
  return __j_ptrItem;
}

// Limpa a lista liberando toda sua memória
void list_Free( list *target)
{
  snode node = target->ini;
  snode aux;
  while ( node != NULL )
  {
    aux = node->next;
    list_nodeRemove(target, node);
    node = aux;
  }
}

#endif
