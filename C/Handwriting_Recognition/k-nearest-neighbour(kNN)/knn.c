#include "knn.h"
//#include <math.h>


//helper function
Dataset *new_dataset(int num_items, Image *images, unsigned char *labels){
  //allocate
  Dataset *dataset = malloc(sizeof(Dataset));
  
  //dataset->num_items = calloc(sizeof(int),1);
  dataset->num_items = num_items;
  dataset->images = malloc(sizeof(Image) * dataset->num_items);
  dataset->labels = malloc(sizeof(unsigned char) * dataset->num_items);
  //assign
  dataset->images = images;
  dataset->labels = labels;
  return dataset;

}
/*
Image *new_image(int sx, int sy, unsigned char *data){ 
  Image *i = malloc(sizeof(Image));
 // i->sx = malloc(sizeof(int));
//  i->sy = malloc(sizeof(int));
  i->sx = sx;
  i->sy = sy;
  //i->data = malloc(sizeof(unsigned char) * sx * sy);
  i->data = data;
  return i;
}
*/

Image new_image(int sx, int sy, unsigned char *data){ 
  Image i;
 // i->sx = malloc(sizeof(int));
//  i->sy = malloc(sizeof(int));
  i.sx= sx;
  i.sy = sy;
  i.data = malloc(sizeof(unsigned char) * sx * sy);
  i.data = data;
  return i;
}


Dataset *load_dataset(const char *filename) {
  // TODO: Allocate data, read image data / labels, return
  int num_items =  0;

  char line[1024];
  int sx,sy;

  //FILE * ds = fopen(filename, "r");
  FILE * ds = fopen(filename, "r");

  if(ds == NULL){ //error checking
        perror("fopen()1\n");
        exit(1);
    }
  while (fgets(line, sizeof(line), ds)){
    num_items++;
  }

  rewind(ds);//read through the file again
  Image images[num_items];      
  unsigned char labels[num_items];
  int index = 0;
  while (fgets(line, sizeof(line), ds)){ //loop through each line
    char fname[1024];
    strcpy(fname,strtok(line,"\n"));
    FILE * fd = fopen(fname, "rb");
    if(fd == NULL){ //error checking
        perror("fopen()2\n");
        exit(1);
    }
    char label = (unsigned char) fname[strlen(fname)-5] - '0'; //get the "groud truth"

    fscanf(fd,"%*s %d %d %*d", &sx,&sy);//skip the P2 and grey level (dont need them)
    int size = sx * sy;
    int int_bytes[size];
    unsigned char bytes[size];
    for(int i = 0; i< size; i++){
        fscanf(fd, "%d", int_bytes);//should i change it afterwards?
        bytes[i] = (unsigned char)int_bytes[i]; //is this valid?
    }

    Image image = new_image(sx, sy, bytes);
   //and labels
    labels[index] = label;
    //and image
    images[index] = image;


    //free(image);
    fclose(fd);
    //update num_items
    index++;

  }

  //create final data
  Dataset *data = new_dataset(num_items, images, labels);
  //free file
  fclose(ds);
  //return dataset
  return data;
}

/****************************************************************************/
/* For all the remaining functions you may assume all the images are of the */
/*     same size, you do not need to perform checks to ensure this.         */
/****************************************************************************/

/** 
 * Return the euclidean distance between the image pixels (as vectors).
 */
double distance(Image *a, Image *b) {
  // TODO: Return correct distance
  int size = (a->sx) * (a->sy);//since same size, dont need to check b
  double SUM = 0.0;
  for(int i = 0; i < size; i++){
    SUM = SUM + pow((double)(a->data[i] - b->data[i]), 2.0);
  }
  return (sqrt(SUM));
  //return 0; 
}




//helper function - return the index of largest distance in d_list
int largest(double d_list[], int size){
  int largest = 0;
  int largest_index = 0;

   //return the index of largest distance in list
   for(int i = 0; i < size; i++){
     if(d_list[i] > largest){
       largest = d_list[i];
       largest_index = i;
     }
   }
   return largest_index;
}
/*
//helper function
bool noExist(unsigned char types[], unsigned char item, int size){
//  int list_size = sizeof(list)/sizeof(unsigned char);
  for(int i = 0; i < size ; i++){
      if(types[i] == item) return false;
  }
  return true;
}
*/

//helper function
unsigned char getType(unsigned char* types, unsigned char * list, int size, int list_size){
  double counts[size];
  for(int i = 0; i < size; i++){//set all the counts to 0 first
    counts[i] = 0;
  }
 // int list_size = sizeof(list)/sizeof(unsigned char);
  for(int i = 0; i < list_size; i++){
    for(int j = 0; j < size; j++){
      if (types[j] == list[i]){
        counts[j]++;
      }
    }
  }
  int largest_index = largest(counts,size);
  return(types[largest_index]);
}

/**
 * Given the input training dataset, an image to classify and K,
 *   (1) Find the K most similar images to `input` in the dataset
 *   (2) Return the most frequent label of these K images
 * 
 * Note: If there's multiple images with the same smallest values, pick the
 *      ones that come first. For automarking we will make sure the K smallest
 *      ones are unique, so it doesn't really matter.
 */ 
//kth closest ints
int knn_predict(Dataset *data, Image *input, int K) {//trainning dataset!!!
  // TODO: Replace this with predicted label (0-9)
  //Image *images_list = data->images;
  int numOfItems = data->num_items;
  //double distances[numOfItems];
  double closest_distances[K];//list of closest distance(in order to update them)
  int closest_indexes[K]; //list of closest images(index)
  unsigned char list_of_labels[K];

  //we compare the image input with 
   int check = 0;
  for(int i = 0; i < numOfItems; i++){
    double dis = distance(&(data->images[i]), input);
    //check if rank is full
    if(check < K){
        closest_distance[check] = dis;
        closest_indexes[check] = i;
        check++;
     }else{
     //else if the rank list is full... we replace
     //we get the largest distance's index on distance_list and compare it
      int largest_index = largest(closest_distances,K);
      if(closest_distance[largest_index] > dis){ //if the dis is smaller, we replace it with the orignal largest distance
        closest_distance[largest_index] = dis;
        closest_indexes[largest_index] = i; //update the index of that image on our dataset as well so we can get the label afterwards
      }
     }
    }
    //after we get the list of closest_distance, we loop through the index loop and get the labels of those closest images
    for(int i = 0; i < K; i++){
        list_of_labels[i] = data->labels[closest_indexes[i]];
    }

    //get possible labels
    unsigned char types_labels[10];//0-9
    for(int i = 0; i < 10; i++){
        types_labels[i] = i;
    }
     //count the number of labels
     //retrun the label
      
    
    return getType(types_labels, list_of_labels, 10, K); //the the type that appears the most in the list
    

// return -1;
  }
 



/** 
 * Free all the allocated memory for the dataset
 */
void free_dataset(Dataset *data) {
  // TODO: free data...and what else? remeber to check!
  //free all the stuff we allocated
  for(int i = 0; i < data->num_items; i++){
    free(data->images[i].data);
  }
  free(data->images);
  free(data->labels);
  free(data);
}
