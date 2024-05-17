/* Considere uma lista simplesmente encadeada circular de numeros inteiros, ordenada, em ordem crescente, e com valores repetidos.
implemente uma função para remover um valor da lista. A função retorna a quantidade de copias do valor que foram removidas. */

// lista duplamente encadeada circular ordenada de forma crescente sem repetidos

// exercício passado na aula do dia 14/05/2024

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLSE{
    int info;
    struct NoLSE* prox;
} TNoLSE;

typedef struct LSE{
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
} PontLSE; 

void inicializar(PontLSE* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(PontLSE* lista){
    if (lista->qtd == 0){
        return TRUE;
    } else {
        return FALSE;
    }
}

void exibir(PontLSE* lista){
    TNoLSE* aux = lista->inicio;
    if(isEmpty(lista) == TRUE){
        printf("\nLista vazia.");
    } else {
        printf("\n[%d] ",aux->info);
        aux = aux->prox;
        while(aux != lista->inicio){
            printf("[%d] ",aux->info);
            aux = aux->prox;
        }
    }
    printf("\n");
}

void inserir(PontLSE* lista, int num){
    if (isEmpty(lista) == TRUE){ // lista vazia
        TNoLSE* novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        novo->info = num;
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = NULL;
        lista->qtd++;
        printf("\nValor inserido.\n");
    } else { // nao vazia
        if (lista->inicio->info > num || lista->inicio->info == num){ // inserir no inicio
            TNoLSE* novo = (TNoLSE*)malloc(sizeof(TNoLSE));
            novo->info = num;
            novo->prox = lista->inicio;
            lista->inicio = novo;
            lista->fim->prox = novo;
            lista->qtd++;
            printf("\nValor inserido.\n");

        } else if (lista->fim->info < num || lista->inicio->info == num){  // inserir no final
            TNoLSE* novo = (TNoLSE*)malloc(sizeof(TNoLSE));
            novo->info = num;
            novo->prox = lista->inicio;
            lista->fim->prox = novo;
            lista->fim = novo;
            lista->qtd++;
            printf("\nValor inserido.\n");

        } else { // inserir no meio
            TNoLSE* novo = (TNoLSE*)malloc(sizeof(TNoLSE));
            TNoLSE* anterior = lista->inicio;
            TNoLSE* atual = anterior->prox;
            while(1){
                if (atual->info > num || atual->info == num){
                    novo->info = num;
                    anterior->prox = novo;
                    novo->prox = atual;
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

int remover(PontLSE* lista, int valor){
    if(isEmpty(lista) == TRUE){
        return 0;
    } else {
        int cont = 0;
        if(lista->inicio->info == valor){
            while(isEmpty(lista) == FALSE && lista->inicio->info == valor){
                lista->fim->prox = lista->inicio->prox;
                lista->qtd--;
                free(lista->inicio);
                lista->inicio = lista->fim->prox;
                cont++;
            }
        } else {
            TNoLSE* anterior, *atual;
            anterior = lista->inicio;
            atual = anterior->prox;
            while(atual != lista->inicio || atual->info > valor){
                if(atual->info == valor){
                    atual->prox = atual->prox;
                    free(atual);
                    lista->qtd--;
                    cont++;
                }
            }
        }
        return cont;
    }
}

void exibirOpcoes(){
    printf("\nOpcoes:\n");
    printf("1 - Inserir valor\n");
    printf("2 - Exibir lista\n");
    printf("3 - Remover valores repetidos\n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opcao desejada: ");
}

int main(){
    PontLSE listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch (op){
        case 1:
            printf("Informe o valor a ser inserido: ");
            scanf("%d",&num);
            inserir(&listaInteiros, num);
            break;
        case 2:
            exibir(&listaInteiros);
            break;
        case 3:
            printf("Informe o valor a ser removido: ");
            scanf("%d",&num);
            int qtd = remover(&listaInteiros,num);
            printf("\nForam removidos %d valores %d.\n",qtd,num);
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
