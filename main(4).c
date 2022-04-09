#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// variável global
char nomeArquivo[20] = "agenda.txt";

struct Pessoa{
    char nome[20];
    int telefone;
};

// prototipação
void menu();
FILE *abrirArquivo(char modo, char *caminho);
void fecharArquivo(FILE *arquivo);
void inserirContato(struct Pessoa umaPessoa);
void listarContato();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op;
    struct Pessoa umaPessoa;
    do{
    menu();
    scanf("%d", &op);

        switch(op) {
        case 1:
            system("cls");
            printf("Ação para inserir\n\n");
            printf("Digite um nome: ");
            scanf("%s", umaPessoa.nome);
            printf("Digite o telefone: ");
            scanf("%d", &umaPessoa.telefone);
            inserirContato(umaPessoa);
            system("pause");
            break;
        case 2:
            system("cls");
            listarContato();
            system("pause");
            break;
        case 3:;
            system("cls");
            printf("\nFinalizando o sistema...\n\n");
            system("pause");
            break;
        default:
            printf("\nOpcao invalida! digite novamente\n\n");
            system("pause");

    }
    }while(op !=3);
    return 0;
}

void menu(){


    puts("\n");
    printf("///////// Bem vindo ao sistema AGENDA ////////////\n");
    printf("/    /    /    /    /    /     /     /    /    / /\n");
    printf("/   /    /  Digite 1 para cadastrar /    /    /  /\n");
    printf("/  /    /   Digite 2 para listar   /    /    /   /\n");
    printf("/ /    /    Digite 3 para sair    /    /    /    /\n");
    printf("//    /    /    /    /    /      /    /    /     /\n");
    printf("//////////////////////////////////////////////////\n\n");
    printf("- ");
}

FILE *abrirArquivo(char modo, char *caminho){
    FILE *arquivo;

    switch (modo){
    case 'a':
        arquivo = fopen(caminho, "a");
        break;
    case 'r':
        arquivo = fopen(caminho, "rt");
        break;
    case 'w':
        arquivo = fopen(caminho, "wt");
        break;
    }
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(0);
    }

    return arquivo;
}

void fecharArquivo(FILE *arquivo){
    fclose(arquivo);
}

void inserirContato(struct Pessoa umaPessoa){
    FILE *arquivo;
    arquivo = abrirArquivo('a', nomeArquivo);
    fprintf(arquivo, "%s %d\n", umaPessoa.nome, umaPessoa.telefone);
    fecharArquivo(arquivo);
}
void listarContato()
{
    FILE *arquivo;
    struct Pessoa umaPessoa;
    int cont = 0;

    arquivo = abrirArquivo('r', nomeArquivo);
    printf("Listando os contatos\n");

    while(!feof(arquivo))
    {
        fscanf(arquivo, "%s %d ", umaPessoa.nome, &umaPessoa.telefone);
        printf("\nNome: %s - Telefone: %d\n\n", umaPessoa.nome, umaPessoa.telefone);
        cont++;
    }

    fecharArquivo(arquivo);
    printf("Total de registros: %d\n", cont);
}
