
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 31
#define MAX_STRING_LENGTH 31
#define MAX_QUEUE_SIZE 100

struct parametri{
    char *fileName;
};
struct node{
    char *string;
    struct node* next;
};
struct queue{
    struct node* front;
    struct node* rear;
};
struct parametri readInput(int argc,char *argv[]){
    struct parametri params;
    if(argc != 2){
        fprintf(stderr,"errore 0");
        exit(EXIT_FAILURE);
    }
    params.fileName = argv[1];

    return params;

}

struct queue* CreateQueue(){
    struct queue* Queue = (struct queue*)calloc(1,sizeof(struct queue));
    return Queue;
}

void enqueueWord(struct queue* Queue,char *string ){
    struct node* nuovo = (struct node*)calloc(1,sizeof(struct node));

    strcpy(nuovo->string,string);

    if(nuovo == NULL){
        fprintf(stderr,"errore -1");
        exit(EXIT_FAILURE);
    }

    Queue->rear->next = nuovo;
    Queue->rear = nuovo;
    

    if(Queue->front == NULL && Queue->rear == NULL){
        Queue->front = Queue->rear = nuovo;
    }

    Queue->rear->next = nuovo;
    Queue->rear = nuovo;
}

char* dequeueWord(struct queue* Queue){

    struct node* temp;
    temp = Queue->front;

    if(Queue->front == NULL && Queue->rear == NULL){
        fprintf(stderr,"la coda è vuota");
        return NULL;
    }
    char *stringa =(char *)calloc(LEN,sizeof(char));
    strcpy(stringa,Queue->front->string);

    Queue->front = temp->next;
    free(temp);
    
    return stringa;
}

void buildQueue(struct queue* Queue,char *fileName){
    FILE *fp =fopen(fileName,"r");
    if(fp == NULL){
        fprintf(stderr,"errore nell'apertura del file   ");
        exit(EXIT_FAILURE);
    }
    
    int sandro = 1;
    

    while(sandro){
        char parola[LEN];
        if(fscanf(fp,"%s",parola) != 1){
            if(feof(fp)){
                sandro = 0;
            }
            else {
                fprintf(stderr,"errore");
                exit(EXIT_FAILURE);
            }
        }
        else{
            enqueueWord(Queue,parola);
        }
        fclose(fp);
    }
}



char** buildStringArray(struct queue* Queue, int *size) {
    *size = (Queue->rear - Queue->front + MAX_QUEUE_SIZE + 1) % MAX_QUEUE_SIZE;
    char** stringArray = (char**)malloc(*size * sizeof(char*));

    for (int i = 0; i < *size; i++) {
        char* word = dequeueWord(Queue);
        printf("%s\n", word);
        stringArray[i] = word;
    }

    return stringArray;
}

void printArray(char **stringArray, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", stringArray[i]);
    }
}




int main(int argc,char *argv[]){
struct parametri params = readInput(argc,argv);
struct queue* Queue = CreateQueue();

int size;
char **stringArray = buildStringArray(Queue, &size);
printArray(stringArray, size);








}
