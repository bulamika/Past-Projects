#include "knn.h"

/**
 * Compilation command
 *    gcc -Wall -std=c99 -lm -o classifier classifier.c knn.c
 *
 * Decompress dataset into individual images:
 *    tar xvzf datasets.tgz
 *
 * Running quick test with 1k training and 1k testing images, K = 1:
 *    ./classifier 1 lists/training_1k.txt lists/testing_1k.txt
 *
 * Running full evaulation with all images, K = 7: (Will take a while)
 *    ./classifier 7 lists/training_full.txt lists/testing_full.txt
 */

/*****************************************************************************/
/* Do not add anything outside the main function here. Any core logic other  */
/* than what is described below should go into `knn.c`. You've been warned!  */
/*****************************************************************************/

/**
 * main() takes in 3 command line arguments:
 *    - K : The K value for K nearest neighbours 
 *    - training_list: Name of a text file with paths to the training images
 *    - testing_list:  Name of a text file with paths to the testing images
 *
 * You need to do the following:
 *    - Parse the command line arguments, call `load_dataset()` appropriately.
 *    - For each test image, call `knn_predict()` and compare with real label
 *    - Print out (only) one integer to stdout representing the number of 
 *        test images that were correctly predicted.
 *    - Free all the data allocated and exit.
 */

//argc = "argument count"
//argv = "argument value"


int main(int argc, char *argv[]) {
  // TODO: Handle command line arguments
  //if(argc != 4){
   // printf("Invalid command!");
  //  return 0;
  //}
  
  int K = atoi(argv[1]);
  //char trainning_list[1024];
  //char testing_list[1024] = argv[2];
 // strcpy(trainning_list, );

  //scanf("%d %s %s", &K, &trainning_list, &testing_list);
  //scanf(*argv,"%d %s %s", &K, &trainning_list, &testing_list);
  Dataset *trainning_set = load_dataset(argv[2]);
  Dataset *testing_set = load_dataset(argv[3]);//get the correct answer for checking
  int total_correct = 0;
  //loop over testing_list with ken_predict and compare with trainning_list
  // TODO: Compute the total number of correct predictions
  
 
  for(int i = 0; i < testing_set->num_items; i++){
    //printf("%d\n",knn_predict(testing_set,testing_set->images[i],K));
    //if(...) total_correct++;
  Image *image_list = testing_set->images;
  //for debug
    //printf("actual is %d ",testing_set->labels[i]);
    //printf("predict is %d\n",knn_predict(trainning_set,&image_list[i],K));
    if(testing_set->labels[i] == knn_predict(trainning_set,&image_list[i],K)){
      total_correct++;
    }
  }
  
  // Print out answer
  printf("%d\n", total_correct);
  free(trainning_set);
  free(testing_set);

  //printf("%d\n", total_correct);
  return 0;
  

}