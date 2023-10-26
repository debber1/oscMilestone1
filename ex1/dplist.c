/**
 * \author Jeroen Van Aken, Bert Lagaisse, Ludo Bruynseels
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "dplist.h"



/*
 * The real definition of struct list / struct node
 */
struct dplist_node {
    dplist_node_t *prev, *next;
    element_t element;
};

struct dplist {
    dplist_node_t *head;
    // more fields will be added later
};

dplist_t *dpl_create() {
    dplist_t *list;
    list = malloc(sizeof(struct dplist));
    list->head = NULL;
  return list;
}

void dpl_free(dplist_t **list) {
  // Stop if the list is NULL
  if(list == NULL){
    return;
  }

  // Get the length of the list
  int length = dpl_size((dplist_t*)*list);
  
  // If the list is empty, just free the dplist_t
  if(length == 0){
    free(*list);
    return;
  }

  // Remove all elements from the list
  for (int index = length - 1; index >= 0; index--) {
    *list = dpl_remove_at_index((dplist_t*)*list, index);
  }
  // Free the list itself
  free(*list);
}

/* Important note: to implement any list manipulation operator (insert, append, delete, sort, ...), always be aware of the following cases:
 * 1. empty list ==> avoid errors
 * 2. do operation at the start of the list ==> typically requires some special pointer manipulation
 * 3. do operation at the end of the list ==> typically requires some special pointer manipulation
 * 4. do operation in the middle of the list ==> default case with default pointer manipulation
 * ALWAYS check that you implementation works correctly in all these cases (check this on paper with list representation drawings!)
 **/


dplist_t *dpl_insert_at_index(dplist_t *list, element_t element, int index) {
    dplist_node_t *ref_at_index, *list_node;
    if (list == NULL) return NULL;

    list_node = malloc(sizeof(dplist_node_t));

    list_node->element = element;
    // pointer drawing breakpoint
    if (list->head == NULL) { // covers case 1
        list_node->prev = NULL;
        list_node->next = NULL;
        list->head = list_node;
        // pointer drawing breakpoint
    } else if (index <= 0) { // covers case 2
        list_node->prev = NULL;
        list_node->next = list->head;
        list->head->prev = list_node;
        list->head = list_node;
        // pointer drawing breakpoint
    } else {
        ref_at_index = dpl_get_reference_at_index(list, index);
        assert(ref_at_index != NULL);
        // pointer drawing breakpoint
        if (index < dpl_size(list)) { // covers case 4
            list_node->prev = ref_at_index->prev;
            list_node->next = ref_at_index;
            ref_at_index->prev->next = list_node;
            ref_at_index->prev = list_node;
            // pointer drawing breakpoint
        } else { // covers case 3
            assert(ref_at_index->next == NULL);
            list_node->next = NULL;
            list_node->prev = ref_at_index;
            ref_at_index->next = list_node;
            // pointer drawing breakpoint
        }
    }
    return list;
}

dplist_t *dpl_remove_at_index(dplist_t *list, int index) {
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

  free(toRemove); // Free the removed node once the list has been fixed

  return list;
}

int dpl_size(dplist_t *list) {
  // If we receive a NULL pointer, return NULL
  if (list == NULL) {
    return NULL;
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

dplist_node_t *dpl_get_reference_at_index(dplist_t *list, int index) {
  // If we receive a NULL pointer, return NULL
  if (list == NULL) {
    return NULL;
  }

  // First get the length of the dpl
  int length = dpl_size(list);

  // If there are no elements, return NULL
  if (length == 0){ 
    return NULL;
  }

  // When we want to lookup a non-positive integer index
  if (index <= 0) {
    return list->head;
  }

  // When we want to lookup an index which is larger then the count,
  // we want to return the last element of the pdl
  // We can do this by changing the index to be the last possible index
  if (length < index){
    index = length-1;
  }

  // Get the reference at `index`
  dplist_node_t *toReturn = list->head;
  for (int i = 0; i <= index-1; i++) {
    toReturn = toReturn->next;
  }

  return toReturn;
}

element_t dpl_get_element_at_index(dplist_t *list, int index) {
  // If we receive a NULL pointer, return '0'
  if (list == NULL) {
    return '0';
  }

  // If the list is empty return 0
  if(dpl_size(list) == 0){
    return '0';
  }

  // get the element itself
  element_t elmnt = dpl_get_reference_at_index(list, index)->element;

  return elmnt;
}

int dpl_get_index_of_element(dplist_t *list, element_t element) {
  // If we receive a NULL pointer, return -1
  if (list == NULL) {
    return -1;
  }

  int foundAt = -1;
  dplist_node_t *currentNode = list->head;
  int length = dpl_size(list);
  for (int index = 0; index < length; index++) {
    element_t currentElement = currentNode->element;
    if(currentElement == element){
      foundAt = index;
      break;
    }
  }

  return foundAt;
}



