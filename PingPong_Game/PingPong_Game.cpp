#include <iostream>
#include <windows.h>
#include<conio.h>

using namespace std;

#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9


void SetClr(int tcl, int bcl)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}


const int l = 70;
const int h = 20;

// ball properties
int yball;
int xball;
int xvelocity;
int yvelocity;

void gotorowcol(int rpos, int cpos) {
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
}

int b = -37;
void draw_boundaries() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            if (j == 0 || j == l - 1 || i == 0 || i == h - 1) {
                SetClr(GREEN, BLACK);
                cout << char(b);
            }
            else {
                cout << " ";
            }

        }
        cout << endl;
    }


}

void initialize_ball() {
    yball = l / 2;
    xball = h / 2;
    xvelocity = 1;
    yvelocity = 1;
}

void draw_ball(int x, int y) {
    gotorowcol(x, y);
    SetClr(RED, BLACK);
    cout << "O";
    gotorowcol(21, 71);
}
int playerbarheight = 6;
int p1_ybar;
int p2_ybar;

void initialize_bar() {
    p1_ybar = 6;
    p2_ybar = 6;
}

void bounce_ball()
{ // for all 8 directions of ball

    if (xball == 1 && yball == 1) {
        xvelocity = 1;
        yvelocity = 1;
    }
    else if (xball == h - 2 && yball == l - 5) {
        xvelocity = -1;
        yvelocity = -1;
    }
    else if (xball == h - 2 && yball == 1) {
        xvelocity = -1;
        yvelocity = 1;
    }
    else if (xball == 1 && yball == l - 5) {
        xvelocity = 1;
        yvelocity = -1;
    }
    else if (xball == 1 && yball > 0 && yball < l - 5) {
        xvelocity = 1;
    }
    else if (xball == h - 2 && yball > 0 && yball < l - 5) {
        xvelocity = -1;
    }
    else if (yball == 1 && xball > 0 && xball < h - 1) {
        yvelocity = 1;
    }
    else if (yball == l - 2 && xball > 0 && xball < h - 1) {
        yvelocity = -1;
    }
}


char space = ' ';
void move_ball() {
    gotorowcol(xball, yball);
    cout << space;
    xball += xvelocity;
    yball += yvelocity;
    bounce_ball();
    draw_ball(xball, yball);


}

//properties of bar

void draw_bars() {
    for (int i = 1; i <= playerbarheight; i++) {
        gotorowcol(p1_ybar + i, 3);
        cout << char(b);
        gotorowcol(p2_ybar + i, l - 4);
        cout << char(b);
    }
}


void move_bars() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'w':
            if (p1_ybar > 0) {
                gotorowcol(p1_ybar + playerbarheight, 3);
                cout << "  ";
                p1_ybar -= 1;
                for (int i = 1; i <= playerbarheight; i++) {
                    gotorowcol(p1_ybar + i, 3);
                    cout << char(b);
                }
            }
            break;
        case 's':
            if (p1_ybar + playerbarheight < h - 2) {
                gotorowcol(p1_ybar + 1, 3);
                cout << "  ";
                p1_ybar += 1;
                for (int i = 1; i <= playerbarheight; i++) {
                    gotorowcol(p1_ybar + i, 3);
                    cout << char(b);
                }
            }
            break;
        case 'i':
            if (p2_ybar > 0) {
                gotorowcol(p2_ybar + playerbarheight, l - 4);
                cout << "  ";
                p2_ybar -= 1;
                for (int i = 1; i <= playerbarheight; i++) {
                    gotorowcol(p2_ybar + i, l - 4);
                    cout << char(b);
                }
            }
            break;
        case 'k':
            if (p2_ybar + playerbarheight < h - 2) {
                gotorowcol(p2_ybar + 1, l - 4);
                cout << "   ";
                p2_ybar += 1;
                for (int i = 1; i <= playerbarheight; i++) {
                    gotorowcol(p2_ybar + i, l - 4);
                    cout << char(b);
                }
            }
            break;
        default:
            gotorowcol(21, 71);
            cout << "Invalid key is pressed";
            break;
        }
    }
}

int hiton() {

    if (yball == 4 && xball > 0 && xball < h - 1) {
        if (xball >= p1_ybar && xball <= p1_ybar + 6) {
            return 1;
        }
    }
    if (yball == l - 5 && xball > 0 && xball < h - 1) {
        if (xball >= p2_ybar && xball <= p2_ybar+6) {
            return 2;
        }
    }
    return 0;
}
void deflection() {
    if (hiton() == 1) {
        if (xball >= p1_ybar && xball < (p1_ybar + playerbarheight - 1) / 3) {
            xvelocity = -1;
            yvelocity = -1;
        }
        if (xball >= (p1_ybar + playerbarheight) / 3 && xball < (p1_ybar + playerbarheight) / 2) {
            xvelocity = -1;
        }
        if (xball >= (p1_ybar + playerbarheight) / 2 && xball < (p1_ybar + playerbarheight)) {
            xvelocity = 1;
            yvelocity = 1;
        }
    }
    if (hiton() == 2) {
        if (xball >= p2_ybar && xball < (p2_ybar + playerbarheight-1) / 3) {
            xvelocity = 1;
            yvelocity = 1;
        }
        if (xball >= (p2_ybar + playerbarheight - 1) / 3 && xball < (p2_ybar + playerbarheight - 1) / 2) {
            xvelocity = 1;
        }
        if (xball >= (p2_ybar + playerbarheight - 1) / 2 && xball < p2_ybar + playerbarheight - 1) {
            xvelocity = -1;
            yvelocity = -1;
        }
    }
}


void score(int score1, int score2) {
    gotorowcol(1, 73);
    cout << "score of player 1:";
    cout << score1;
    if (yball == l - 2 && xball > 0 && xball < h - 1) {
        score1 = score1 + 1;
        cout << score1;
    }
    cout << endl;
    gotorowcol(2, 73);
    cout << "score of player 1:";
    cout << score2;
    if (yball == 1 && xball > 0 && xball < h - 1) {
        score2 = score2 + 1;
        cout << score2;
    }


}
int score1 = 0;
int score2 = 0;

void score() {

    if (yball == 1 && xball > 0 && xball < h - 1) {
        score1++;
    }


    if (yball == l - 2 && xball > 0 && xball < h - 1) {
        score2++;
    }


    gotorowcol(1, 73);
    cout << "Score of player 1: " << score2;
    gotorowcol(2, 73);
    cout << "Score of player 2: " << score1;

}

void pong() {
    gotorowcol(22, 0);
    cout << "     *****  ***  **     *  ******   *****  ****  **     *  ******" << endl;
    cout << "     *   *   *   * *    *  *    *   *   *  *  *  * *    *  *    *" << endl;
    cout << "     *****   *   *  *   *  *        *****  *  *  *  *   *  *     " << endl;
    cout << "     *       *   *   *  *  *  ***   *      *  *  *   *  *  *  ***" << endl;
    cout << "     *       *   *    * *  *    *   *      *  *  *    * *  *    *" << endl;
    cout << "     *      ***  *     **  ******   *      ****  *     **  ******" << endl;
}

int main() {
    initialize_ball();
    draw_boundaries();
    initialize_bar();
    draw_bars();


    while (true) {

        
        move_bars();
        move_ball();
        deflection();
        score();
        pong();
        if (score1 == 5 || score2 == 5) {//do check this one

            gotorowcol(6, 73);
            if (score1 == 5) {
                cout << "Player 1 wins!";

            }
            else {
                cout << "Player 2 wins!";

            }
            break;
        }
        Sleep(100);
    }
    gotorowcol(30, 80);



    return 0;
}