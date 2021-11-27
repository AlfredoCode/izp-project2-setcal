#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS 31
#define MAX_LINES 1000

enum set_type{U,S,R};
enum error_type{U_};

void err(char *msg){

    fprintf(stderr,"%s",msg);
}

void errAlloc(){

    fprintf(stderr,"Memory allocation failed\n");
}

typedef struct{
    char *word;

}element_t;

typedef struct{
    element_t *set;
    int size;
    int type;

}set_t;


element_t * relGetLeft(set_t *relation,int index){
	return &(relation->set[index*2]);
}
element_t * relGetRight(set_t *relation,int index){
	return &(relation->set[(index*2)+1]);
}

/**
 * @brief Allocates memory for set_t
 * 
 * @param type Defines type of TODO
 * @return set_t* 
 */
set_t *ctor(int type){
    set_t *s;
    s = malloc(sizeof(set_t));
    if(s == NULL){
        return NULL;
    }
    s->set = NULL;
    s->type = type;
    s->size = 0;
    return s;
}

void dtor(set_t *s){
    if(s == NULL){
        return;
    }
    if(s->set == NULL){
        return;

    }
    for(int i = 0;i < s->size;i++){
        free(s->set[i].word);

    }
    free(s->set);
    free(s);
}


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
        if(setContains(set,set.set[i]) > 1){
	    	return 0;
        }
	return 1;

    }

}
void fill(set_t *s, char *element){
    
    
    if(s->size == 0){
        s->set = malloc(sizeof(element_t));
        if(s->set == NULL){
            errAlloc();    
        }
        
        
    }
    else{
        s->set = realloc(s->set, sizeof(element_t) * (s->size+1));
        if(s->set == NULL){
            errAlloc();
        }
        
    }
    s->set[s->size].word = malloc(sizeof(element_t));
    if(s->set[s->size].word == NULL){
        errAlloc();
    }
    strcpy(s->set[s->size].word, element);
    (s->size)++;

}
void allocLine(FILE *file,set_t *s){
    int c;
    char word[MAX_LETTERS];
    int i = 0;
    while(((c = fgetc(file)) != EOF) && c != '\n'){
        if(i >= MAX_LETTERS){

            fprintf(stderr,"Maximum length exceeded\n");
        }
        if(c == ' '){
            //Add to struct
            word[i] = '\0';
            fill(s, word);
            i = 0;
            continue;


        }
        
        else{
            word[i] = c;
        }
        i++;
    }
    if(c != EOF){
        word[i] = '\0';
        fill(s, word);

    }
}

void printSet(set_t *s){
    
    printf("%d ",s->type);
    for(int i = 0;i < s->size;i++){

        printf("%s ",s->set[i].word);
    }
    printf("\n");
}

int parse(FILE *file,set_t **data, int *lineCount){
    int c;
    //int charPos = 0;
    
    bool isUniversum = false;
    set_t *setTmp;
    while((c = fgetc(file)) != EOF){
        //printf("%c",c);
        if(c != 'U' && *lineCount == 0){
            fprintf(stderr,"Universe not defined!\n");
        }
        if(c == 'U' && *lineCount == 0){
            
            //Struct Universe is being created
            if(fgetc(file) == ' '){
                setTmp = ctor(U);
                allocLine(file,setTmp);
            }
            
            else{
                fprintf(stderr,"Universe not defined\n");
            }
                   
                               
           
            
        }
        if(c == 'U' && *lineCount != 0){

            fprintf(stderr,"Multiple universe definition!\n");
        }

        if(c == 'S'){
            
                //Struct is being created
                if(fgetc(file) == ' '){
                    setTmp = ctor(S);
                    allocLine(file,setTmp);
                    if(!isSet(*setTmp)){
                        err("Duplicate elements in set\n");

                    }
                } 
                 
        }
        if(c == 'R'){
            
                //Struct is relation being created
                if(fgetc(file) == ' '){
                    setTmp = ctor(R);
                    allocLine(file,setTmp);
                } 
                 
                 
        }
        if(c == 'C'){
            
                //Commands
               printf("Command read\n");
               (*lineCount)++;
               return 0; //DEBUG
                 
        }  
        
        data[*lineCount] = setTmp;
        //printf("%s",data[lineCount]->set[lineCount].word);
        (*lineCount)++;

        //printSet(setTmp);
        //charPos++;
        //printSet((setTmp));
    }

    return 0;

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
    set_t **data = (set_t **)malloc(sizeof(set_t*)*MAX_LINES);
    if(data == NULL){
        errAlloc();
    }
    int i = 0;
    int err_code = parse(input,data,&i); //NACTENI DAT A INICIALIZACE KODOVEHO HLASENI
    
    int count = 0;
    while(count < i-1){
        printSet((data[count]));
        dtor(data[count]);
        count++;
        
    }
    free(data);
    
    
    fclose(input);
    return 0;
}
