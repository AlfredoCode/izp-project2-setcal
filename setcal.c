#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



//Possible remove of Univerzum_Check() up to Command_Check()
int Univerzum_Check(char c){
    if(c == 'U'){
        return true;
    }
    else{
        return false;
    }    
}

int Set_Check(char c){
    if(c == 'S'){
        return true;
    }
    else{
        return false;
    }
}

int Relations_Check(char c){
    if(c == 'R'){
        return true;
    }
    else{
        return false;
    }  
}

int Command_Check(char c){
    if(c == 'C'){
        return true;
    }
    else{
        return false;
    }  
}


int main(int argc, char **argv){

    if(argc == 2){
        FILE *fileptr;
        
        if((fileptr = fopen(argv[1],"r")) == NULL){
            fprintf(stderr,">File '%s' could not be opened\n",argv[1]);
            return 1;
            
        }
        else{
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
            char prvek[32] = {0};
            int i = 0;
            int z = 0;
             
            
            
            while((c = fgetc(fileptr)) != EOF){
                
                if(c == '\n'){
                    CharCount = 0;
                    break;                       
                }
                if (CharCount == 0){
                    if(Univerzum_Check(c) == true){     
                        isUniverzum = true;
                        CharCount++;
                        continue;
                    }
                    else if(Univerzum_Check(c) == false){
                        isUniverzum = false;
                        fprintf(stderr,"Universum has not been found\n");
                        return 0;                    
                    }
                }    
                else if(CharCount == 1){
                    if(c == ' '){
                        isUniverzum = true;
                        printf("I found U definition\n");
                    }
                    else{
                        isUniverzum = false;
                        fprintf(stderr,"Universum has not been found\n");
                        return 0; 
                    }
                }
                    if(isUniverzum == true && c != '\n'){                  
                        
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
                    }   
                CharCount++;
            } 
            /*char Univerzum_Elements[U_MAX][30];
            strcpy(Univerzum_Elements[z],prvek);
            printf("%s ",Univerzum_Elements[z]);*/     
        }
        fclose(fileptr);
    }




    else if(argc == 1){
        fprintf(stderr,"Please provide input FILE\n");
    }
    else{
        fprintf(stderr,"Too many arguments\n");
    }

    return 0;
}