/* por algum motivo esse codigo nao funciona direito no meu vscode? sempre testar no compilador online
corretissimo!! */

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

void inserir(PontLDE* lista){
    int valor;
    printf("\nInsira o valor: ");
    scanf("%d",&valor);
    TNoLDE* novo = (TNoLDE*)malloc(sizeof(TNoLDE*));
    if(isEmpty(lista) == TRUE){ // lista vazia
        novo->num = valor;
        novo->prox = NULL;
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd = 1;

    } else if (valor < lista->inicio->num || valor == lista->inicio->num){ // inserir no inicio
        novo->prox = lista->inicio;
        lista->inicio->ant = novo;
        lista->inicio = novo;
        novo->ant = NULL;
        novo->num = valor;
        lista->qtd++;

    } else if (valor > lista->fim->num || valor == lista->fim->num){ // inserir no final
        lista->fim->prox = novo;
        novo->ant = lista->fim;
        lista->fim = novo;
        novo->prox = NULL;
        novo->num = valor;
        lista->qtd++;

    } else {  // adiciona depois de um menor ou depois de uma repeticao dele mesmo, antes do maior
        TNoLDE *atual = lista->inicio; 
        while(atual->num < valor || atual->num == valor){
            atual = atual->prox;
        }
        atual->ant->prox = novo;
        novo->ant = atual->ant;
        atual->ant = novo;
        novo->prox = atual;
        novo->num = valor;
        lista->qtd++;
        free(atual);
    }
    printf("Valor adicionado.\n");
}

void exibir(PontLDE* lista){
    TNoLDE* aux = lista->inicio;
    if (lista->qtd == 0){
        printf("\nLista vazia.\n");
    } else {
        printf("\n");
        while(aux != NULL){
            printf("[%d] ", aux->num);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void exibirOpcoes(){
    printf("\nOpções:\n");
    printf("1 - Inserir\n");
    printf("2 - Exibir lista\n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opção desejada: ");
}

int main(){
    PontLDE listaOrdenada;
    inicializar(&listaOrdenada);
    int op; 
    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            inserir(&listaOrdenada);
            break;
        case 2:
            exibir(&listaOrdenada);
            break;
        case 0:
            printf("\nEncerrando programa...\n");
            break;
        default:
                printf("\nOpção inválida.\n");
            break;
        }
    } while (op != 0);
}
