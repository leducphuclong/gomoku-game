#pragma once
#include "const.h"
class Game {
public:
    Game();
    ~Game();
    int specialCheking(int, int , int , int);
    int checking(int, int);
    void endOfGame();
    void shuneo_aka_AI(int&x, int&y);
    int who();
    int theTurn();
    void set(int x, int y);
    void show();
    void setTurn();
    int isBlank(int x, int y);
    int already(int x, int y);
    void setStatus(int table[2*N][2*N]) {
        for (int i = 0; i < 2*N; ++i) {
            for (int j = 0; j < 2*N; ++j) {
                if (status[i][j] = table[i][j]);
            }
        }
    }
//private:
    int playerWin;
    int **status;
    int turn;
    int player[2];
};
