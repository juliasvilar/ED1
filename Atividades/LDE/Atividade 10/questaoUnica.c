#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLDE{
    int num;
    struct NoLDE* ant;
    struct NoLDE* prox;
} TNoLDE;

typedef struct LDE{
    TNoLDE* inicio;
    TNoLDE* fim;
    int qtd;
} PontLDE;

void inicializar(PontLDE* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(PontLDE* lista){
    if (lista->qtd == 0){
        return TRUE;
    } else {
        return FALSE;
    }
}

TNoLDE* busca(PontLDE* lista, int valor){
    if(isEmpty(lista) == TRUE){
        return NULL;
    } else {
        TNoLDE* aux = lista->inicio;
        while(aux != NULL){
            if (aux->num == valor){
                return aux;
            }
            aux = aux->prox;
        }
    }
    return NULL;
}

int buscarRepetido(PontLDE* lista, int valor){
    TNoLDE* aux = lista->inicio;
    while(aux != NULL){
        if(aux->num == valor){
            return TRUE; // achou
        } else {
            aux = aux->prox;
        }
    }
    return FALSE; // nao achou
}

void inserir(PontLDE* lista, int valor){
    if (lista->qtd == 0){ // lista vazia 
        TNoLDE* novo = (TNoLDE*)malloc(sizeof(TNoLDE));
        lista->inicio = novo;
        lista->fim = novo;
        novo->ant = NULL;
        novo->prox = NULL;
        novo->num = valor;
        lista->qtd = 1;
    } else if (lista->inicio->num > valor){ // insere no inicio
        TNoLDE* novo = (TNoLDE*)malloc(sizeof(TNoLDE));
        novo->num = valor;
        novo->ant = NULL;
        novo->prox = lista->inicio;
        lista->inicio->ant = novo;
        lista->inicio = novo;
        lista->qtd++;
    } else if (lista->fim->num < valor){ // insere no final
        TNoLDE* novo = (TNoLDE*)malloc(sizeof(TNoLDE));
        novo->num = valor;
        novo->ant = lista->fim;
        novo->prox = NULL;
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->qtd++;
    } else {
        TNoLDE* aux = lista->inicio;
        while(aux != NULL){
            if (buscarRepetido(lista,valor) == TRUE){
                printf("Valor repetido.\n");
                return;
            } else if (aux->num < valor){ // insere no meio
                TNoLDE* novo = (TNoLDE*)malloc(sizeof(TNoLDE));
                novo->ant = aux;
                novo->prox = aux->prox;
                aux->prox = novo;
                novo->prox->ant = novo;
                novo->num = valor;
                lista->qtd++;
                return;
            } else {
                aux = aux->prox;
            }
        }
    }
}


void intersecao(PontLDE* listaA, PontLDE* listaB, PontLDE* listaIntersecao){
    TNoLDE* auxA = listaA->inicio;
    while(auxA != NULL){
        if (buscarRepetido(listaB,auxA->num) == TRUE){
            inserir(listaIntersecao,auxA->num);
        }
        auxA = auxA->prox;
    }
}

void exibir(PontLDE* lista){
    if(lista->qtd == 0){
        printf("\nLista vazia.");
    } else {
        TNoLDE* aux = lista->inicio;
        printf("\n");
        while(aux != NULL){
            printf("[%d] ",aux->num);
            aux = aux->prox;
        }
    }
    printf("\n");
}

void diferenca(PontLDE* listaA, PontLDE* listaB, PontLDE* listaDiferenca){
    TNoLDE* aux = listaA->inicio;
    while(aux != NULL){
        if(!buscarRepetido(listaB, aux->num)){
            inserir(listaDiferenca, aux->num);
        }
        aux = aux->prox;
    }
}


void uniao (PontLDE* listaA, PontLDE* listaB, PontLDE* listaUniao){
    TNoLDE* aux = listaA->inicio;
    while (aux != NULL){
        inserir(listaUniao,aux->num);
        aux = aux->prox;
    }
    aux = listaB->inicio;
    while(aux != NULL){
        int valor = aux->num;
        if(buscarRepetido(listaUniao,valor) == FALSE && buscarRepetido(listaA, valor) == FALSE){
            inserir(listaUniao,valor);
        }
        aux = aux->prox;
    }
    
}

void exibirOpcoes(){
    printf("\nOpcoes:\n");
    printf("1 - Inserir na lista A\n"); // ok
    printf("2 - Inserir na lista B\n"); // ok
    printf("3 - Exibir lista de intersecao\n"); // ok
    printf("4 - Exibir lista de uniao\n"); // fazer
    printf("5 - Exibir lista de diferenca (estao na lista A mas nao na lista B)\n"); // ok
    printf("6 - Exibir lista A\n"); // ok
    printf("7 - Exibir lista B\n"); // ok
    printf("0 - Encerrar programa\n"); // ok
    printf("Opcao escolhida: ");
}


int main(){
    PontLDE listaA, listaB, listaIntersecao, listaUniao, listaDiferenca;
    inicializar(&listaA);
    inicializar(&listaB);
    inicializar(&listaIntersecao);
    inicializar(&listaUniao);
    inicializar(&listaDiferenca);
    int op, valor;

    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch (op){
            case 1:
                printf("\nValor a ser inserido: ");
                scanf("%d",&valor);
                inserir(&listaA,valor);
                break;
            case 2:
                printf("\nValor a ser inserido: ");
                scanf("%d",&valor);
                inserir(&listaB,valor);
                break;
            case 3:
                intersecao(&listaA,&listaB,&listaIntersecao);
                exibir(&listaIntersecao);
                break;
            case 4:
                uniao(&listaA,&listaB,&listaUniao);
                exibir(&listaUniao);
                break;
            case 5:
                diferenca(&listaA,&listaB,&listaDiferenca);
                exibir(&listaDiferenca);
                break;
            case 6:
                exibir(&listaA);
                break;
            case 7:
                exibir(&listaB);
                break;
            case 0:
                printf("\nEncerrando programa...\n\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (op != 0);
}
