#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 31

struct parametri{
    char *filename;
    int k;
};

struct node{
    char string[LEN];
    struct node* next;
    struct node* prev;
};



struct parametri readInput(int argc,char *argv[]){
    struct parametri params;

    if(argc != 3){
        printf("errore");
        exit(-1);
    }

    params.filename = argv[1];
    params.k = atoi(argv[2]);

    if(strstr(params.filename,".txt") == NULL){
        printf("errore");
        exit(-1);
    }

    if(params.k < 7 || params.k > 13){
        printf("errore");
        exit(-1);
    }
    return params;
}

void insertWord(struct node **head,char *string){
   struct node* nuovo = (struct node*)calloc(1,sizeof(struct node));

   strcpy(nuovo->string,string);
   nuovo->next = NULL;
   nuovo->prev == NULL;

   if(*head == NULL){
    *head = nuovo;
    return;
   }

   struct node* current = *head;
   struct node* p = NULL;

   while(current != NULL && strcmp(string,current->string) > 0){
    p = current;
    current = current->next;
   }

   if(p == NULL){
        nuovo->next = *head;
        (*head)->prev = nuovo;
        *head = nuovo;
   }
   else{
    p->next = nuovo;
    nuovo->prev = p;
    nuovo->next = current;
        if(current != NULL){
            current->prev = nuovo;
        }
    }
}

void  buildList(struct node **head,char *filename){
    FILE *fp = fopen(filename,"r");

    if(fp == NULL){
        printf("errore nell'apertura del file");
        exit(-1);
    }

    char parola[LEN];
    while(fscanf(fp,"%s",parola) != EOF){
        insertWord(head,parola);
    }
    fclose(fp);
}

void printList(struct node *head){
    struct node* current = head;

    while(current != NULL){
        printf("%s \n",current->string);
        current = current->next;
    }
}

int  elab(struct node *head,int k){
    struct node* current = head;
    int count = 0;
    while(current != NULL){
        if(strlen(current->string) >= k){
            count++;
        }
        current = current->next;
    }
    return count;
}

int main(int argc,char *argv[]){
    struct parametri params = readInput(argc,argv);
    struct node *head = NULL;
    buildList(&head,params.filename);
    printList(head);
    int n = elab(head,params.k);
    printf("il numero di stringhe che ha una lunghezza maggiore o uguale a k sono: %d",n);
}