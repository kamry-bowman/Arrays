#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Node
{
  struct Node *next;
  char *value;
} Node;

typedef struct Array
{
  Node *head;
  Node *tail;
  int count; // How many states does the array currently hold?
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *
create_array()
{
  Array *array = malloc(sizeof(Array));
  array->count = 0;

  array->head = NULL;
  array->tail = NULL;

  return array;
}

Node *create_node(Node *next, char *value)
{
  Node *node = malloc(sizeof(Node));
  node->next = next;
  node->value = strdup(value);
  return node;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{
  // Free all elements
  Node *current = arr->head;
  while (current)
  {
    Node *next = current->next;
    free(current);
    current = next;
  }

  // Free array
  free(arr);
}

/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

// checks index range, and converts to a positive int for negative values
int process_index(Array *arr, int index)
{
  if (
      (index > 0 && index >= arr->count) ||
      (index < 0 && index * -1 * index > arr->count))
  {
    return -1;
  }
  if (index < 0)
  {
    index *= -1;
  }
  return index;
}

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index)
{
  index = process_index(arr, index);
  if (index == -1)
  {
    perror("Index out of range");
    return NULL;
  }
  int current_index = 0;
  Node *current = arr->head;
  while (current_index != index)
  {
    current = current->next;
    current_index++;
  }

  return current->value;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{
  if (arr->count == 0)
  {
    arr->head = create_node(NULL, element);
    arr->tail = arr->head;
  }
  else
  {
    arr->tail->next = create_node(NULL, element);
    arr->tail = arr->tail->next;
  }
  arr->count++;
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index)
{
  // handle adding to tail
  if (index == arr->count)
  {
    arr_append(arr, element);
  }
  else
  {

    // Throw an error if the index is greater than the current count
    index = process_index(arr, index);

    if (index == -1)
    {
      perror("Index out of range");
      exit(1);
    }

    if (index == 0)
    {
      Node *old_head = arr->head;
      arr->head = create_node(old_head, element);
    }
    else
    {
      int current_index = 0;
      Node *current = arr->head;
      while (current_index != index - 1)
      {
        current = current->next;
        current_index++;
      }
      current->next = create_node(current->next, element);
    }
    // Increment count by 1
    arr->count++;
  }
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
// void arr_remove(Array *arr, char *element)
// {

//   // Search for the first occurence of the element and remove it.
//   // Don't forget to free its memory!
//   int found = -1;
//   for (int i = 0; i < arr->count; i++)
//   {
//     int string_match = strcmp(element, arr->elements[i]);
//     if (string_match == 0)
//     {
//       found = i;
//       break;
//     }
//   }

//   if (found == -1)
//   {
//     perror("Item not found");
//     exit(1);
//   }
//   // Shift over every element after the removed element to the left one position
//   for (int j = found; j < arr->count - 1; j++)
//   {
//     arr->elements[j] = arr->elements[j + 1];
//   }

//   // Decrement count by 1
//   arr->count--;
// }

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  Node *current = arr->head;
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", current->value);
    current = current->next;
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array();
  // arr_append(arr, "test0");
  // arr_append(arr, "test1");
  // arr_append(arr, "test2");
  // arr_append(arr, "test3");
  // arr_append(arr, "test4");
  // arr_append(arr, "test5");
  // arr_append(arr, "test6");
  // arr_append(arr, "test7");
  // arr_append(arr, "test8");
  // arr_append(arr, "test9");
  // arr_append(arr, "test10");
  // arr_append(arr, "test11");
  // arr_append(arr, "test12");
  // arr_append(arr, "test13");
  // arr_append(arr, "test14");
  // arr_append(arr, "test15");

  // arr_insert(arr, "insert at 4", 4);
  // arr_insert(arr, "insert at 0", 0);

  // arr_remove(arr, "insert at 0");
  // arr_remove(arr, "insert at 4");

  // arr_print(arr);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  // arr_remove(arr, "STRING3");
  // arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
