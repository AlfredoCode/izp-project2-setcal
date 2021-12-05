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


char *ForbiddenWords [FORBIDDEN_WORDS_COUNT] =  {
                                    "empty","true","false","card",
                                    "complement","union","intersect","minus",
                                    "subseteq","subset","equals","reflexive",
                                    "symmetric","antisymmetric","transitive",
                                    "function","domain","codomain","injective",
                                    "surjective","bijective"
                                };


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
    }
    return 1;
}
/**
 * @brief Fills s.set with element_t values
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
int allocLine(FILE *file,set_t *s){
    int c;
    char word[MAX_LETTERS];
    int i = 0;
    bool inRelation = false;
    int elNumber = 0;
    
    while(((c = fgetc(file)) != EOF)){
        if(i >= MAX_LETTERS){

            err("Maximum length exceeded\n");
            return -1;
        }
        if(c == ' ' || c=='\n'){
            //Add to struct
            word[i] = '\0';
            //printf("%s %d\n", word,strlen(word));
            if(strlen(word)>0){
	            fill(s, word);
   	        }
            if(inRelation==true){
                elNumber++;
            }
            i = 0;
            if(c=='\n'){
                break;
            }
            continue;
        }

        if(s->type == R){
            if(c == '('){
                if(inRelation == true){
                    err("Relation is not defined correctly\n"); //TODO
                    return -1;
                }
                inRelation = true;
                continue;
            }
            if(c == ')'){
                if(inRelation == false){
                    err("Relation not defined correctly\n");
                    return -1;
                }  
                if(elNumber != 1){
                    err("Invalid number of elements in relation\n");
                    return -1;
                }
                inRelation = false;
                elNumber = 0;
		
                continue;
            } 
           
        }
        
        
        word[i] = c;
       
        i++;
    }
    //if(c != EOF){     //DOES NOT WORK FOR LAST STRING ON LAST LINE
        /*word[i] = '\0';
        fill(s, word);*/
    //}

    
    return 0;
}
/**
 * @brief Prints the type of the set followed by all its elements
 * 
 * @param s Set_t to be printed
 */
void printSet(set_t *s){
    switch(s->type){
	case U:
		printf("U");
		break;
	case R:
		printf("R");
		break;
	
	case S:
		printf("S");
		break;
    default:
		printf("jiny typ mnoziny");
	}
    //printf("%d ",s->type);
    int size = s->size;
    if(s->type == R){
        size = size / 2;
    }
    for(int i = 0;i < size;i++){
        
        if(s->type == R){
            printf(" (%s %s)",relGetLeft(s,i)->word,relGetRight(s,i)->word);

        }
        else{
            printf(" %s",s->set[i].word);
        }
        
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


/**
 * 
 * @brief Prints true if given set A is empty 
 * 
 * @param s Pointer to set A
 */
int empty(set_t *s){
    if (s == NULL ){
        err("Set undefined\n");
        return -1;
    }
    if(!((s->type == S) || (s->type == U))){
        err("Ivalid command\n");
        return -1;
    }

    if(s->size == 0)
        printf("true\n");
    else printf("false\n"); 
    return 0;
}

/**
 * @brief Prints cardinality of a set A 
 * 
 * @param s Pointer to set A
 */
int card(set_t *s){
    if (s == NULL ){
        err("Set undefined\n");
        return -1;
    }
    if(!((s->type == S) || (s->type == U))){
        err("Invalid command\n");
        return -1;
    }
    printf("%d\n", s->size);
    return 0;
}

/**
 * @brief Prints complement of set A to set B
 * 
 * @param s1 Pointer to a set A
 * @param s2 Pointer to a set B to which complement is made. In this case always Universe
 */
int complement(set_t *s1, set_t *s2){
    if (s1 == NULL || s2 == NULL){
        err("Set undefined\n");
        return -1;
    }
    if (!((s1->type == S) || (s1->type == U)) || !((s2->type == S) || (s2->type == U))){
        err("Invalid command\n");
        return -1;
    }
    
    bool inSet=false;
    printf("S");
    for(int i = 0; i < s2->size; i++){
        for(int j = 0;j < s1->size; j++){
            if(!strcmp(s2->set[i].word, s1->set[j].word))
                inSet = true;
        }
        if (!(inSet))
            printf(" %s", s2->set[i].word);
        inSet = false;
    }
    printf("\n");
    return 0;
}

/**
 * @brief Prints union of set A and set B
 * 
 * @param s1 Pointer to set A
 * @param s2 Pointer to set B
 */
int union_set(set_t *s1, set_t *s2){
    if (s1 == NULL || s2 == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(!((s1->type == S) || (s1->type == U)) || !((s2->type == S) || (s2->type == U))){
        err("Invalid command\n");
        return -1;
    }

    bool inSet = false;
    printf("S");

    for(int i = 0; i < s1->size; i++){
        printf(" %s", s1->set[i].word);
    }
    for(int i = 0; i < s2->size; i++){
        for(int j = 0; j < s1->size; j++){
            if(!strcmp(s2->set[i].word, s1->set[j].word)){
                inSet = true;
            }
        }
        if(!inSet){
            printf(" %s", s2->set[i].word);
        }
        inSet=false;
    }
    printf("\n");
    return 0;

}

/**
 * @brief Prints intersection of set A and set B
 * 
 * @param s1 Pointer to set A
 * @param s2 Pointer to set B
 */
int intersect(set_t *s1, set_t *s2){
    if (s1 == NULL || s2 == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(!((s1->type == S) || (s1->type == U)) || !((s2->type == S) || (s2->type == U))){
        err("Invalid command\n");
        return -1;
    }

    bool inSet = false;
    printf("S");

    for(int i = 0; i < s1->size; i++){
        for(int j = 0; j < s2->size; j++){
            if(!strcmp(s1->set[i].word, s2->set[j].word)){
                inSet = true;
            }
        }
        if(inSet){
            printf(" %s", s1->set[i].word);
        }
        inSet=false;
    }
    printf("\n");
    return 0;
}

/**
 * @brief Prints subtraction of set A \ set B
 * 
 * @param s1 Pointer to set A 
 * @param s2 Pointer to set B
 */
int minus(set_t *s1, set_t *s2){
    if (s1 == NULL || s2 == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(!((s1->type == S) || (s1->type == U)) || !((s2->type == S) || (s2->type == U))){
        err("Invalid command\n");
        return -1;
    }

    bool inSet = false;
    printf("S");

    for(int i = 0; i < s1->size; i++){
        for(int j = 0; j < s2->size; j++){
            if(!strcmp(s1->set[i].word, s2->set[j].word)){
                inSet = true;
            }
        }
        if(!inSet){
            printf(" %s", s1->set[i].word);
        }
        inSet=false;
    }
    printf("\n");
    return 0;
}

int subseteqCheck(set_t *s,set_t *uni){
    int count = 0;
    for(int i = 0;i < s->size;i++){
        for(int j = 0; j < uni->size;j++){
            if(!strcmp(s->set[i].word,uni->set[j].word)){
                count++;
            }    
        }
     }
     if(count!=s->size){
  	return 0;
     }
     return 1;
}
void subseteq(set_t *a,set_t *b){
    if(subseteqCheck(a, b)){
        printf("true\n");
    }
    else{
        printf("false\n");
    }
}

/**
 * @brief Prints true if set A is a subset of B
 * 
 * @param s1 Pointer to set A
 * @param s2 Pointer to set B
 */
int subset(set_t *s1, set_t *s2){
    if (s1 == NULL || s2 == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(!((s1->type == S) || (s1->type == U)) || !((s2->type == S) || (s2->type == U))){
        err("Invalid command\n");
        return -1;
    }

    if(s1->size >= s2->size){
        printf("false\n");
        return 0;
    }

    bool inSet = false;

    for(int i = 0; i < s1->size; i++){
        for(int j = 0; j < s2->size; j++){
            if(!strcmp(s1->set[i].word, s2->set[j].word)){
                inSet = true;
            }
        }
        if(!inSet){
            printf("false\n");
            return 0;
        }
        inSet=false;
    }
    printf("true\n");
    return 1;
}

int equals(set_t *s1,set_t *s2){
    if (s1 == NULL || s2 == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(!((s1->type == S) || (s1->type == U)) || !((s2->type == S) || (s2->type == U))){
        err("Invalid set input\n");
        return -1;
    }
    if(s1->size != s2->size){
        printf("false\n");
        return 0;
    }
    bool isEqual = true;
    for(int i = 0;i < s1->size;i++){
        if(isEqual != true){
            printf("false\n");
            return 0;
        }
        for(int j = 0;j < s2->size;j++){
            if(!strcmp(s1->set[i].word,s2->set[j].word)){
                isEqual = true;
                break;
            }
            else{
                isEqual = false;
            }

        }
    }
    printf("true\n");
    return 1;

}

/**
 * @brief Prints true if given relation R is reflexive on S
 * 
 * @param r Pointer to relation R
 * @param s Pointer to set S. in this case always universe
 */
int reflexive(set_t *r, set_t *s){
    if (r == NULL || s == NULL){
        err("Set undefined\n");
        return -1;
    }
    if((r->type != R) || !(s->type == S || s->type == U)){
        err("Invalid command\n");
        return -1;
    }
    if(r->size/2 < s->size){
        printf("false\n");
        return 0;
    }

    bool inSet = false;

    for(int i = 0; i < s->size; i++){
        for(int j = 0; j < r->size/2; j++){
            if(!strcmp(s->set[i].word, relGetLeft(r,j)->word) && !strcmp(s->set[i].word, relGetRight(r,j)->word))
            {
                inSet = true;
            }
        }
        if(!inSet){
            printf("false\n");
            return 0;
        }
        inSet=false;
    }
    printf("true\n");
    return 1;
}

/**
 * @brief Prints true if given relation R is symmetric
 * 
 * @param r Pointer to relation R
 */
int symmetric(set_t *r){
    if (r == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R){
        err("Invalid command\n");
        return -1;
    }

    bool isSymmetric = false;

    for(int i = 0; i < r->size/2; i++){
        if (!strcmp(relGetLeft(r,i)->word, relGetRight(r, i)->word))
            continue;
        for(int j = 0; j < r->size/2; j++){
            if(i==j){
                continue;
            }
            if(!strcmp(relGetLeft(r,i)->word, relGetRight(r, j)->word) && !strcmp(relGetRight(r, i)->word, relGetLeft(r, j)->word))
            {
                isSymmetric = true;
            }
        }
        if(!isSymmetric){
            printf("false\n");
            return 0;
        }
        isSymmetric=false;
    }
    printf("true\n");
    return 1;
}

/**
 * @brief Prints true if given relation R is Antisymmetric
 * 
 * @param r Pointer to relation R
 */
int antisymmetric(set_t *r){
    if (r == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R){
        err("Invalid command\n");
        return -1;
    }

    bool isAntiSymmetric = true;

    for(int i = 0; i < r->size/2; i++){
        if (!strcmp(relGetLeft(r, i)->word,relGetRight(r, i)->word))
            continue;
        for(int j = 0; j < r->size/2; j++){
            if(i==j){
                continue;
            }
            if(!strcmp(relGetLeft(r,i)->word, relGetRight(r, j)->word) && !strcmp(relGetRight(r, i)->word, relGetLeft(r, j)->word))
            {
                isAntiSymmetric = false;
            }
        }
        if(!isAntiSymmetric){
            printf("false\n");
            return 0;
        }
        isAntiSymmetric=true;
    }
    printf("true\n");
    return 1;
}

/**
 * @brief Prints true if given relation R is transitive
 * 
 * @param r Pointer to relation R
 */
int transitive(set_t *r){
    if (r == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R){
        err("Invalid command\n");
        return -1;
    }

    bool isTransitive = false;

    for(int i = 0; i < r->size/2; i++){
        for(int j = 0; j < r->size/2; j++){
            if(!strcmp(relGetRight(r, i)->word, relGetLeft(r, j)->word)){
                for(int k = 0; k < r->size/2; k++){
                    if(!strcmp(relGetLeft(r, i)->word, relGetLeft(r, k)->word) && !strcmp(relGetRight(r, j)->word, relGetRight(r, k)->word)){
                        isTransitive=true;
                    }
                }
                if(!isTransitive){
                printf("false\n");
                return 0;
                }
                isTransitive=false;
            }
        }
    }
    printf("true\n");
    return 1;
}

/**
 * @brief checks whether given relation R is a funciton
 * 
 * @param r Pointer to relation R
 * @return true Given relation is a function
 * @return false Given relation is not a function
 */
bool functionCheck(set_t *r){
    for(int i = 0; i < r->size/2; i++){
        for(int j = 0; j < r->size/2; j++){
            if(!strcmp(relGetLeft(r, i)->word, relGetLeft(r, j)->word) && strcmp(relGetRight(r,i)->word, relGetRight(r, j)->word)){
                return false;
            }
        }
    }
    return true;

}

/**
 * @brief Prints true if given relation R is a function
 * 
 * @param r Pointer to relation R
 */
int function(set_t *r){
    if (r == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R){
        err("Invalid command\n");
        return -1;
    }

    if(functionCheck(r)){
        printf("true\n");
        return 1;
    }
    else{
    printf("false\n");
    return 0;
    }
}

int domain(set_t *s){
    if (s == NULL ){
        err("Relation undefined\n");
        return -1;
    }
    if(s->type != R){
        err("Invalid relation input\n");
        return -1;
    }
    int count;
    printf("S");
    for(int i = 0;i < s->size;i++){
        count = i*2;
        if(s->size > count){
            printf(" %s",relGetLeft(s,i)->word);
        }
        
    }
    printf("\n");
    return 0;
    

}

int codomain(set_t *s){
    if (s == NULL ){
        err("Relation undefined\n");
        return -1;
    }
    if(s->type != R){
        err("Invalid relation input\n");
        return -1;
    }
    int count;
    printf("S");
    for(int i = 0;i < s->size;i++){
        count = (i * 2 ) + 1;
        if(s->size > count){
            printf(" %s",relGetRight(s,i)->word);
        }
        
    }
    printf("\n");
    return 0;

}

/**
 * @brief Checks whether given relation R is injective on sets A and B
 * 
 * @param r Pointer to relation R
 * @param a Pointer to set A (Codomain)
 * @param b Pointer to set B (Domain)
 * @return true Given relation is injective
 * @return false Given relation is not injective
 */
bool injectiveCheck(set_t *r, set_t *a, set_t *b){
    
    if(r->size!= a->size){
        return false;
    }

    bool isInjective=true;

    for(int i = 0; i < a->size; i++){
        for(int j = 0; j < b->size; j++){
            if(!strcmp(a->set[i].word, a->set[j].word))
                continue;
            if(strcmp(a->set[i].word, a->set[j].word) && !strcmp(b->set[i].word,b->set[j].word)){
                isInjective=false;
            }
            if(!isInjective){
                return isInjective;
            }
            isInjective = true;
        }
    }
    return isInjective;
}

/**
 * @brief Prints true if given relation R is injective on sets A and B
 * 
 * @param r Pointer to relation R
 * @param a Pointer to set A (Codomain)
 * @param b Pointer to set B (Domain)
 */
int injective(set_t *r, set_t *a, set_t *b){
    if (r == NULL || a == NULL || b == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R || !(a->type == S || a->type == U) || !(b->type == S || b->type == U)){
        err("Invalid command\n");
        return -1;
    }

    if(!functionCheck(r)){
        printf("false\n");
        return 0;
    }

    if(injectiveCheck(r,a,b)){
        printf("true\n");
        return 1;
    }
    else{
    printf("False\n");
    return 0;
    }
}

/**
 * @brief Checks whether given relation R is surjective on sets A and B
 * 
 * @param r Pointer to relation R
 * @param a Pointer to set A (Codomain)
 * @param b Pointer to set B (Domain)
 * @return true Given relation is surjective
 * @return false Given relation is not surjective
 */
bool surjectiveCheck(set_t *r, set_t *a, set_t *b){
    
    if(r->size!= a->size){
        return false;
    }
    bool isSurjective=false;

    for(int i = 0; i < b->size; i++){
        for (int j = 0; j < r->size/2; j++){
            if(!strcmp(b->set[i].word, relGetRight(r,j)->word)){
                isSurjective = true;
            }
        }
        if(!isSurjective){
            return false;
        }
        isSurjective=false;
    }
    return true;
}

/**
 * @brief Prints true if given relation R is surjective on sets A and B
 * 
 * @param r Pointer to relation R
 * @param a Pointer to set A (Codomain)
 * @param b Pointer to set B (Domain)
 */
int surjective(set_t *r, set_t *a, set_t *b){
    if (r == NULL || a == NULL || b == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R || !(a->type == S || a->type == U) || !(b->type == S || b->type == U)){
        err("Invalid command\n");
        return -1;
    }

    if(!functionCheck(r)){
        printf("false\n");
        return 0;
    }

    if(surjectiveCheck(r,a,b)){
        printf("true\n");
        return 1;
    }
    else{
    printf("False\n");
    return 0;
    }
}

/**
 * @brief Prints true if given relation R is bijective on sets A and B
 * 
 * @param r Pointer to relation R
 * @param a Pointer to set A (Codomain)
 * @param b Pointer to set B (Domain)
 */
int bijective(set_t *r, set_t *a, set_t *b){
    if (r == NULL || a == NULL || b == NULL){
        err("Set undefined\n");
        return -1;
    }
    if(r->type != R || !(a->type == S || a->type == U) || !(b->type == S || b->type == U)){
        err("Invalid command\n");
        return -1;
    }

    if(!functionCheck(r)){
        printf("false\n");
        return 0;
    }

    if(injectiveCheck(r,a,b) && surjectiveCheck(r,a,b)){
        printf("true\n");
        return 1;
    }
    else{
    printf("false\n");
    return 0;
    }
}

int getIndex(set_t **data, int lineCount, int i){
    return strtol(data[lineCount]->set[i].word,NULL,10)-1;
}

/**
 * @brief Decides which command function to execute
 * 
 * @param data Dynamically allocated array of pointers to set_t where input is stored
 * @param lineCount Line on which given command is located
 */
int callOperation(set_t **data,int lineCount){
    char *word = data[lineCount]->set[0].word;
    
    if(!strcmp(word,"empty")){
        if(data[lineCount]->size!=2){
            err("invalid argument of command empty");
            return -1;
        }
        int setLine = getIndex(data,lineCount,1);
        empty(data[setLine]);
    }
    else if(!strcmp("card",word)){
        if(data[lineCount]->size!=2){
            err("invalid argument of command card\n");
            return -1;
        }
        long setLine = getIndex(data,lineCount,1);
        card(data[setLine]);
    }
    else if(!strcmp("complement",word)){
        if(data[lineCount]->size!=2){
            err("invalid argument of command complement\n");
            return -1;
        }
        long setLine = getIndex(data,lineCount,1);
        
        complement(data[setLine], data[0]);
    }
    else if(!strcmp("union",word)){
         if(data[lineCount]->size != 3){
             err("invalid argument of command union\n");
             return -1;
         }
         long setLine1 = getIndex(data,lineCount,1);
         long setLine2 = getIndex(data,lineCount,2);
         union_set(data[setLine1],data[setLine2]);
    }
    else if(!strcmp("intersect",word)){
         if(data[lineCount]->size != 3){
             err("invalid argument of command intersect\n");
             return -1;
         }
         long setLine1 = getIndex(data,lineCount,1);
         long setLine2 = getIndex(data,lineCount,2);
         intersect(data[setLine1],data[setLine2]);
    }
    else if(!strcmp("minus",word)){
        if(data[lineCount]->size != 3){
             err("invalid argument of command minus\n");
             return -1;
         }
         long setLine1 = getIndex(data,lineCount,1);
         long setLine2 = getIndex(data,lineCount,2);
         minus(data[setLine1],data[setLine2]);
    }
    else if(!strcmp("subseteq",word)){
     	if(data[lineCount]->size != 3){
             err("invalid argument of command subseteq\n");
             return -1;
         }
         long setLine1 = getIndex(data,lineCount,1);
         long setLine2 = getIndex(data,lineCount,2);
         subseteq(data[setLine1],data[setLine2]);
    }
    else if(!strcmp("subset",word)){
     	if(data[lineCount]->size != 3){
             err("invalid argument of command subset\n");
             return -1;
         }
         long setLine1 = getIndex(data,lineCount,1);
         long setLine2 = getIndex(data,lineCount,2);
         subset(data[setLine1],data[setLine2]);
    }
    else if(!strcmp("equals",word)){
        if(data[lineCount]->size != 3){
             err("invalid argument of command equals\n");
             return -1;
        }
        long setLine1 = getIndex(data,lineCount,1);
        long setLine2 = getIndex(data,lineCount,2);
        equals(data[setLine1],data[setLine2]);
    }
    else if(!strcmp("reflexive",word)){
        if(data[lineCount]->size!=2){
            err("invalid argument of command reflexive");
            return -1;
        }
        int setLine = getIndex(data,lineCount,1);
        reflexive(data[setLine], data[0]);
    }
    else if(!strcmp("symmetric",word)){
     	if(data[lineCount]->size!=2){
            err("invalid argument of command symmetric");
            return -1;
        }
        int setLine = getIndex(data,lineCount,1);
        symmetric(data[setLine]);
    }
    else if(!strcmp("antisymmetric",word)){
        if(data[lineCount]->size!=2){
            err("invalid argument of command antisymmetric");
            return -1;
        }
        int setLine = getIndex(data,lineCount,1);
        antisymmetric(data[setLine]);
    }
    else if(!strcmp("transitive",word)){
        if(data[lineCount]->size!=2){
            err("invalid argument of command transitive");
            return -1;
        }
        int setLine = getIndex(data,lineCount,1);
        transitive(data[setLine]);
    }
    else if(!strcmp("function",word)){
        if(data[lineCount]->size!=2){
            err("invalid argument of command function");
            return -1;
        }
        int setLine = getIndex(data,lineCount,1);
        function(data[setLine]);
    }
    else if(!strcmp("domain",word)){
        if(data[lineCount]->size != 2){
             err("invalid argument of command domain\n");
             return -1;
        }
        long setLine1 = getIndex(data,lineCount,1);
        domain(data[setLine1]);
    }
    else if(!strcmp("codomain",word)){
        if(data[lineCount]->size != 2){
             err("invalid argument of command codomain\n");
             return -1;
        }
        long setLine1 = getIndex(data,lineCount,1);
        codomain(data[setLine1]);
    }
    else if(!strcmp("injective",word)){
        if(data[lineCount]->size != 4){
             err("invalid argument of command injective\n");
             return -1;
        }
        long setLine1 = getIndex(data,lineCount,1);
        long setLine2 = getIndex(data,lineCount,2);
        long setLine3 = getIndex(data,lineCount,3);
        injective(data[setLine1], data[setLine2], data[setLine3]);
    }
 
    else if(!strcmp("surjective",word)){
        if(data[lineCount]->size != 4){
             err("invalid argument of command surjective\n");
             return -1;
        }
        long setLine1 = getIndex(data,lineCount,1);
        long setLine2 = getIndex(data,lineCount,2);
        long setLine3 = getIndex(data,lineCount,3);
        surjective(data[setLine1], data[setLine2], data[setLine3]);
    }
    else if(!strcmp("bijective",word)){
        if(data[lineCount]->size != 4){
             err("invalid argument of command bijective\n");
             return -1;
        }
        long setLine1 = getIndex(data,lineCount,1);
        long setLine2 = getIndex(data,lineCount,2);
        long setLine3 = getIndex(data,lineCount,3);
        bijective(data[setLine1], data[setLine2], data[setLine3]);
    }
    else{
        err("Command not found!\n");
    }
    return 0;
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

int subsetElements2(set_t *s1){   
    for(int i = 0;i < s1->size;i++){  
        for(int j = 0; j < FORBIDDEN_WORDS_COUNT;j++){
            if(!strcmp(s1->set[i].word,ForbiddenWords[j])){
                return -1;                                       
            }    
        }
    
    }
    
    return 1;
}

/**
 * @brief Checks whether all elements of set are in universe and whether the set is a Set
 * 
 * @param data Dynamically allocated array of pointers to set_t where input is stored
 * @param lineCount Line on which given set is located
 * @return int Value 0(false) - check failed and and error message was printed. Value 1(true) - check successful
 */
int checkElements(set_t **data, int lineCount){
    if(!subseteqCheck(data[lineCount], data[0])){
       err("Set element not defined in universe!\n");
       return -1; 
    }
    if(data[lineCount]->type!=R){
        if(!isSet(*(data[lineCount]))){
            err("Invalid set!\n");
            return -1;      
        }
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
    bool isC = false;
    //bool isUniversum = false;
    set_t *setTmp;
    while((c = fgetc(file)) != EOF){
        //printf("%c",c);
        if(isC == true && c != 'C'){

            err("Set declaration after commands\n");
            return -1; //TODO
        }
        if(c != 'U' && *lineCount == 0){
            err("Universe not defined!\n");
            return -1;
        }
        if(c == 'U' && *lineCount == 0){
            
            //Struct Universe is being created
            if(fgetc(file) == ' '){
                setTmp = ctor(U);
                if(allocLine(file,setTmp) == -1){
                    return -1;
                }
                
                //UN-SUCCESSFUL PASS FORBIDDEN_WORDS INTO UNIVERSE CHECK
		if(setTmp->type!=C){	
                    if((subsetElements2(setTmp)) == -1){    
                        err("Commands or keywords used in universe!\n");
                        return -1;
                    }
                 }
            }
            else{
                err("Universe not defined\n");
                return -1;
            }    
        }
        if(c == 'U' && *lineCount != 0){

            err("Multiple universe definition!\n");
            return -1;
        }

        if(c == 'S'){
            
            //Struct is being created
            if(fgetc(file) == ' '){
                setTmp = ctor(S);
                if(allocLine(file,setTmp) == -1){
                    return -1;
                }
                
            } 
                 
        }
        if(c == 'R'){
            
            //Struct is relation being created
            if(fgetc(file) == ' '){
                setTmp = ctor(R);
                if(allocLine(file,setTmp) == -1){
                    return -1;
                }
            } 
                 
                 
        }
        if(c == 'C'){
            isC = true;

            if(fgetc(file) == ' '){
                setTmp = ctor(C);
                if(allocLine(file,setTmp) == -1){
                    return -1;
                }
            }
                
                //Commands
               /*printf("Command read\n");
               (*lineCount)++;
               return 0;*/
                 
        }

          
        
        data[*lineCount] = setTmp;
       //setTmp=NULL;
        if(setTmp->type != C){
            if(checkElements(data,*lineCount) == -1){
                return -1;
            }
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
        return -1;   
    }


    FILE *input;
    if((input = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,">File '%s' could not be opened\n",argv[1]);
        return -1;
    } 
    set_t **data = (set_t **)malloc(sizeof(set_t*)*MAX_LINES);
    if(data == NULL){
        errAlloc();
    }
    int i = 0;
    int count = 0;
    int err_code = parse(input,data,&i); //NACTENI DAT A INICIALIZACE KODOVEHO HLASENI
    if(err_code == -1){

        while(count < i){
        
            dtor(data[count]);
            count++;  
        }

        free(data);
        fclose(input);
        return -1;
    }
    
    while(count < i){
        if((data[count]->type) != C){
            
            printSet((data[count]));
        }
        else{
            if(callOperation(data,count) == -1){
                return -1;
            }
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