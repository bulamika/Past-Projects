#include "dectree.h"

DTNode *new_node(){
  DTNode *node = malloc(sizeof(DTNode));
  if(node == NULL){
    fprintf(stderr,"invalid malloc for node");
    exit(1);
  }
  node->classification = -1;
  node->left = calloc(1, sizeof(DTNode));
  //node->left = NULL;
  node->right = calloc(1, sizeof(DTNode));
  //node->right = NULL;
  node->pixel = -1;
  return node;
}


Image *list_of_images(int num){
  Image *list = malloc(sizeof(Image) * num);
   if(list == NULL){
    fprintf(stderr,"invalid malloc for image's data!");
    exit(1);
  }
  for(int i = 0; i < num; i++){
    list[i].sx = 28;
    list[i].sy = 28;
    list[i].data = calloc(784, sizeof(unsigned char));
  }
  return list;
}

Dataset *new_dataset(int num_items, Image *images, unsigned char *labels){
  //allocate
  Dataset *dataset = malloc(sizeof(Dataset));
  if(dataset == NULL){
    fprintf(stderr,"invalid malloc for dataset!");
    exit(1);
  }
  
  //dataset->num_items = calloc(sizeof(int),1);
  dataset->num_items = num_items;
  dataset->images = images;  //get the pointer
  if(dataset->images == NULL){
    fprintf(stderr,"invalid malloc for images!");
    exit(1);
  }
  dataset->labels = calloc(num_items,sizeof(unsigned char));
  if(dataset->labels == NULL){
    fprintf(stderr,"invalid malloc for labels!");
    exit(1);
  }
  //assign
  for(int i = 0; i < num_items;i++){
    dataset->labels[i] = labels[i];
  }
 
  return dataset;

}


/**
 * This function takes in the name of the binary file containing the data and
 * loads it into memory. The binary file format consists of the following:
 *
 *     -   4 bytes : `N`: Number of images / labels in the file
 *     -   1 byte  : Image 1 label
 *     - 784 bytes : Image 1 data (28x28)
 *          ...
 *     -   1 byte  : Image N label
 *     - 784 bytes : Image N data (28x28)
 *
 * You can simply set the `sx` and `sy` values for all the images to 28, we
 * will not test this with different image sizes.
 */
Dataset *load_dataset(const char *filename) {
  // TODO: Allocate data, read image data / labels, return
  FILE * file = fopen(filename, "rb");
  if(file == NULL){ //error checking
      perror("fopen(1)\n");
      exit(1); 
  }
  int n;
  fread(&n, sizeof(int), 1, file);
  //printf("total counted=%d\n", n);
  Image *images = list_of_images(n);

  unsigned char labels[n];
 
  for(int i = 0; i < n; i++){
    unsigned char data[784];
    unsigned char label;
    fread(&label, sizeof(unsigned char), 1, file);
    fread(data, sizeof(unsigned char), 784, file);
  
    labels[i] = label;
    for(int j = 0; j < 784; j++){
      images[i].data[j] = data[j];
    }
    
  
  
   // printf("count=%d\n", i);
   // printf("label=%d\n", label);
  }
  /*
    for(int i = 0; i < n; i++){
      for(int j = 0; i < 784; j++){
        printf("%4d", images[i].data[j]);
          if((i+1) % 28 == 0){
            printf("\n");
          }
        }
      }
      */

  /*
    if(!feof(file)){
      fprintf(stderr,"Error file reading");
      exit(1);
    }
  */

  Dataset *dataset = new_dataset(n,images,labels);
  if(dataset == NULL){
    fprintf(stderr, "invalid dataset");
  }
    
  fclose(file);
  //printf("count = %d", n);//error checker
  return dataset;
}


/**
 * This function computes and returns the Gini impurity of the M images
 * (with their indices stored in the array) if they were to be split
 * based on the given pixel.
 * 
 * DO NOT CHANGE THIS FUNCTION; It is already implemented for you.
 */
double split_gini_impurity(Dataset *data, int M, int indices[M], int pixel) {
  int a_freq[10] = {0}, a_count = 0;
  int b_freq[10] = {0}, b_count = 0;
  for (int i = 0; i < M; i++) {
    int img_idx = indices[i];
    // The pixels are always either 0 or 255, but using < 128 for generality.
    if (data->images[img_idx].data[pixel] < 128)
      a_freq[data->labels[img_idx]]++, a_count++;
    else
      b_freq[data->labels[img_idx]]++, b_count++;
  }

  double a_gini = 0, b_gini = 0;
  for (int i = 0; i < 10; i++) {
    double a_i = ((double)a_freq[i]) / ((double)a_count);
    double b_i = ((double)b_freq[i]) / ((double)b_count);
    if (a_count) a_gini += a_i * (1 - a_i);
    if (b_count) b_gini += b_i * (1 - b_i);
  }
  // Weighted average of gini impurity of children
  return (a_gini * a_count + b_gini * b_count) / M;
}

/**
 * Given a subset of M images and their corresponding indices, find and return
 * the most frequent label and it's frequency. The last 2 parameters are
 * only for outputs.
 *
 * - The most frequent label should be stored in `*label`
 * - The frequency of this label should be stored in `*freq`
 * 
 * If multiple labels have the same maximal frequency, return the smallest one.
 */
void get_most_frequent(Dataset *data, int M, int indices[M], 
                       int *label, int *freq) {
  // TODO: Set the correct values and return
  int label_type[10];//0-9
  for(int i = 0; i < 10; i++){
    label_type[i] = 0;
  }


  for(int i = 0; i < M; i++){
    int index = indices[i];
    int appearent_label = (int)data->labels[index];//0-9
    label_type[appearent_label]++;
  }

  int max_label = 0;
  int max_freq = 0;

  for(int i = 0; i < 10; i++){
    if(label_type[i] > max_freq){
      max_label = i;
      max_freq = label_type[i];
    }
  }

  *label = max_label;
  *freq = max_freq;
 // printf("most label = %d, freq = %d\n", max_label,max_freq);
}

/**
 * Given a subset of M images and their corresponding indices, find and return
 * the best pixel to split the data based on. The best pixel is the one which
 * has the minimum Gini impurity as computed by `split_gini_impurity()`.
 * 
 * The return value should be a number between 0-783 (inclusive), representing
 *  the pixel the M images should be split based on.
 * 
 * If multiple pixels have the same minimal Gini impurity, return the smallest.
 */
int find_best_split(Dataset *data, int M, int indices[M]) {
  // TODO: Return the correct pixel 
  // data->images[img_idx].data[pixel]
  double smallest = split_gini_impurity(data,M,indices,0);
  int best_split = 0;
  
  double current;
  for(int i = 0; i < 784; i++){
    current = split_gini_impurity(data,M,indices,i);
   if(current < smallest){
     smallest = current;
     best_split = i;
   }
  }
  //printf("best split: %d\n", best_split);
  return best_split;
}

/**
 * This is the recursive function that creates the Decision tree. In each
 * recursive call, we only want to consider some subset of the entire dataset
 * corresponding to the node. To represent this, we pass in an array of indices
 * of these images in the dataset, along with it's length M. Be careful to
 * allocate this on the array for any recursive calls made, and free it when
 * you're done with creating the tree. Here, you need to:
 *
 *    - Compute ratio of most frequent image in current call, terminate if >95%
 *    - Find the best pixel to split on using `find_best_split()`
 *    - Split the data, allocate corresponding arrays, and recurse
 *    - In either case, allocate a new node, set the correct values and return
 *       - If it's a child, set `classification`, and both children = NULL.
 *       - If it's not a child, set `pixel` and `left`/`right` (recursively). 
 */
DTNode *make_helper(Dataset *data, int M, int indices[M]) {
  // TODO: COnstruct and return tree
//get_most_frequent() is > 95%, terminate

int label = 0;
int freq = 0;
get_most_frequent(data, M, indices, &label, &freq);

DTNode *node = new_node();

if((double)(freq) / (M) >= .95){
  node->classification = label; //(most frequent label)
  node->left = NULL;
  node->right = NULL;
  return node;
}

//step 2 
//find_best_split() -best pixel to split the tree upon based on the data set
int best_split = find_best_split(data, M, indices); 
   
//make two different arrays again (like indices)
  //the left array filed with indicies of images that have pixel at best_split to 0
  //the rightarray filed with indicies of images that have pixel at best_split to 255
  int left_size = 0;

  for(int i = 0; i < M; i++){
    int current_index = indices[i];
    if(data->images[current_index].data[best_split] == 0){
      left_size++;
    } 
  }
  int right_size = M - left_size;


  /*
  for(int i = 0; i < M; i++){
    int current_index = indices[i];
    printf("index = %d, pixel at best split = %d\n",current_index,data->images[current_index].data[best_split]); 
  }
 
  printf("left size = %d, right size = %d\n", left_size,right_size);
  

 
  int *left_array = (int*)malloc(sizeof(int) * left_size);
  int *right_array = (int*)malloc(sizeof(int) * right_size);
*/
  int *left_array = malloc(sizeof(int) * left_size);
  int *right_array = malloc(sizeof(int) * right_size);

  int left_index = 0;
  int right_index = 0;

   for(int i = 0; i < M; i++){
     int current_index = indices[i];
    if(data->images[current_index].data[best_split] == 0){
      left_array[left_index] = current_index;
      left_index++;
    } else if(data->images[current_index].data[best_split] == 255){
      right_array[right_index] = current_index;
      right_index++;
    } 
  }
  
  node->left = make_helper (data, left_size, left_array);
  node->right = make_helper (data, right_size, right_array);

  free(left_array);
  free(right_array);
  
  node-> pixel = best_split;
  
  return node;
}

/**
 * This is the function exposed to the user. All you should do here is set
 * up the `indices` array correctly for the entire dataset and call 
 * `make_helper()` with the correct parameters.
 */
DTNode *make_dec_tree(Dataset *data) {
  // TODO: Set up `indices` array, call `make_helper` and return tree.
  //     Make sure you free any data that is not needed anymore (hint)
  int* indices = (int*) malloc(sizeof(int) * data-> num_items);
  if(indices == NULL){
    fprintf(stderr,"invalid malloc of indices");
    exit(1);
  }
  for(int i = 0; i< data->num_items; i++){
    indices[i] = i;
  }
  DTNode *tree = make_helper(data, data->num_items, indices);
 
  free(indices);
  return tree;
}

/**
 * Given a decision tree and an image to classify, return the predicted label.
 */
int dec_tree_classify(DTNode *root, Image *img) {
  // TODO: Return the correct label
  if(root == NULL){
    return -1;
  }
  int pixel = root->pixel;
  if(root->left == NULL && root->right == NULL){ //leaf node
    return root->classification;
  }else if(img->data[pixel] == 0){
    return dec_tree_classify(root->left,img);
  }else if(img->data[pixel] == 255){
    return dec_tree_classify(root->right, img);
  }
  return root -> classification; 
}

/**
 * This function frees the Decision tree.
 */
void free_dec_tree(DTNode *node) {
  // TODO: Free the decision tree
  if(node == NULL){
    return;
  }
  free_dec_tree(node->left);
  free_dec_tree(node->right);
  free(node);
  //return;
}

/**
 * Free all the allocated memory for the dataset
 */
void free_dataset(Dataset *data) {
  // TODO: Free dataset (Same as A1)
  
  for(int i = 0; i < data->num_items; i++){
    free(data->images[i].data);
  }
  
  free(data->images);
  free(data->labels);
  free(data);
  //return;
}