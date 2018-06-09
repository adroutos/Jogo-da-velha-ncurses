#include<ncurses.h>

#define MAX 35

void coloca(void);/*-------------------------------------------->funcao que "cria" o tabuleiro(fazendo eu ganhar tempo nao precisando desenhar*/
void print(void); /*-------------------------------------------->funcao que printa o tabuleiro*/
void cores(void); /*-------------------------------------------->funcao que faz as possibilidades de cores*/
void ganhou(int il, int ic, int *teste,int gx[1], int go[1]); /*>funcao que checará se ganhou*/
void jogo(int gx[1],int go[1]); /*------------------------------>funcao que roda o jogo*/
void menu(void); /*--------------------------------------------->funcao do menu inicial*/
void imprimemenu(int *a,char menuzao[5][15]);/*----------------->imprime o menu inicial*/

char matriz[MAX][MAX + 30]; /*campo do jogo da velha*/

int main(void)
{
    int gx[1] = {0};
    int go[1] = {0};
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr,TRUE);
    curs_set(0);
  //  menu();
    jogo(gx,go);
}

/************************************************************************************************
 *funcao que rodará o jogo!*/

void jogo(int gx[1],int go[1])
{
    int r,il = 5,ic = 10,l,c,teste = 0;

    getmaxyx(stdscr,l,c);

    refresh();
    matriz[il][ic] = '@';
    cores();
    menu();
    coloca();
    refresh();
    print();
    refresh();

    do
    {
        print();
        refresh();
        ganhou(il,ic,&teste,gx,go);
        if(teste == 1)
            break;
        attron(COLOR_PAIR(2) | A_REVERSE);
        mvprintw(l/2 - 21,c/2 - 9,"PLACAR = %d(X) vs %d(O)",gx[0],go[0]);
        attroff(COLOR_PAIR(2) | A_REVERSE);
        attron(COLOR_PAIR(1) | A_UNDERLINE);
        mvprintw(l/2 + 16,c/2 - 10,"Q PARA SAIR");
        mvchgat(l/2 + 16,c/2 - 10,1,A_REVERSE,1,NULL);
        mvprintw(l/2 + 16,c/2 + 5,"X COLOCA O 'X'");
        mvchgat(l/2 + 16,c/2 + 5,1,A_REVERSE,1,NULL);
        mvprintw(l/2 + 18,c/2 - 10,"O COLOCA O 'O'");
        mvchgat(l/2 + 18,c/2 - 10,1,A_REVERSE,1,NULL);
        mvprintw(l/2 + 18,c/2 + 5,"ESC 2x APAGAR");
        mvchgat(l/2 + 18,c/2 +5,6,A_REVERSE,1,NULL);
        attroff(A_UNDERLINE);
        print();
        refresh();
        r = getch();
        if(r == 'q')
            break;
        switch(r)
        {
            case 27: /*esc*/
                if(matriz[il][ic] == 'x' || matriz[il][ic] == 'o')
                {
                    matriz[il][ic] = ' '; /*pra voce apagar o que escreveu*/
                    print();
                    refresh();
                }
                print();
                refresh();
                break;
            case 'x':
                matriz[il][ic] = 'x'; /*caso tecle x coloca um x*/
                print();
                refresh();
                break;
            case 'o':
                matriz[il][ic] = 'o';
                print();
                refresh();
                break;
            case KEY_UP:
                if(il != 5)
                {
                    if(matriz[il - 12][ic] == 'x')
                        matriz[il - 12][ic] = 'x';
                    else
                    {
                        if(matriz[il - 12][ic] == 'o')
                            matriz[il - 12][ic] = 'o';
                        else
                            matriz[il - 12][ic] = '@';
                    }
                    if(matriz[il][ic] == 'x')
                    {
                        matriz[il][ic] = 'x';
                        il = il - 12;
                        print();
                        refresh();
                        break;
                    }
                    if(matriz[il][ic] == 'o')
                    {
                        matriz[il][ic] = 'o';
                        il = il - 12;
                        print();
                        refresh();
                        break;
                    }
                    else
                    {
                        matriz[il][ic] = ' ';
                        il = il - 12;
                        print();
                        refresh();
                        break;
                    }
                }
                else
                    break;
            case KEY_DOWN:
                if(il != 29)
                {
                    if(matriz[il + 12][ic] == 'x')
                        matriz[il + 12][ic] = 'x';
                    else
                    {
                        if(matriz[il + 12][ic] == 'o')
                            matriz[il + 12][ic] = 'o';
                        else
                            matriz[il + 12][ic] = '@';
                    }
                    if(matriz[il][ic] == 'x')
                    {
                        matriz[il][ic] = 'x';
                        il = il + 12;
                        print();
                        refresh();
                        break;
                    }
                    if(matriz[il][ic] == 'o')
                    {
                        matriz[il][ic] = 'o';
                        il = il + 12;
                        print();
                        refresh();
                        break;
                    }
                    else
                    {
                        matriz[il][ic] = ' ';
                        il = il + 12;
                        print();
                        refresh();
                        break;
                    }
                }
                break;
            case KEY_RIGHT:
                if(ic != 52)
                {
                    if(matriz[il][ic + 21] == 'x')
                        matriz[il][ic + 21] = 'x';
                    else
                    {
                        if(matriz[il][ic + 21] == 'o')
                            matriz[il][ic + 21] = 'o';
                        else
                            matriz[il][ic + 21] = '@';
                    }
                    if(matriz[il][ic] == 'x')
                    {
                        matriz[il][ic] = 'x';
                        ic = ic + 21;
                        print();
                        refresh();
                        break;
                    }
                    if(matriz[il][ic] == 'o')
                    {
                        matriz[il][ic] = 'o';
                        ic = ic + 21;
                        print();
                        refresh();
                        break;
                    }
                    else
                    {
                        matriz[il][ic] = ' ';
                        ic = ic + 21;
                        print();
                        refresh();
                        break;
                    }
                }
                break;
            case KEY_LEFT:
                if(ic != 10)
                {
                    if(matriz[il][ic - 21] == 'x')
                        matriz[il][ic - 21] = 'x';
                    else
                    {
                        if(matriz[il][ic - 21] == 'o')
                            matriz[il][ic - 21] = 'o';
                        else
                            matriz[il][ic - 21] = '@';
                    }
                    if(matriz[il][ic] == 'x')
                    {
                        matriz[il][ic] = 'x';
                        ic = ic - 21;
                        print();
                        refresh();
                        break;
                    }
                    if(matriz[il][ic] == 'o')
                    {
                        matriz[il][ic] = 'o';
                        ic = ic - 21;
                        print();
                        refresh();
                        break;
                    }
                    else
                    {
                        matriz[il][ic] = ' ';
                        ic = ic - 21;
                        print();
                        refresh();
                        break;
                    }
                }
                break;
        }
    }while(r != 'q');
    endwin();
}
void imprimemenu(int *a,char menuzao[5][15])
{
    int i,j,l,c,pula = 0;
    getmaxyx(stdscr,l,c);

    attron(COLOR_PAIR(1));
    for(i = 0;i < 5;i++)
    {


            if(i == *a)
            {
                attron(A_REVERSE);
                mvprintw(l/2 - 7 + pula,c/2 - 15,"%s",menuzao[i]);
            }
            else
            {
                attroff(A_REVERSE);
                mvprintw(l/2 - 7 + pula,c/2 - 15,"%s",menuzao[i]);
            }
            pula = pula + 2;


    }
    attroff(A_REVERSE);
    refresh();
}
void menu(void)
{
    int l,c,r,a = 0,b;
    char menuzao[5][15] = {{"IR PARA O JOGO"},
                           {"REGRAS"},
                           {"CONTROLES"},
                           {"DESENVOLVEDOR"},
                           {"SAIR DO JOGO"}};

    getmaxyx(stdscr,l,c);
    do
    {
        attron(COLOR_PAIR(1) | A_UNDERLINE);
        mvprintw(l/2 - 13,c/2 - 18,"BEM VINDO AO JOGO DA VELHA!");
        attroff(A_UNDERLINE);
        imprimemenu(&a,menuzao);
        refresh();
        r = getch();
        switch(r)
        {
            case KEY_UP:
                a = a - 1;
                if(a < 0)
                {
                    a = 4;
                    imprimemenu(&a,menuzao);
                    refresh();
                }
                else
                {
                    imprimemenu(&a,menuzao);
                    refresh();
                }
                break;
            case KEY_DOWN:
                a = a + 1;
                if(a > 4)
                {
                    a = 0;
                    imprimemenu(&a,menuzao);
                    refresh();
                }
                else
                {
                    imprimemenu(&a,menuzao);
                    refresh();
                }
                break;
            case 10:
                if(a == 0)
                    r = 'q';
                if(a == 1)
                {
                    clear();
                    refresh();
                    attron(COLOR_PAIR(1)| A_REVERSE);
                    mvprintw(l/2 - 5,c/2 - 25,"GANHA SE CONSEGUIR FAZER UMA RETA DE 3 SIMBOLOS IGUAIS");
                    mvprintw(l/2 - 3,c/2 - 25,"NAO PODE COLOCAR ONDE JA ESTIVER COLOCADO ALGUM SIMBOLO");
                    mvprintw(l/2 + 5,c/2 - 25,"APERTE 1 PARA VOLTAR PRO MENU");
                    attroff(COLOR_PAIR(1) | A_REVERSE);
                    r = getch();
                    if(r == '1')
                    {
                        clear();
                        refresh();
                        menu();
                    }
                }
                if(a == 2)
                {
                    clear();
                    refresh();
                    attron(COLOR_PAIR(1)| A_REVERSE);
                    mvprintw(l/2 - 5,c/2 - 25,"X PARA COLOCAR O 'X'");
                    mvprintw(l/2 -3,c/2 - 25,"O PARA COLOCAR O 'O'");
                    mvprintw(l/2 -1,c/2 - 25,"ESC DUAS VEZES PARA APAGAR");
                    mvprintw(l/2 + 5,c/2 - 25,"APERTE 1 PARA VOLTAR PRO MENU");
                    attroff(COLOR_PAIR(1) | A_REVERSE);
                    r = getch();
                    if(r == '1')
                    {
                        clear();
                        refresh();
                        menu();
                    }
                }
                if(a == 3)
                {
                    clear();
                    refresh();
                    attron(COLOR_PAIR(1) | A_REVERSE);
                    mvprintw(l/2 -5,c/2 - 25,"JOGO DA VELHA NCURSES BY ADRIANO PEDRO");
                    mvprintw(l/2 +5,c/2 - 25,"APERTE 1 PARA VOLTAR PRO MENU");
                    attroff(COLOR_PAIR(1) | A_REVERSE);
                    r = getch();
                    if(r == '1')
                    {
                        clear();
                        refresh();
                        menu();
                    }

                }/*
                if(a == 4)
                {
                    mvprintw(l/2 - 5,c/2 - 25,"ADEUS");
                    clear();
                    refresh();
                    napms(600);
                    refresh();
                    endwin();
                }*/
                break;
        }
    }while(r != 'q');
}
/************************************************************************************************
 *funcao que checará que ganhou!!*/

void ganhou(int il,int ic,int *teste,int gx[1], int go[1])
{
    int r,l,c;

    getmaxyx(stdscr,l,c);

    /*   keypad(stdscr,FALSE);*/
    if((matriz[5][10] == 'x' && matriz[5][10 + 21] == 'x' && matriz[5][10 + 42 ] == 'x') ||
            (matriz[5][10] == 'x' && matriz[5 + 12][10] == 'x' && matriz[5 + 24][10] == 'x') ||
            (matriz[5][10] == 'x' && matriz[5 + 12][10 + 21] == 'x' && matriz[5 + 24][10 + 42] == 'x') ||
            (matriz[5][10 + 42] == 'x' && matriz[5 + 12][10 + 42] == 'x' && matriz[5 + 24][10 + 42] == 'x') ||
            (matriz[5 + 24][10] == 'x' && matriz[5 + 24][10 + 21] == 'x' && matriz[5 +24][10 + 42] == 'x') ||
            (matriz[5][10 + 42] == 'x' && matriz[5 + 12][10 + 21] == 'x' && matriz[5 + 24][10] == 'x') ||
            (matriz[5 + 12][10] == 'x' && matriz[5 + 12][10 + 21] == 'x' && matriz[5 + 12][10 + 42] == 'x') ||
            (matriz[5][10 + 21] == 'x' && matriz[5 + 12][10 + 21] == 'x' && matriz[5 + 24][10 + 21] == 'x'))
    {
        attron(A_UNDERLINE);
        mvprintw(l/2,c/2 - 15,"O JOGADOR DO X GANHOU!!!PARABENS OTARIO!");
        mvprintw(l/2 + 2,c/2 - 15,"PARA JOGAR NOVAMENTE APERTE ENTER, PARA SAIR APERTE B");
        r = getch();
        switch(r)
        {
            case 10:
                refresh();
                clear();
                refresh();
                gx[0] = gx[0] + 1;
                jogo(gx,go);
                break;
            case 'b':
                *teste = 1;
                break;
            default:
                refresh();
                ganhou(il,ic,teste,gx,go);
                break;
        }
    }
    attroff(A_UNDERLINE);
    if((matriz[5][10] == 'o' && matriz[5][10 + 21] == 'o' && matriz[5][10 + 42 ] == 'o') ||
            (matriz[5][10] == 'o' && matriz[5 + 12][10] == 'o' && matriz[5 + 24][10] == 'o') ||
            (matriz[5][10] == 'o' && matriz[5 + 12][10 + 21] == 'o' && matriz[5 + 24][10 + 42] == 'o') ||
            (matriz[5][10 + 42] == 'o' && matriz[5 + 12][10 + 42] == 'o' && matriz[5 + 24][10 + 42] == 'o') ||
            (matriz[5 + 24][10] == 'o' && matriz[5 + 24][10 + 21] == 'o' && matriz[5 +24][10 + 42] == 'o') ||
            (matriz[5][10 + 42] == 'o' && matriz[5 + 12][10 + 21] == 'o' && matriz[5 + 24][10] == 'o') ||
            (matriz[5 + 12][10] == 'o' && matriz[5 + 12][10 + 21] == 'o' && matriz[5 + 12][10 + 42] == 'o') ||
            (matriz[5][10 + 21] == 'o' && matriz[5 + 12][10 + 21] == 'o' && matriz[5 + 24][10 + 21] == 'o'))
    {
        attron(A_UNDERLINE);
        mvprintw(l/2,c/2 - 15,"O JOGADOR DO O GANHOU!!!PARABENS OTARIO!");
        mvprintw(l/2 + 2,c/2 - 15,"PARA JOGAR NOVAMENTE APERTE ENTER, PARA SAIR APERTE B");
        r = getch();
        switch(r)
         {
            case 10:
                refresh();
                clear();
                refresh();
                go[0] = go[0] + 1;
                jogo(gx,go);
                break;
            case 'b':
                *teste = 1;
                break;
            default:
                refresh();
                ganhou(il,ic,teste,gx,go);
                break;

        }
    }
    if((matriz[5][10] != ' ' && matriz[5][10] != '@') && (matriz[5][10 + 21] != ' ' && matriz[5][10 + 21] != '@') && (matriz[5][10 + 42] != ' ' && matriz[5][10 + 42]!= '@') &&
            (matriz[5+ 12][10] != ' ' && matriz[5 + 12][10] != '@') && (matriz[5 + 12][10 + 21] != ' ' && matriz[5 + 12][10 + 21]!= '@' ) && (matriz[5 + 12][10 + 42] != ' ' && matriz[5 + 12][10 + 42] != '@') &&
            (matriz[5 + 24][10] != ' ' && matriz[5 + 24][10] != '@') && (matriz[5 + 24][10 + 21] != ' '&& matriz[5 + 24][10 + 21] != '@') && (matriz[5 + 24][10 + 42] != ' ' && matriz[5 + 24][10 + 42] != '@'))
    {
        attron(A_UNDERLINE);
        mvprintw(l/2,c/2 - 15,"DEU VELHA!PARABENS OTARIOS!");
        mvprintw(l/2 + 2,c/2 - 15,"PARA JOGAR NOVAMENTE APERTE ENTER, PARA SAIR APERTE B");
        r = getch();
        switch(r)
        {
            case 10:
                refresh();
                clear();
                refresh();
                go[0] = go[0];
                gx[0] = gx[0];
                jogo(gx,go);
                break;
            case 'b':
                *teste = 1;
                break;
            default:
                refresh();
                ganhou(il,ic,teste,gx,go);
                break;

        }

    }
    attroff(A_UNDERLINE);

}

/************************************************************************************************
 *funcao que colocará pra mim, as coisas no tabuleiro, como #,x,etc.*/

void coloca(void)
{
    int i,j;

    for(i = 0;i < MAX;i++)
    {
        for(j = 0;j < MAX + 30;j++)
        {
            if(matriz[i][j] == '@')
                matriz[i][j] = '@';
            else
            {


                if(j == 0 || i == 0 || j == MAX + 29 || i == MAX - 1)
                {
                    matriz[i][j] = '#';
                }
                else
                {
                    if(i == 11 || i == 22)
                        matriz[i][j] = '-';
                    else
                    {
                        if(j == 21 || j == 42)
                            matriz[i][j] = '|';
                        else
                            matriz[i][j] = ' ';
                    }
                }
            }
        }


    }
    refresh();
}

/************************************************************************************************
 *funcao das cores*/

void cores(void)
{
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
}

/************************************************************************************************
 *funcao que printa o tabuleiro*/

void print(void)
{
    int i,j,l,c;

    getmaxyx(stdscr,l,c);

    attron(COLOR_PAIR(1));
    for(i = 0;i < MAX;i++)
    {
        for(j = 0;j < MAX + 30;j++)
        {
            if(matriz[i][j] == '@')
            {
                attron(A_REVERSE);
                mvprintw(l/2 - 19 + i,c/2 - 30 + j,"%c",matriz[i][j]);
                attroff(A_REVERSE);
            }
            else
            {
                if(matriz[i][j] == 'x')
                {
                    attron(COLOR_PAIR(2) | A_REVERSE);
                    mvprintw(l/2 - 19 + i,c/2 - 30 + j,"%c",matriz[i][j]);
                    attroff(COLOR_PAIR(2) | A_REVERSE);
                }
                else
                {
                    if(matriz[i][j] == 'o')
                    {
                        attron(COLOR_PAIR(3) | A_REVERSE);
                        mvprintw(l/2 -19 + i,c/2 - 30 + j,"%c",matriz[i][j]);
                        attroff(COLOR_PAIR(3) | A_REVERSE);
                    }
                    else
                    {
                        attron(COLOR_PAIR(1));
                        mvprintw(l/2 - 19 + i,c/2 - 30 + j,"%c",matriz[i][j]);
                    }
                }
            }
        }
        refresh();
    }
}
