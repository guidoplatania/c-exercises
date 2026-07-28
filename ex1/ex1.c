
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 31

struct parametri{
    char *fileName;
    int k;
};

struct node{
    char stringa[LEN];
    struct node* next;
};
struct stack{
    struct node* top;
};


struct parametri readInput(int argc,char *argv[]){
    struct parametri params;
    if(argc != 3){
       fprintf(stderr,"errore -1");
       exit(EXIT_FAILURE);
    }

    params.fileName = argv[1];
    params.k = atoi(argv[2]);

    if(params.k < 5 || params.k >15){
        fprintf(stderr,"errore -2");
       exit(EXIT_FAILURE);
    }

    return params;
    
}

struct stack* createStack(){
    struct stack* Stack = (struct stack*)calloc(1,sizeof(struct stack));
    return Stack;
}

void pushWord(struct stack* Stack,char* str){
    struct node* nuovo = (struct node*)calloc(1,sizeof(struct node));

    if(nuovo == NULL){
        fprintf(stderr,"errore -3");
        exit(EXIT_FAILURE);
    }
    strcpy(nuovo->stringa,str);

    nuovo->next = Stack->top;
    Stack->top = nuovo;
    
}

char* popWord(struct stack* Stack){
    if(Stack == NULL || Stack->top == NULL){
        fprintf(stderr,"errore -4");
        exit(EXIT_FAILURE);
    }

    struct node* temp = Stack->top;
    Stack->top = temp->next;
    char* popped = strdup(temp->stringa); // Copia la stringa prima di liberare il nodo
    free(temp);
    return popped;
}
   


void buildStack(struct stack* Stack,char *fileName){
    char* string =(char *)calloc(LEN,sizeof(char));
    FILE *file = fopen(fileName,"r");
    if (file == NULL) {
        fprintf(stderr, "errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(file,"%s",string) != EOF){
        
        pushWord(Stack,string);
    }
    fclose(file);
}

void sortWord(char *string){
    for(int i = 1;i<strlen(string);i++){
        for(int j=0;j<strlen(string)-1;j++){
            if(string[j]>string[j+1]){
            char temp = string[j];
            string[j] = string[j+1];
            string[j+1] = temp;
            }
            
        }
    }
    
}

void printStack(struct stack* Stack,int k){
    
     
    while(Stack->top != NULL){
        char *pop = popWord(Stack);

        if(strlen(pop)>= k){
            sortWord(pop);
        }
        printf("%s \n ",pop);
        free(pop);
    }
}





int main(int argc,char *argv[]){
struct parametri params = readInput(argc,argv);
struct stack* Stack = createStack();
buildStack(Stack,params.fileName);
printStack(Stack,params.k);


}
