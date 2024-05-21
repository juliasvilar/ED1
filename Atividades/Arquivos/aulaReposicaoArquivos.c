// Aula de reposição - 21-05-2024
// Exercício de revisão de manipulação de arquivos binários

#include <stdio.h>

typedef struct Aluno {
    char ra[12];
    char nome[100];
    float media;
    int faltas;
    int status;
} TAluno;

void exibirOpcoes() {
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir alunos cadastrados \n");
    printf("3 - Exibir os dados de um aluno \n");
    printf("4 - Alterar a média de um aluno \n");
    printf("5 - Alterar a quantidade de faltas de um aluno \n");
    printf("6 - Remover um aluno do cadastro \n");
    printf("0 - Encerrar o programa \n");
}

FILE* prepararArquivo(char nomeArq[]) {
    FILE* arq;
    arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
        arq = fopen(nomeArq, "w+b");
    }
    return arq;
}

void cadastrarAluno (FILE* arq) {
    // Em desenvolvimento: Solicita os dados de um aluno e grava no final do arquivo
    // OBS: Todo novo registro é gravado no arquivo com status igual a 1 (ativo)
}

void exibirTodos (FILE* arq) {
    // Em desenvolvimento: Exibe os dados de todos os alunos cadastrados no arquivo
}

void exibirAluno(FILE* arq, char ra[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, exibe os dados.
    // Se não encontrar, informa que o aluno não pertence a turma.
}

void alterarMedia(FILE* arq, char ra[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, altera a média.
    // Se não encontrar, informa que o aluno não pertence a turma.
}

void alterarFaltas(FILE* arq, char ra[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, altera as faltas.
    // Se não encontrar, informa que o aluno não pertence a turma.
}

void removerAluno(FILE* arq, char ra[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. 
    // Se encontrar, remove logicamente o aluno, seja, altera o status para 0 (deletado).
    // Se não encontrar, informa que o aluno não pertence a turma.
}

void limparArquivo(FILE* arq) {
    // Em desenvolvimento: remove fisicamente do arquivo os registros de status 0.
}

int main() {
    FILE* turma;
    char nomeFile[100] = "d:/prog1.dat";
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
            case 1: cadastrarAluno(turma);
                break;
            case 2: exibirTodos(turma);
                break;
            case 3: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                exibirAluno(turma, ra);
                break;
            case 4: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                alterarMedia(turma, ra);
                break;
            case 5: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                alterarFaltas(turma, ra);
                break;
            case 6: printf("Informe o RA do aluno: ");
                gets_s(ra); fflush(stdin);
                removerAluno(turma, ra);
                break;
            case 0: limparArquivo(turma);
                break;
            default: printf("Opção inválida \n");
            }
        } while (op != 0);
    }
    return 0;
}
