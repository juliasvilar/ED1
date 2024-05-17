// corretissimo !!!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLDE{
    int num;
    struct NoLDE* prox;
    struct NoLDE* ant;
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

void inserir(PontLDE* lista){
    int valor;
    printf("\nQue valor você deseja inserir? ");
    scanf("%d",&valor);
    TNoLDE* novo = (TNoLDE*)malloc(sizeof(TNoLDE));

    if (isEmpty(lista) == TRUE){ // lista vazia
        lista->inicio = novo;
        lista->fim = novo;
        novo->num = valor;
        novo->ant = NULL;
        novo->prox = NULL;
        lista->qtd = 1;
    } else {
        if (lista->inicio->num < valor){ // inserir no inicio
            novo->prox = lista->inicio;
            lista->inicio->ant = novo;
            lista->inicio = novo;
            novo->ant = NULL;
            novo->num = valor;
            lista->qtd++;
            printf("\nValor inserido.\n");

        } else if (lista->fim->num > valor){  // inserir no final
            novo->ant = lista->fim;
            lista->fim->prox = novo;
            lista->fim = novo;
            novo->prox = NULL;
            novo->num = valor;
            lista->qtd++;
            printf("\nValor inserido.\n");

        } else if (valor == lista->inicio->num){ // se repetir o valor do PRIMEIRO
            printf("Valor repetido.\n");

        } else if (valor == lista->fim->num){ // se repetir o valor do ULTIMO
            printf("Valor repetido.\n");

        } else { // inserir no meio
            TNoLDE* anterior = lista->inicio;
            TNoLDE* atual = anterior->prox;
            while(1){
                if (atual->num == valor){
                    printf("Valor repetido.\n");
                    free(novo);
                    return;
                } else if (atual->num < valor){
                    anterior->prox = novo; // ok
                    atual->ant = novo;
                    novo->num = valor; // ok
                    novo->ant = anterior;
                    novo->prox = atual; // ok
                    lista->qtd++;
                    printf("\nValor inserido.\n");
                    break;
                } else {
                    atual = atual->prox;
                    anterior = anterior->prox;
                }
            }
        }
    }
}

TNoLDE* busca (PontLDE* lista, int valor){
    if(isEmpty(lista) == TRUE){
        return NULL;
    } else {
        TNoLDE* aux;
        aux = lista->inicio;
        while (aux != NULL){
            if(aux->num == valor){
                return aux;
            } 
            aux = aux->prox;
        }  
    }
    return NULL;
}

void remover(PontLDE* lista){
    printf("Que valor você deseja remover? ");
    int valor;
    scanf("%d",&valor);
    TNoLDE* aux = busca(lista, valor);

    if (aux == NULL){
        printf("Valor não encontrado.\n");
    } else {
        if (aux == lista->inicio && lista->qtd == 1){ // removendo o inicio e o fim ao msm tempo
            free(lista->inicio);
        } else if (aux == lista->inicio && lista->qtd != 1){ // remove o inicio
            lista->inicio = aux->prox;
            free(lista->inicio->ant);
            lista->inicio->ant = NULL;
            lista->qtd--;
        } else if (aux == lista->fim){ // remove o fim
            lista->fim = aux->ant;
            free(lista->fim->prox);
            lista->fim->prox = NULL;
            lista->qtd--;
        } else {
            aux->ant->prox = aux->prox;
            free(aux->prox->ant);
            aux->prox->ant = aux->ant;
            lista->qtd--;
        }
    }
    printf("\nValor removido.\n");
}

void exibir(PontLDE* lista){
    TNoLDE* aux = lista->inicio;
    if (lista->qtd == 0){
        printf("\nLista vazia.\n");
    } else {
        printf("\n");
        while (aux != NULL){
            printf("[%d] ",aux->num);
            aux = aux->prox;
        }
        printf("\n");
    }
}


void exibirOpcoes(){
    printf("\nOpções:\n");
    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Exibir\n");
    printf("0 - Encerrar programa\n");
    printf("Escolha: ");
}

int main(){
    PontLDE listaOrdenada;
    inicializar(&listaOrdenada);
    int op;
    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch(op){
            case 1:
                inserir(&listaOrdenada);
                break;
            case 2:
                remover(&listaOrdenada);
                break;
            case 3:
                exibir(&listaOrdenada);
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }   
    } while (op != 0);
}
