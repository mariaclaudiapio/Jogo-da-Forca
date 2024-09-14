#include <stdio.h>
#include <string.h> // para o uso da função strlen (que mede o tamanho do array)
#include <time.h> // para uso da função time
#include <stdlib.h> // para uso da função rand

#include "header.h"

void verificarExistênciaDoArquivo(FILE * f)
{
    if(f == 0)
    {
        puts("Falha ao abrir o arquivo");       
        exit(1);
    }
}

void escolherPalavra(char palavraSecreta[20])
{
    FILE* f;
    f = fopen("palavras.txt", "r"); // abre e lê o arquivo leitura

    verificarExistênciaDoArquivo(f);    

    int quantidadePalavras;
    fscanf(f, "%d", &quantidadePalavras); // lê o primeiro valor que está
                                         // na linha (número total de palavras)

    // escolhe uma palavra do arquivo de forma randômica
    srand(time(0));
    int randomico = rand() % quantidadePalavras;

    for(int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

void imprimirCabecalho(void)
{
    puts("***********************");
    puts("**   Jogo da Forca   **");
    puts("***********************");
}

/* Quando a letra chutada pelo usuário pertence à palavra secreta, a letra
é impressa na posição correspondente. Caso não pertença à palavra secreta,
é impresso o caractere _ */
void desenharForca(char palavraSecreta[20], char chutes[26], int chutesDados)
{
    for(int i = 0; i < strlen(palavraSecreta); i++)
        {
            int achou = jaChutou(palavraSecreta[i], chutes, chutesDados);

            if(achou)
            {
                printf("%c ", palavraSecreta[i]);
            }
            else
            {
                printf("_ ");            
            }
        }
        puts("\n");
}

// função que captura e armazena o chute do jogador
void guardarChute(char chutes[26], int* chutesDados)
{
    char chute; // variável para guardar o chute do jogador
    puts("Digite uma letra (em caixa alta, sem caracteres especiais):\n");
    scanf(" %c", &chute);

    chutes[(*chutesDados)] = chute;
    (*chutesDados)++;
}

// verifica se a letra capturada já foi chutada antes pelo usuário
int jaChutou(char letra, char chutes[26], int chutesDados)
{
    int achou = 0;
    for(int j = 0; j < chutesDados; j++)
    {
        if(chutes[j] ==  letra)
        {
            achou = 1;
            break;
        }
    }
    return achou;        
}

int acertou(char palavraSecreta[20], char chutes[26], int chutesDados)
{
    for(int i = 0; i < strlen(palavraSecreta); i++)
    {
        if(!jaChutou(palavraSecreta[i], chutes, chutesDados))
        {
            return 0;
        }
    }
    return 1;
}

/* conta a quantidade de chutes fora da palavra secreta que o jogador deu.
   ou, em outras palavras, conta o número de chutes errados. */
int enforcou(char palavraSecreta[20], char chutes [26], int* chutesDados)
{
    int erros = 0;

    for(int i = 0; i < (*chutesDados); i++)
    {
        int existe = 0;

        for(int j = 0; j < strlen(palavraSecreta); j++)
        {
            if(chutes[i] == palavraSecreta[j])
            {
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros >= 5;
}

void adicionaPalavra()
{
    char escolha;

    puts("Você deseja adicionar uma nova palavra ao banco de dados?");
    puts("Digite 'S' para sim e 'N' para não.");
    scanf(" %c", &escolha);

    if(escolha == 'S')
    {
        char novaPalavra[20];
        puts("Qual a nova palavra?");
        puts("(Digite em caixa alta sem usar caracteres especiais)");
        scanf("%s", novaPalavra);

        FILE* f;
        f = fopen("palavras.txt", "r+");

        verificarExistênciaDoArquivo(f);

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET); // posiciona o leitor no início do arquivo
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END); // posiciona o leitor no final do arquivo
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

int main()
{
    // criação e inicialização do array de palavras (funcionando como string)
    char palavraSecreta[20];

    char chutes[26]; // armazena os chutes do usuário
    int chutesDados = 0;

    escolherPalavra(palavraSecreta);

    imprimirCabecalho();

    do
    {
        desenharForca(palavraSecreta, chutes, chutesDados);

        guardarChute(chutes, &chutesDados);
    } 
    while (!acertou(palavraSecreta, chutes, chutesDados) && !enforcou(palavraSecreta, chutes, &chutesDados));

    printf("%s\n", palavraSecreta);

    if(acertou(palavraSecreta, chutes, chutesDados))
    {
        puts("");
        puts("** Parabéns, você descobriu a palavra secreta! **");
        puts("\t\t     _______________");
        puts("\t\t    |@@@@|     |####|");        
        puts("\t\t    |@@@@|     |####|");
        puts("\t\t    |@@@@|     |####|");
        puts("\t\t    \\@@@@|     |####/");
        puts("\t\t     \\@@@|     |###/");
        puts("\t\t      `@@|_____|##'");
        puts("\t\t           (O)");
        puts("\t\t        .-'''''-.");
        puts("\t\t      .'  * * *  `.");
        puts("\t\t     :  *       *  :");
        puts("\t\t    : ~ F O R C A ~ :");
        puts("\t\t    : ~ A W A R D ~ :");
        puts("\t\t     :  *       *  :");
        puts("\t\tjgs   `.  * * *  .'");
        puts("\t\t        `-.....-'");
        puts("");
    }
    else
    {
        printf("Sorry! You lost!");
    }
    

    return 0;
}
