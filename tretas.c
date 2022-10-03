#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define TEMPO_MEXER 50
#define ASCII_PECA 178
#define ASCII_FUNDO 0

int mapa[22][12];
int cores[22][12];
char controle;
int score = 0;
int linhas_feitas = 0;
int level = 1;
int tempo_cair = 500;

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void imprimir_quadrado(int largura, int altura , int x, int y)
{
    int i, j;
    gotoxy (x,y);
    for (i = 1; i <= altura ; i ++){
        if (i == 1){
            printf("%c", 201);
            for(j=1 ; j<= largura-2; j++)
                printf("%c", 205);
            printf("%c", 187);
            y++;
        }
        else if (i != altura){
            gotoxy(x,y);
            printf("%c", 186);
            for (j=1; j<= largura-2; j++ )
                 printf(" ");
            printf("%c", 186);
            y++;
        }else{
            gotoxy(x,y);
            printf("%c", 200);
            for(j=1 ; j<= largura-2; j++)
                printf("%c", 205);
            printf("%c", 188);
        }
    }
}
void cor (int cor)
{
    if (cor == 0){ // BRANCO
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }else if (cor == 1){ //  ROXO
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_RED | FOREGROUND_BLUE);
    }else if (cor==2){ // VERMELHO
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_RED);
    }else if (cor==3){ // VERDE
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }else if (cor==4){ // CIANO
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }else if (cor==5){ // AMARELO
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_RED | FOREGROUND_GREEN);
    }else if (cor==6){ // AZUL
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_BLUE);
    }else if (cor==7){ // BRANCO INTENSO
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }

}

void imprimir_uma_peca(int linha , int coluna)
{
    mapa[linha][coluna] = ASCII_PECA;// Inicialiazação da peça
    gotoxy(coluna, linha + 4);
    printf("%c", mapa[linha][coluna]);
}
void apagar_uma_peca(int linha , int coluna)
{
    mapa[linha][coluna] = ASCII_FUNDO;// Inicialiazação da peça
    gotoxy(coluna, linha + 4);
    printf("%c", mapa[linha][coluna]);
}
void imprimir_peca_T (int linha , int coluna ,  int posicao)
{
    cor(1);
    if (posicao == 0){
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 1;
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 1;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 1;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 1;
    }
    if(posicao == 1 ){
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 1;
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 1;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 1;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 1;
    }
     if (posicao == 2){
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 1;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 1;
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 1;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 1;

    }
    if(posicao == 3 ){
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 1;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 1;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 1;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 1;
    }
}
void apagar_peca_T (int linha , int coluna ,  int posicao)
{
    if (posicao == 0){
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha+1 ,coluna);
        apagar_uma_peca(linha ,coluna+1);
    }
    if(posicao == 1 ){
         apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha-1 ,coluna);
        apagar_uma_peca(linha+1 ,coluna);
    }
     if (posicao == 2){
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha-1 ,coluna);
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha ,coluna+1);

    }
    if(posicao == 3 ){
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha-1 ,coluna);
        apagar_uma_peca(linha ,coluna+1);
        apagar_uma_peca(linha+1 ,coluna);
    }
}
void imprimir_peca_Z(int linha, int coluna, int posicao)
{
    cor(2);
    if (posicao == 0){
        imprimir_uma_peca(linha, coluna);
        cores[linha][coluna] = 2;
        imprimir_uma_peca(linha-1, coluna-1);
        cores[linha][coluna-1] = 2;
        imprimir_uma_peca(linha-1, coluna);
        cores[linha-1][coluna] = 2;
        imprimir_uma_peca(linha, coluna+1);
        cores[linha][coluna+1] = 2;
    }
    if (posicao == 1){
        imprimir_uma_peca(linha, coluna);
        cores[linha][coluna] = 2;
        imprimir_uma_peca(linha-1, coluna+1);
        cores[linha-1][coluna+1] = 2;
        imprimir_uma_peca(linha, coluna+1);
        cores[linha][coluna+1] = 2;
        imprimir_uma_peca(linha+1, coluna);
        cores[linha+1][coluna] = 2;
    }
}
void apagar_peca_Z(int linha, int coluna, int posicao)
{
    if (posicao == 0){
        apagar_uma_peca(linha, coluna);
        apagar_uma_peca(linha-1, coluna-1);
        apagar_uma_peca(linha-1, coluna);
        apagar_uma_peca(linha, coluna+1);
    }
    if (posicao == 1){
        apagar_uma_peca(linha, coluna);
        apagar_uma_peca(linha-1, coluna+1);
        apagar_uma_peca(linha, coluna+1);
        apagar_uma_peca(linha+1, coluna);
    }
}
void imprimir_peca_S(int linha, int coluna, int posicao)
{
    cor(3);
    if (posicao == 0){
        imprimir_uma_peca(linha, coluna);
        cores[linha][coluna] = 3;
        imprimir_uma_peca(linha, coluna-1);
        cores[linha][coluna-1] = 3;
        imprimir_uma_peca(linha-1, coluna);
        cores[linha-1][coluna] = 3;
        imprimir_uma_peca(linha-1, coluna+1);
        cores[linha-1][coluna+1] = 3;
    }
    if (posicao == 1){
        imprimir_uma_peca(linha, coluna);
        cores[linha][coluna] = 3;
        imprimir_uma_peca(linha, coluna-1);
        cores[linha][coluna-1] = 3;
        imprimir_uma_peca(linha-1, coluna-1);
        cores[linha-1][coluna-1] = 3;
        imprimir_uma_peca(linha+1, coluna);
        cores[linha+1][coluna] = 3;
    }
}
void apagar_peca_S (int linha, int coluna, int posicao)
{
    if (posicao == 0){
        apagar_uma_peca(linha, coluna);
        apagar_uma_peca(linha, coluna-1);
        apagar_uma_peca(linha-1, coluna);
        apagar_uma_peca(linha-1, coluna+1);
    }
    if (posicao == 1){
        apagar_uma_peca(linha, coluna);
        apagar_uma_peca(linha, coluna-1);
        apagar_uma_peca(linha-1, coluna-1);
        apagar_uma_peca(linha+1, coluna);
    }
}
void imprimir_peca_linha (int linha , int coluna ,  int posicao)
{
    cor(4);
    if (posicao == 0){
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 4;
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 4;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 4;
        imprimir_uma_peca(linha ,coluna+2);
        cores[linha][coluna+2] = 4;
    }
    if(posicao == 1 ){
        imprimir_uma_peca(linha ,coluna );
        cores[linha][coluna] = 4;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 4;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 4;
        imprimir_uma_peca(linha-2 ,coluna);
        cores[linha-2][coluna] = 4;
    }
}
void apagar_peca_linha (int linha , int coluna ,  int posicao)
{
    if (posicao == 0){
        apagar_uma_peca(linha,coluna-1);
        apagar_uma_peca(linha,coluna);
        apagar_uma_peca(linha,coluna+1);
        apagar_uma_peca(linha,coluna+2);
    }
    if (posicao == 1 ){
        apagar_uma_peca(linha,coluna);
        apagar_uma_peca(linha+1,coluna);
        apagar_uma_peca(linha-1,coluna);
        apagar_uma_peca(linha-2,coluna);
    }
}
void imprimir_peca_quadrada(int linha , int coluna)
{
    cor(5);
    imprimir_uma_peca(linha ,coluna);
    cores[linha][coluna] = 5;
    imprimir_uma_peca(linha ,coluna+1);
    cores[linha][coluna+1] = 5;
    imprimir_uma_peca(linha-1 ,coluna);
    cores[linha-1][coluna] = 5;
    imprimir_uma_peca(linha-1 ,coluna+1);
    cores[linha-1][coluna+1] = 5;
}
void apagar_peca_quadrada(int linha , int coluna)
{
    apagar_uma_peca(linha ,coluna);
    apagar_uma_peca(linha ,coluna+1);
    apagar_uma_peca(linha-1 ,coluna);
    apagar_uma_peca(linha-1 ,coluna+1);
}
void imprimir_peca_L (int linha , int coluna ,  int posicao)
{
    cor(6);
    if (posicao == 0){
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 6;
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 6;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 6;
        imprimir_uma_peca(linha+1 ,coluna+1);
        cores[linha+1][coluna+1] = 6;
    }
    if (posicao == 1 ){
         imprimir_uma_peca(linha ,coluna );
         cores[linha][coluna] = 6;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 6;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 6;
        imprimir_uma_peca(linha+1 ,coluna-1);
        cores[linha+1][coluna-1] = 6;
    }
    if (posicao == 2){
        imprimir_uma_peca(linha-1 ,coluna-1);
        cores[linha-1][coluna-1] = 6;
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 6;
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 6;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 6;

    }
    if (posicao == 3 ){
        imprimir_uma_peca(linha ,coluna );
        cores[linha][coluna] = 6;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 6;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 6;
        imprimir_uma_peca(linha-1 ,coluna+1);
        cores[linha-1][coluna+1] = 6;
    }
}
void apagar_peca_L (int linha , int coluna ,  int posicao)
{
    if (posicao == 0){
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha ,coluna+1);
        apagar_uma_peca(linha+1 ,coluna+1);
    }
    if (posicao == 1 ){
        apagar_uma_peca(linha ,coluna );
        apagar_uma_peca(linha+1 ,coluna);
        apagar_uma_peca(linha-1 ,coluna);
        apagar_uma_peca(linha+1 ,coluna-1);
    }
    if (posicao == 2){
        apagar_uma_peca(linha-1 ,coluna-1);
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha ,coluna+1);

    }
    if (posicao == 3 ){
        apagar_uma_peca(linha ,coluna );
        apagar_uma_peca(linha+1 ,coluna);
        apagar_uma_peca(linha-1 ,coluna);
        apagar_uma_peca(linha-1 ,coluna+1);
    }
}
void imprimir_peca_L_invertida (int linha , int coluna ,  int posicao)
{
    cor(7);
    if (posicao == 0){
        imprimir_uma_peca(linha+1 ,coluna-1);
        cores[linha+1][coluna-1] = 7;
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 7;
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 7;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 7;
    }
    if (posicao == 1 ){
        imprimir_uma_peca(linha-1 ,coluna-1);
        cores[linha-1][coluna-1] = 7;
        imprimir_uma_peca(linha ,coluna );
        cores[linha][coluna] = 7;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 7;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 7;

    }
    if (posicao == 2){
        imprimir_uma_peca(linha-1 ,coluna+1);
        cores[linha-1][coluna+1] = 7;
        imprimir_uma_peca(linha ,coluna-1);
        cores[linha][coluna-1] = 7;
        imprimir_uma_peca(linha ,coluna);
        cores[linha][coluna] = 7;
        imprimir_uma_peca(linha ,coluna+1);
        cores[linha][coluna+1] = 7;

    }
    if (posicao == 3 ){
        imprimir_uma_peca(linha ,coluna );
        cores[linha][coluna] = 7;
        imprimir_uma_peca(linha+1 ,coluna);
        cores[linha+1][coluna] = 7;
        imprimir_uma_peca(linha-1 ,coluna);
        cores[linha-1][coluna] = 7;
        imprimir_uma_peca(linha+1 ,coluna+1);
        cores[linha+1][coluna+1] = 7;
    }
}
void apagar_peca_L_invertida  (int linha , int coluna ,  int posicao)
{
    if (posicao == 0){
        apagar_uma_peca(linha+1 ,coluna-1);
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha ,coluna+1);

    }
    if (posicao == 1 ){
        apagar_uma_peca(linha-1 ,coluna-1);
        apagar_uma_peca(linha ,coluna );
        apagar_uma_peca(linha+1 ,coluna);
        apagar_uma_peca(linha-1 ,coluna);

    }
    if (posicao == 2){
        apagar_uma_peca(linha-1 ,coluna+1);
        apagar_uma_peca(linha ,coluna-1);
        apagar_uma_peca(linha ,coluna);
        apagar_uma_peca(linha ,coluna+1);

    }
    if(posicao == 3 ){
        apagar_uma_peca(linha ,coluna );
        apagar_uma_peca(linha+1 ,coluna);
        apagar_uma_peca(linha-1 ,coluna);
        apagar_uma_peca(linha+1 ,coluna+1);
    }
}
int condicao_direita_peca_L (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna+2] == ASCII_FUNDO &&  mapa[linha+1][coluna+2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2 &&  mapa[linha][coluna+2] == ASCII_FUNDO  &&  mapa[linha-1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha-1][coluna+2] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_esquerda_peca_L (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha+1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha-1][coluna-2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3 && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_rotacao_peca_L (int linha,int coluna,int posicao){
    if ( posicao == 0 && mapa[linha+1][coluna] == ASCII_FUNDO && mapa[linha-1][coluna] == ASCII_FUNDO  && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2  &&  mapa[linha-1][coluna] == ASCII_FUNDO &&  mapa[linha-1][coluna+1] == ASCII_FUNDO &&  mapa[linha+1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3  && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_fim_peca_L (int linha,int coluna,int posicao){

    if ( posicao == 0 && (linha+1 == 20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+2][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 1 && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+2][coluna-1] == ASCII_PECA))
        return 1;
    if ( posicao == 2  &&  (linha == 20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 3  && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha][coluna+1] == ASCII_PECA))
        return 1;
    return 0;
}

int condicao_direita_peca_L_invertida (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna+2] == ASCII_FUNDO &&  mapa[linha+1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2 &&  mapa[linha][coluna+2] == ASCII_FUNDO  &&  mapa[linha-1][coluna+2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+2] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_esquerda_peca_L_invertida (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha+1][coluna-2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-2] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha-1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3 && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_rotacao_peca_L_invertida (int linha,int coluna,int posicao){
    if ( posicao == 0 && mapa[linha+1][coluna] == ASCII_FUNDO && mapa[linha-1][coluna] == ASCII_FUNDO  && mapa[linha-1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2  &&  mapa[linha-1][coluna] == ASCII_FUNDO &&  mapa[linha+1][coluna] == ASCII_FUNDO &&  mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3  && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_fim_peca_L_invertida (int linha,int coluna,int posicao){
    if ( posicao == 0 && (linha+1==20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+2][coluna-1] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 1 && (linha+1 ==20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha][coluna-1] == ASCII_PECA))
        return 1;
    if ( posicao == 2  &&  (linha==20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 3  && (linha+1 ==20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+2][coluna+1] == ASCII_PECA))
        return 1;
    return 0;
}

int condicao_direita_peca_T (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna+2] == ASCII_FUNDO &&  mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2 &&  mapa[linha][coluna+2] == ASCII_FUNDO  &&  mapa[linha-1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3 && mapa[linha][coluna+2] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_esquerda_peca_T (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna-2] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha-1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3 && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_rotacao_peca_T (int linha,int coluna,int posicao){
    if ( posicao == 0 && mapa[linha-1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 2  &&  mapa[linha+1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 3  && mapa[linha][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_fim_peca_T (int linha,int coluna,int posicao){
    if ( posicao == 0 && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 1 && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA))
        return 1;
    if ( posicao == 2  &&  (linha == 20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 3  && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    return 0;
}

int condicao_direita_peca_Z (int linha, int coluna, int posicao){
    if ( posicao == 0 &&  mapa[linha-1][coluna+1] == ASCII_FUNDO &&  mapa[linha][coluna+2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha-1][coluna+2] == ASCII_FUNDO && mapa[linha][coluna+2] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_esquerda_peca_Z (int linha, int coluna, int posicao){
    if ( posicao == 0 &&  mapa[linha-1][coluna-2] == ASCII_FUNDO &&  mapa[linha][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha-1][coluna] == ASCII_FUNDO && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_rotacao_peca_Z (int linha, int coluna, int posicao){
    if ( posicao == 0 && mapa[linha-1][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha+1][coluna] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_fim_peca_Z (int linha, int coluna, int posicao){
    if ( posicao == 0 && (linha == 20 || mapa[linha][coluna-1] == ASCII_PECA || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    else if ( posicao == 1 && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA))
        return 1;
    return 0;
}

int condicao_direita_peca_S (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha-1][coluna+2] == ASCII_FUNDO &&  mapa[linha][coluna+1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO && mapa[linha-1][coluna] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_esquerda_peca_S (int linha,int coluna,int posicao){
    if ( posicao == 0 &&  mapa[linha][coluna-2] == ASCII_FUNDO &&  mapa[linha-1][coluna-1] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna-2] == ASCII_FUNDO && mapa[linha-1][coluna-2] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_rotacao_peca_S (int linha,int coluna,int posicao){
    if ( posicao == 0 && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha-1][coluna] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_fim_peca_S (int linha,int coluna,int posicao){
    if ( posicao == 0 && (linha == 20 || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha][coluna+1] == ASCII_PECA))
        return 1;
    if ( posicao == 1 && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA))
        return 1;
    return 0;
}

int condicao_direita_peca_linha (int linha,int coluna,int posicao){
    if ( posicao == 0 && mapa[linha][coluna+3] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha-1][coluna+1] == ASCII_FUNDO && mapa[linha+1][coluna+1] == ASCII_FUNDO && mapa[linha-2][coluna+1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_esquerda_peca_linha (int linha,int coluna,int posicao){
    if ( posicao == 0 &&   mapa[linha][coluna-2] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO && mapa[linha+1][coluna-1] == ASCII_FUNDO && mapa[linha-2][coluna-1] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_rotacao_peca_linha (int linha,int coluna,int posicao){
    if ( posicao == 0 && mapa[linha+1][coluna] == ASCII_FUNDO && mapa[linha-1][coluna] == ASCII_FUNDO && mapa[linha-2][coluna] == ASCII_FUNDO)
        return 1;
    else if ( posicao == 1 &&  mapa[linha][coluna+1] == ASCII_FUNDO && mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha][coluna+2] == ASCII_FUNDO)
        return 1;
    return 0;
}
int condicao_fim_peca_linha (int linha,int coluna,int posicao){
    if ( posicao == 0 && (linha == 20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna-1] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA || mapa[linha+1][coluna+2]== ASCII_PECA))
        return 1;
    if ( posicao == 1 && (linha+1 == 20 || mapa[linha+2][coluna] == ASCII_PECA))
        return 1;
    return 0;
}
//movimento

int move_peca_Z (void)
{
    int linha , coluna;
    int posicao =0;
    linha = 2 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_Z(linha,coluna,posicao);
        if(kbhit() == 1)
        {
            apagar_peca_Z(linha,coluna,posicao);
            controle = getch();
                if(controle == 'd'  && condicao_direita_peca_Z(linha,coluna,posicao))
                    coluna ++;
                if(controle == 'a' && condicao_esquerda_peca_Z(linha,coluna,posicao))
                    coluna --;
                if(controle == 'w' && condicao_rotacao_peca_Z(linha,coluna,posicao)){
                    posicao++;
                    if(posicao == 2)
                        posicao = 0;
                }
            if (controle == 's' && condicao_fim_peca_Z(linha,coluna,posicao) == 0)
                linha++;
            imprimir_peca_Z(linha,coluna,posicao);
            Sleep(TEMPO_MEXER);
            continue;
        }
        if (condicao_fim_peca_Z(linha,coluna,posicao)){
            if(linha == 2)
                return  1;
            return 0;
        }
        Sleep(tempo_cair);
        apagar_peca_Z(linha,coluna,posicao);
        linha++;
    }

}

int move_peca_S (void)
{
    int linha, coluna;
    int posicao = 0;
    linha = 2 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_S(linha,coluna,posicao);
        if(kbhit() == 1)
        {
            apagar_peca_S(linha, coluna, posicao);
            controle = getch();
            if(controle == 'd'  && condicao_direita_peca_S(linha,coluna,posicao))
                coluna ++;
            if(controle == 'a' &&  condicao_esquerda_peca_S(linha,coluna,posicao))
                coluna --;
            if(controle == 'w' && condicao_rotacao_peca_S(linha,coluna,posicao)){
                posicao++;
                if (posicao == 2)
                    posicao = 0;
            }
            if (controle == 's' && condicao_fim_peca_S(linha,coluna,posicao) == 0)
                linha++;
            imprimir_peca_S(linha,coluna,posicao);
            Sleep(TEMPO_MEXER);
            continue;
        }
        if(condicao_fim_peca_S(linha,coluna,posicao))
        {
            if(linha == 2)
                return  1;
            return 0;
        }

        Sleep(tempo_cair);
        apagar_peca_S(linha,coluna,posicao);
        linha++;
    }
}

int move_peca_linha (void)
{
    int linha , coluna;
    int posicao = 0;
    linha = 1 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_linha(linha,coluna,posicao);
         if(kbhit() == 1)
        {
            apagar_peca_linha(linha,coluna,posicao);
            controle = getch();
            if(controle == 'd'  &&  condicao_direita_peca_linha (linha,coluna,posicao))
                coluna ++;
            if(controle == 'a' &&   condicao_esquerda_peca_linha (linha,coluna,posicao))
                coluna --;
            if(controle == 'w' &&  condicao_rotacao_peca_linha (linha,coluna,posicao)){
                posicao++;
                if(posicao == 2)
                    posicao = 0;
            }
            if (controle == 's' && condicao_fim_peca_linha(linha,coluna,posicao) == 0)
                linha++;
            imprimir_peca_linha(linha,coluna,posicao);
            Sleep(TEMPO_MEXER);
            continue;
        }
        if( condicao_fim_peca_linha (linha,coluna,posicao))
        {
            if(linha == 1)
                return 1;
            return 0;
        }
        Sleep(tempo_cair);
        apagar_peca_linha(linha,coluna,posicao);
        linha++;
    }

}

int move_peca_L (void)
{
    int linha , coluna;
    int posicao =0;
    linha = 1 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_L(linha,coluna,posicao);
         if(kbhit() == 1)
        {
            apagar_peca_L(linha,coluna,posicao);
            controle = getch();
                if(controle == 'd'  && condicao_direita_peca_L(linha,coluna,posicao))
                    coluna ++;
                if(controle == 'a' && condicao_esquerda_peca_L(linha,coluna,posicao))
                    coluna --;
                if(controle == 'w' && condicao_rotacao_peca_L(linha,coluna,posicao)){
                    posicao++;
                    if(posicao == 4)
                        posicao = 0;
                }
            if (controle == 's' && condicao_fim_peca_L(linha,coluna,posicao) == 0)
                linha++;
            imprimir_peca_L(linha,coluna,posicao);
            Sleep(TEMPO_MEXER);
            continue;
        }
        if (condicao_fim_peca_L(linha,coluna,posicao)){
            if(linha == 1)
                return  1;
            return 0;
        }

        Sleep(tempo_cair);
        apagar_peca_L(linha,coluna,posicao);
        linha++;
    }

}

int move_peca_L_invertida (void)
{
    int linha , coluna;
    int posicao = 0;
    linha = 1 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_L_invertida(linha,coluna,posicao);
         if(kbhit() == 1)
        {
            apagar_peca_L_invertida(linha,coluna,posicao);
            controle = getch();
                if(controle == 'd'  && condicao_direita_peca_L_invertida(linha,coluna,posicao))
                    coluna ++;
                if(controle == 'a' && condicao_esquerda_peca_L_invertida(linha,coluna,posicao))
                    coluna --;
                if(controle == 'w' && condicao_rotacao_peca_L_invertida(linha,coluna,posicao)){
                    posicao++;
                    if(posicao == 4)
                        posicao = 0;
                }
            if (controle == 's' && condicao_fim_peca_L_invertida(linha,coluna,posicao) == 0)
                linha++;
            imprimir_peca_L_invertida(linha,coluna,posicao);
            Sleep(TEMPO_MEXER);
            continue;
        }
        if (condicao_fim_peca_L_invertida(linha,coluna,posicao)){
            if(linha == 1)
                return  1;
            return 0;
        }

        Sleep(tempo_cair);
        apagar_peca_L_invertida(linha,coluna,posicao);
        linha++;
    }

}

int move_peca_quadrado (void)
{
   int linha , coluna;
    linha = 2 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_quadrada(linha,coluna);
         if(kbhit() == 1)
        {
            apagar_peca_quadrada(linha,coluna);
            controle = getch();
            if(controle == 'd'  &&  mapa[linha][coluna+2] == ASCII_FUNDO &&  mapa[linha-1][coluna+2] == ASCII_FUNDO)
                coluna ++;
            if(controle == 'a' &&  mapa[linha][coluna-1] == ASCII_FUNDO && mapa[linha-1][coluna-1] == ASCII_FUNDO)
                coluna --;
            if (controle == 's' && (linha==20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA) == 0)
                linha++;
            imprimir_peca_quadrada(linha,coluna);
            Sleep(TEMPO_MEXER);
            continue;
        }

        if(linha==20 || mapa[linha+1][coluna] == ASCII_PECA || mapa[linha+1][coluna+1] == ASCII_PECA)
        {
            if(linha ==  2)
                return 1;
            return 0;
        }
        Sleep(tempo_cair);
        apagar_peca_quadrada(linha,coluna);
        linha++;
    }
}

int move_peca_T (void)
{
    int linha , coluna;
    int posicao =0;
    linha = 1 ;
    coluna = 5 ;

    while(1)
    {
        imprimir_peca_T(linha,coluna,posicao);
        if(kbhit() == 1)
        {
            apagar_peca_T(linha,coluna,posicao);
            controle = getch();
                if(controle == 'd'  && condicao_direita_peca_T(linha,coluna,posicao))
                    coluna++;
                if(controle == 'a' && condicao_esquerda_peca_T(linha,coluna,posicao))
                    coluna--;
                if(controle == 'w' && condicao_rotacao_peca_T(linha,coluna,posicao)){
                    posicao++;
                    if(posicao == 4)
                        posicao = 0;
                }
            if (controle == 's' && condicao_fim_peca_T(linha,coluna,posicao) == 0)
                linha++;
            imprimir_peca_T(linha,coluna,posicao);
            Sleep(TEMPO_MEXER);
            continue;
        }
        if (condicao_fim_peca_T(linha,coluna,posicao)){
            if(linha == 1)
                return  1;
            return 0;
        }

        Sleep(tempo_cair);
        apagar_peca_T(linha,coluna,posicao);
        linha++;
    }

}


void tabuleiro(void){
    int linha, coluna;
    gotoxy(0,0);
    printf(" ROTATE ------ W\n");
    printf(" LEFT -------- A\n RIGHT ------- D\n SPEED DOWN -- S\n");
    for(linha = 0; linha<22; linha++){
        for(coluna = 0; coluna<12; coluna++){
            if(coluna == 0 || coluna == 11)
                mapa[linha][coluna] = 186; //bordas verticais 'a' = 97

            if(linha == 0 || linha == 21)
                mapa[linha][coluna] = 205; //bordas horizontais

            if((coluna != 0 && coluna != 11) && (linha != 0 && linha != 21))
                mapa[linha][coluna] = ASCII_FUNDO; //centro '0' = 48

            if(linha == 0 && coluna == 0)
                mapa[linha][coluna] = 201; //borda superior esquerdo

            if(linha == 0 && coluna == 11)
                mapa[linha][coluna] = 187; //borda superior direito

            if(linha == 21 && coluna == 0)
                mapa[linha][coluna] = 200; //borda inferior esquerdo

            if(linha == 21 && coluna == 11)
                mapa[linha][coluna] = 188; //borda inferior direito

            printf("%c", mapa[linha][coluna]);
        }
        printf("\n");
    }
}

void placar(void){
    int i;
    gotoxy(15, 4);
    printf("%c%c%cSCORE%c%c%c", 201, 205, 185, 204, 205, 187);

    gotoxy(15, 5);
    printf("%c000000000%c", 186,186);

    gotoxy(15, 6);
    printf("%c", 200);
    for(i=0; i<9; i++)
        printf("%c", 205);
    printf("%c", 188);

    gotoxy(16, 5);
    printf("%9d", score);

    imprimir_quadrado(10, 3, 27, 4);
    gotoxy(28, 5);
    printf("LEVEL %2d", level);
}

void tetris(void){
    int linha, coluna, verifica_tetris=0;

    for(linha = 0; linha<22; linha++){
        for(coluna = 0; coluna<12; coluna++){
            if(mapa[linha][coluna] == ASCII_PECA){
                verifica_tetris++;
                if(verifica_tetris == 10){
                    for(; linha >= 2; linha--){
                        Sleep(1);
                        for(coluna = 1; coluna<11; coluna++){
                            mapa[linha][coluna] = mapa[linha-1][coluna];
                            cores[linha][coluna] = cores[linha-1][coluna];
                            gotoxy(coluna, linha+4);
                            cor(cores[linha][coluna]);
                            printf("%c",mapa[linha][coluna]);
                        }
                    }
                    linhas_feitas++;
                    score = score + (80*level)/2;
                    if(linhas_feitas%3 == 0){
                        level++;
                        if(tempo_cair > 60)
                            tempo_cair = tempo_cair - 30;
                    }
                }
            }
            else{
                verifica_tetris = 0;
            }
        }
    }
}

void inicializador(void){
    hidecursor();
    while (1){
        imprimir_quadrado(24,3,10,9);
        gotoxy(11, 10);
        printf("PRESS ANY KEY TO START");
        Sleep(300);
        gotoxy(11, 10);
        printf("                      ");
        Sleep(100);
        if(kbhit()==1){
            gotoxy(10, 9);
            printf("                                          \n                                                                  \n                                                             \n");
            return;
        }
    }
}

int fim_reset(void){
    int estado = 0;
    hidecursor();
    gotoxy(25 , 9);
    printf("PLAY AGAIN?");
    while (1){
        imprimir_quadrado(7,3,22,11);
        gotoxy(23,12);
        printf("RESET");
        imprimir_quadrado(6,3,33,11);
        gotoxy(34,12);
        printf("QUIT");
        Sleep(100);
        if (estado ==0)
        {
            gotoxy(23, 12);
            printf("     ");
            gotoxy(32, 12);
            printf(" ");
            gotoxy(21, 12);
            printf("%c", 16);
        }
        if (estado ==1)
        {
            gotoxy(34, 12);
            printf("    ");
            gotoxy(21, 12);
            printf(" ");
            gotoxy(32, 12);
            printf("%c", 16);
        }
        Sleep(100);
        if(kbhit()==1){
            controle = getch();
            if (controle == 'd'){
                estado= 1;
            }else if (controle == 'a'){
                estado= 0;
            }else if (controle == 32 && estado ==0){
            gotoxy(20, 9);
            printf("                                     \n                                                 \n                                        \n                                                   \n                                                             \n");
            return 0;
            }else if (controle ==32 && estado==1){
            return 1;
            }
        }
    }
}

void preenche_tabuleiro(void){
    int linha, coluna;

    for(linha=20; linha>0; linha--){
        for(coluna=0; coluna<10; coluna++){
            mapa[linha][coluna] = 178;
            gotoxy(coluna+1, linha+4);
            printf("%c", mapa[linha][coluna]);
            if (coluna == 10)
                break;
            Sleep(10);
        }
    }
}

void imprime_game_over(void){
    int i;

    preenche_tabuleiro();

    gotoxy(0,9);
    printf("%c", 204);
    for(i=1; i<11; i++){
        printf("%c", 205);
    }
    printf("%c", 185);
    gotoxy(0, 10);
    printf("%cGAME  OVER%c", 186, 186);
    gotoxy(0, 11);
    printf("%c", 204);
    for(i=1; i<11; i++){
        printf("%c", 205);
    }
    printf("%c", 185);
    gotoxy(0, 25);
}

void agradecimento(void){
    imprimir_quadrado(23, 3, 0, 27);
    gotoxy(1, 28);
    printf("Obrigado por jogar =)");
    gotoxy(0, 31);
}


//START =================================================
int main(){

    int game_over = 0;
    int sorteio;
    inicializador();
    hidecursor();
    tabuleiro();

    while(game_over == 0){
        placar();
        tetris();

        srand(time(0));
        sorteio = rand()%7;
        if (sorteio == 0)
            game_over = move_peca_L();
        if (sorteio == 1)
            game_over = move_peca_quadrado();
        if (sorteio == 2)
            game_over = move_peca_linha();
        if (sorteio == 3)
            game_over = move_peca_L_invertida();
        if (sorteio == 4)
            game_over = move_peca_S();
        if (sorteio == 5)
            game_over = move_peca_Z();
        if (sorteio == 6)
            game_over = move_peca_T();
        cor(0);
        placar();
        tetris();
        if (game_over==1){
            imprime_game_over();
            if  (fim_reset()){
                agradecimento();
                return 0;
            }
            else{
                game_over = 0;
                score = 0;
                linhas_feitas = 0;
                level = 1;
                tempo_cair = 500;
            }
            tabuleiro();
        }
    }
}
