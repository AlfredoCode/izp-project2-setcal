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


/**
 * @brief Function for printing error messages
 * 
 * @param msg Message to be printed
 */
void err(char *msg){

    fprintf(stderr,"%s",msg);
}
/**
 * @brief often used error message
 * 
 */
void errAlloc(){

    err("Memory allocation failed\n");
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
 * @brief Allocates memory for set_t and sets default value to s.type, the rest of the value are set to 0 or NULL
 * 
 * @param type Defines type of the set_t
 * @return set_t* Pointer to newly created set
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
/**
 * @brief Systematically frees s.set and then the set itself
 * 
 * @param s Pointer to set_t to be freed
 */
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

/**
 * @brief Counts how many times specific element_t appears in set_t
 * 
 * @param set Set_t to be checked
 * @param element Element_t to be found
 * @return int Number of times element_t is in set_t
 */
int setContains(set_t set, element_t element){
    int count = 0;

    for(int i = 0;i < set.size;i++){
        if(!strcmp(set.set[i].word, element.word)){
            count++;
        }   
    }
    return count;
}
/**
 * @brief Checks if given set_t is a Set
 * 
 * @param set Set_t to be checked
 * @return int Value 0(false) - set_t set is not a set. Value 1(true) - set_t set is a set
 */
int isSet(set_t set){
    for(int i = 0;i < set.size;i++){
        if(setContains(set,set.set[i]) > 1){
	    	return 0;
        }
	return 1;
    }
}
/**
 * @brief Adds set_t values to s.set
 * 
 * @param s Set to which a value is added
 * @param element Word to be added
 */
// We should probably rename this function to add
// Also why char * Element why not word - Michal
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
/**
 * @brief Load a line from file to a set_t
 * 
 * @param file Input file
 * @param s Set_t in which a line kept
 */
void allocLine(FILE *file,set_t *s){
    int c;
    char word[MAX_LETTERS];
    int i = 0;

    
    while(((c = fgetc(file)) != EOF) && c != '\n'){
        if(i >= MAX_LETTERS){

            err("Maximum length exceeded\n");
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
/**
 * @brief Prints the type of the set followed by all its elements
 * 
 * @param s Set_t to be printed
 */
void printSet(set_t *s){
    switch(s->type){
	case U:
		printf("U ");
		break;
	case R:
		printf("R ");
		break;
	
	case S:
		printf("S ");
		break;
    	default:
		printf("jiny typ mnoziny");
	}
    //printf("%d ",s->type);
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

void card(set_t *s){
    /*if(s->type == S){
        printf("There are %d elements in set above\n",s);
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

/**
 * @brief Decides which command function to execute
 * 
 * @param data Dynamically allocated array of pointers to set_t where input is stored
 * @param lineCount Line on which given command is located
 */
void callOperation(set_t **data,int lineCount){
    char *word = data[lineCount]->set[0].word;

    if(strcmp("empty",word)){
        empty(data, lineCount);
    }
    else if(strcmp("card",word)){
	if(data[lineCount]->size!=2){
		err("invalid argument of command card\n");
		return;
	}
	// int setLine = strtol(data[lineCount]->set[1].word);
        //card(data[setLine]);
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
/**
 * @brief Checks whether s1 is subset of s2
 * 
 * @param s1 Possible subset 
 * @param s2 Possible superset
 * @return int Value 0(false) - set_t s1 is not a subset. Value 1(true) - set_t s1 is a subset
 */
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

/**
 * @brief Checks whether all elements of set are in universe and whether the set is a Set
 * 
 * @param data Dynamically allocated array of pointers to set_t where input is stored
 * @param lineCount Line on which given set is located
 * @return int Value 0(false) - check failed and and error message was printed. Value 1(true) - check successful
 */
int checkElements(set_t **data, int lineCount){
    if(!subsetElements(data[lineCount], data[0])){
       err("Set element not defined in universe!\n");
       return 0; 
    }
    if(!isSet(*(data[lineCount]))){
        err("Invalid set!\n");
        return 0;      
    }
    
    return 1;
}


/**
 * @brief Parses input file and loads data
 * 
 * @param file Pointer to input file
 * @param data Dynamically allocated array of pointers to set_t where input is stored
 * @param lineCount Number of already parsed lines
 * @return Value 0 - parse successful, else output for error value
 */
int parse(FILE *file,set_t **data, int *lineCount){
    int c;
    //int charPos = 0;
    
    bool isUniversum = false;
    set_t *setTmp;
    while((c = fgetc(file)) != EOF){
        //printf("%c",c);
        if(c != 'U' && *lineCount == 0){
            err("Universe not defined!\n");
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
                err("Universe not defined\n");
            }    
        }
        if(c == 'U' && *lineCount != 0){

            err("Multiple universe definition!\n");
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
        err("Invalid count of arguments\n");
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
            callOperation(data,count);
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