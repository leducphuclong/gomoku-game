
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include "material.h"
#include "Game.h"
#include "Human.h"
#include "AI.h"
#include "../other.h"
#include <chrono>
#include <iomanip>
//#include "const.h"
using namespace std;
using namespace chrono;
// g++ -std=c++11 main.cpp  material.cpp Game.cpp AI.cpp Human.cpp -o game -L/usr/local/lib -lglfw -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./game

Game game;
Human human;
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
        Material::display_table(x, y, deltax, deltay, game.status);
        Material::display_x(x, y);
        Material::display_matrix(game.status, deltax, deltay);
}
void running() {
        if (game.result != BLANK) return ;
        if (game.turn == SHUNEO) {
                game.update(AI::put(game.status));
        } else 
        if (mouse_released == 1) {
                Material::getXY01(xmouse_released, ymouse_released);
                for (int i = 0; i < 2* N; ++i) {
                        for (int j = 0; j < 2 * N; ++j) {
                                if (game.status[i][j] != BLANK) continue;
                                double x, y;
                                x = i * a_square + a_square/2;
                                x = -x; 
                                y =  j * a_square + a_square / 2;
                                if (theCheckMain(x, y, deltax, deltay)) {
                                        //cout << "used\n" << i << ' ' << j << endl;
                                        //cout << i << ' ' << j << ' ' << x << ' ' << xmouse_released << ' ' << y << ' ' << ymouse_released << endl;
                                        if (fabs(x - xmouse_released) <= a_square / 2 && fabs(y - ymouse_released) <= a_square / 2) {
                                                human.get(make_pair(i, j));
                                                game.update(human.put());                                                
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
void centerWindow(GLFWwindow* window) {

    if (window == NULL) {

        return;

    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if (monitor != NULL) {

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);



        if (mode != NULL) {

            int windowWidth, windowHeight;

            glfwGetWindowSize(window, &windowWidth, &windowHeight);

            int xPos = (mode->width - windowWidth) / 2;

            int yPos = (mode->height - windowHeight) / 2;

            glfwSetWindowPos(window, xPos, yPos);

        }

    }

}
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
int main() {
        ifstream inpMatch("./x/idMatch.txt");
        int ID;
        inpMatch >> ID;
        inpMatch.close();
        ofstream outMatch("./x/idMatch.txt");
        outMatch << ++ID;
        outMatch.close();
        string curr_guess;
        ifstream curr_guessFile("./curr_guess.txt");
        curr_guessFile >> curr_guess;
        curr_guessFile.close();

        ofstream seeFile("./see.txt");
        seeFile << "curr_user_name:: " << curr_guess << endl;

        // seeFile << "line3: " << line << endl;
        seeFile.close();

        // auto start = std::chrono::high_resolution_clock::now();
        if (!glfwInit()) {
                return -1;
        }
        GLFWwindow* window = glfwCreateWindow(HEIGHT, WIDTH, "CARO", NULL, NULL);
        if (!window) {
                glfwTerminate();
                return -1;
        }
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwMakeContextCurrent(window);
        glfwSetCharCallback(window, character_callback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCursorPosCallback    ( window, cursor_position_callback); 
        double lastTime = glfwGetTime();
        double x = glfwGetTime();
        centerWindow(window);
        glfwSetWindowSizeLimits(window, HEIGHT, WIDTH, HEIGHT, WIDTH);
        while (!glfwWindowShouldClose(window)) {
                if (game.result == DRAW) {
                //       continue; 
                }
                if (game.result == SHUNEO) {
                        cout << "shuneo\n";
                //        continue;
                        
                        break;
                }
                if (game.result == GUEST) {
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
                if (game.result == BLANK) running();
        }
        double y = glfwGetTime() - x;
        ofstream out("./x/Match.txt", ios :: app);
        string c = currentDateTime();
        out << ID << '\n' << curr_guess << '\n' << (game.result == SHUNEO ? "LOSE" : "WIN");
        out << '\n' << c << '\n' << y << endl;
        out.close();
        if (game.result == GUEST) {
                ifstream check("./best player.txt");
                int t;
                check >> t;
                check.close();
                if (t > y) {
                        ofstream check("./best player.txt");
                        check << y << endl;
                        check << "player " + curr_guess + ": " << y << " at " << c;
                        check.close();
                }
        }
        
        

        glfwTerminate();
        glfwDestroyWindow(window);
        //if (game.playerWin == SHUNEO) 
        if (game.result == SHUNEO) 
                system("./lose");
        else if (game.result == GUEST)
                system("./victory");

        // auto end = std::chrono::high_resolution_clock::now();

        // ifstream seeFile("../see.txt");
        // // Calculate the duration

        // auto duration = duration_cast<seconds>(end - start);

        // // Extract minutes and seconds from the duration
        // auto minutes = duration_cast<std::chrono::minutes>(duration);
        // auto remaining_seconds = duration_cast<std::chrono::seconds>(duration - minutes);


        // // Output the formatted time
        // cout << "Execution time: " << setfill('0') << setw(2) << minutes.count() << ":" << setw(2) << remaining_seconds.count() << endl;
        // seeFile.close();

        return 0;
}
