#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  Array *array = malloc(sizeof(Array));
  // Allocate memory for the Array struct
  // Set initial values for capacity and count
  array->count = 0;
  array->capacity = capacity;

  // Allocate memory for elements
  char **elements = malloc(capacity * sizeof(char **));
  array->elements = elements;

  return array;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{

  // Free all elements
  for (int i = 0; i < arr->capacity; i++)
  {
    free(arr->elements[i]);
  }

  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr)
{

  // Create a new element storage with double capacity
  char **new_elements = malloc(sizeof(char **) * arr->capacity * 2);

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    new_elements[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = new_elements;
  arr->capacity = arr->capacity * 2;
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
  return arr->elements[index];
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index)
{

  // Throw an error if the index is greater than the current count
  index = process_index(arr, index);
  if (index == -1)
  {
    perror("Index out of range");
    exit(1);
  }
  int old_count = arr->count;

  // Resize the array if the number of elements is over capacity
  if (arr->count == arr->capacity)
  {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i = old_count; i > index; i--)
  {
    arr->elements[i] = arr->elements[i - 1];
  }

  // Copy the element and add it to the array
  arr->elements[index] = strdup(element);

  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{
  // Resize the array if the number of elements is over capacity
  if (arr->count == arr->capacity)
  {
    resize_array(arr);
  }
  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);
  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int found = -1;
  for (int i = 0; i < arr->count; i++)
  {
    int string_match = strcmp(element, arr->elements[i]);
    if (string_match == 0)
    {
      found = i;
      break;
    }
  }

  if (found == -1)
  {
    perror("Item not found");
    exit(1);
  }
  // Shift over every element after the removed element to the left one position
  for (int j = found; j < arr->count - 1; j++)
  {
    arr->elements[j] = arr->elements[j + 1];
  }

  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
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

  Array *arr = create_array(1);
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
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
