
#include "AI.h"
AI::AI() {

}
AI::~AI() {

}
int max(int a, int b) {
    if (a < b) return b;
    return a;
}
int abs(int a) {
    if (a > 0) return a;
    return -a;
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
pair<int,int> AI::put(int **status) {
    tier best;
    int founded = 0;
    int x = 1, y = -1;
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
    return make_pair(x, y);
}