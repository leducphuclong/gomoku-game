// thought
// 1. lợi trước mắt
// 2. có nhiều điểm đặt đươc cái lợi trước mắt -> tìm xem những cái lợi đó đã bị chặn hay chưa
// 3. xét đến tiềm năng của điểm đánh được -> so sánh điểm tiềm năng
//
//#pragma once
#include "game.h"
#include <bits/stdc++.h>
using namespace std;
Game::Game() {
        cout << "creating game\n";
        turn = GUEST;
        player[0] = GUEST;
        player[1] = SHUNEO;
        playerWin = BLANK;
        status = new int*[2*N];
        for (int i = 0; i < 2*N; ++i) {
                status[i] = new int[2*N];
                for (int j = 0;j < 2*N; ++j) status[i][j] = BLANK;
        }
}
Game::~Game() {
        for (int i = 0; i < 2*N; ++i) {
                delete[] status[i];
        }
        delete[] status;
}
int cal(int x, int y, int type, int **status) {
        int cntx = 0, cnty = 0, cnt1 = 0, cnt2 = 0;
        for (int i = x+1, j = y; i < 2*N && status[i][j] == type; ++i) cntx ++;
        for (int i = x-1, j = y; i >= 0 && status[i][j] == type; --i) cntx ++;

        for (int i = x, j = y + 1; j < 2*N && status[i][j] == type; ++j) cnty ++;
        for (int i = x, j = y - 1; j >= 0 && status[i][j] == type; --j) cnty ++;

        for (int i = x + 1, j = y + 1; i < 2*N && j < 2*N && status[i][j] == type; ++i, ++j) cnt1 ++;
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0 && status[i][j] == type; --i, --j) cnt1 ++;

        for (int i = x + 1, j = y - 1; i < 2*N && j >= 0 && status[i][j] == type; ++i, --j) cnt2 ++;
        for (int i = x - 1, j = y + 1; i >= 0 && j < 2*N && status[i][j] == type; --i, ++j) cnt2 ++;
        return max({cntx, cnty, cnt1, cnt2}) + 1;
}

int Game::specialCheking(int x, int y, int cnt, int id) {
        if (cnt == 5) return true;
        if (cnt == 4){
                // checking hoi bi ngu ti
                // 
                if (id == 1) {
                        if (x + 5 <= 2 * N && status[x+4][y] == BLANK && x - 1 >= 0 && status[x-1][y] == BLANK) return 1;
                }
                if (id == 2) {
                        if (y + 5 <= 2 * N && status[x][y+4] == BLANK && y - 1 >= 0 && status[x][y-1] == BLANK) return 1;
                }
                if (id == 3) {
                        if (x > 0 && y > 0 && status[x-1][y-1] == BLANK && x + 5 <= 2*N && y + 5 <= 2*N && status[x+4][y+4] == BLANK) return true;        
                }
                if (id == 4) { 
                        if (x > 0 && y + 1 < 2 * N && status[x-1][y+1] == BLANK&& y - 4 >= 0 && x + 5 <= 2*N && status[x+4][y-4] == BLANK) return 1;
                }
        }       

        return 0;
}
int Game::checking(int x, int y) {
        int flag = 0;
        // choking in line x_axis
        int cnt_x_axis = 0;
        int cnt_y_axis = 0;
        int cnt_diag1 = 0;
        int cnt_diag2 = 0;
        for (int i = x; x + 5 <= 2 * N && i < x + 5 && status[x][y] == status[i][y]; ++i, cnt_x_axis ++);
        for (int i = y; y + 5 <= 2 * N && i < y + 5 && status[x][y] == status[x][i]; ++i, cnt_y_axis ++);
        for (int i = x, j = y; x + 5 <= 2 * N && y + 5 <= 2 * N && i < x + 5 && j < y + 5 && status[x][y] == status[i][j]; ++i, ++j, ++cnt_diag1);
        for (int i = x, j = y; x + 5 <= 2 * N && y - 5 >= -1 && i < x + 5 && j > y - 5 && status[x][y] == status[i][j]; ++i, --j, ++cnt_diag2);
        // important note: xxx_xxx, give one BLANK in middle, that makes a chain 7x
        // actually, if x create a chain with 3sequences, that being blocked before

        if (cnt_x_axis > 5 || ((x > 0 && status[x-1][y] == BLANK ) || (x + 5 < 2*N && status[x+5][y] == BLANK)) && specialCheking(x, y, cnt_x_axis, 1)) return 1;
        if (cnt_y_axis > 5 || ((y > 0 && status[x][y-1] == BLANK ) || (y + 5 < 2*N && status[x][y+5] == BLANK)) && specialCheking(x, y, cnt_y_axis, 2)) return 1;
        if (cnt_diag1 > 5 || ((x > 0 && y > 0 && status[x-1][y-1] == BLANK) || (x + 5 < 2*N && y + 5 < 2*N && status[x+5][y+5] == BLANK)) && specialCheking(x, y, cnt_diag1, 3)) return 1;
        if (cnt_diag2 > 5 || ((y + 1 < 2*N && x > 0 && status[x-1][y+1] == BLANK) || (y - 5 >= 0 && x + 5 < 2*N && status[x+5][y-5] == BLANK)) && specialCheking(x, y, cnt_diag2, 4)) return 1;
        // fixed above
        return 0;
}

int DRAWChecking(int x, int y, int type, int **status, int counter) {
        int cnt_x_axis = 0; int cnt1=0, cnt2=0, cnt3=0,cnt4=0;
        int cnt_y_axis = 0;
        int cnt_diag1 = 0;
        int cnt_diag2 = 0;
        for (int i = x; x + 5 <= 2 * N && i < x + 5 && (type == status[i][y] || status[i][y] == BLANK); ++i, cnt_x_axis += (status[i][y] == BLANK), cnt1++);
        for (int i = y; y + 5 <= 2 * N && i < y + 5 && (type == status[x][i] || status[x][i] == BLANK); ++i, cnt_y_axis += (status[x][i] == BLANK), cnt2++);
        for (int i = x, j = y; x + 5 <= 2 * N && y + 5 <= 2 * N && i < x + 5 && j < y + 5 && (type == status[i][j] || status[i][j] == BLANK); ++i, ++j, cnt_diag1 += (status[i][j] == BLANK), cnt3++);
        for (int i = x, j = y; x + 5 <= 2 * N && y - 5 >= -1 && i < x + 5 && j > y - 5 && (type == status[i][j] || status[i][j] == BLANK); ++i, --j, cnt_diag2 += (status[i][j] == BLANK), cnt4++);
        return (cnt1 < 5 || cnt_x_axis > counter) && (cnt2 < 5 || cnt_y_axis > counter) && (cnt3 < 5 || cnt_diag1 > counter) && (cnt4 < 5 || cnt_diag2 > counter);
}

bool quickFix(int **table, int turn) {
        int n = 2*N; 
        for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                        if (turn == table[i][j]) {
                                for (int dx = -1; dx <= 1; ++dx) {
                                        for (int dy = -1; dy <= 1; ++dy) {
                                                if (dx == 0 && dy == 0) continue;
                                                int cnt = 0;
                                                for (int x = i, y = j; 0 <= x && x < n && 0 <= y && y < n && turn == table[x][y]; x += dx, y += dy) {
                                                        cnt ++;
                                                }
                                                if (cnt > 4) return 1;
                                        }
                                }
                        }
                }
        }
        return 0;
}

void Game::endOfGame() {
        if (quickFix(status, GUEST)) playerWin = this->turn;
        if (quickFix(status, SHUNEO)) playerWin = this->turn;
        return ;

        int BLANKCells = 0;
        for (int i = 0; i < 2*N; ++i) {
                for (int j = 0; j < 2*N; ++j) {
                        if (status[i][j] == BLANK) BLANKCells ++;
                        if (turn == status[i][j]) {
                                if (checking(i, j)) {
                                        playerWin = turn;
                                        return ;
                                }
                        }           
                }
        }
        for (int i = 0; i < 2*N; ++i) {
                for (int j = 0; j < 2*N; ++j) {
                        if (!DRAWChecking(i, j, GUEST, this->status, BLANKCells / 2)) return ;
                        if (!DRAWChecking(i, j, SHUNEO, this->status, BLANKCells / 2 + BLANKCells % 2)) return ;
                }
        }
        playerWin = DRAW;
}
int Game::who() {
        return playerWin;
}
int Game::theTurn() {
        return turn;
}
void Game::set(int x, int y) {
        status[x][y] = GUEST;
}
void Game::show() {
        for (int i = 0; i < 2*N; ++i) {
                for (int j = 0; j < 2*N; ++j) {
                        cout << status[i][j] << ' ';
                }
                cout << '\n';
        }
}
void Game::setTurn(){

        if (this->turn == SHUNEO) this->turn = GUEST;
        else this->turn = SHUNEO;
}
int Game::isBlank(int x, int y) {
        return status[x][y] == BLANK;
}
int Game::already(int x, int y) {
        return status[x][y] != BLANK;
}
int impossible(int x, int y) {
        return 0 <= x && x < 2*N && 0 <= y && y < 2*N;
}

int checkingTierSplus(int x, int y, int **status, int type, const int dx[], const int dy[], int dddd) {
        int st_x = x, st_y = y, en_x = x, en_y = y;
        status[x][y] = type;
        for (; impossible(en_x, en_y) && status[en_x][en_y] == type; en_x += dx[0], en_y += dy[0]);
        for (; impossible(st_x, st_y) && status[st_x][st_y] == type; st_x += dx[1], st_y += dy[1]);
        status[x][y] = BLANK;
        if ((!impossible(st_x, st_y) || status[st_x][st_y] != BLANK) ^ (!impossible(en_x, en_y) || status[en_x][en_y] != BLANK)) {
                if (max(abs(en_x - st_x), abs(en_y - st_y)) - 1 >= dddd) return 1;
        }
        return 0;
}

int isTierSplus(int x, int y, int **status, int type){
        if (checkingTierSplus(x, y, status, type, hor_x, hor_y, 5)) return 1;
        if (checkingTierSplus(x, y, status, type, ver_x, ver_y, 5)) return 1;
        if (checkingTierSplus(x, y, status, type, diag1_x, diag1_y, 5)) return 1;
        if (checkingTierSplus(x, y, status, type, diag2_x, diag2_y, 5)) return 1;
        return 0;

};

int checkingTierS(int x, int y, int **status, int type, const int dx[], const int dy[], int dddd) {
        int st_x = x, st_y = y, en_x = x, en_y = y;
        status[x][y] = type;
        for (; impossible(en_x, en_y) && status[en_x][en_y] == type; en_x += dx[0], en_y += dy[0]);
        for (; impossible(st_x, st_y) && status[st_x][st_y] == type; st_x += dx[1], st_y += dy[1]);
        status[x][y] = BLANK;
        if ((impossible(st_x, st_y) && status[st_x][st_y] == BLANK) && (impossible(en_x, en_y) && status[en_x][en_y] == BLANK)) 
                if (max(abs(en_x - st_x), abs(en_y - st_y)) - 1 >= dddd) return 1;
        return 0;
}

int isTierS(int x, int y, int **status, int type){
        if (checkingTierS(x, y, status, type, hor_x, hor_y, 4)) return 1;
        if (checkingTierS(x, y, status, type, ver_x, ver_y, 4)) return 1;
        if (checkingTierS(x, y, status, type, diag1_x, diag1_y, 4)) return 1;
        if (checkingTierS(x, y, status, type, diag2_x, diag2_y, 4)) return 1;
        return 0;

}

int resSmall(int x, int y, int **status, int type, int inc_x, int inc_y, int onemore) {
        int cnt = 0;
        status[x][y] = type;
        int ix = x, iy = y;
        for (; impossible(x,y) && (status[x][y] == type || status[x][y] == BLANK && onemore == 1); x += inc_x, y += inc_y) {
                if (status[x][y] == BLANK) onemore --;
                cnt ++;
        }
        status[ix][iy] = BLANK;
        return cnt;
}

int step(int x, int y, int **status, int type, const int dx[], const int dy[]) {
        int res1 = resSmall(x, y, status, type, dx[0], dy[0], 1);
        int res2 = resSmall(x, y, status, type, dx[1], dy[1], 0);
        int res3 = resSmall(x, y, status, type, dx[0], dy[0], 0);
        int res4 = resSmall(x, y, status, type, dx[1], dy[1], 1);
        return max(res1+res2, res3+res4) - 1;
}

int checkChild(int x) {
        return x >= 4;
}
int isTierA(int x, int y, int **status, int type) {
        int res1 = step(x, y, status, type, hor_x, hor_y);
        int res2 = step(x, y, status, type, ver_x, ver_y);
        int res3 = step(x, y, status, type, diag1_x, diag2_y);
        int res4 = step(x, y, status, type, diag2_x, diag2_y);
        if ((checkChild(res1) + checkChild(res2) + checkChild(res3) + checkChild(res4)) >= 2) return 1;
        return 0;
}

int isTierB(int x, int y, int **status, int type) {
        if (checkingTierSplus(x, y, status, type, hor_x, hor_y, 4)) return 1;
        if (checkingTierSplus(x, y, status, type, ver_x, ver_y, 4)) return 1;
        if (checkingTierSplus(x, y, status, type, diag1_x, diag1_y, 4)) return 1;
        if (checkingTierSplus(x, y, status, type, diag2_x, diag2_y, 4)) return 1;
        return 0;

}
int isTierC(int x, int y, int **status, int type) {
        if (checkingTierS(x, y, status, type, hor_x, hor_y, 3)) return 1;
        if (checkingTierS(x, y, status, type, ver_x, ver_y, 3)) return 1;
        if (checkingTierS(x, y, status, type, diag1_x, diag1_y, 3)) return 1;
        if (checkingTierS(x, y, status, type, diag2_x, diag2_y, 3)) return 1;
        return 0;

}
int isTierD(int x, int y, int **status, int type) {
        if (checkingTierS(x, y, status, type, hor_x, hor_y, 2)) return 1;
        if (checkingTierS(x, y, status, type, ver_x, ver_y, 2)) return 1;
        if (checkingTierS(x, y, status, type, diag1_x, diag1_y, 2)) return 1;
        if (checkingTierS(x, y, status, type, diag2_x, diag2_y, 2)) return 1;
        return 0;

}
struct tier {
        int tierSplus=0, tierS=0, tierA=0, tierB=0, tierC=0, tierD=0;
};
void ass(int &a, int i, int j, int**status, int f(int,int,int**, int)) {
        a = max(f(i,j,status, SHUNEO), f(i,j,status, GUEST));
}
bool operator < (const tier A, const tier B) {
        if (A.tierSplus == B.tierSplus) {
                if (A.tierS == B.tierS) {
                        if (A.tierA == B.tierA) {
                                if (A.tierB == B.tierB) {
                                        if (A.tierC == B.tierC) {
                                                return (A.tierD <= B.tierD); 
                                        }
                                        return A.tierC < B.tierC;
                                }
                                return A.tierB < B.tierB;
                        }
                        return A.tierA < B.tierA;
                }
                return A.tierS < B.tierS;
        }
        return A.tierSplus < B.tierSplus;
}
void Game::shuneo_aka_AI(int& x, int& y) { 
        tier best;
        int founded = 0;
        x = 1, y = -1;
        for (int i = 0; i < 2*N; ++i) {
                for (int j = 0; j < 2*N; ++j) {
                        if (status[i][j] == BLANK) {
                                tier curr;
                                ass(curr.tierSplus, i,j,status,isTierSplus);
                                ass(curr.tierS, i,j,status,isTierS);
                                ass(curr.tierA, i,j,status, isTierA);
                                ass(curr.tierB, i,j,status, isTierB);
                                ass(curr.tierC, i,j,status, isTierC);
                                ass(curr.tierD, i,j,status, isTierD);
                                if (founded == 0|| best < curr) {
                                        x = i, y = j;
                                        best = curr;
                                        founded = 1;
                                }
                        }
                }
        }
        if (x != -1 && y != -1)
                status[x][y] = SHUNEO;
        //        srand(time(NULL));
        //        while (true) {
        //                x = rand() % (2*N);
        //                y = rand() % (2*N);
        //                if (status[x][y] == BLANK) {
        //                        this->status[x][y] = SHUNEO;
        //                        break;
        //                }
        //        }
}

