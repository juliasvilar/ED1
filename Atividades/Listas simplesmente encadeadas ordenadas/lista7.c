#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLSE {
    int info;
    struct NoLSE* prox;
} TNoLSE;

typedef struct LSE{
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
} PontLSE;

void inicializar(PontLSE* lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->qtd = 0;
}

int isfull(){
    return 0;
}

int isempty(PontLSE* lista) {
    if (lista->inicio == NULL){
        return 1;
    } else {
        return 0;
    }
}

void insercao(PontLSE* lista, int num){
    TNoLSE* aux = (TNoLSE*)malloc(sizeof(TNoLSE));
    lista->qtd += 1;
    aux->info = num;
    aux->prox = NULL;

    if(isempty(lista ) == TRUE){
        lista->inicio = aux;
        lista->fim = aux;
    } else {
        if(num < lista->inicio->info){
            aux->prox = lista->inicio;
            lista->inicio = aux;
        }
        if(num > lista->fim->info){
            lista->fim->prox = aux;
            lista->fim = aux;
        } else{
            TNoLSE* aux1;
            TNoLSE* aux2;
            aux1 = lista->inicio;
            aux2 = NULL;
            for(int i=0; i < lista->qtd; i++){
                if(aux1->info == num){
                    printf("Essa lista não aceita números repetidos!\n");
                    break;
                }
                if(aux1->info > num){
                    aux->prox = aux1;
                    aux2->prox = aux;
                    break;
                } else {
                    aux2 = aux1;
                    aux1 = aux1->prox;
                }
            }
        }
    }
    lista->qtd++;
}

int remocao(PontLSE* lista, int num){
    TNoLSE* aux1 = lista->inicio;
    TNoLSE* aux2 = NULL;
    int encontrado = TRUE;

    if(lista->inicio == lista->fim && lista->inicio->info != num){
        return TRUE;
    }

    for(int i = 0; i < lista->qtd; i++){
        if(aux1->info == num){
            encontrado = FALSE;
            break;
        }else{
            aux2 = aux1;
            aux1 = aux1->prox;
        }
    }
    if(encontrado == TRUE){
        return TRUE;
    } else {
        if(lista->inicio == lista->fim){
            lista->inicio = NULL;
            lista->fim = NULL;
        } else {
            if(aux2 == NULL){
                lista->inicio = aux1->prox;
                aux2 = aux1->prox;
            }
            else{
                aux2->prox = aux1->prox;
                if(aux2->prox == NULL){
                    lista->fim = aux2;
                }
            }
        }
        free (aux1);
        return 0;
    }
    
}

void exibir(PontLSE* lista) {
    TNoLSE* aux = lista->inicio;
    printf("\n");
    while (aux != NULL) {
        printf("[%d] ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}



void exibirOpcoes(){
    printf("\nOpções: \n");
    printf("1 - Inserir valor\n");
    printf("2 - Remover valor\n");
    printf("3 - Exibir lista\n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main(){
    PontLSE listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("\nValor a inserir: ");
                scanf("%d", &num);
                if(isfull(listaInteiros) == FALSE){
                    insercao(&listaInteiros,num);
                }
                break;
            case 2:
                if(isempty(&listaInteiros) == TRUE){
                    printf("Fila vazia\n");
                }
                else{
                    int valor;
                    printf("\nValor a remover: ");
                    scanf("%d", &num);
                    printf("\n");
                    valor = remocao(&listaInteiros, num);
                    if(valor == 1){
                        printf("O valor %d não está na lista\n", num);
                    } else {
                        printf("Valor removido!\n");
                    }
                }
                break;
            case 3:
                if(isempty(&listaInteiros) == TRUE){
                    printf("Lista vazia!\n");
                }
                else{
                    exibir(&listaInteiros);
                }
                break;
            case 0: 
                printf("Fim de programa! \n");
                break;
            default: 
            printf("Opção inválida! \n");
        }
    } while (op != 0);

    return 0;

}
