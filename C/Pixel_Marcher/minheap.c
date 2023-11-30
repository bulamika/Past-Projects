/**
 *                        Min-Heaps
 * 
 * This is the A2 section of your coding assignment. You will only submit this
 * along with the A3 section when A3 is due, but it is recommended that you
 * complete this early on so you have time to work on second part of this
 * assignment (in `marcher.c` ).
 * 
 * Please make sure you read the blurb in `minheap.h` to ensure you understand 
 * how we are implementing min-heaps here and what assumptions / requirements 
 * are being made.
 * 
 * CSCB63 Winter 2021 - Assignment 2/3
 * (c) Mustafa Quraish
 */

#include "minheap.h"

//helper function
HeapElement *element_array(int size){
   HeapElement *arr = malloc(sizeof(HeapElement) * size);
   if(arr == NULL){
    fprintf(stderr,"invalid malloc for array of heap elements!");
    exit(1);
  }
  for(int i = 0; i < size; i++){
    arr[i].val = -1;
    arr[i].priority = INFINITY;
  }
  return arr;
}
/**
 * Allocate a new min heap of the given size.
 * 
 * TODO: 
 *  Allocate memory for the `MinHeap` object, and the 2 arrays inside it.
 *  `numItems` should initially be set to 0, and all the indices should be
 *   set to -1 to start with (since we don't have anything in the heap).
 */
MinHeap *newMinHeap(int size) {
  MinHeap *heap = malloc(sizeof(MinHeap)*size);
  if(heap == NULL){
    fprintf(stderr,"invalid malloc for minHeap!");
    exit(1);
  }
  heap->numItems = 0;
  heap->maxSize = size;
  heap->arr = element_array(size);
 
  heap->indices = calloc(size,sizeof(int));
   if(heap->indices == NULL){
    fprintf(stderr,"invalid malloc for indices!");
    exit(1);
  }
  //assign
  for(int i = 0; i < size;i++){
    heap->indices[i] = -1;
  }

  return heap;
  //return NULL; // Allocate and return heap.
}

/**
 * Swaps elements at indices `a` and `b` in the heap, and also updates their
 * indices. Assumes that `a` and `b` are valid.
 * 
 * NOTE: This is already implemented for you, no need to change anything.
 */
void swap(MinHeap *heap, int a, int b) {
  // Swap the elements
  HeapElement temp = heap->arr[a];
  heap->arr[a] = heap->arr[b];
  heap->arr[b] = temp;

  // Refresh their indices
  heap->indices[heap->arr[a].val] = a;
  heap->indices[heap->arr[b].val] = b;
}
//helper function
//arguments: heap, size of the heap, and the index of indices of the inserted node
void Percolate(MinHeap *heap, int size, int i){ 
  int parent = (i - 1)/2;
  int parent_index = heap->indices[parent];
  int child_index = heap->indices[i];

  if(heap->arr[parent_index].val > 0){
    if(heap->arr[parent_index].val > heap->arr[child_index].val || heap->arr[parent_index].priority < heap->arr[child_index].priority ){
      swap(heap,i,parent);
      Percolate(heap,size,parent); //keep percolating until the heap is correct after the insertion
    }
  }
}

void Heapify(MinHeap *heap, int size, int i){
  int smallest = i;
  int left = 2*i + 1;
  int right = 2*i + 2;

  int smallest_index = heap->indices[smallest];
  int left_index = heap->indices[left];
  int right_index = heap->indices[right];

  if(left < size && (heap->arr[left_index].val < heap->arr[smallest].val || heap->arr[left_index].priority > heap->arr[smallest].priority )){
    smallest = left;
  }
  if(right < size && (heap->arr[right_index].val < heap->arr[smallest].val || heap->arr[right_index].priority > heap->arr[smallest].priority )){
    smallest = right;
  }
  if(smallest != i){
    swap(heap,i,smallest);
    Heapify(heap,size,smallest);
  }
}
/**
 * Add a value with the given priority into the heap.
 * 
 * TODO: Complete this function, and make sure all the relevant data is updated
 *      correctly, including the `indices` array if you move elements around. 
 *      Make sure the heap property is not violated. 
 * 
 * You may assume the value does not already exist in the heap, and there is
 * enough space in the heap for it.
 */
void heapPush(MinHeap *heap, int val, double priority) {
  heap->numItems++; //increase the current number of items.

  int current_index = (heap->numItems)-1;

  HeapElement node;
  heap->arr[current_index] = node;
  heap->arr[current_index].priority = priority;
  heap->arr[current_index].val = val;
  
  heap->indices[current_index] = current_index;
  Percolate(heap,current_index +1, current_index);

  return; // Push value to heap before returning
}

/**
 * Extract and return the value from the heap with the minimum priority. Store
 *  the priority for this value in `*priority`. 
 * 
 * For example, if `10` was the value with the lowest priority of `1.0`, then
 *  you would have something that is equivalent to:
 *      
 *        *priority = 1.0;
 *        return 10;
 * 
 * TODO: Complete this function, and make sure all the relevant data is updated
 *      correctly, including the `indices` array if you move elements around. 
 *      Make sure the heap property is not violated. 
 * 
 * You may assume there is at least 1 value in the heap.
 */
int heapExtractMin(MinHeap *heap, double *priority) {
  if(heap->numItems<=0){
    fprintf(stderr,"invalid extract min call");
    exit(1);
  }
  int arr_index = heap->indices[0] ;
  int val = heap->arr[arr_index].val;
 // *priority = 0.0;  // Set correct priority  
  *priority = heap->arr[arr_index].priority;

  if(heap->numItems == 1){
    heap->numItems--;
    return val;
  }

  heap->indices[0] = heap->indices[heap->numItems-1];
  heap->numItems--;
  Heapify(heap,heap->numItems,0);


  return val;         // Return correct value
}

/**
 * Decrease the priority of the given value (already in the heap) with the
 * new priority.
 * 
 * NOTE: You will find it helpful here to first get the index of the value
 *       in the heap from the `indices` array.
 * 
 * TODO: Complete this function, and make sure all the relevant data is updated
 *      correctly, including the `indices` array if you move elements around. 
 *      Make sure the heap property is not violated. 
 * 
 * You may assume the value is already in the heap, and the new priority is
 *  smaller than the old one (caller is responsible for ensuring this).
 */
void heapDecreasePriority(MinHeap *heap, int val, double priority) {
  int index = 0;
  int arr_index = heap->indices[index];
  while(index < heap->numItems && heap->arr[arr_index].val != val){
    index++;
    arr_index = heap->indices[index];
  }

  heap->arr[arr_index].priority = priority;

  Heapify(heap, heap->numItems, 0); //since our priority decreases, we check if the children will have higher priority
  
 
  return;   // Decrease priority before return
}

/**
 * Free the data for the heap. This won't be marked, but it is always good
 * practice to free up after yourself when using a language like C.
 */
void freeHeap(MinHeap *heap) {
  free(heap->arr);
  free(heap);
  return;   // Free heap and it's arrays
}
