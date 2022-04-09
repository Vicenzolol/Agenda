#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// variável global
char nomeArquivo[20] = "agenda.txt";

struct Pessoa
{
    int codigo;
    char nome[20];
    int telefone;
};

// prototipação
void menu();
FILE *abrirArquivo(char modo, char *caminho);
void fecharArquivo(FILE *arquivo);
void inserirContato(struct Pessoa umaPessoa);
void listarContato();
int ultimoCodigoInserido();
struct Pessoa pesquisarContatoPorCodigo();
struct Pessoa pesquisarContatoPorNome();
struct Pessoa pesquisarContatoPorNomeAprox();
struct Pessoa pesquisarContatoPorNomeMult();
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op,codigo;
    char nome[20];
    struct Pessoa umaPessoa;
    do
    {
        menu();
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            printf("Digite um nome: ");
            getchar();
            scanf("%[^\n]s", umaPessoa.nome);
            printf("Digite o telefone: ");
            scanf("%d", &umaPessoa.telefone);
            inserirContato(umaPessoa);
            system("pause");
            system("cls");
            break;
        case 2:
            listarContato();
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            printf("\n- ");
            scanf("%d", &umaPessoa.codigo);
            umaPessoa = pesquisarContatoPorCodigo(umaPessoa.codigo);
            if (umaPessoa.codigo != -1)
            {
                printf("\nCodigo: %d - Nome: %s - Telefone: %d \n\n", umaPessoa.codigo, umaPessoa.nome, umaPessoa.telefone);
            }
            else
            {
                printf("\nDesculpe, o codigo %d nao foi encontrado! \n\n");
            }
            system("pause");
            break;
        case 4:
            system("cls");
            printf("\nNome: ");
            getchar();
            scanf("%[^\n]s", nome);
            umaPessoa = pesquisarContatoPorNome(umaPessoa.nome);
            if (umaPessoa.codigo != -1)
            {
                printf("\nCodigo: %d - Nome: %s - Telefone: %d\n\n", umaPessoa.codigo, umaPessoa.nome, umaPessoa.telefone);
            }
            else
            {
                printf("\nDesculpe, o nome %d nao foi encontrado!\n\n");
            }
            system("pause");
            break;
        case 5:
            system("cls");
            printf("\nNome: ");
            getchar();
            {
                scanf("%[^\n]s", nome);
                umaPessoa = pesquisarContatoPorNomeAprox(nome);
                if (umaPessoa.codigo != -1)
                {
                    printf("\nCodigo: %d - Nome: %s - Telefone: %d\n\n", umaPessoa.codigo, umaPessoa.nome, umaPessoa.telefone);
                }
                else
                {
                    printf("\nDesculpe, o nome %d nao foi encontrado!\n\n");
                }
            }
            system("pause");
            break;
        case 6:
            system("cls");
            printf("\nNome: ");
            getchar();
            scanf("%[^\n]s", nome);
            pesquisarContatoPorNomeMult(nome);
            system("pause");
            break;
        case 0:
            system("cls");
            printf("\nFinalizando o sistema...\n\n");
            system("pause");
            break;
        default:
            printf("\nOpcao invalida! digite novamente\n\n");
            system("pause");

        }
    }
    while(op !=0);
    return 0;
}

void menu()
{
    puts("\n");
    printf("///////// Bem vindo ao sistema AGENDA ////////////\n");
    printf("/    /    /    /    /    /     /     /    /    / /\n");
    printf("/   /    /  Digite 1 para cadastrar /    /    /  /\n");
    printf("/  /    /   Digite 2 para listar   /    /    /   /\n");
    printf("/ /    /   /Digite 3 para procurar por codigo    /\n");
    printf("//    /   / Digite 4 para procurar por nome /    /\n");
    printf("/    /   /  Digite 5 para procurar por nome(~)   /\n");
    printf("/   /   /   Digite 6 para procurar por nome(-)   /\n");
    printf("/  /   /   /Digite 0 para sair/    /    /        /\n");
    printf("/ /   /   /   /    /    /    /    /    /         /\n");
    printf("//////////////////////////////////////////////////\n");
    printf("- ");
}

FILE *abrirArquivo(char modo, char *caminho)
{
    FILE *arquivo;

    switch (modo)
    {
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
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(0);
    }

    return arquivo;
}

void fecharArquivo(FILE *arquivo)
{
    fclose(arquivo);
}

void inserirContato(struct Pessoa umaPessoa)
{
    struct Pessoa pesquisarContatoPorNome();
    int codigo;
    FILE *arquivo;
    arquivo = abrirArquivo('a', nomeArquivo);
    codigo = ultimoCodigoInserido() + 1;
    fprintf(arquivo, "%d;%s;%d\n", codigo, umaPessoa.nome, umaPessoa.telefone);
    fecharArquivo(arquivo);
}
void listarContato()
{
    FILE *arquivo;
    struct Pessoa umaPessoa;
    int cont = 0;

    arquivo = abrirArquivo('r', nomeArquivo);
    printf("Listando os contatos:\n");

    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d", &umaPessoa.codigo);
        fscanf(arquivo, ";%[^;]s", umaPessoa.nome);
        fscanf(arquivo, ";%d ", &umaPessoa.telefone);

        printf("\nCodigo: %d - Nome: %s - Telefone: %d\n\n", umaPessoa.codigo, umaPessoa.nome, umaPessoa.telefone);
        cont++;
    }

    fecharArquivo(arquivo);
    printf("Total de registros: %d\n", cont);
}
int ultimoCodigoInserido()
{
    FILE *arquivo;
    struct Pessoa umaPessoa;
    int cont = 0;

    arquivo = abrirArquivo('r', nomeArquivo);

    fseek(arquivo,0,SEEK_END);
    if ((ftell(arquivo) -1) > 0)
    {
        fseek(arquivo,0, SEEK_SET);
        while(!feof(arquivo))
        {
            fscanf(arquivo, "%d", &umaPessoa.codigo);
            fscanf(arquivo, ";%[^;]s", umaPessoa.nome);
            fscanf(arquivo, ";%d ", &umaPessoa.telefone);
            cont = umaPessoa.codigo;
            struct Pessoa pesquisarContatoPorNome();
        }
    }
    fecharArquivo(arquivo);
    return cont;
}
struct Pessoa pesquisarContatoPorCodigo(int codigo)
{
    FILE *arquivo;
    struct Pessoa umaPessoa;

    arquivo = abrirArquivo('r', nomeArquivo);
    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d", &umaPessoa.codigo);
        fscanf(arquivo, ";%[^;]s", umaPessoa.nome);
        fscanf(arquivo, ";%d ", &umaPessoa.telefone);
        if (umaPessoa.codigo == codigo)
        {
            fecharArquivo(arquivo);
            return umaPessoa;
        }
    }
    fecharArquivo(arquivo);
    umaPessoa.codigo = -1;
    return umaPessoa;
};
struct Pessoa pesquisarContatoPorNome(char *nome)
{
    FILE *arquivo;
    struct Pessoa umaPessoa;
    arquivo = abrirArquivo('r', nomeArquivo);
    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d", &umaPessoa.codigo);
        fscanf(arquivo, ";%[^;]s", umaPessoa.nome);
        fscanf(arquivo, ";%d ", &umaPessoa.telefone);
        if (stricmp(umaPessoa.nome, nome) == 0)
        {
            fecharArquivo(arquivo);
            return umaPessoa;
        }
    }
    fecharArquivo(arquivo);
    umaPessoa.codigo = -1;
    return umaPessoa;
}
struct Pessoa pesquisarContatoPorNomeAprox(char *nome)
{
    FILE *arquivo;
    struct Pessoa umaPessoa;
    char nomeaux[20];

    arquivo = abrirArquivo('r', nomeArquivo);
        while(!feof(arquivo))
        {
            fscanf(arquivo, "%d", &umaPessoa.codigo);
            fscanf(arquivo, ";%[^;]s", umaPessoa.nome);
            fscanf(arquivo, ";%d ", &umaPessoa.telefone);
            strcpy(nomeaux, umaPessoa.nome);
            if (strstr(strlwr(nomeaux), strlwr (nome)) != NULL){
                fecharArquivo(arquivo);
                return umaPessoa;
            }
        }
    fecharArquivo(arquivo);
    umaPessoa.codigo = -1;
    return umaPessoa;
};
struct Pessoa pesquisarContatoPorNomeMult(char *nome)
{
    FILE *arquivo;
    struct Pessoa umaPessoa;
    int cont;
    arquivo = abrirArquivo('r', nomeArquivo);
    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d", &umaPessoa.codigo);
        fscanf(arquivo, ";%[^;]s", umaPessoa.nome);
        fscanf(arquivo, ";%d ", &umaPessoa.telefone);
        if (strstr(umaPessoa.nome, nome) == 0)
        {
            printf("\nCodigo: %d - Nome: %s - Telefone: %d\n\n", umaPessoa.codigo, umaPessoa.nome, umaPessoa.telefone);
            cont++;
        }
    }
    if (cont != 0)
    {
        printf("\nForam encontrados %d registros: \n", cont);
    }
    else
    {
        printf("\nNome %s não encontrado \n", nome);
    }
    fecharArquivo(arquivo);
}
