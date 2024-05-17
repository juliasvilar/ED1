/* Considere uma lista duplamente encadeada de números inteiros.
A lista não está ordenada e não possui valores repetidos.
Implemente um procedimento para remover um dado valor da lista.
Este procedimento recebe como parâmetro a lista de onde o valor será removido e o valor a ser removido. */

// ecercício passado na aula do dia 16/04/2024

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct noLDE {
    struct noLDE* ant;
    int info;
    struct noLDE* prox;
} TNoLDE;

typedef struct lde {
    TNoLDE* inicio;
    TNoLDE* fim;
    int qtd;
} LDE;

void inicializar(LDE* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LDE lista){
    if (lista.qtd == 0){
        return TRUE;
    } else {
        return FALSE;
    }
}

TNoLDE* buscar(LDE* lista, int valor){ ////////////////////////////////////////// to fazendo aqui
    TNoLDE* aux;

    if(isEmpty(*lista) == TRUE) {
        return NULL; // lista vazia
    } else {
        if(lista->inicio->info == valor){
            return lista->inicio;
        } else if (lista->fim->info == valor){
            return lista->fim;
        } else {
            aux = lista->inicio->prox;
            while (aux != NULL){ // podia ser NULL mas botamos lista->fim pra ele nao comparar com o fim dnv
                if (aux->info == valor){
                    return aux; // achou
                } else {
                    aux = aux->prox;
                }
            }
            return NULL; // nao achou
        
        }
    }
}

void inserirInicio(LDE* lista){
    TNoLDE* novo;
    TNoLDE* retorno;
    int valor;
    
    if (isEmpty(*lista) == TRUE){
        novo = (TNoLDE*)malloc(sizeof(TNoLDE));
        printf("\nValor novo : ");
        scanf("%d",&valor);
        novo->info = valor;
        novo->ant =  NULL;
        novo->prox = NULL;
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd++;
        printf("Valor inserido!\n");
    } else {
        printf("Valor novo: ");
        scanf("%d",&valor);
        retorno = buscar(lista, valor);
        if (retorno == NULL) {
            novo = (TNoLDE*)malloc(sizeof(TNoLDE));
            novo->info = valor;
            novo->ant = NULL;
            novo->prox = lista->inicio;
            lista->inicio->ant = novo;
            lista->inicio = novo;
            lista->qtd++;
            printf("Valor inserido!\n");
        } else {
            printf("Valor repetido.\n");
        }
    }
}

void exibir(LDE lista) {
    TNoLDE* aux;
    if (isEmpty(lista) == TRUE) {
        printf("Lista vazia\n");
    }
    else {
        aux = lista.inicio;
        while (aux != NULL) {
            printf("%d ", aux->info);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void exibirInversa(LDE* lista){ 
    TNoLDE* aux = lista->fim;
    while(aux != NULL){
        printf("%d\n",aux->info);
        aux = aux->ant;
    }
    return;
}

void remover(LDE* lista){
    TNoLDE* retorno;
    int valor;
    TNoLDE* atual;

    printf("Qual valor deseja remover? ");
    scanf("%d",&valor);

    retorno = buscar(lista, valor);

    if (retorno == NULL){  // vazia
        printf("Valor não encontrado na lista.\n");

    } else if (retorno == lista->inicio){   // inicio
        atual = lista->inicio;
        lista->inicio = atual->prox;
        lista->inicio->ant = NULL;
        lista->qtd--;
        free(atual);
        printf("Valor removido.\n");
    
    } else if (retorno == lista->fim){  // final
        atual = lista->fim->ant;
        atual->prox = NULL;
        free(lista->fim);

    } else {  // meio
        atual = retorno->ant;
        atual->prox = retorno->prox;
        retorno->prox->ant = atual;
        free(retorno);
        printf("Valor removido.\n");
    }
    return;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Inserir valor no início da lista \n");
    printf("2 - Inserir valor no final da lista \n");
    printf("3 - Remover primeiro da lista \n");
    printf("4 - Remover último da lista \n");
    printf("5 - Exibir lista do início para o final \n");
    printf("6 - Exibir lista do final para o início \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main(){
    LDE listaD;
    inicializar(&listaD);
    int op;
    do {
        exibirOpcoes();
        scanf("%d",&op);
        switch(op){
            case 1:
                inserirInicio(&listaD);
                break;
            case 2:
                break;
            case 3:
                remover(&listaD);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                exibirInversa(&listaD);
                break;
            case 0:
                printf("Finalizando o programa...\n");
                break;
            default:
                printf("Opção inválida.");
        } 
    } while(op != 0);

    return 0;
}
