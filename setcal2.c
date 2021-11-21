#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LETTERS 31



typedef struct{
    int size;
    char *word;

}element_t;

typedef struct{
    element_t *set;
    int size;

}set_t;


int setContains(set_t set, element_t element){
    int count = 0;

    for(int i = 0;i < set.size;i++){
        if(strcmp(set.set[i].word, element.word)){

            count++;
        }
        
        
    }
    return count;

}

int isSet(set_t set){
    for(int i = 0;i < set.size;i++){
        if(setContains(set,set.set[i]) == 1){

        }
        else{}

    }

}



int parse(FILE *file){
    int c;
    int CharPos = 0;
    bool isUniversum = false;
    while((c = fgetc(file)) != EOF){
        printf("%c",c);
        if(c == 'U' && CharPos == 0){
            if(!isUniversum){
                isUniversum = true;


            }
            else{
                fprintf(stderr,"Error of multiple universe definition\n"); 
                return 1;
            }
            
        }


    }

}



int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr,"Invalid count of arguments\n");
        return 1;   
    }
    /*set_t setU;
    
    element_t test;
    test = malloc();
    test.word = "App";
    setContains(setU,test);*/

    FILE *input;
    if((input = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,">File '%s' could not be opened\n",argv[1]);
        return 1;
    } 
    parse(input);
    fclose(input);
    return 0;
}