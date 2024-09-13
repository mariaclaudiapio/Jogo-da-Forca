#include <stdio.h>
#include <string.h> // para o uso da função strlen (que mede o tamanho do array)

#include "header.h"

void gerarPalavraSecreta(char palavraSecreta[20])
{
    sprintf(palavraSecreta, "MELANCIA");
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

int main()
{
    // criação e inicialização do array de palavras (funcionando como string)
    char palavraSecreta[20];

    char chutes[26]; // armazena os chutes do usuário
    int chutesDados = 0;

    gerarPalavraSecreta(palavraSecreta);

    imprimirCabecalho();

    do
    {
        desenharForca(palavraSecreta, chutes, chutesDados);

        guardarChute(chutes, &chutesDados);
    } 
    while (!acertou(palavraSecreta, chutes, chutesDados) && !enforcou(palavraSecreta, chutes, &chutesDados));

    printf("%s\n", palavraSecreta);

    return 0;
}
