#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{

    int matricula;
    char nome[50];
    float nota[3];

} Aluno;

#define MAX_ALUNOS 40

int main()
{

    Aluno alunos[MAX_ALUNOS];
    int quantidade = 0, opt, matricula, matDelete;
    char enter;

    FILE *arquivo;

    for (int i = 0; i < MAX_ALUNOS; i++)
    {
        alunos[i].matricula = 0;
        strcpy(alunos[i].nome, "");
        for (int j = 0; j < 3; j++)
        {
            alunos[i].nota[j] = 0.0;
        }
    }

    arquivo = fopen("alunos.txt", "r");
    if (arquivo != NULL)
    {
        if (fscanf(arquivo, "%d", &quantidade) == 1)
        {
            for (int i = 0; i < quantidade; i++)
            {
                if (fscanf(arquivo, "%d %[^\n]", &alunos[i].matricula, alunos[i].nome) == 2)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        fscanf(arquivo, "%f", &alunos[i].nota[j]);
                    }
                }
            }
        }
        fclose(arquivo);
    }

    do
    {
        system("clear");
        printf("\n====================================\n");
        printf("1 - Adicionar aluno\n");
        printf("2 - Deletar aluno\n");
        printf("3 - Listar alunos\n");
        printf("0 - Sair\n");
        printf("Escolha:");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            if (quantidade >= MAX_ALUNOS)
            {
                printf("Contigente atingido.\n");
            }
            else
            {
                alunos[quantidade].matricula = quantidade + 1;
                printf("Matricula: %d\n", alunos[quantidade].matricula);
                printf("Nome: ");
                getchar();
                scanf("%[^\n]", alunos[quantidade].nome);
                for (int j = 0; j < 3; j++)
                {
                    do
                    {
                        printf("Nota %d: ", j + 1);
                        scanf("%f", &alunos[quantidade].nota[j]);
                        if (alunos[quantidade].nota[j] < 0 || alunos[quantidade].nota[j] > 10)
                        {
                            printf("Nota invalida.");
                        }
                    } while (alunos[quantidade].nota[j] < 0 || alunos[quantidade].nota[j] > 10);
                }
                quantidade++;
                printf("Aluno Adicionado com Sucesso!\n");
                break;

            case 2:
                printf("Qual a matricula do aluno a ser deletado? ");
                scanf("%d", &matricula);
                matDelete = 0;

                for (int i = 0; i < quantidade; i++)
                {
                    if (alunos[i].matricula == matricula)
                    {
                        for (int j = i; j < quantidade - 1; j++)
                        {
                            alunos[j] = alunos[j + 1];
                        }
                        quantidade--;
                        matDelete = 1;
                        printf("Aluno deletado com sucesso!\n");
                        break;
                    }
                }
                if (!matDelete)
                {
                    printf("Aluno não existente.\n");
                }
                break;

            case 3:
                if (quantidade == 0)
                {
                    printf("Nenhum aluno encontrado.\n");
                }
                else
                {
                    for (int i = 0; i < quantidade; i++)
                    {
                        printf("Matricula: %d\n", alunos[i].matricula);
                        printf("Nome: %s\n", alunos[i].nome);
                        for (int j = 0; j < 3; j++)
                        {
                            printf("Nota %d: %.2f\n", j + 1, alunos[i].nota[j]);
                        }
                    }
                }
                printf("Aperte ENTER para continuar...");
                getchar();
                scanf("%c", &enter);
                break;

            case 0:
                arquivo = fopen("alunos.txt", "w");
                if (arquivo != NULL)
                {
                    fprintf(arquivo, "%d\n", quantidade);
                    for (int i = 0; i < quantidade; i++)
                    {
                        fprintf(arquivo, "%d\n", alunos[i].matricula);
                        fprintf(arquivo, "%s\n", alunos[i].nome);
                        for (int j = 0; j < 3; j++)
                        {
                            fprintf(arquivo, "%.2f\n", alunos[i].nota[j]);
                        }
                    }
                    fclose(arquivo);
                }
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao Invalida\n");
                break;
            }
        }
    } while (opt != 0);

    return 0;
}
