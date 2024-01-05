// g++ -std=c++11 "main 2.cpp" game.cpp -o main -L/usr/local/lib -lglfw -framework OpenGL -I/opt/local/include -I/usr/local/opt/freetype/include/freetype2 -I/usr/local/opt/libpng/include/libpng16 && ./main
#pragma once
#include <tuple>
const int ZOOM = 3;
const int n = 5;
const int N = ZOOM * n;
const int NUMBER_BLOCK_TRANSITION = n * 2 * (ZOOM / 2);
const int HEIGHT = 680;
const int WIDTH = 680;
const double SQ = WIDTH;
const float scale = 0.8; // full screen IF 1
const float a_square = scale / n;
const float A02 = 0.2 * SQ / 2;
const float a = a_square * SQ / 2;
const int SHUNEO = 1;
const int GUEST = 2;
const int BLANK = 0;
const int DRAW = -1;

const float LIMIT = a_square * (2 * NUMBER_BLOCK_TRANSITION);
const int hor_x[] = {-1, 1};
const int hor_y[] = {0, 0}; 
const int ver_x[] = {0, 0};
const int ver_y[] = {-1, 1} ;
const int diag1_x[] = {-1, 1};
const int diag1_y[] = {-1, 1};
const int diag2_x[] = {-1, 1};
const int diag2_y[] = {1, -1};

const std::tuple<float, float, float> COLOR_X = {1, 0, 0};
const std::tuple<float, float, float> COLOR_O = {0, 0, 1};
const std::tuple<float, float, float> COLOR_TABLE = {0.5, 0.5, 0.5};
const int SIZE_LINE_COMMON = 4;
const int SIZE_X = SIZE_LINE_COMMON;
const int SIZE_LINE_TABLE = SIZE_LINE_COMMON;
const int SIZE_LINE_O = SIZE_LINE_COMMON;
const float RATIO_X = 0.3;
const float RATIO_O = 0.4;
const int NUM_SEGMENTS = 200;
