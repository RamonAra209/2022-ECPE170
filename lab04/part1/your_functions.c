#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "your_functions.h"

// Merge sort algorithm
// Arguments:
//  (1) Pointer to start of array to sort
//  (2) Pointer to start of temporary array
//  (3) Number of elements in array
// Return value: None
void mergeSort(int *array_start, int *temp_array_start, int array_size)
{
  printf("Using merge sort algorithm...\n");

  // Solution from: http://p2p.wrox.com/visual-c/66348-merge-sort-c-source-code.html

  mergeSort_sort(array_start, temp_array_start, 0, array_size - 1);

  return;
}

void mergeSort_sort(int array_start[], int temp[], int left, int right)
{
  int mid;
 
  if (right > left)
  {
    mid = (right + left) / 2;
    mergeSort_sort(array_start, temp, left, mid);
    mergeSort_sort(array_start, temp, mid+1, right);
 
    mergeSort_merge(array_start, temp, left, mid+1, right);
  }
}
 
void mergeSort_merge(int array_start[], int temp[], int left, int mid, int right)
{
  int i, left_end, num_elements, tmp_pos;
 
  left_end = mid - 1;
  tmp_pos = left;
  num_elements = right - left + 1;
 
  while ((left <= left_end) && (mid <= right))
  {
    if (array_start[left] <= array_start[mid])
    {
      temp[tmp_pos] = array_start[left];
      tmp_pos = tmp_pos + 1;
      left = left +1;
    }
    else
    {
      temp[tmp_pos] = array_start[mid];
      tmp_pos = tmp_pos + 1;
      mid = mid + 1;
    }
  }
 
  while (left <= left_end)
  {
    temp[tmp_pos] = array_start[left];
    left = left + 1;
    tmp_pos = tmp_pos + 1;
  }
  while (mid <= right)
  {
    temp[tmp_pos] = array_start[mid];
    mid = mid + 1;
    tmp_pos = tmp_pos + 1;
  }
 
  for (i=0; i < num_elements; i++)
  {
    // JAS: Used to be <= num_elements...
    array_start[right] = temp[right];
    right = right - 1;
  }
}


// Tree sort algorithm
//Requires the following steps:
//1. Construct a Binary Tree using the array elements. If the current element is less than
//the node, place the element on the left branch, else place it on the right branch. See BTreeNode structure in your_functions.h.
//2. Once binary tree is constructed, perform in-order traversal of the binary tree (HINT: use recursion).
//FILL in the functions: inorder, insert_element, and tree_sort for sorting.

void inorder(struct BTreeNode *node, int *array, int *index)
{
	//Recursive In-order traversal: leftchild, element, rightchild
  if (node == NULL) {
    return;
  }

  inorder(node->leftnode, array, index);
  array[*index] = node->element;
  (*index)++;

  inorder(node->rightnode, array, index);
}

void insert_element(struct BTreeNode **node, int element) 
{
  // 3 cases
  //  1. figuring out what subtree to insert at
  //  2. if left or right child is NULL, create a leaf
  
  //? What do these point to
  //? node:   BTreeNode node (passing through node wont modify)
  //? *node:  points to node (passing through would only modify where its point to)
  //? **node: points to a pointer to a node (passing through would let you modify the children)

  if (*node == NULL) {
    *node = create_node(element);
  } else if (element < (*node)->element) {
    insert_element(&(*node)->leftnode, element);
  } else {
    insert_element(&(*node)->rightnode, element);
  }
  
}

struct BTreeNode* create_node(int element) { 
  struct BTreeNode* new_node = malloc(sizeof(struct BTreeNode));
  new_node->element = element;
  new_node->leftnode = NULL;
  new_node->rightnode = NULL;
  return new_node;
}

void free_btree(struct BTreeNode **node)
{ 
  if (*node == NULL) {
    return;
  }

  free_btree(&(*node)->leftnode);
  free_btree(&(*node)->rightnode);
  free((*node));
}

void tree_sort(int *array, int size)
{

//1. Construct the binary tree using elements in array
//2. Traverse the binary tree in-order and update the array
//3. Free the binary tree
  printf("Using Tree Sort Algorithm \n");
  struct BTreeNode* root = NULL;
  int iterator = 0;

  // insert_element(&root, 1);
  for (int i = 0; i < size; i++) {
    insert_element(&root, array[i]);
  }

  inorder(root, array, &iterator);
  
  printf("Array\n");
  for (int i = 0; i < 10; i++) {
    printf("%d:%d, ", size-i, array[size - i]);
  }
  printf("\n");

  free_btree(&root);
}


