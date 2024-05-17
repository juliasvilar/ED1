/* lista simplesmente encadeada circular, nao ordenada, permite repetidos
questao com solicitacao apenas de implementacao dos metodos no exibirOpcoes */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLSEC{
    int info;
    struct NoLSEC* prox;
} TNoLSEC;

typedef struct LSEC{
    TNoLSEC* inicio;
    TNoLSEC* fim;
    int qtd;
} PontLSEC; 

void inicializar(PontLSEC* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(PontLSEC* lista){
    if (lista->qtd == 0){
        return TRUE;
    } else {
        return FALSE;
    }
}

void exibir(PontLSEC* lista){
    TNoLSEC* aux = lista->inicio;
    if(isEmpty(lista) == TRUE){
        printf("\nLista vazia.");
    } else {
        printf("\n");
        printf("[%d] ",aux->info);
        aux = aux->prox;
        while(aux != lista->inicio){
            printf("[%d] ",aux->info);
            aux = aux->prox;
        }
    }
    printf("\n");
}


void inserirInicio(PontLSEC* lista, int num){
    TNoLSEC* novo = (TNoLSEC*)malloc(sizeof(TNoLSEC));
    if(isEmpty(lista) ==  TRUE){ // lista vazia cria um so no
        novo->info = num;
        lista->inicio = novo;
        lista->fim = novo;
        lista->inicio->prox = lista->fim;
        lista->qtd++;
    } else { // lista nao vazia
        if(lista->qtd == 1){ // so tem um no
            novo->info = num;
            lista->inicio = novo;
            novo->prox = lista->fim;
            lista->fim->prox = novo;
            lista->qtd++;
        } else { // mais de um no
            novo->info = num;
            novo->prox = lista->inicio;
            lista->fim->prox = novo;
            lista->inicio = novo;
            lista->qtd++;
        }
    }
    printf("Valor inserido no inicio!\n");
}

void inserirFinal(PontLSEC* lista, int num){
    TNoLSEC* novo = (TNoLSEC*)malloc(sizeof(TNoLSEC));
    if(isEmpty(lista) ==  TRUE){ // lista vazia cria um so no
        novo->info = num;
        lista->inicio = novo;
        lista->fim = novo;
        lista->inicio->prox = lista->fim;
        lista->qtd++;
    } else { // lista nao vazia
        if(lista->qtd == 1){ // so tem um no
            novo->info = num;
            novo->prox = lista->inicio;
            lista->inicio->prox = novo;
            lista->fim = novo;
            lista->qtd++;
        } else { // mais de um no
            novo->info = num;
            lista->fim->prox = novo;
            novo->prox = lista->inicio;
            lista->fim = novo;
            lista->qtd++;
        }
    }
    printf("\nValor inserido no final!\n");
}

void removerPrimeiro(PontLSEC* lista){
    if(isEmpty(lista) == TRUE){
        printf("\nLista vazia!\n");
    } else {
        if(lista->qtd == 1){
            free(lista->inicio); // remove o unico no que existe
        } else {
            lista->inicio = lista->inicio->prox;
            free(lista->fim->prox);
            lista->fim->prox = lista->inicio;
        }
        printf("\nPrimeiro valor removido!\n");
    }
}

void removerUltimo(PontLSEC* lista){
    if(isEmpty(lista) == TRUE){
        printf("\nLista vazia!\n");
    } else {
        if(lista->qtd == 1){
            free(lista->inicio); // remove o unico no que existe
        } else {
            TNoLSEC* aux = lista->inicio;
            while (aux->prox != lista->fim){
                aux = aux->prox;
            }
            aux->prox = lista->inicio;
            free(lista->fim);
            lista->fim = aux;
        }
        printf("\nUltimo valor removido!\n");
    }
}


void exibirOpcoes(){
    printf("\nOpcoes:\n");
    printf("1 - Inserir o valor no inicio da lista\n");
    printf("2 - Inserir valor no final da lista\n");
    printf("3 - Remover primeiro da lista\n");
    printf("4 - Remover ultimo da lista\n");
    printf("5 - Exibir a lista\n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opcao desejada: ");
}

int main(){
    PontLSEC listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch (op){
        case 1:
            printf("\nInforme o valor a ser inserido: ");
            scanf("%d",&num);
            inserirInicio(&listaInteiros, num);
            break;
        case 2:
            printf("\nInforme o valor a ser inserido: ");
            scanf("%d",&num);
            inserirFinal(&listaInteiros, num);
            break;
        case 3: 
            removerPrimeiro(&listaInteiros);
            break;
        case 4:
            removerUltimo(&listaInteiros);
            break;
        case 5:
            exibir(&listaInteiros);
            break;
        case 0:
            printf("\nFim de programa!\n");
            break;
        default:
            printf("\nOpcao inválida!\n");
            break;
        }
    } while(op != 0);
    return 0;
}
