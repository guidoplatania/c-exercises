#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//STRUTTURA DEI PARAMETRI
struct parametri {
    int N;
    char a;
    char b;
};
//STRUTTURA DEL NODO
struct node{
    char data;
    struct node* next;
};
//STRUTTURA DELLO STACK
struct stack{
    struct node* top;
};
unsigned int get_random() {
static unsigned int m_w = 123456;
static unsigned int m_z = 789123;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}
//CONTROLLO DEI PARAMETRI
struct parametri readInput(int argc,char *argv[]){
    struct parametri params;
    if(argc!=4){
        printf("Errore: Devi inserire esattamente 4 parametri");
        exit(1);
    }

    params.N = atoi(argv[1]);
    params.a = argv[2][0];
    params.b = argv[3][0];

    if(params.N < 5 || params.N > 10){
        printf("Errore: N deve essere compreso tra 5,10");
        exit(1);
    }

    if(params.a < 'a' || params.a > 'z'){
        printf("Errore: a deve essere compresa tra 'a,'z' ");
    }
    if(params.b < 'a' || params.b > 'z'){
        printf("Errore: b deve essere compresa tra 'a,'z' ");
    }
    
return params;

}
//FUNZIONE PER LA STAMPA DI UN CARATTERE VOCALE CASUALE
char genVowel(){
    char v;
    int ciclo = 0;
    do{
    v = get_random()%('z'-'a')+'a';

    if(v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u'){
        ciclo = 1;
        
    }

    }while(ciclo != 1);
    return v;
}
//FUNZIONE PER LA STAMPA DI UN CARATTERE CONSONANTE CASUALE
char genConsonant (){
    char c;
    int ciclo = 0;
    do{
    c = get_random()%('z'-'a')+'a';

    if(c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u'){
        ciclo = 1;
        
    }

    }while(ciclo != 1);
    return c;
}
//CREAZIONE DELLO STACK
struct stack* createStack(){
    struct stack* Stack = (struct stack *)malloc(sizeof(struct stack));
    Stack->top = NULL;
    return Stack;
}
//PUSH PER L'INSERIMENTO
void push(struct stack* Stack,char newData){
    struct node* nuovo = (struct node *)malloc(sizeof(struct node));
    if(nuovo == NULL){
        printf("errore");
        exit(1);
    }

    nuovo->data=newData;
    nuovo->next=Stack->top;
    Stack->top=nuovo;
   
    
}
//FUNZIONE PER RIEMPIRE LO STACK
void fillStack(struct stack* Stack,struct parametri params){
    
    char x;
    for(int i=0;i<params.N;i++){
         x = get_random()%('9'-'1')+'1';

        if(x >= '1' && x <= '4'){
            for(char i='1';i<=x;i++){
                char c = genVowel();
                if(c == params.a){
                    c = '*';
                }
                else if(c == params.b){
                    c = '?';
                }
                push(Stack,c);
            }
                push(Stack,x);
        }

        else{ //if(x >= '5' && x <= '9')
            for(char i='1';i<=x;i++){
                char c = genConsonant();
                if(c == params.a){
                    c = '*';
                }
                else if(c == params.b){
                    c = '?';
                }
                push(Stack,c);
            }
                push(Stack,x);
        }
    }

}
//FUNZOINE PER STAMPARE LO STACK
void printStack(struct stack* Stack){
    struct node* current = Stack->top;
    printf(" ** TOP->");
    while(current != NULL){
        printf("%c ",current->data);
        current = current->next;
    }
    printf("<- BOTTOM **");

}











int main(int argc,char *argv[]){
    
    struct parametri params = readInput(argc,argv);
    struct stack* Stack = createStack();
    fillStack(Stack,params);
    printStack(Stack);
}
