#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLSE{
    char nome[30];
    char telefone[15];
    char email[50];
    struct NoLSE* prox;
} TNoLSE;

typedef struct Lse{
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
} PontLDEC;

void inicicializar(PontLDEC* lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(PontLDEC lista){
    if (lista.qtd == 0){ 
        return TRUE;
    } else {
        return FALSE;
    }
}

void adicionar(PontLDEC* lista, char nomeAux[50]){
    char telAux[15], emailAux[50];
    TNoLSE* novo, *atual, *anterior;

    if (isEmpty(*lista)){ // vazia, inicio e fim = mesmo no de informacoes
        novo = (TNoLSE*)malloc(sizeof(TNoLSE));
        strcpy(novo->nome,nomeAux);
        printf("Telefone: ");
        scanf("%s",telAux);
        strcpy(novo->telefone,telAux);
        printf("Email: ");
        scanf("%s",emailAux);
        strcpy(novo->email,emailAux);
        novo->prox = NULL;
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd = 1;
        printf("Contato adicionado!\n");

    } else { // nao vazia
        if (strcmp(lista->inicio->nome,nomeAux) == FALSE){ // igual ao primeiro
            printf("Nome já existente na lista.\n"); 
    
        } else if (strcmp(lista->fim->nome,nomeAux) == FALSE){ // igual oa ultimo
            printf("Nome já existente na lista.\n");   
        
        } else { // procura o nome
            anterior = lista->inicio;
            atual = anterior->prox;
            
            while(atual != NULL){
                if (strcmp(atual->nome,nomeAux) == FALSE){
                    printf("Nome já existente na lista.\n");
                    return;
                } else if(strcmp(atual->nome, nomeAux) > 0){
                    break;
                } 
                atual = atual->prox;
                anterior = anterior->prox;
            }

            novo = (TNoLSE*)malloc(sizeof(TNoLSE));
            strcpy(novo->nome,nomeAux);
            anterior->prox = novo;
            novo->prox = atual;
            printf("Telefone: ");
            scanf("%s",telAux);
            strcpy(novo->telefone,telAux);
            printf("Email: ");
            scanf("%s",emailAux);
            strcpy(novo->email,emailAux);
            lista->qtd++;
            printf("Contato adicionado!\n");
        }
    }
} 

void remover(PontLDEC* lista, char nomeAux[50]){
    TNoLSE *atual, *anterior;
    atual = lista->inicio;
    anterior = NULL;

    if (strcmp(lista->inicio->nome,nomeAux) == FALSE){ // igual ao primeiro
        atual = lista->inicio;
        lista->inicio = atual->prox;
        lista->qtd--;
        free(atual);
        printf("Contato removido!\n");
        return;
    
    } else if (strcmp(lista->fim->nome,nomeAux) == FALSE){ // igual oa ultimo
        anterior = NULL;
        atual = lista->fim;
        
        while(atual != NULL){
            anterior = atual;
            atual = atual->prox;
        }
        anterior->prox = NULL;
        lista->fim = anterior;
        free(atual);
        lista->qtd--;
        printf("Contato removido!");
        return;
    
    } else {  // busca o contato
        anterior = NULL;
        atual = lista->inicio;
        while (strcmp(atual->nome,nomeAux) != 0){
            anterior = atual;
            atual = atual->prox;
        }
        anterior->prox = atual->prox;
        free(atual);
        printf("Contato removido!");
        return;
    }
}

void procurar(PontLDEC* lista, char nomeAux[50]){
    TNoLSE *atual, *anterior;
    atual = lista->inicio;
    anterior = NULL;

    if (strcmp(lista->inicio->nome,nomeAux) == FALSE){ // igual ao primeiro
        printf("\nNome: %s\nTelefone: %s\nEmail: %s\n",lista->inicio->nome,lista->inicio->telefone,lista->inicio->email);
        return;
    
    } else if (strcmp(lista->fim->nome,nomeAux) == FALSE){ // igual oa ultimo
        printf("\nNome: %s\nTelefone: %s\nEmail: %s\n",lista->fim->nome,lista->fim->telefone,lista->fim->email);
        return;

    } else {
        anterior = lista->inicio;
        atual = anterior->prox;
        int achado = 0;

        while (atual != NULL){
            if (strcmp(atual->nome,nomeAux) == 0){
                achado = 1;
                break;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }

        if (achado == 0){
            printf("O nome procurado não está na lista.\n");
        } else {
            printf("\nNome: %s\nTelefone: %s\nEmail: %s\n",atual->nome,atual->telefone,atual->email);
            return;
        }
    }
}

void alterar(PontLDEC* lista, char nomeAux[50]){////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TNoLSE *atual;
    atual = lista->inicio;
    int escolha;

    if (strcmp(lista->inicio->nome,nomeAux) == FALSE){ // igual ao primeiro
        printf("\nO que deseja mudar?\n1 - Telefone\n2 - Email\nEscolha: ");
        scanf("%d",&escolha);
        do {
        switch (escolha) {
            case 1: // telefone
                printf("\nNovo telefone: ");
                char telNovo[50];
                scanf("%s",telNovo);
                strcpy(lista->inicio->telefone,telNovo);
                printf("Telefone alterado!\n");
                break;
            case 2: // email 
                printf("\nNovo email: ");
                char emailNovo[50];
                scanf("%s",emailNovo);
                strcpy(lista->inicio->email,emailNovo);
                printf("Email alterado!\n");
                break;
            default: 
                printf("\nOpção inválida!\n");
            } 
        } while (escolha != 1 && escolha != 2);
        return;
    } else if (strcmp(lista->fim->nome,nomeAux) == FALSE){ // igual oa ultimo
        printf("\nO que deseja mudar?\n1 - Telefone\n2 - Email\nEscolha: ");
        scanf("%d",&escolha);
        do {
        switch (escolha) {
            case 1: // telefone
                printf("\nNovo telefone: ");
                char telNovo[50];
                scanf("%s",telNovo);
                strcpy(lista->fim->telefone,telNovo);
                printf("Telefone alterado!\n");
                break;
            case 2: // email 
                printf("\nNovo email: ");
                char emailNovo[50];
                scanf("%s",emailNovo);
                strcpy(lista->fim->email,emailNovo);
                printf("Email alterado!\n");
                break;
            default: 
                printf("\nOpção inválida!\n");
            } 
        } while (escolha != 1 && escolha != 2);
        return;

    } else {
        atual = lista->inicio;
        int achado = 0;

        while (atual != NULL){
            if (strcmp(atual->nome,nomeAux) == 0){
                achado = 1;
                break;
            } else {
                atual = atual->prox;
            }
        }

        if (achado == 0){
            printf("Contato não existente.\n");
        } else {
            printf("\nO que deseja mudar?\n1 - Telefone\n2 - Email\nEscolha: ");
            scanf("%d",&escolha);
            do {
            switch (escolha) {
                case 1: // telefone
                    printf("\nNovo telefone: ");
                    char telNovo[50];
                    scanf("%s",telNovo);
                    strcpy(atual->telefone,telNovo);
                    printf("Telefone alterado!\n");
                    break;
                case 2: // email 
                    printf("\nNovo email: ");
                    char emailNovo[50];
                    scanf("%s",emailNovo);
                    strcpy(atual->email,emailNovo);
                    printf("Email alterado!\n");
                    break;
                default: 
                    printf("\nOpção inválida!\n");
                }
            } while (escolha != 1 && escolha != 2);
            return;
        }
    }
} //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exibirContatos(PontLDEC* lista){
    TNoLSE* aux = lista->inicio;
    while(aux != NULL){
        printf("\nNome: %s\nTelefone: %s\nEmail: %s\n",aux->nome,aux->telefone,aux->email);
        aux = aux->prox;
    }
    return;
}

void exibirOpcoes(){
    printf("\nOpções: \n");
    printf("1 - Adicionar novo contato\n");
    printf("2 - Remover contato\n");
    printf("3 - Exibir todos os contatos\n");
    printf("4 - Procurar um contato pelo nome\n");
    printf("5 - Alterar dados do contato\n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opção desejada: ");
}

int main(){
    PontLDEC listaOrdenada;
    inicicializar(&listaOrdenada);
    int op;
    char nome[50];

    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1: // adicionar
                printf("\nNome: ");
                scanf("%s",nome);
                adicionar(&listaOrdenada,nome);
                break;
            case 2: // remover 
                if (isEmpty(listaOrdenada) == TRUE){
                    printf("\nLista vazia.\n");
                } else {
                    printf("\nQue contato deseja remover? ");
                    scanf("%s",nome);
                    remover(&listaOrdenada,nome);
                }
                break;
            case 3: // exibir
                if (isEmpty(listaOrdenada) == TRUE){
                    printf("\nLista vazia.\n");
                } else {
                    exibirContatos(&listaOrdenada);
                }
                break;
            case 4: // procurar
                if (isEmpty(listaOrdenada) == TRUE){
                    printf("\nLista vazia.\n");
                } else {
                    printf("\nQue contato deseja procurar? ");
                    scanf("%s",nome);
                    procurar(&listaOrdenada, nome);
                }
                break;
            case 5: // alterar
                if (isEmpty(listaOrdenada) == TRUE){
                    printf("\nLista vazia.\n");
                } else {
                    printf("\nQue contato deseja alterar? ");
                    scanf("%s",nome);
                    alterar(&listaOrdenada, nome);
                }
                break;
            case 0:
                printf("\nFim de programa!\n");
                break;
            default: 
                printf("\nOpção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
