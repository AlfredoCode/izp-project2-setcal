#include <stdio.h>
#include <stdbool.h>
#define MAX_LETTERS 31


typedef struct{
    int size;
    char *word;

}element_t;

typedef struct{
    element_t *set;
    int size;

}set_t;




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

    FILE *input;
    if((input = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,">File '%s' could not be opened\n",argv[1]);
        return 1;
    } 
    parse(input);
    fclose(input);
    return 0;
}