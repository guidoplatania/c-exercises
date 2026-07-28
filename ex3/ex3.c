#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 31

struct parametri{
    char *filename;
    double f;
};

struct node{
    double V;
    char string[LEN];
    struct node* next;
    struct node* prev;
};

struct parametri readInput(int argc,char *argv[]){
    struct parametri params;

    if(argc != 3){
        printf("errore -1");
        exit(-1);
    }

    params.filename = argv[1];
    params.f = atof(argv[2]);

    if(strstr(params.filename,".txt") == NULL){
        printf("errore -2");
        exit(-1);
    }

    if(params.f < 1.0 || params.f > 20.0){
        printf("errore -3");
        exit(-1);
    }
    return params;
}

void insertRecord(struct node **head,char *string,double V){
    struct node* nuovo = (struct node*)malloc(sizeof(struct node));
    // copio la stringa e il numero double,e imposto prev e next a NULL;
    nuovo->V = V;
    strcpy(nuovo->string,string);
    nuovo->prev = NULL;
    nuovo->next = NULL;
    
    //se la lista è vuota,il nuovo nodo diventa la testa
    if(*head == NULL){
        *head = nuovo;
        return;
    }
    //definizione di due puntatori temporanei,current punta a head
    struct node *current = *head;
    struct node *p = NULL;
    //questo ciclo attraversa la lista,fino a quando non trova una stringa
    //maggiore da quella da inserire
    while(current != NULL && strcmp(string,current->string) > 0){
        p = current;
        current = current->next;
    }
        //se il nodo deve essere inserito all'inizio della lista,
        //quel nodo diventa la testa
        if(p == NULL){
            nuovo->next = *head;
            (*head)->prev = nuovo;
            *head = nuovo;
        }
        //altrimenti il nuovo nodo viene inserito tra p e current;
        else {
            p->next = nuovo;
            nuovo->prev = p;
            nuovo->next = current;
            if(current != NULL){
                current->prev = nuovo;
            }
        }
    }


void buildList(struct node **head,char *filename,double V){
    FILE *fp = fopen(filename,"r");

    if(fp == NULL){
        printf("errore nell'apertura del file");
        exit(-1);
    }
    char parola[LEN];
    
    while(fscanf(fp, "%s %lf", parola, &V) != EOF){
        insertRecord(head,parola,V);
    }
    fclose(fp);
}

void printList(struct node *head){
    struct node *current = head;
    while(current != NULL){
        printf("%s %lf \n",current->string,current->V);
        current = current->next;
    }
}








int main(int argc,char *argv[]){
    struct parametri params = readInput(argc,argv);
    struct node* head = NULL;
    buildList(&head,params.filename,params.f);
    printList(head);
}
