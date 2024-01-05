#include "material.h"
//#include "const.h"
#include <tuple>
#include <iostream>
#include <math.h>
void Material::display_o(float x, float y) {
        //std::cout << x << ' ' << y << std::endl;
        //std::cout << "O\n";
        float red, green, blue;
        std::tie(red, green, blue) = COLOR_O;
        // glColor3f(red, green, blue);
        glColor3ub(0, 0, 0);
        display_circle(x, y, a_square * RATIO_O, NUM_SEGMENTS);
}
bool check(double x, double y) {
        return -scale <= x && x <= scale && -scale <= y && y <= scale;
}
void Material::display_x(float x,float y) {
        //std::cout << "x\n";
        float red, green, blue;
        std::tie(red, green, blue) = COLOR_X;
        //glColor3f(red, green, blue);
        float halfLength = a_square * RATIO_X;
        glColor3ub(0, 0, 0);

        glBegin(GL_LINES);
        if (check(x - halfLength, y + halfLength)) glVertex2f(x - halfLength, y + halfLength);
        if (check(x + halfLength, y - halfLength)) glVertex2f(x + halfLength, y - halfLength);
        glEnd();
        glBegin(GL_LINES);
        if (check(x - halfLength, y - halfLength)) glVertex2f(x - halfLength, y - halfLength);
        if (check(x + halfLength, y + halfLength)) glVertex2f(x + halfLength, y + halfLength);
        glEnd();
}
void Material::display_circle(float cx, float cy, float r, int num_segments) {
        float theta = 3.1415926 * 2 / num_segments;
        glBegin(GL_LINE_LOOP);
        double R = r;
        for (int ii = 0; ii < num_segments; ii++)
        {
                float x_axis = R * cos(theta * ii) + cx;
                float y_axis = R * sin(theta * ii) + cy;
                if (-scale <= x_axis && x_axis <= scale && -scale <= y_axis && y_axis <= scale) 
                        glVertex2f(x_axis, y_axis);
        }
        glEnd();
}
void Material::convert(double&x, double &y) {
        x = x / HEIGHT;
        y = y / WIDTH;
}
void Material::rect(float below_x, float below_y, float upper_x, float upper_y) {
        //std::cout << "drawing rect\n";
        //       std::cout << x_axis << ' ' << y_axis << std::endl;
        glColor3ub(255, 255, 128);
        glBegin(GL_QUADS);
        /*
           glVertex2f(fmax(x_axis, -scale), fmax(y_axis, -scale));
           glVertex2f(fmin(x_axis + a_square, scale), fmax(y_axis, -scale));
           glVertex2f(fmin(x_axis + a_square, scale), fmin(y_axis + a_square, scale));
           glVertex2f(fmax(x_axis, -scale), fmin(y_axis + a_square, scale));
           */
        glVertex2f(below_x, below_y);
        glVertex2f(upper_x, below_y);
        glVertex2f(upper_x, upper_y);
        glVertex2f(below_x, upper_y);
        glEnd();

}
void Material::getXY01(double&xmouse, double&ymouse) {
        xmouse -= HEIGHT / 2;
        ymouse -= WIDTH / 2;
        xmouse /= (HEIGHT / 2);
        ymouse /= (WIDTH / 2);
        ymouse = -ymouse;

}
bool theCheck(double& x, double& y, double deltax, double deltay) {
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
void Material::display_table(double xmouse, double ymouse, double deltax, double deltay, int table[2*N][2*N]) {
        float red, green, blue;
        std::tie(red, green, blue) = COLOR_TABLE;
        glColor3f(red, green, blue);
        // make 4 main points corner
        glLineWidth(5);
        glColor3ub(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-scale, scale);
        glVertex2f(scale, scale);
        glVertex2f(scale, -scale);
        glVertex2f(-scale, -scale);
        glEnd();
        glLineWidth(2);
        //Material::getXY01(xmouse, ymouse);
        //std::cout << xmouse << ' ' << ymouse << std::endl;
        float below_y = -scale, below_x = -scale;
        float upper_x = scale, upper_y = scale;
        for (int i = -n - 1; i <= n + 1; ++i) {
                float x_axis_left = -scale;
                float x_axis_right = scale;
                float y_axis = i * a_square + deltay;                
                y_axis -= int(y_axis / (2 * scale)) * (2 * scale);
                if (y_axis > scale) y_axis -= 2 * scale;
                if (y_axis < -scale) y_axis += 2 * scale;
                glBegin(GL_LINES);
                glVertex2f(x_axis_left, y_axis);
                glVertex2f(x_axis_right, y_axis);
                glEnd();
                if (ymouse > y_axis) below_y = fmax(below_y, y_axis);                
                if (ymouse < y_axis) upper_y = fmin(upper_y, y_axis);                                
        }
        for (int i = -n - 1; i <= n + 1; ++i) {
                float y_axis_bot = -scale;
                float y_axis_top = scale;
                float x_axis = i * a_square + deltax;                
                x_axis -= int(x_axis / (2 * scale)) * (2 * scale);
                if (x_axis > scale) x_axis -= 2 * scale;
                if (x_axis < -scale) x_axis += 2 * scale;
                glBegin(GL_LINES);
                glVertex2f(x_axis, y_axis_bot);
                glVertex2f(x_axis, y_axis_top);
                glEnd();
                if (xmouse > x_axis) below_x = fmax(below_x, x_axis);                
                if (xmouse < x_axis) upper_x = fmin(upper_x, x_axis);                

        }
        if (-scale <= xmouse && xmouse <= scale && -scale <= ymouse && ymouse <= scale) {
                for (int i = 0; i < 2* N; ++i) {
                        for (int j = 0; j < 2 * N; ++j) {
                                if (table[i][j] != 0) continue;
                                double x, y;
                                x = i * a_square + a_square/2;
                                x = -x; 
                                y =  j * a_square + a_square / 2;

                                if (theCheck(x, y, deltax, deltay) || 1) {
                                        if (fabs(x - xmouse) <= a_square / 2 && fabs(y - ymouse) <= a_square / 2) {
                                                Material::rect(below_x, below_y, upper_x, upper_y);

                                        }

                                }

                        }
                }
        }

}

void Material::display_matrix(int table[2*N][2*N], double deltax, double deltay) {
        for (int i = 0; i < 2* N; ++i) {
                for (int j = 0; j < 2 * N; ++j) {
                        double x, y;
                        x = i * a_square + a_square/2;
                        x = -x; 
                        y =  j * a_square + a_square / 2;

                        if (theCheck(x, y, deltax, deltay)) {
                                if (table[i][j] == GUEST) Material::display_x(x, y);
                                if (table[i][j] == SHUNEO) Material::display_o(x, y);
                        }

                }
        }
}
