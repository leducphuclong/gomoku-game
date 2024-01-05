#pragma once
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <tuple>
#include "const.h"
class Material {
        public:
                static void display_o(float x, float y);
                static void display_x(float x, float y);
                static void display_circle(float cx, float cy, float r, int num_segments);
                static void rect(float , float, float, float);
                static void convert(double &x, double&y);
                static void getXY01(double&, double &);
                static void display_table(double, double, double , double, int table[2*N][2*N]);
                static void display_matrix(int table[2*N][2*N], double, double);
};
