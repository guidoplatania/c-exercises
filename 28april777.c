#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LEN 31

struct parametri{
    char *filename;
    char a;
    char b;
};

struct node{
    char string[LEN];
    struct node* next;
};

struct queue{
    struct node* front;
    struct node* rear;
};

struct parametri readInput(int argc,char *argv[]){
    struct parametri params;

    if(argc != 4){
        printf("errore -1");
        exit(-1);
    }

    params.filename = argv[1];
    params.a = argv[2][0];
    params.b = argv[3][0];

    if(strstr(params.filename,".txt") == NULL){
        printf("errore -2");
        exit(-1);
    }

    if(isupper(params.a) || isupper(params.b)){
        printf("errore -3");
        exit(-1);
    }

    if(params.a > params.b){
        printf("errore -4");
        exit(-1);
    }
    return params;
} 

struct queue* createQueue(){
    struct queue* Queue = (struct queue*)calloc(1,sizeof(struct queue));
    return Queue; 
}

void enqueue(struct queue* Queue, char *string){
    struct node* nuovo = (struct node*)calloc(1,sizeof(struct node));

    strcpy(nuovo->string,string);

    if(Queue->front == NULL && Queue->rear == NULL){
        Queue->front = Queue->rear = nuovo; 
    }

    (Queue->rear)->next = nuovo;
    Queue->rear = nuovo;
}

char *dequeue(struct queue* Queue){
    if(Queue->front == NULL){
        printf("la coda è vuota");
        return NULL;
    }

    char *string = (char*)calloc(LEN,sizeof(char));

    strcpy(string,Queue->front->string);

    struct node* temp = Queue->front;
    Queue->front = temp->next;
    free(temp);
    return string;
}

void buildQueue(struct queue* Queue,char *filename){
    FILE *fp = fopen(filename,"r");

    if(fp == NULL){
        printf("errore nell'apertura del file");
        exit(-1);
    }
    char parola[LEN];
    while(fscanf(fp,"%s",parola) != EOF){
        enqueue(Queue,parola);
    }
}

void elab(char *string,char a,char b,struct parametri params){
    for(int i = 0;i<strlen(string);i++){
        if(string[i] >= params.a && string[i] <= params.b){
            string[i] = '0';
        }
    }
}

void printQueue(struct queue* Queue,struct parametri params){
    while(Queue->front != NULL){
        char *deq = dequeue(Queue);
        elab(deq,params.a,params.b,params);
        printf("%s \n",deq);
    }
}

int main(int argc,char *argv[]){
    struct parametri params = readInput(argc,argv);
    struct queue* Queue = createQueue();

    buildQueue(Queue,params.filename);
    printQueue(Queue,params);
}