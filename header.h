void gerarPalavraSecreta(char palavraSecreta[20]);
void imprimirCabecalho(void);
void desenharForca(char palavraSecreta[20], char chutes[26], int chutesDados);
void guardarChute(char chutes[26], int* chutesDados);
int jaChutou(char letra, char chutes[26], int chutesDados);
int acertou(char palavraSecreta[20], char chutes[26], int chutesDados);
int enforcou(char palavraSecreta[20], char chutes [26], int* chutesDados);