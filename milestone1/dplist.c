/*
 * Author: Robbe Decapmaker <debber@dcpm.be>
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dplist.h"




/*
 * The real definition of struct list / struct node
 */

struct dplist_node {
    dplist_node_t *prev, *next;
    void *element;
};

struct dplist {
    dplist_node_t *head;

    void *(*element_copy)(void *src_element);

    void (*element_free)(void **element);

    int (*element_compare)(void *x, void *y);
};


dplist_t *dpl_create(// callback functions
        void *(*element_copy)(void *src_element),
        void (*element_free)(void **element),
        int (*element_compare)(void *x, void *y)
) {
    dplist_t *list;
    list = malloc(sizeof(struct dplist));
    list->head = NULL;
    list->element_copy = element_copy;
    list->element_free = element_free;
    list->element_compare = element_compare;
    return list;
}

void dpl_free(dplist_t **list, bool free_element) {
  // Stop if the list is NULL
  if(list == NULL){
    return;
  }

  // Get the length of the list
  int length = dpl_size((dplist_t*)*list);
  
  // If the list is empty, just free the dplist_t
  if(length == 0){
    free(*list);
    *list = NULL;
    return;
  }

  // Remove all elements from the list
  for (int index = length - 1; index >= 0; index--) {
    *list = dpl_remove_at_index((dplist_t*)*list, index, free_element);
  }
  // Free the list itself
  free(*list);
  *list = NULL;
}

dplist_t *dpl_insert_at_index(dplist_t *list, void *element, int index, bool insert_copy) {

    //TODO: add your code here

}

dplist_t *dpl_remove_at_index(dplist_t *list, int index, bool free_element) {
  // If we receive a NULL pointer, return NULL
  if (list == NULL) {
    return NULL;
  }

  // Get the amount of elements 
  int length = dpl_size(list);

  // If the list is empty, return the same list
  if(length == 0){
    return list;
  }

  // Rework the index to be valid if it is outside of the allowed range
  if(index < 0){ // Too  small
    index = 0;
  }
  if(index > length){ // Too large
    index = length - 1;
  }

  // To remove an element, we should free the element itself and fix the adjacent nodes
  // The head node should also be adjusted when the first element gets changed
  dplist_node_t *toRemove = dpl_get_reference_at_index(list,  index);
  dplist_node_t *prevNode = toRemove->prev;
  dplist_node_t *nextNode = toRemove->next;

  if(prevNode != NULL){ // Fix the prev node if it exists
    prevNode->next = nextNode;
  }

  if(nextNode != NULL){ // Fix the next node if it exists
    nextNode->prev = prevNode;
  }

  if(index == 0){ // Fix head if needed
    list->head = nextNode;
  }

  if(free_element){
    list->element_free((void**)toRemove);
  }else{
    free(toRemove); // Free the removed node once the list has been fixed
  }

  return list;
}

int dpl_size(dplist_t *list) {
  // If we receive a NULL pointer, return NULL
  if (list == NULL) {
    return -1;
  }

  // Trivial case when there are no elements
  if(list->head == NULL){
    return 0;
  }

  // If the list does contain elements, we should count them
  int count = 1;
  dplist_node_t *currentNode = list->head;
  while (currentNode->next != NULL ) {
    count ++;
    currentNode = currentNode->next;
  }
  return count;
}

void *dpl_get_element_at_index(dplist_t *list, int index) {

    //TODO: add your code here

}

int dpl_get_index_of_element(dplist_t *list, void *element) {

    //TODO: add your code here

}

dplist_node_t *dpl_get_reference_at_index(dplist_t *list, int index) {

    //TODO: add your code here

}

void *dpl_get_element_at_reference(dplist_t *list, dplist_node_t *reference) {

    //TODO: add your code here

}


