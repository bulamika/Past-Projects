#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//malloc for sx and sy
int main(int argc, char *argv[]){
    char fname[1024];
    int num_items;
    FILE * ds = fopen("lists/testing_1k.txt", "r");
     if(ds == NULL){ //error checking
        perror("fopen()\n");
        exit(1);
    }
     while (fgets(fname, sizeof(fname), ds)){
        num_items++;
    }
    rewind(ds);
    while (fgets(fname, sizeof(fname), ds)){
       printf("%s \n", fname);
     }
     printf("%d", num_items);
     return 0;

   // printf("%d , %s, %s \n", atoi(argv[1]), argv[2], argv[3]);
   /* 
    FILE * fd = fopen("datasets/testing/0-7.pgm", "r"); //we only need reading for this case
    
    //return value is NULL if not seccesfully opened
    if(fd ==NULL){
        perror("fopen()\n");
        exit(1);
    }
    char str[1024];
    int sx,sy;
    //int grey;
//P2
//28 28
//255
    fscanf(fd,"%*s %d %d %*d", &sx,&sy); //read things and stores it at the pointer
    //%*s - i want to read the string but dont store it
    //P2-not important
  
    int size = sx * sy, buffer;
   // int buffer;
    for(int i = 0; i< size; i++)
    {
        scanf(fd, "%d", &buffer);
    }

   //rewind(fd); //set the file pointer back again, or just close it
    fclose(fd);//close file
//dont need to write the path for these txt since we already considered it 
//in command line
*/

/*char fname[1024] = "datasets/testing/1016-6.pgm";
char label = (unsigned char) fname[strlen(fname)-5] - 48;
//char label = (unsigned char) fname[strlen(fname)-5] - '0'; //so you have the label(-4?)
printf("label = %d\n",label);
*/
//int K = 5;
//int fname[K];
//unsigned char *hi;
/*char *argv[] = "1", "abcde", "cdefg";
//*(hi+1) = 6;
int K;
char trainning_list[1024];
char testing_list[1024];
scanf(*argv,"%d %s %s", &K, &trainning_list, &testing_list);
printf("%d %s %s\n", K, trainning_list, testing_list);
*/

//Image *i = new_image(10, 10, 0);

//printf("%d, %d, %c\n", i->sx, i->sy, i->data);
//printf("size is %d\n", sizeof(i));





}
//quick sort for the training set?


//know the number of items for dataset?
//run through the code once to get the total number of items
//and then rewind!

//Dataset *load_dataset(const char *filename){


//}
