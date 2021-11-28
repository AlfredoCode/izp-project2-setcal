#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS 31
#define MAX_LINES 1000
#define FORBIDDEN_WORDS_COUNT 21
#define FORBIDDEN_WORDS_MAX_LENGTH 15
enum set_type{U,S,R,C};
enum error_type{U_};


/*char ForbiddenWords [FORBIDDEN_WORDS_COUNT][FORBIDDEN_WORDS_MAX_LENGTH] =  {
                                    {"empty"},{"true"},{"false"},{"card"},
                                    {"complement"},{"union"},{"intersect"},{"minus"},
                                    {"subseteq"},{"subset"},{"equals"},{"reflexive"},
                                    {"symmetric"},{"antisymmetric"},{"transitive"},
                                    {"function"},{"domain"},{"codomain"},{"injective"},
                                    {"surjective"},{"bijective"}
                                };*/



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
        if(!strcmp(set.set[i].word, element.word)){
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
    //if(c != EOF){     //DOES NOT WORK FOR LAST STRING ON LAST LINE
        word[i] = '\0';
        fill(s, word);
    //}

    
    
}

void printSet(set_t *s){
    
    printf("%d ",s->type);
    for(int i = 0;i < s->size;i++){

        printf("%s ",s->set[i].word);
    }
    printf("\n");
}


/*int convertToNum(char *string)
{
    char end;
    int value = strtol(string, &end, 10);
    if( (end == string) || (end != '\0'))
        return 0;
    else
        return value;
}*/
void empty(set_t **data,int index){


}


void card(set_t **data, int lineCount){
    /*if(data[lineCount]->type == S){
        printf("There are %d elements in set above\n",data->size);
    }*/
}

void complement(set_t **s, int lineCount){ //TODO
    /*if(s->type == S){
        printf("Complement of < ");
        for(int i = 0;i < s->size;i++){

            printf("%s ",s->set[i].word);
        }
        printf("> is: ");
        printf("\n");
        
    }*/
}

void union_set(set_t **data,int index){


}

void intersect(set_t **data,int index){


}

void minus(set_t **data,int index){


}

void subseteq(set_t **data,int index){


}

void subset(set_t **data,int index){


}

void equals(set_t **data,int index){


}

void reflexive(set_t **data,int index){


}

void symmetric(set_t **data,int index){


}

void antisymmetric(set_t **data,int index){


}

void transitive(set_t **data,int index){


}

void function(set_t **data,int index){


}

void domain(set_t **data,int index){


}

void codomain(set_t **data,int index){


}

void injective(set_t **data,int index){


}

void surjective(set_t **data,int index){


}

void bijective(set_t **data,int index){


}


void callOperation(set_t **data,int lineCount){
    char *word = data[lineCount]->set[0].word;

    if(strcmp("empty",word)){
        empty(data, lineCount);
    }
    else if(strcmp("card",word)){
        card(data, lineCount);
    }
    else if(strcmp("complement",word)){
        complement(data, lineCount);
    }
    else if(strcmp("union",word)){
        union_set(data, lineCount);
    }
    else if(strcmp("intersect",word)){
        intersect(data, lineCount);
    }
    else if(strcmp("minus",word)){
        minus(data, lineCount);
    }
    else if(strcmp("subseteq",word)){
        subseteq(data, lineCount);
    }
    else if(strcmp("subset",word)){
        subset(data, lineCount);
    }
    else if(strcmp("equals",word)){
        equals(data, lineCount);
    }
    else if(strcmp("reflexive",word)){
        reflexive(data, lineCount);
    }
    else if(strcmp("symmetric",word)){
        symmetric(data, lineCount);
    }
    else if(strcmp("antisymmetric",word)){
        antisymmetric(data, lineCount);
    }
    else if(strcmp("transitive",word)){
        transitive(data, lineCount);
    }
    else if(strcmp("function",word)){
        function(data, lineCount);
    }
    else if(strcmp("domain",word)){
        domain(data, lineCount);
    }
    else if(strcmp("codomain",word)){
        codomain(data, lineCount);
    }
    else if(strcmp("injective",word)){
        injective(data, lineCount);
    }
    else if(strcmp("surjective",word)){
        surjective(data, lineCount);
    }
    else if(strcmp("bijective",word)){
        bijective(data, lineCount);
    }
    else{
        err("Command not found!\n");
    }

}
int subsetElements(set_t *s1, set_t *s2){
    int code = 0;
    for(int i = 0;i < s1->size;i++){
        code = 0;
        for(int j = 0; j < s2->size;j++){
            if(!strcmp(s1->set[i].word,s2->set[j].word)){
                code = 1;
            }    
        }
        if(!code){      
            return 0;
        }    
    }
    
    return 1;
}

/*int subsetElements2(set_t *s1, char **word_arr, int arr_size){
    int code = 0;
    for(int i = 0;i < s1->size;i++){
        code = 0;
        for(int j = 0; j < arr_size;j++){
            if(!strcmp(s1->set[i].word,word_arr[j])){
                code = 1;                                       
            }    
        }
        if(!code){      
            return 0;
        }    
    }
    
    return 1;
}*/


int checkValidity(set_t *s){
    int isValid = 1;
    for(int i = 0;i < s->size;i++){
        
        int elCount = setContains(*s,s->set[i]);
        if(elCount > 1){
            isValid = 0;
        }       
    }
    return isValid;

}

int checkElements(set_t **data, int lineCount){
    if(!subsetElements(data[lineCount], data[0])){
       err("Set element not defined in universe!\n");
       return 0; 
    }
    if(!checkValidity(data[lineCount])){
        err("Invalid set!\n");
        return 0;      
    }
    
    return 1;
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
                
                //UN-SUCCESSFUL PASS FORBIDDEN_WORDS INTO UNIVERSE CHECK

                /*if(subsetElements2(setTmp, ForbiddenWords,FORBIDDEN_WORDS_COUNT)){    
                    err("Commands or keywords used in universe!\n");
                }*/
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
            

            if(fgetc(file) == ' '){
                setTmp = ctor(C);
                allocLine(file,setTmp);
            }
                
                //Commands
               /*printf("Command read\n");
               (*lineCount)++;
               return 0;*/
                 
        }

          
        
        data[*lineCount] = setTmp;
        
        if(setTmp->type != C){
            checkElements(data,*lineCount);
        }
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
    
    while(count < i){
        if((data[count]->type) != C){
            
            printSet((data[count]));
        }
        else{
            callOperation(data,i);
        }
        //card((data[count]));
        //complement((data[count]),/*TODO*/);
        //dtor(data[count]);
        count++;  
    }
    count = 0;
    while(count < i){
        
        dtor(data[count]);
        count++;  
    }

    free(data);
    
 
    fclose(input);
    return 0;
}
