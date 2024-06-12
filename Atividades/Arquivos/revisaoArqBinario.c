// Aula de reposição - 21-05-2024
// Exercício de revisão de manipulação de arquivos binários

#include <stdio.h>
#include <string.h>

typedef struct Aluno {
    char ra[12];
    char nome[100];
    float media;
    int faltas;
    int status;
} TAluno;

int qtd = 0;


FILE* prepararArquivo(char nomeArq[]) {
    FILE* arq;
    arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
        arq = fopen(nomeArq, "w+b");
    }
    return arq;
}

int buscar(FILE* arq, char ra[12]){
    int cont = -1;
    int retorno;
    TAluno al;
    fseek(arq, 0, SEEK_SET);

    do{
        retorno = fread(&al,sizeof(TAluno),1,arq);
        if (retorno == 1){
            cont++;
            if(al.status == 1){
                if(strcmp(ra,al.ra) == 0){
                    return cont;
                }
            }
        }
    } while(!feof(arq));

    return -1;
}

void cadastrarAluno (FILE* arq) {
    TAluno al;
    int retorno, posicao;
    printf("\nInforme o RA do aluno: ");
    scanf("%s",al.ra);

    
    posicao = buscar(arq,al.ra);
    if (posicao != -1){
        printf("Aluno já cadastrado.\n");

    } else {
        printf("Informe o nome do aluno: ");
        scanf("%s",al.nome);
        printf("Informe a media do aluno: ");
        scanf("%f",&al.media);
        printf("Informe a quantidade de faltas do aluno: ");
        scanf("%d",&al.faltas);
        al.status = 1;
        fseek(arq, 0, SEEK_END);
        retorno = fwrite(&al,sizeof(TAluno),1,arq);
        if (retorno == 1){
            fflush(arq);
            printf("Aluno cadastrado com sucesso!\n");
            qtd++;
        } else {
            printf("Erro de gravação!\n"); 
        }
    }
}


void exibirTodos(FILE* arq){
    TAluno al;
    fseek(arq, 0, SEEK_SET);
    printf("\nAlunos cadastrados:\n");
    while (fread(&al, sizeof(TAluno), 1, arq)) {
        if (al.status == 1) {
            printf("RA: %s\nNome: %s\nMédia: %.2f\nFaltas: %d\n", al.ra, al.nome, al.media, al.faltas);
        }
        printf("\n");
    }
}

void exibirAluno(FILE* arq, char ra[]){
    TAluno al;
    int posicao = buscar(arq, ra);
    if (posicao == -1) {
        printf("Aluno não cadastrado na turma\n");
    } else {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET);
        fread(&al, sizeof(TAluno), 1, arq);
        printf("RA: %s\nNome: %s\nMédia: %.1f\nFaltas: %d\n", al.ra, al.nome, al.media, al.faltas);
    }
}

void alterarMedia(FILE* arq, char ra[]) {
    TAluno al;
    int retorno, posicao;
    
    posicao = buscar(arq,ra);
    if (posicao == -1){
        printf("Aluno não cadastrado na turma\n");
    } else {
        fseek(arq,posicao*sizeof(TAluno),SEEK_SET);
        retorno = fread(&al,sizeof(TAluno),1,arq);
        if(retorno == 1){
            printf("Informe a nova media: ");
            scanf("%f",&al.media);
            fseek(arq,-sizeof(TAluno),SEEK_CUR);
            retorno = fwrite(&al,sizeof(TAluno),1,arq);
            if(retorno == 1){
                fflush(arq);
                printf("Media alterada com sucesso!\n");
            } else {
                printf("Erro de gravação.\n");
            }
        } else {
            printf("Erro de leitura!\n");
        }
    }
}

void alterarFaltas(FILE* arq, char ra[]) {
    TAluno al;
    int retorno, posicao;

    posicao = buscar(arq, ra);
    if (posicao == -1) {
        printf("Aluno não cadastrado na turma\n");
    } else {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET);
        retorno = fread(&al, sizeof(TAluno), 1, arq);
        if (retorno == 1) {
            printf("Informe a nova quantidade de faltas: ");
            scanf("%d", &al.faltas);
            fseek(arq, -sizeof(TAluno), SEEK_CUR);
            retorno = fwrite(&al, sizeof(TAluno), 1, arq);
            if (retorno == 1) {
                fflush(arq);
                printf("Faltas alteradas com sucesso!\n");
            } else {
                printf("Erro de gravação.\n");
            }
        } else {
            printf("Erro de leitura!\n");
        }
    }
}

void removerAluno(FILE* arq, char ra[]) {
    TAluno al;
    int retorno, posicao;

    posicao = buscar(arq, ra);
    if (posicao == -1) {
        printf("Aluno não cadastrado na turma\n");
    } else {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET);
        retorno = fread(&al, sizeof(TAluno), 1, arq);
        if (retorno == 1) {
            al.status = 0;
            fseek(arq, -sizeof(TAluno), SEEK_CUR);
            retorno = fwrite(&al, sizeof(TAluno), 1, arq);
            if (retorno == 1) {
                fflush(arq);
                printf("Aluno removido com sucesso!\n");
                qtd--;
            } else {
                printf("Erro de gravação.\n");
            }
        } else {
            printf("Erro de leitura!\n");
        }
    }
}

void limparArquivo(FILE* arq) {
    FILE* temp;
    TAluno al;
    temp = fopen("temp.bin", "w+b");
    fseek(arq, 0, SEEK_SET);
    while (fread(&al, sizeof(TAluno), 1, arq)) {
        if (al.status == 1) {
            fwrite(&al, sizeof(TAluno), 1, temp);
        }
    }
    fclose(arq);
    fclose(temp);
    remove("C:/aulaReposicaoFILE");
    rename("temp.bin", "C:/aulaReposicaoFILE");
    arq = prepararArquivo("C:/aulaReposicaoFILE");
}

void exibirOpcoes() {
    printf("\nOpcoes:\n");
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir alunos cadastrados \n");
    printf("3 - Exibir os dados de um aluno \n");
    printf("4 - Alterar a média de um aluno \n");
    printf("5 - Alterar a quantidade de faltas de um aluno \n");
    printf("6 - Remover um aluno do cadastro \n");
    printf("0 - Encerrar o programa \n");
    printf("Escolha: ");
}

int main() {
    FILE* turma;
    char nomeFile[100] = "C:/aulaReposicaoFILE";
    char ra [12];
    int op;
    turma = prepararArquivo (nomeFile);
    if (turma == NULL) {
        printf("Erro ao tentar criar/abrir o arquivo \n");
    }
    else { 
        do {
            exibirOpcoes();
            scanf("%d", &op); fflush(stdin);
            switch (op) {
            case 1: 
                cadastrarAluno(turma);
                break;
            case 2:
                if (qtd == 0){
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    exibirTodos(turma);
                }
                break;
            case 3:
                if (qtd == 0){
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    printf("\nInforme o RA do aluno: ");
                    scanf("%s",ra);
                    fflush(stdin);
                    exibirAluno(turma, ra);
                }
                break;
            case 4: 
                if (qtd == 0){
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    printf("\nInforme o RA do aluno: ");
                    scanf("%s",ra);
                    fflush(stdin);
                    alterarMedia(turma, ra);
                }
                break;
            case 5:
                if (qtd == 0){
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    printf("\nInforme o RA do aluno: ");
                    scanf("%s",ra);
                    fflush(stdin);
                    alterarFaltas(turma, ra);
                }
                break;
            case 6:
                if (qtd == 0){
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    printf("\nInforme o RA do aluno: ");
                    scanf("%s",ra);
                    fflush(stdin);
                    removerAluno(turma, ra);
                }
                break; 
            case 0:
                if (qtd == 0){
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    limparArquivo(turma);
                }
                break;
            default: 
                printf("Opçao inválida \n");
            }
        } while (op != 0);
    }
    return 0;
}
