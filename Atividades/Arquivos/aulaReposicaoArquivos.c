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


FILE* prepararArquivo(char nomeArq[]) {
    FILE* arq;
    arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
        arq = fopen(nomeArq, "w+b");
    }
    return arq;
}

void cadastrarAluno (FILE* arq) {
    // Solicita os dados de um aluno e grava no final do arquivo
    // OBS: Todo novo registro é gravado no arquivo com status igual a 1 (ativo)
    TAluno al;
    int retorno, posicao;
    printf("Informe o RA do aluno: ");
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
        } else {
            printf("Erro de gravação!\n"); 
        }
    }
}

 int buscar(FILE* arq, int ra){
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
    } while(!feof(arq)); // enquanto nao for o fim do arquivo

    return -1;
}

/* void exibirTodos (FILE* arq) {
    // Em desenvolvimento: Exibe os dados de todos os alunos cadastrados no arquivo
}

void exibirAluno(FILE* arq, char ra[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, exibe os dados.
    // Se não encontrar, informa que o aluno não pertence a turma.
} */

void alterarMedia(FILE* arq, char ra[]) {
    // Busca no arquivo um aluno com o RA dado. Se encontrar, altera a média.
    // Se não encontrar, informa que o aluno não pertence a turma.
    TAluno al;
    int retorno, posicao;
    printf("Informe o RA do aluno: ");
    scanf("%s",al.ra);
    
    posicao = buscar(arq,al.ra);
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
            printf("Alteração realizada com sucesso!\n");
            } else {
                printf("Erro de gravação.\n");
            }
        } else {
            printf("Erro de leitura!\n");
        }
    }
}

/* void alterarFaltas(FILE* arq, char ra[]) {
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
} */

void exibirOpcoes() {
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir alunos cadastrados \n");
    printf("3 - Exibir os dados de um aluno \n");
    printf("4 - Alterar a média de um aluno \n");
    printf("5 - Alterar a quantidade de faltas de um aluno \n");
    printf("6 - Remover um aluno do cadastro \n");
    printf("0 - Encerrar o programa \n");
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
            case 1: cadastrarAluno(turma);
                break;
            case 2: //exibirTodos(turma);
                break;
            case 3: printf("Informe o RA do aluno: ");
                scanf("%s",ra);
                fflush(stdin);
                //exibirAluno(turma, ra);
                break;
            case 4: printf("Informe o RA do aluno: ");
                scanf("%s",ra);
                fflush(stdin);
                //alterarMedia(turma, ra);
                break;
            case 5: printf("Informe o RA do aluno: ");
                scanf("%s",ra);
                fflush(stdin);
                //alterarFaltas(turma, ra);
                break;
            case 6: printf("Informe o RA do aluno: ");
                scanf("%s",ra);
                fflush(stdin);
                //removerAluno(turma, ra);
                break; 
            case 0: //limparArquivo(turma); */
                break;
            default: printf("Opção inválida \n");
            }
        } while (op != 0);
    }
    return 0;
}
