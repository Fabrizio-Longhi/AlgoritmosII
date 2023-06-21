#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

struct _node_t {
  unsigned int key;
  list_value value;
  struct _node_t *next;
};

typedef struct _node_t * node_t;

struct _list_t {
  unsigned int size;
  node_t elems;
};

static bool invrep(list_t list) {
  unsigned int aux_size = 0;
      struct _node_t *aux = list->elems;
      
      bool valid = true;

      while (aux != NULL){
        ++aux_size;
        aux = aux->next;
      }


      if (list->size == 0){
        valid = true;
      }
      else if (list->size == 1){
        valid = true;
      }
      else{
        struct _node_t *check_key = list->elems;

        while (check_key->next != NULL){
          valid = valid && check_key->key < check_key->next->key;
          check_key = check_key->next;
        }

      }
    return valid && aux_size == list->size && list != NULL;
}

static struct _node_t * create_node(unsigned int key, list_value value) {
      struct _node_t  * new_node = malloc (sizeof (struct _node_t));

      new_node->key = key;
      new_node->value = value;
      new_node->next = NULL;


      return new_node;
}

static struct _node_t * destroy_node(struct _node_t *node) {

      node->next = NULL;
      free (node);
      node = NULL;

      return node;
}

list_t list_empty(void) {
      list_t new_list = malloc (sizeof (struct _list_t));

      new_list->size = 0;
      new_list->elems = NULL;

      return new_list;
}

list_t list_add(list_t list, unsigned int key, list_value value) {
        assert (invrep(list));


      if (list_exists(list,key)){              // if key is exist
          bool valid = false;
          struct _node_t *aux = list->elems;
          while (aux != NULL && !valid) {                 

            if (aux->key == key){
                aux->value = value;       //change only value
                valid = true;
            }
            aux = aux->next;
          }
      }
      else{                                     // if key isnt exist
      
            struct _node_t *new_node = create_node (key,value);
            if (list->elems == NULL){
                list->elems = new_node;
            }
            else{
              struct _node_t *post = list->elems;
              struct _node_t *pre = NULL;
              while (post->next != NULL && post->key < new_node->key){
                  pre = post;
                  post = post->next;
              }
              if (list->elems->key > new_node->key){          //insert in the first place
                  new_node->next = post;
                  list->elems = new_node;
              }
              else if (post->key > new_node->key){             // insert between of extrems
                  new_node->next = post;
                  pre->next = new_node;
              }
              else{                                           // insert last
                  post->next = new_node;
              }
            }

            ++list->size;

      }

      assert (invrep(list) );
      return list;
}

unsigned int list_length(list_t list) {


      return list->size;
}

bool list_is_empty(list_t list) {


      return list->size == 0;
}

bool list_exists(list_t list, unsigned int key) {

  assert(invrep(list));
  node_t cursor = list->elems;
  while (cursor != NULL && cursor->key < key) {
    cursor = cursor->next;
  }
  return cursor != NULL && cursor->key == key;
}


char list_search(list_t list, unsigned int key) {
      assert (list_exists(list,key));

      char valid = false;
      char ret_value;
      struct _node_t *aux = list->elems;

      while (aux != NULL && !valid){

          if (aux->key == key){
              ret_value = aux->value;
              valid = true;
          }
          aux = aux->next;
      }
      
      return ret_value;
}

list_t list_remove(list_t list, unsigned int key) {
      assert (invrep(list));

      if (list_exists(list,key)){

          struct _node_t *kill = list->elems;
          struct _node_t *pre = NULL;

          while (kill->next != NULL && kill->key != key){
              pre = kill;
              kill = kill->next;
          }

          if (list->elems->key == key){
              list->elems = kill->next;
              kill = destroy_node (kill);
          }
          else if(kill->key == key){
              pre->next = kill->next;
              kill = destroy_node (kill);
          }
          --list->size;
      }

       assert (invrep(list) && !list_is_empty(list));
      return list;
}

list_t list_remove_all(list_t list) {
      assert (invrep(list));
      struct _node_t *kill = list->elems;

      while (list->elems != NULL){
        kill = list->elems;
        list->elems = kill->next;
        kill = destroy_node (kill);
      }

      list->size = 0;


      assert (invrep(list) && list_length(list) == 0);
      return list;
}


list_value* list_to_array(list_t list) {
    assert (invrep(list));
    unsigned int size = list->size;
    list_value * array = calloc (size+1, sizeof (list_value));
    struct _node_t *aux = list->elems;

    for (unsigned int i = 0; i < size ; ++i){
        array[i] = aux->value;
        aux = aux->next;
    }

    assert (invrep(list) );
    return array;
}

list_t list_destroy(list_t list) {
    assert (invrep(list));
    struct _node_t *kill = NULL;

    while (list->elems != NULL){
        kill = list->elems;
        list->elems = kill->next;
        kill = destroy_node (kill);
    }
    free (list->elems);
    free (list);
    list = NULL;


    assert (list == NULL);
    return list;
}