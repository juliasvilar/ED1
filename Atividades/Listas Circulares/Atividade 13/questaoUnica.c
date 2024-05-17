// código em desenvolvimento

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLDEC{
    char nome[40];
    float media;
    int faltas;
    struct NoLDEC* prox;
    struct NoLDEC* ant;
} TNoLDEC;

typedef struct LDEC{
    TNoLDEC* inicio;
    TNoLDEC* fim;
    int qtd;
} PontLDEC;

void inicializar (PontLDEC* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(PontLDEC* lista){
    if (lista->qtd == 0){ 
        return TRUE;
    } else {
        return FALSE;
    }
}




void cadastrar(PontLDEC* lista, char nomeAux[40]){
    float mediaAux;
    int faltasAux;

    if (isEmpty(lista)){ // vazia, inicio e fim = mesmo no de informacoes
        TNoLDEC* novo = (TNoLDEC*)malloc(sizeof(TNoLDEC));
        strcpy(novo->nome,nomeAux);
        printf("Media final: ");
        scanf("%f",&mediaAux);
        novo->media = mediaAux;
        printf("Faltas: ");
        scanf("%d",&faltasAux);
        novo->faltas = faltasAux;
        lista->inicio = novo;
        novo->prox = novo;
        lista->fim = novo;
        lista->qtd = 1;
        printf("Cadastro realizado!\n");

    } else { // nao vazia
        if (strcmp(lista->inicio->nome,nomeAux) == FALSE){ // igual ao primeiro
            printf("Nome já existente na lista.\n"); 
    
        } else if (strcmp(lista->fim->nome,nomeAux) == FALSE){ // igual ao ultimo
            printf("Nome ja existente na lista.\n"); 

        } else if (lista->inicio->nome > nomeAux){ // inserir no inicio
            TNoLDEC* novo = (TNoLDEC*)malloc(sizeof(TNoLDEC));
            novo->prox = lista->inicio;
            lista->inicio->ant = novo;
            lista->inicio = novo;
            novo->ant = lista->fim;
            strcpy(novo->nome,nomeAux);
            printf("Media final: ");
            scanf("%f",&mediaAux);
            novo->media = mediaAux;
            printf("Faltas: ");
            scanf("%d",&faltasAux);
            novo->faltas = faltasAux;
            lista->fim->prox = novo;
            lista->qtd++;
            printf("\nCadastro realizado!\n");

        } else if (lista->fim->nome < nomeAux){  // inserir no final
            TNoLDEC* novo = (TNoLDEC*)malloc(sizeof(TNoLDEC));
            strcpy(novo->nome,nomeAux);
            printf("Media final: ");
            scanf("%f",&mediaAux);
            novo->media = mediaAux;
            printf("Faltas: ");
            scanf("%d",&faltasAux);
            novo->faltas = faltasAux;
            novo->ant = lista->fim;
            novo->prox = lista->inicio;
            lista->fim->prox = novo;
            lista->fim = novo;
            lista->qtd++;
            printf("\nValor inserido.\n");

        } else { // procura o nome e insere no meio
            TNoLDEC* novo = (TNoLDEC*)malloc(sizeof(TNoLDEC));
            TNoLDEC* anterior = lista->fim;
            TNoLDEC* atual = lista->inicio;
            while(1){
                if (strcmp(atual->nome,nomeAux) == FALSE){ // achou igual
                    printf("Nome ja existente na lista.\n");
                    free(novo);
                    return;
                } else if (atual->nome > nomeAux){
                    strcpy(novo->nome,nomeAux);
                    printf("Media final: ");
                    scanf("%f",&mediaAux);
                    novo->media = mediaAux;
                    printf("Faltas: ");
                    scanf("%d",&faltasAux);
                    novo->faltas = faltasAux;
                    atual->ant = novo; 
                    novo->prox = atual;
                    anterior->prox = novo;
                    novo->ant = anterior;
                    lista->qtd++;
                    printf("\nCadastro realizado!\n");
                    break;
                } else {
                    atual = atual->prox;
                    anterior = anterior->prox;
                }
            }
        }
    }
}

void listar(PontLDEC* lista){
    if(lista->qtd == 1){
        printf("\nNome: %s\nMedia final: %f\nFaltas: %d\n",lista->inicio->nome,lista->inicio->media,lista->inicio->faltas);
    } else {
        printf("\nNome: %s\nMedia final: %f\nFaltas: %d\n",lista->inicio->nome,lista->inicio->media,lista->inicio->faltas);
        TNoLDEC* aux = lista->inicio->prox;
        while(aux != lista->inicio){
            printf("\nNome: %s\nMedia final: %f\nFaltas: %d\n",aux->nome,aux->media,aux->faltas);
            aux = aux->prox;
        }
    }
    return;
}


void exibirOpcoes(){
    printf("\nOpcoes:\n");
    printf("1 - Cadastrar\n");
    printf("2 - Listar\n");
    printf("3 - Consultar\n");
    printf("4 - Alterar media final\n");
    printf("5 - Alterar quantidade de faltas\n");
    printf("6 - Exibir dados de um aluno especifico\n");
    printf("7 - Remover um aluno\n");
    printf("8 - Limpar cadastro (todos)\n");
    printf("0 - Encerrar programa\n");
    printf("Escolha: ");
}


int main(){
    PontLDEC listaUm;
    PontLDEC listaDois;
    inicializar(&listaUm);
    inicializar(&listaDois);
    char nome[40];
    int op, turma;

    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("Em que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }
                
                if(turma == 1){
                    printf("\nNome: ");
                    scanf("%s",nome);
                    cadastrar(&listaUm,nome);
                } else {
                    printf("\nNome: ");
                    scanf("%s",nome);
                    cadastrar(&listaDois,nome);
                }
                
                break;
            case 2:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }
                
                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("Turma vazia.\n");
                    } else {
                        listar(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("Turma vazia.\n");
                    } else {
                        listar(&listaDois);
                    }
                }
                break;
            case 3:
                printf("\nEm desenvolvimento\n");
                break;
            case 4:
                printf("\nEm desenvolvimento\n");
                break;
            case 5:
                printf("\nEm desenvolvimento\n");
                break;
            case 6:
                printf("\nEm desenvolvimento\n");
                break;
            case 7:
                printf("\nEm desenvolvimento\n");
                break;
            case 8:
                printf("\nEm desenvolvimento\n");
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
        }

    } while (op != 0);


}
