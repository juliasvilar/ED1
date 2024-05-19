/* listas duplamente encadeadas circulares com nome, média final e quantidade de faltas de duas turmas de alunos
ordenada alfabeticamente */

// finalizado!

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
        lista->fim = novo;
        novo->prox = novo;
        novo->ant = novo;
        lista->qtd = 1;
        printf("Cadastro vazio realizado!\n");

    } else { // nao vazia
        if (strcmp(lista->inicio->nome,nomeAux) == FALSE){ // igual ao primeiro
            printf("Nome já existente na lista.\n"); 
    
        } else if (strcmp(lista->fim->nome,nomeAux) == FALSE){ // igual ao ultimo
            printf("Nome ja existente na lista.\n"); 

        } else if (strcmp(lista->inicio->nome,nomeAux) > 0){ // inserir no inicio
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

        } else if (strcmp(nomeAux,lista->fim->nome) > 0){  // inserir no final
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
            printf("\nCadastro realizado!\n");

        } else { // procura o nome e insere no meio
            TNoLDEC* novo = (TNoLDEC*)malloc(sizeof(TNoLDEC));
            TNoLDEC* anterior = lista->fim;
            TNoLDEC* atual = lista->inicio;
            while(1){
                if (strcmp(atual->nome,nomeAux) == FALSE){ // achou igual
                    printf("Nome ja existente na lista.\n");
                    free(novo);
                    return;
                } else if (strcmp(atual->nome,nomeAux) > 0){
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
        printf("\nNome: %s\nMedia final: %.1f\nFaltas: %d\n",lista->inicio->nome,lista->inicio->media,lista->inicio->faltas);
    } else {
        printf("\nNome: %s\nMedia final: %.1f\nFaltas: %d\n",lista->inicio->nome,lista->inicio->media,lista->inicio->faltas);
        TNoLDEC* aux = lista->inicio->prox;
        while(aux != lista->inicio){
            printf("\nNome: %s\nMedia final: %.1f\nFaltas: %d\n",aux->nome,aux->media,aux->faltas);
            aux = aux->prox;
        }
    }
    return;
}

TNoLDEC* consultar(PontLDEC* lista, char nome[40]){
    TNoLDEC* atual = lista->inicio;
    do{
        if(strcmp(atual->nome,nome) == FALSE){
            return atual; // achou o nome, retorna endereço dele
        }
        atual = atual->prox;
    } while(atual != lista->inicio);

    return NULL; // não achou o nome, retorna NULL
}

void alterarMedia(PontLDEC* lista){
    printf("\nInsira o nome do aluno: ");
    char nome[40];
    scanf("%s",nome);
    TNoLDEC* aux = consultar(lista,nome);
    if(aux == NULL){
        printf("Aluno nao pertencente a turma.\n");
    } else {
        printf("Nova media: ");
        float mediaNova;
        scanf("%f",&mediaNova);
        while(mediaNova == aux->media){
            printf("Informe uma nova media diferente da atual: ");
            scanf("%f",&mediaNova);
        }
        aux->media = mediaNova;
        printf("Media alterada!\n");
    }
}

void alterarfaltas(PontLDEC* lista){
    printf("\nInsira o nome do aluno: ");
    char nome[40];
    scanf("%s",nome);
    TNoLDEC* aux = consultar(lista,nome);
    if(aux == NULL){
        printf("Aluno nao pertencente a turma.\n");
    } else {
        printf("Acrescentar (1) ou retirar (2) faltas? ");
        int resp;
        scanf("%d",&resp);
        while(resp != 1 && resp != 2){
            printf("Opcao invalida. Tente novamente: ");
            scanf("%d",&resp);
        }
        int faltasNovo;
        if (resp == 1){
            printf("Faltas a serem adicionadas: ");
            scanf("%d",&faltasNovo);
            aux->faltas = aux->faltas + faltasNovo;
        } else {
            printf("Faltas a serem retiradas: ");
            scanf("%d",&faltasNovo);
            while(faltasNovo > aux->faltas){
                printf("O numero de faltas nao pode estar negativo. Tente novamente: ");
                scanf("%d",&faltasNovo);
            }
            aux->faltas = aux->faltas - faltasNovo;
        }
        printf("Quantidade de faltas alterada!\n");
    }
}

void exibirAlunoEspecifico(PontLDEC* lista){
    printf("\nInsira o nome do aluno: ");
    char nome[40];
    scanf("%s",nome);
    TNoLDEC* aux = consultar(lista,nome);
    if(aux == NULL){
        printf("Aluno nao pertencente a turma.\n");
    } else {
        printf("\nNome: %s\nMedia final: %.1f\nFaltas: %d\n",aux->nome,aux->media,aux->faltas);
    }
}

void remover(PontLDEC* lista){
    printf("\nInsira o nome do aluno: ");
    char nome[40];
    scanf("%s",nome);
    TNoLDEC* aux = consultar(lista,nome);
    if(aux == NULL){
        printf("Aluno nao pertencente a turma.\n");
    } else {
        if(aux == lista->inicio){ // retira do inicio
            lista->inicio->prox->ant = lista->fim;
            lista->inicio = lista->inicio->prox;
            lista->fim->prox = lista->inicio;
            free(aux);
            lista->qtd--;
            printf("Aluno removido!\n");
        } else if (aux == lista->fim){
            lista->fim->ant->prox = lista->inicio;
            lista->fim = lista->fim->ant;
            lista->inicio->ant = lista->fim;
            lista->qtd--;
            printf("Aluno removido!\n");
        } else {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
            lista->qtd--;
            printf("Aluno removido!\n");
        }
    }
}

void limparTurma(PontLDEC* lista){
    TNoLDEC* aux = lista->inicio;
    while(lista->qtd != 0){
        lista->inicio->prox->ant = lista->fim;
        lista->inicio = lista->inicio->prox;
        lista->fim->prox = lista->inicio;
        free(aux);
        lista->qtd--;
        TNoLDEC* aux = lista->inicio;
        aux = aux->prox;
    }
    printf("\nCadastros limpos.\n");
}


void exibirOpcoes(){
    printf("\nOpcoes:\n");
    printf("1 - Cadastrar\n");
    printf("2 - Listar\n");
    printf("3 - Alterar media final\n");
    printf("4 - Alterar quantidade de faltas\n");
    printf("5 - Exibir dados de um aluno especifico\n");
    printf("6 - Remover um aluno\n");
    printf("7 - Limpar cadastro (todos)\n");
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
                        printf("\nTurma vazia.\n");
                    } else {
                        listar(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        listar(&listaDois);
                    }
                }
                break;
            case 3:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarMedia(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarMedia(&listaDois);
                    }
                }
                break;
            case 4:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarfaltas(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarfaltas(&listaDois);
                    }
                }
                break;
            case 5:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        exibirAlunoEspecifico(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        exibirAlunoEspecifico(&listaDois);
                    }
                }
                break;
            case 6:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        remover(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        remover(&listaDois);
                    }
                }
                break;
            case 7:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        limparTurma(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        limparTurma(&listaDois);
                    }
                }
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
        }

    } while (op != 0);
}
