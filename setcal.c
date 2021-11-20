#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LETTERS 31

typedef struct{
    char **set;
    int WordCount;

}set_t;



int main(int argc, char **argv){
    if(argc !=2){
        fprintf(stderr,"invalid count of arguments\n");
        return 1;   
    }


    FILE *fileptr;
        
    if((fileptr = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,">File '%s' could not be opened\n",argv[1]);
        return 1;
            
    }
   char ForbiddenWords [21][15] =  {
                                        {"empty"},{"true"},{"false"},{"card"},
                                        {"complement"},{"union"},{"intersect"},{"minus"},
                                        {"subseteq"},{"subset"},{"equals"},{"reflexive"},
                                        {"symmetric"},{"antisymmetric"},{"transitive"},
                                        {"function"},{"domain"},{"codomain"},{"injective"},
                                        {"surjective"},{"bijective"}
                                        };
            

                //printf("%c %s\n",ForbiddenWords[2][3], ForbiddenWords[4]);
                
    char c;
    int CharCount = 0;
    int U_MAX = 0;
    bool isUniverzum = false;
    char buffer[100] = {0};
    int i = 0;
    int z = 0;
    int WordCount = 0;
               
    set_t U;
                
    while((c = fgetc(fileptr)) != EOF){
        printf("%c\n",c);
        if(c == ' '){
            buffer[CharCount] = '\0';
            if(WordCount == 0){
                printf("Aho");
                U.set = malloc(sizeof(char) * MAX_LETTERS);

            }
            else{
                U.set = realloc(U.set,sizeof(char) * MAX_LETTERS * (WordCount+1));
                        
            }
            if(U.set == NULL){

                fprintf(stderr, "Not enough memory1");
                return 1;
            }


            U.set[WordCount] = buffer;
            U.set[WordCount] = malloc(sizeof(char) * strlen(buffer));
            if(U.set[WordCount] == NULL){

                fprintf(stderr, "Not enough memory");
            }     
                    
            WordCount++;
            U.WordCount = WordCount;
                    
        }
        if(c == '\n'){
            CharCount = 0;
            isUniverzum = false;
                    
            WordCount = 0;
            continue;                      
        }
                //if (CharCount == 0){
            if(c == 'U'){   
                if(CharCount == 0){
                    isUniverzum = true;
                    CharCount++;
                    if(fgetc(fileptr) != ' '){
                                
                        fprintf(stderr,"Space after initializator error\n");
                        return 1;
                    }
                            //printf("I found U definition\n");
                    continue;
                } 
                else{
                            
                    fprintf(stderr,"Error on token U %d\n",CharCount);
                    return 1;
                }
            }
            buffer[CharCount] = c;
            CharCount++;




                    /*else{
                        isUniverzum = false;
                        fprintf(stderr,"Universum has not been found\n");
                        return 0;                    
                    }*/
                    
               // }    
                //else if(CharCount == 1){
                    /*if(c == ' ' ){
                        isUniverzum = true;
                        printf("I found U definition\n");
                    }
                    else{
                        isUniverzum = false;
                        fprintf(stderr,"Universum has not been found\n");
                        return 0; 
                    }*/
                //}
                    
                    
                    
                    
                    
                    /*if(isUniverzum == true && c != '\n'){                  
                        
                        if(c == ' '){
                            
                            U_MAX++; 
                            for(i = 0;i <= 31;i++){
                                prvek[i] = 0;
                            }
                            i = 0;        
                        }
                        else{    
                            prvek[i] = c;
                            if(strcmp(prvek,"empty") == false){
                                fprintf(stderr,"Universum cannot contain command identifiers or key words 'true' or 'false'\n");
                                return 0;
                            }    
                            prvek[i+1] = '\0';
                            i++;                      
                        }                           
                    } */  
                //CharCount++;
                
    } 
    for(i = 0; i < U.WordCount;i++){
        free(U.set[i]);

    }
            
    free(U.set);
            

    printf("Debug\n");
        

    fclose(fileptr);

    return 0;
}