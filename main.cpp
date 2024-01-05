
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include "material.h"
#include "shuneo.h"
#include "game.h"
//#include "const.h"
using namespace std;


Game game;

double deltax = -NUMBER_BLOCK_TRANSITION * a_square, deltay = NUMBER_BLOCK_TRANSITION * a_square;
int turn = GUEST;
//double deltax = 0, deltay = 0;
double xmouse, ymouse;
int mouse_released = 0;
double xmouse_released , ymouse_released;
void character_callback(GLFWwindow* window, unsigned int codepoint) {
        if (codepoint == 'a') deltax -= 0.1;
        if (codepoint == 'd') deltax += 0.1;
        if (deltax < -LIMIT) deltax = -LIMIT;
        if (deltax > 0) deltax = 0;
        if (deltay > LIMIT) deltay = LIMIT;
        if (deltay < 0) deltay = 0;
        if (codepoint == 'o') {
                cout << "pausing\n";
                system("pause");
        }
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                glfwGetCursorPos(window, &xmouse_released, &ymouse_released);
                mouse_released = 1;
        }
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        deltax += xoffset / 10;
        deltay -= yoffset / 10;
        if (deltax < -LIMIT) deltax = -LIMIT;
        if (deltax > 0) deltax = 0;
        if (deltay > LIMIT) deltay = LIMIT;
        if (deltay < 0) deltay = 0;
        //cout << deltax << ' ' << deltay << endl;

}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
        //double xpos, ypos;
        //glfwGetCursorPos(window, &xpos, &ypos);
        //std::cout << "Position: (" << xpos <<":"  << ypos << ")";
}
int table[2*N][2*N];
bool theCheckMain(double& x, double& y, double deltax, double deltay) {
        double rangex = -2 * n * a_square, rangey = 2 * n * a_square;
        //std::cout << deltax << ' ' << deltay << ' ' << deltax + rangex << ' ' << deltay + rangey << std::endl;
        if (deltax + rangex<= x && x <= deltax && deltay <= y && y <= deltay + rangey) {
                //std::cout << "doning\n";
                x = x - (deltax + rangex / 2);
                y = y - (deltay + rangey / 2);
                x = -x;
                y = -y;
                return 1;
        }
        return 0;
}
void render_loop() {
        double x = xmouse, y = ymouse;
        Material::getXY01(x, y);
        //cout << "XY01 " << x << " " <<  y << endl;
        Material::display_table(x, y, deltax, deltay, table);
        Material::display_x(x, y);
        Material::display_matrix(table, deltax, deltay);
}
void running() {
        if (game.playerWin != BLANK) return ;
        if (turn == SHUNEO) {
                game.setStatus(table);

                //pair<int,int> move = Shuneo::giveMeAMove(table);
                pair<int,int> move;
                game.shuneo_aka_AI(move.first, move.second);
                table[move.first][move.second] = SHUNEO;
                turn = GUEST;
        }
        if (mouse_released == 1 && turn == GUEST) {
                Material::getXY01(xmouse_released, ymouse_released);
                cout << "im here\n";
                for (int i = 0; i < 2* N; ++i) {
                        for (int j = 0; j < 2 * N; ++j) {
                                if (table[i][j] != 0) continue;
                                double x, y;
                                x = i * a_square + a_square/2;
                                x = -x; 
                                y =  j * a_square + a_square / 2;
                                if (theCheckMain(x, y, deltax, deltay)) {
                                        //cout << "used\n" << i << ' ' << j << endl;
                                        //cout << i << ' ' << j << ' ' << x << ' ' << xmouse_released << ' ' << y << ' ' << ymouse_released << endl;
                                        if (fabs(x - xmouse_released) <= a_square / 2 && fabs(y - ymouse_released) <= a_square / 2) {
                                                cout << i << ' ' << j << endl;
                                                table[i][j] = GUEST;
                                                turn = SHUNEO;

                                        }

                                }

                        }
                }

                /*
                //mouse_released = 0;
                double mouse_x = xmouse, mouse_y = ymouse;
                Material::convert(mouse_x, mouse_y);
                double x = deltax + mouse_x - (1 - scale) / 2;
                double y = deltay + mouse_y - (1 - scale) / 2;
                //cout << x << ' ' << y << endl;
                */
                mouse_released = 0;
        }
}

int main() {
        cout << a_square << '\n';
        //table[0][0] = SHUNEO;
        //table[4][3] = GUEST;
        //table[4][4] = SHUNEO;
        if (!glfwInit()) {
                return -1;
        }
        GLFWwindow* window = glfwCreateWindow(HEIGHT, WIDTH, "CARO", NULL, NULL);
        if (!window) {
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetCharCallback(window, character_callback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCursorPosCallback    ( window, cursor_position_callback); 
        double lastTime = glfwGetTime();
        game.setStatus(table);
        while (!glfwWindowShouldClose(window)) {
                game.endOfGame();
                if (game.playerWin == DRAW) {
                //       continue; 
                }
                if (game.playerWin == SHUNEO) {
                        cout << "shuneo\n";
                //        continue;
                        
                        break;
                }
                if (game.playerWin == GUEST) {
                        cout << "guest\n";
                        break;
                //        continue;
                }
                double currentTime = glfwGetTime();
                if (currentTime - lastTime > 1.0 / 120 ) {
                        glClearColor(1, 1, 1, 1);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                        glfwGetCursorPos(window, &xmouse, &ymouse);
                        render_loop();


                        glfwSwapBuffers(window);
                        glfwPollEvents();
                        lastTime = currentTime;
                }
                if (game.playerWin == BLANK) running();
        }

        glfwTerminate();
        glfwDestroyWindow(window);
        //if (game.playerWin == SHUNEO) 
        if (game.playerWin == GUEST) 
                system("./lose");
        else if (game.playerWin == SHUNEO)
                system("./victory");
        return 0;
}
