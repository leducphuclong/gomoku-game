#include "Game.h"
Game::Game(int turn) : turn(turn) {
    this->status = new int*[2*N];
    for (int i = 0; i < 2*N; ++i) {
        this->status[i] = new int[2*N];
        for (int j = 0; j < 2*N; ++j) {
            this->status[i][j] = BLANK;
        }
    }
    this->result = BLANK;
    moves = 0;
}
Game::~Game() {
    for (int i = 0; i < 2*N; ++i) {
        delete[] this->status[i];
    }
    delete[] this->status;
}
// int cal(int x, int y, int type, int **status) {
//         int cntx = 0, cnty = 0, cnt1 = 0, cnt2 = 0;
//         for (int i = x+1, j = y; i < 2*N && status[i][j] == type; ++i) cntx ++;
//         for (int i = x-1, j = y; i >= 0 && status[i][j] == type; --i) cntx ++;

//         for (int i = x, j = y + 1; j < 2*N && status[i][j] == type; ++j) cnty ++;
//         for (int i = x, j = y - 1; j >= 0 && status[i][j] == type; --j) cnty ++;

//         for (int i = x + 1, j = y + 1; i < 2*N && j < 2*N && status[i][j] == type; ++i, ++j) cnt1 ++;
//         for (int i = x - 1, j = y - 1; i >= 0 && j >= 0 && status[i][j] == type; --i, --j) cnt1 ++;

//         for (int i = x + 1, j = y - 1; i < 2*N && j >= 0 && status[i][j] == type; ++i, --j) cnt2 ++;
//         for (int i = x - 1, j = y + 1; i >= 0 && j < 2*N && status[i][j] == type; --i, ++j) cnt2 ++;
//         int a = cntx < cnty ? cnty : cntx;
//         int b = cnt1 < cnt2? cnt2: cnt1;
//         return a < b? b + 1 : a + 1;
// }

// int specialCheking(int **status, int x, int y, int cnt, int id) {
//         if (cnt == 5) return true;
//         if (cnt == 4){
//                 // checking hoi bi ngu ti
//                 // 
//                 if (id == 1) {
//                         if (x + 5 <= 2 * N && status[x+4][y] == BLANK && x - 1 >= 0 && status[x-1][y] == BLANK) return 1;
//                 }
//                 if (id == 2) {
//                         if (y + 5 <= 2 * N && status[x][y+4] == BLANK && y - 1 >= 0 && status[x][y-1] == BLANK) return 1;
//                 }
//                 if (id == 3) {
//                         if (x > 0 && y > 0 && status[x-1][y-1] == BLANK && x + 5 <= 2*N && y + 5 <= 2*N && status[x+4][y+4] == BLANK) return true;        
//                 }
//                 if (id == 4) { 
//                         if (x > 0 && y + 1 < 2 * N && status[x-1][y+1] == BLANK&& y - 4 >= 0 && x + 5 <= 2*N && status[x+4][y-4] == BLANK) return 1;
//                 }
//         }       

//         return 0;
// }
// int checking(int **status, int x, int y) {
//         int flag = 0;
//         // choking in line x_axis
//         int cnt_x_axis = 0;
//         int cnt_y_axis = 0;
//         int cnt_diag1 = 0;
//         int cnt_diag2 = 0;
//         for (int i = x; x + 5 <= 2 * N && i < x + 5 && status[x][y] == status[i][y]; ++i, cnt_x_axis ++);
//         for (int i = y; y + 5 <= 2 * N && i < y + 5 && status[x][y] == status[x][i]; ++i, cnt_y_axis ++);
//         for (int i = x, j = y; x + 5 <= 2 * N && y + 5 <= 2 * N && i < x + 5 && j < y + 5 && status[x][y] == status[i][j]; ++i, ++j, ++cnt_diag1);
//         for (int i = x, j = y; x + 5 <= 2 * N && y - 5 >= -1 && i < x + 5 && j > y - 5 && status[x][y] == status[i][j]; ++i, --j, ++cnt_diag2);
//         // important note: xxx_xxx, give one BLANK in middle, that makes a chain 7x
//         // actually, if x create a chain with 3sequences, that being blocked before

//         if (cnt_x_axis > 5 || ((x > 0 && status[x-1][y] == BLANK ) || (x + 5 < 2*N && status[x+5][y] == BLANK)) && specialCheking(status, x, y, cnt_x_axis, 1)) return 1;
//         if (cnt_y_axis > 5 || ((y > 0 && status[x][y-1] == BLANK ) || (y + 5 < 2*N && status[x][y+5] == BLANK)) && specialCheking(status, x, y, cnt_y_axis, 2)) return 1;
//         if (cnt_diag1 > 5 || ((x > 0 && y > 0 && status[x-1][y-1] == BLANK) || (x + 5 < 2*N && y + 5 < 2*N && status[x+5][y+5] == BLANK)) && specialCheking(status, x, y, cnt_diag1, 3)) return 1;
//         if (cnt_diag2 > 5 || ((y + 1 < 2*N && x > 0 && status[x-1][y+1] == BLANK) || (y - 5 >= 0 && x + 5 < 2*N && status[x+5][y-5] == BLANK)) && specialCheking(status, x, y, cnt_diag2, 4)) return 1;
//         // fixed above
//         return 0;
// }

// int DRAWChecking(int x, int y, int type, int **status, int counter) {
//         int cnt_x_axis = 0; int cnt1=0, cnt2=0, cnt3=0,cnt4=0;
//         int cnt_y_axis = 0;
//         int cnt_diag1 = 0;
//         int cnt_diag2 = 0;
//         for (int i = x; x + 5 <= 2 * N && i < x + 5 && (type == status[i][y] || status[i][y] == BLANK); ++i, cnt_x_axis += (status[i][y] == BLANK), cnt1++);
//         for (int i = y; y + 5 <= 2 * N && i < y + 5 && (type == status[x][i] || status[x][i] == BLANK); ++i, cnt_y_axis += (status[x][i] == BLANK), cnt2++);
//         for (int i = x, j = y; x + 5 <= 2 * N && y + 5 <= 2 * N && i < x + 5 && j < y + 5 && (type == status[i][j] || status[i][j] == BLANK); ++i, ++j, cnt_diag1 += (status[i][j] == BLANK), cnt3++);
//         for (int i = x, j = y; x + 5 <= 2 * N && y - 5 >= -1 && i < x + 5 && j > y - 5 && (type == status[i][j] || status[i][j] == BLANK); ++i, --j, cnt_diag2 += (status[i][j] == BLANK), cnt4++);
//         return (cnt1 < 5 || cnt_x_axis > counter) && (cnt2 < 5 || cnt_y_axis > counter) && (cnt3 < 5 || cnt_diag1 > counter) && (cnt4 < 5 || cnt_diag2 > counter);
// }

// bool quickFix(int **table, int turn) {
//         int n = 2*N; 
//         for (int i = 0; i < n; ++i) {
//                 for (int j = 0; j < n; ++j) {
//                         if (turn == table[i][j]) {
//                                 for (int dx = -1; dx <= 1; ++dx) {
//                                         for (int dy = -1; dy <= 1; ++dy) {
//                                                 if (dx == 0 && dy == 0) continue;
//                                                 int cnt = 0;
//                                                 for (int x = i, y = j; 0 <= x && x < n && 0 <= y && y < n && turn == table[x][y]; x += dx, y += dy) {
//                                                         cnt ++;
//                                                 }
//                                                 if (cnt > 4) return 1;
//                                         }
//                                 }
//                         }
//                 }
//         }
//         return 0;
// }
#include <iostream>
using namespace std;
int final(int **status, int blanks, int turn) {
        int opponent = turn == SHUNEO? GUEST : SHUNEO;
        int isDraw = DRAW;
        for (int i = 0; i < 2*N; ++i) {
                for (int j = 0; j < 2*N; ++j) {
                        for (int x = -1; x <= 1; ++x) {
                                for (int y = -1; y <= 1; ++y) {
                                        if (x == 0 && y == 0) continue;
                                        if (i + 5 * x > 2 * N || i + 5 * x < -1 || j + 5 * y > 2 * N || j + 5 * y < -1) continue;
                                        int countTurn = 0;
                                        int countBlank = 0;
                                        for (int t = 0; t < 5; ++t) {
                                                int curx = i + t * x;
                                                int cury = j + t * y;
                                                if (status[curx][cury] == turn) countTurn ++;
                                                if (status[curx][cury] == BLANK) countBlank ++ ;
                                        }
                                        int base = turn;
                                        if (countTurn == 5) {
                                                if (0 <= i-x && i-x < 2*N && 0 <= j-y && j-y < 2*N && (status[i-x][j-y] == base || status[i-x][j-y] == BLANK)) return turn;
                                                if (0 <= i+5*x && i+5*x < 2*N && 0 <= j+5*y && j+5*y < 2*N && (status[i+5*x][j+5*y] == base || status[i+5*x][j+5*y] == BLANK)) return turn;
                                        }
                                        if (isDraw == BLANK) continue;
                                        if (countBlank > blanks / 2) continue;
                                        if (countTurn + countBlank == 5) {
                                                if (0 <= i-x && i-x < 2*N && 0 <= j-y && j-y < 2*N && (status[i-x][j-y] == base || (status[i-x][j-y] == BLANK && countBlank + 1 <= blanks / 2))) isDraw = BLANK;
                                                if (0 <= i+5*x && i+5*x < 2*N && 0 <= j+5*y && j+5*y < 2*N && (status[i+5*x][j+5*y] == base || (status[i+5*x][j+5*y] == BLANK && countBlank + 1 <= blanks / 2))) isDraw = BLANK;
                                        }
                                        if (countTurn == 0) {
                                                if (0 <= i-x && i-x < 2*N && 0 <= j-y && j-y < 2*N && (status[i-x][j-y] == opponent || (status[i-x][j-y] == BLANK && countBlank + 1 <= (blanks + 1) / 2))) isDraw = BLANK;
                                                if (0 <= i+5*x && i+5*x < 2*N && 0 <= j+5*y && j+5*y < 2*N && (status[i+5*x][j+5*y] == opponent || (status[i+5*x][j+5*y] == BLANK && countBlank + 1 <= (blanks + 1) / 2))) isDraw = BLANK;
                                        }
                                }
                        }                        
                }
        }
        return isDraw;
}
void Game::update(pair<int,int> position) {
    this->moves ++;
    this->status[position.first][position.second] = turn;
    // update who win
    //if (quickFix(status, this->turn)) this->result = this->turn;
    int blanks = 4 * N * N - this->moves;

    this->result = final(this->status, blanks, this->turn);
    cout << this->result << endl;
    if (this->result != BLANK) return ;
    
    if (this->turn == SHUNEO) this->turn = GUEST;
    else this->turn = SHUNEO;
}