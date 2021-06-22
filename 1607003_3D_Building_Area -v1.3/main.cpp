
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include <stdlib.h>
#include <stdio.h>

#include <windows.h>
#include<math.h>

#include<bits/stdc++.h>

#include "BmpLoader.h"

#define PI 3.1415927

using namespace std;



/// Initialization

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=800, windowWidth=800;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;



//double ex=18.80, ey=11.80, ez=-14.80, lx=-0.40, ly=1.60, lz=0.80, hx=0, hy=1, hz=0, n=9.40, angleX = 9.60, angleY=19.80, angleZ=12.00; // 5,8,-10, 0,0,0, 0,1,0 x=15, y=30,z=15
//double ex=13.80, ey=16.20, ez=86.20, lx=23.40, ly=3.60, lz=-2.20, hx=0, hy=1, hz=0, n=9.40, angleX = 9.60, angleY=19.80, angleZ=12.00; // 5,8,-10, 0,0,0, 0,1,0 x=15, y=30,z=15

GLfloat ex=97.40, ey=10.20, ez=69.67, lx=82.40, ly=10.20, lz=64.30, hx=0, hy=1, hz=0, n=9.40, angleX = 9.60, angleY=19.80, angleZ=12.00; // 5,8,-10, 0,0,0, 0,1,0 x=15, y=30,z=15

void console_output();

float fan_rot =0.0,fan_speed = 0.2;

float clock_rot1 =0.0, clock_rot2 =0.0, clock_rot3 =0.0;

unsigned int ID[30];


GLfloat angle_second, angle_min,angle_hour;

enum status
{
    off = false, on = true
} lightStatus0=off, lightStatus1 = off, lightStatus2=off, amStatus0=on, amStatus1=on, amStatus2=on, diffStatus0 = on, diffStatus1 = on, diffStatus2 = on, specStatus0 = on, specStatus1 = on, specStatus2 = on;


status fan_flag = off;
status door_open = off;
// No light property
GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

// Light 0 properties
GLfloat light_ambient0[]  = {0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse0[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular0[] = { 1.0, 1.0, 1.0,1.0};
GLfloat light_position0[] = { 0.0, 8.075, -3.175, 1.0};
// Light 1 properties
GLfloat light_ambient1[]  = { 0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse1[]  = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_position1[] = {6.075, 7.075 ,5.0, 1.0}; //5.87

// Light 2 (spotlight) properties
GLfloat light_ambient2[]  = {0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse2[]  = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_position2[] = { 35.0,10.0,15.0, 1.0};
//GLfloat light_position2[] = { 3.0,5.0,-6.0, 1.0};


GLfloat light_position3[] = {0.0, 380 ,0.0, 0.0};
GLfloat light_position4[] = {-20, 200 , 20.0, 0.0};

float coff = 72.0;




static GLfloat v_Cube[8][3] =
{
    {0.0, 0.0, 0.0}, // 1 origin
    {1.0, 0.0, 0.0}, // 2 x
    {0.0, 1.0, 0.0}, // 3 y
    {0.0, 0.0, 1.0}, // 4 z


    {1.0, 1.0, 0.0}, // 5 xy plane
    {0.0, 1.0, 1.0}, // 6 yz plane
    {1.0, 0.0, 1.0}, // 7 zx plane

    {1.0, 1.0, 1.0}  // 8 xyz
};


static GLubyte p_Indices[6][4] =
{

    {0, 3, 6, 1},//{}, // base
    {2, 5, 7, 4}, // top

    {0, 2, 4, 1},//{0, 1, 4, 2}, // back
    {3, 6, 7, 5}, // front

    {6, 1, 4, 7}, // right
    {0, 3, 5, 2} // {0, 2, 5, 3} // left
};


static GLfloat colors[255][4] =
{
    {1.0, 0.0, 0.0,1}, // 0 red
    {0.0, 1.0, 0.0,1}, // 1 green
    {0.0, 0.0, 1.0,1}, // 2 blue
    {0.5, 0.0, 1.0,1}, // 3
    {0.0, 1.0, 0.0,1}, // 4
    {0.0, 1.0, 1.0,1}, // 5
    {0.8, 0.0, 0.0,1}, // 6
    {
        0.34, 0.16, 0.07,1
    }, // 7 bed lower portion
    {
        0.71, 0.11, 0.10,1
    }, // 8 upper bed portion
    {
        0.95, 0.26, 0.20,1
    }, // 9  bed top portion

    {
        0.37, 0.21, 0.69,1
    },  // 10 blanket

    {
        0.98, 0.95, 0.61,1
    },  // 11 balish top
    {
        1.00, 0.52, 0.09,1
    }, // 12 balish side

    {
        0.29, 0.15, 0.09,1
    },  // 13 bed head

    {
        0.47, 0.17, 0.12,1
    }, // 14 lower bed portion design
    {
        0.76, 0.70, 0.64,1
    }, // 15 north wall

    {
        0.51, 0.42, 0.35,1
    }, // 16 north-east wall
    {
        0.40, 0.33, 0.23,1
    }, // 17 east wall 1
    {
        0.78, 0.75, 0.70,1
    }, // 18 east wall 2
    {
        0.14, 0.12, 0.07,1
    }, // 19 wardrobe
    {
        0.15, 0.09, 0.05,1
    }, // 20 wardrobe front
    {
        0.98, 0.97, 0.98,1
    }, // 21 wardrobe handle
    {
        1.00,1.00,1.00,1
    }, // 22 window-outside
    {
        0.60, 0.55, 0.49,1
    }, //23 roof
    {
        0.00,0.00,0.00,1
    }, // 24 pure black
    {
        0.70, 0.70, 0.78,1.0
    }, // 25 floor
    {
        0.50, 0.21, 0.13,1.0
    }, // 26 bed side_table
    {
        0.24, 0.05, 0.04,1.0
    }, // 27 fan-pakha
    {
        0.22, 0.34, 0.37,1.0
    }, // 28 clock frame
    {
        0.91, 0.86, 0.82,1.0
    }, // 29 clock inside
    {
        0.72, 0.58, 0.32,1.0
    } // 30 chester color

};


static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void quad(int c_index,bool surf[], float top_curve =  0.375 ,int plane = 0) //
{
    GLfloat v_quad[8][3];
    if(plane==0)
    {
        GLfloat v_quad1[8][3] = {
    {0.0, 0.0, 0.0}, // 1 origin
    {1.0, 0.0, 0.0}, // 2 x

    {top_curve, 1.0, top_curve}, // 3 y

    {0.0, 0.0, 1.0}, // 4 z


    { 1 - top_curve, 1.0, top_curve}, // 5 xy plane

    {top_curve, 1.0, 1-top_curve}, // 6 yz plane
    {1.0, 0.0, 1.0}, // 7 zx plane

    {1-top_curve, 1.0, 1-top_curve}  // 8 xyz

};
    //v_quad = v_quad1;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<3;j++)
            v_quad[i][j] = v_quad1[i][j];
    }

    }
    if(plane ==1 ){
            GLfloat v_quad1[8][3] = {
    {0.0, 0.0, 0.0}, // 1 origin
    {1.0, 0.0, 0.0}, // 2 x

    {top_curve, 1.0, top_curve}, // 3 y

    {0.0, 0.0, 1.0}, // 4 z


    //{ 1 - top_curve, 1.0, top_curve}, // 5 xy plane
    { 1.0, 1.0, 0.0}, // 5 xy plane
    {top_curve, 1.0, 1-top_curve}, // 6 yz plane
    {1.0, 0.0, 1.0}, // 7 zx plane

    //{1-top_curve, 1.0, 1-top_curve}  // 8 xyz
    {1, 1.0, 1} // 8 xyz
};



        for(int i=0;i<8;i++)
        {
            for(int j=0;j<3;j++)
                v_quad[i][j] = v_quad1[i][j];
        }
    }

if(plane == 2)
{
    GLfloat v_quad1[8][3] = {
    {0.0, 0.0, 0.0}, // 1 origin
    {1.0, 0.0, 0.0}, // 2 x

    //{top_curve, 1.0, top_curve}, // 3 y
    {0.0, 1.0, 0.0}, // 3 y

    {0.0, 0.0, 1.0}, // 4 z


    { 1 - top_curve, 1.0, top_curve}, // 5 xy plane

    //{top_curve, 1.0, 1-top_curve}, // 6 yz plane
    {0.0, 1.0, 1}, // 6 yz plane
    {1.0, 0.0, 1.0}, // 7 zx plane

    {1-top_curve, 1.0, 1-top_curve}  // 8 xyz

};

        for(int i=0;i<8;i++)
        {
            for(int j=0;j<3;j++)
                v_quad[i][j] = v_quad1[i][j];
        }

}




     GLfloat no_mat[] = { 0.0, 0.0, 0.0,1.0};
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5,1.0};
    //GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0,1.0};
    GLfloat mat_shininess[] = {30};  //ns


    //glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);

    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors[index[i]][0]);

//        glMaterialfv( GL_FRONT, GL_AMBIENT, &colors[index[i]][0]);
//        glMaterialfv( GL_FRONT, GL_DIFFUSE, &colors[index[i]][0]);

        glMaterialfv( GL_FRONT, GL_AMBIENT, &colors[c_index][0]);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, &colors[c_index][0]);

        getNormal3p(v_quad[p_Indices[i][0]][0], v_quad[p_Indices[i][0]][1], v_quad[p_Indices[i][0]][2],
                    v_quad[p_Indices[i][1]][0], v_quad[p_Indices[i][1]][1], v_quad[p_Indices[i][1]][2],
                    v_quad[p_Indices[i][2]][0], v_quad[p_Indices[i][2]][1], v_quad[p_Indices[i][2]][2]);

        //for(GLint j =0; j<4; j++)
        //{
            //glVertex3fv(&v_quad[p_Indices[i][j]][0]);
            glVertex3fv(&v_quad[p_Indices[i][0]][0]);
            if(surf[i]==true)
                glTexCoord2f(1,1);

            glVertex3fv(&v_quad[p_Indices[i][1]][0]);
            if(surf[i]==true)
            glTexCoord2f(1,0);

            glVertex3fv(&v_quad[p_Indices[i][2]][0]);
            if(surf[i]==true)
            glTexCoord2f(0,0);

            glVertex3fv(&v_quad[p_Indices[i][3]][0]);
            if(surf[i]==true)
            glTexCoord2f(0,1);

        //}
    }
    glEnd();

}


void cube(int c_index,bool surf[])
{
    //glColor3f(1,0,0);
// int surf_c1, int surf_c2, int surf_c3, int surf_c4, int surf_c5, int surf_c6
//    vector<int> index;
//    index.push_back(surf_c1);
//    index.push_back(surf_c2);
//    index.push_back(surf_c3);
//
//    index.push_back(surf_c4);
//    index.push_back(surf_c5);
//    index.push_back(surf_c6);


    GLfloat no_mat[] = { 0.0, 0.0, 0.0,1.0};
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5,1.0};
    //GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0,1.0};
    GLfloat mat_shininess[] = {30};  //ns


    //glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);

    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3fv(&colors[index[i]][0]);

//        glMaterialfv( GL_FRONT, GL_AMBIENT, &colors[index[i]][0]);
//        glMaterialfv( GL_FRONT, GL_DIFFUSE, &colors[index[i]][0]);

        glMaterialfv( GL_FRONT, GL_AMBIENT, &colors[c_index][0]);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, &colors[c_index][0]);

        getNormal3p(v_Cube[p_Indices[i][0]][0], v_Cube[p_Indices[i][0]][1], v_Cube[p_Indices[i][0]][2],
                    v_Cube[p_Indices[i][1]][0], v_Cube[p_Indices[i][1]][1], v_Cube[p_Indices[i][1]][2],
                    v_Cube[p_Indices[i][2]][0], v_Cube[p_Indices[i][2]][1], v_Cube[p_Indices[i][2]][2]);

        //for(GLint j =0; j<4; j++)
        //{
            //glVertex3fv(&v_Cube[p_Indices[i][j]][0]);
            glVertex3fv(&v_Cube[p_Indices[i][0]][0]);
            if(surf[i]==true)
                //glTexCoord2f(1,1);
                //glTexCoord2f(0,0);
                glTexCoord2f(1,0);

            glVertex3fv(&v_Cube[p_Indices[i][1]][0]);
            if(surf[i]==true)
            //glTexCoord2f(1,0);
            //glTexCoord2f(0,1);
            glTexCoord2f(1,1);

            glVertex3fv(&v_Cube[p_Indices[i][2]][0]);
            if(surf[i]==true)
            //glTexCoord2f(0,0);
            //glTexCoord2f(1,1);
            glTexCoord2f(0,1);


            glVertex3fv(&v_Cube[p_Indices[i][3]][0]);
            if(surf[i]==true)
            //glTexCoord2f(0,1);
            //glTexCoord2f(1,0);
            glTexCoord2f(0,0);

        //}
    }
    glEnd();

}


void cylinder(float radius1,float radius2, float height, float theta_stepsize, float r, float g, float b, bool solid)
{

    //GLfloat no_mat[] = { 0.0, 0.0, 0.0,1};
    GLfloat mat_ambient[] = {r,g,b, 1.0 };
    GLfloat mat_diffuse[] = {r,g,b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0,1.0};
    GLfloat mat_shininess[] = {30};


    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    float x1,y1,x2,y2,x,y;
    float theta = 0.0;

    //theta_stepsize = 0.1;

    int cnt=0;
    vector<float> vf_point;
    // Draw the tube
    glBegin(GL_QUAD_STRIP);

    theta = 0.0;
    while( theta < 2*PI )
    {
//        x = radius * cos(theta);
//        y = radius * sin(theta);

        x1 = radius1 * cos(theta);
        y1 = radius1 * sin(theta);

        x2 = radius2 * cos(theta);
        y2 = radius2 * sin(theta);

        glVertex3f(x1, height,y1);
        glVertex3f(x2,0.0, y2 );


//        glVertex3f(x, height,y);
//        glVertex3f(x,0.0, y );
        theta = theta + theta_stepsize;
        if(cnt<3){
            vf_point.push_back(x1);
            vf_point.push_back(height/2);
            vf_point.push_back(y1);
            cnt++;
        }

    }
    glVertex3f(radius1, height, 0.0);
    glVertex3f(radius2, 0.0, 0.0);

        getNormal3p(vf_point[0],vf_point[1],vf_point[2],vf_point[3],vf_point[4],vf_point[5],vf_point[6],vf_point[7],vf_point[8]);
    glEnd();

    if(solid){
        //the top-circle of cylinder
    cnt =0;
    vf_point.clear();
    glBegin(GL_POLYGON);
    theta = 0.0;
    while( theta < 2*PI )
    {
        x = radius1 * cos(theta);
        y = radius1 * sin(theta);
        glVertex3f(x, height, y);
        theta = theta + theta_stepsize;
        if(cnt<3){
            vf_point.push_back(x);
            vf_point.push_back(height);
            vf_point.push_back(y);
            cnt++;
        }
    }

    glVertex3f(radius1, height, 0.0);
    getNormal3p(vf_point[0],vf_point[1],vf_point[2],vf_point[3],vf_point[4],vf_point[5],vf_point[6],vf_point[7],vf_point[8]);
    glEnd();


    //the bottom-circle of cylinder
    cnt =0;
    vf_point.clear();

    glBegin(GL_POLYGON);
    theta = 0.0;
    while( theta < 2*PI )
    {
        x = radius2 * cos(theta);
        y = radius2 * sin(theta);
        glVertex3f(x, 0, y);
        theta = theta + theta_stepsize;
        if(cnt<3){
            vf_point.push_back(x);
            vf_point.push_back(0);
            vf_point.push_back(y);
            cnt++;
        }
    }
    glVertex3f(radius2, 0.0, 0.0);

    getNormal3p(vf_point[0],vf_point[1],vf_point[2],vf_point[3],vf_point[4],vf_point[5],vf_point[6],vf_point[7],vf_point[8]);

    glEnd();
    }

}


/// end initialization



/// Curve declaration

float wcsClkDn[3],wcsClkUp[3];
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];
int flag=0;



GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info

const int L_bottle=20;
const int L_flwr_con=20;
const int L_flwr = 8;
const int dgre=3;
int ncpt=L_flwr_con+1;
int clikd=0;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;

GLfloat bottle[L_bottle+1][3] =
{
    { 0.0, 0.0, 0.0}, { -0.3, 0.5, 0.0},
    { 0.1, 1.7, 0.0},{ 0.5, 1.5, 0.0},
    {1.0, 1.5, 0.0}, {1.4, 1.4, 0.0},
    {1.8, 0.4, 0.0},{2.2, 0.4, 0.0},
    {2.6, 1.5, 0.0}, {3.0, 1.4, 0.0},
    {3.4, 1.4, 0.0},{3.8, 1.4, 0.0},
    {4.2, 1.0, 0.0},{4.6, 1.0, 0.0},
    {5.0, 1.0, 0.0},{5.4, 1.0, 0.0},
    {5.8, 0.5, 0.0},{6.2, 0.5, 0.0},
    {6.6, 0.5, 0.0},{7.2, 0.2, 0.0},
    {6.8, 0.52, 0.0}
};

GLfloat flwr_con[L_flwr_con+1][3] =
{
    { 0.0, 0.0, 0.0}, { -0.3, 0.5, 0.0},
    { 0.1, 1.7, 0.0},{ 0.5, 1.5, 0.0},
    {1.0, 1.5, 0.0}, {1.4, 1.4, 0.0},
    {1.8, 0.4, 0.0},{2.2, 0.4, 0.0},
    {2.6, 1.5, 0.0}, {3.0, 1.4, 0.0},

    {3.4, 1.4, 0.0}, {3.0, 1.8,0.0}
};


//GLfloat flwr[L_flwr+1][3] ={
//    {0.0, 0.0, 0.0}, {0.15,0.25,0.0},
//    {0.25,0.5,0.0}, {0.35,1.0,0.0},
//    {0.45,0.5,0.0}, {0.5,0.1,0.0},
//    {0.55,0.05,0.0}, {0.57,0.1,0.0},
//    {0.6,0.5,0.0}, {0.7,1.0,0.0},
//    {0.8,0.5,0.0}, {0.9,0.25,0.0},
//    {1.0,0.0,0.0}
//};


GLfloat flwr[L_flwr + 1][3] ={
    {0.0, 0.0, 0.0}, {0.15,0.25,0.0},
    {0.25,0.5,0.0}, {0.35,1.0,0.0},
    {0.45,0.5,0.0}, {0.5,0.1,0.0},
    {0.6,0.05,0.0}, {0.7,0.01,0.0},
    {0.8,0.0,0.0}
};


/// end curve declaration

long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

void BezierCurve ( double t,  float xy[2], GLfloat ctrlpoints[][3], int L)
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

void bottleBezier(GLfloat ctrlpoints[][3], int L, float kr, float kg, float kb )
{


    const GLfloat mat_ambient[]    = { kr, kg, kb, 1.0f};
    const GLfloat mat_diffuse[]    = { kr, kg, kb, 1.0f};

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0,1.0};
    GLfloat mat_shininess[] = {30};

    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy, ctrlpoints, L );
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy, ctrlpoints, L);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {

                    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
                    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);


            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);
            //glTexCoord2f(0,0);

            if(j>0)
            {
                getNormal3p(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);
            //glTexCoord2f(0,1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void showControlPoints(GLfloat ctrlpoints[][3], int L)
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}



/// Text Drawing
void drawText(const char *text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();

    glOrtho(0,800,0,600,-5,5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glLoadIdentity();
        glRasterPos2i(x,y);
        for(int i=0;i<length;i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
        }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}



void drawStrokeText1(string str,int x,int y,int z,float val=1,int col=0)
{
    //char *c;
    glPushMatrix();
    glLineWidth(5);
    glTranslatef(x,y,z);

    //  glRotatef(184,0,1,0);
    //cube(1,col,0,0,1,1);
    glScalef(.004f*val,.004f*val,10);

    for (int c=0; c != str.size(); c++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[c]);
    }
    glPopMatrix();
    //cout<<spt_cutoff<<" "<<l_height<<endl;
}

/// end Text Drawing


/// Surrounding

GLUquadric* sphere;

void glusphereDraw(int id, float radius, int a, int b)
{


    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, ID[id]);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, radius, a, b);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}


void fieldDraw()
{


            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[10]);


    glTranslatef(-200,-3.25,-200.0);
    glScalef(512,2.15,512);
    //glTranslatef(-0.5,-1,-0.5);
    cube(25,surf);
    glPopMatrix();

     glDisable(GL_TEXTURE_2D);
}


void tree()
{
    glPushMatrix();
        glTranslatef(0,25,0);
        glusphereDraw(11,10,7,5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,25,3);
        glusphereDraw(11,8,10,5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,15,-3);
        glusphereDraw(11,5,   10,5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2,17,0);
        glusphereDraw(11,5,   10,5);
    glPopMatrix();

    glPushMatrix();
        cylinder(2,3,  18.0   ,   0.9      ,0.47, 0.30, 0.17,    true);
    glPopMatrix();

    /// branch
    glPushMatrix();
        glTranslatef(0,9,1);
        glRotatef(-100,1,1,0);
        cylinder(1,2,  8.0   ,   0.9      ,0.47, 0.30, 0.17,    true);
    glPopMatrix();
}


void tree2()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();
        glTranslatef(3,0,3);
        cylinder(1,1, 5,     0.1,       0.47, 0.30, 0.17,      true);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[11]);
        glTranslatef(0,4,0);
        glScalef(7,14,7);
        quad(25,surf,0.5,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void road()
{

     /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    /// road
    glPushMatrix();
        glTranslatef(-5,0,40);
        glScalef(1,2,1);
        tree2();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[12]);
        glTranslatef(-300,0,60);
        glScalef(600,1,15);
        cube(17,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[13]);
        glTranslatef(90,0.1,-300);
        glScalef(15,1,600);
        cube(17,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void sr_forest()
{
     /// north-west

    glPushMatrix();
        tree2();
    glPopMatrix();

     glPushMatrix();
        glTranslatef(7,0,0);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-7,0,0);
        glScalef(2,1,1);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10,0,7);
        glScalef(2,2,2);
        tree2();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(10,0,10);
        tree2();
    glPopMatrix();

     glPushMatrix();
        glTranslatef(7,0,7);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-7,0,18);
        glScalef(1,2,1);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10,0,7);
        tree2();
    glPopMatrix();



    for(int i=0;i<100;i+=7)
    {

        if(i%2==0){
            glPushMatrix();
            glTranslatef(-10-i, 0, 10+i);
            glScalef(1,2,2);
            tree();
            glPopMatrix();
        }
        else{
            glPushMatrix();
            glTranslatef(-10-i, 0, 10+i);
            glScalef(2,1,2);
            tree();
            glPopMatrix();
        }

        if(i%2==0){
            glPushMatrix();
            glTranslatef(10+i, 0, -10-i);
            glScalef(2,1,2);
            tree2();
            glPopMatrix();
        }
        else{
            glPushMatrix();
            glTranslatef(10+i, 0, -10-i);
            glScalef(2,2,2);
            tree2();
            glPopMatrix();
        }


        if(i%2==0){
            glPushMatrix();
            glTranslatef(-10-i, 0, 14+i);
            glScalef(1,2,1);
            tree2();
            glPopMatrix();
        }
        else{
            glPushMatrix();
            glTranslatef(-10-i, 0, 14+i);
            //glScalef(1,2,1);
            tree2();
            glPopMatrix();
        }

        glPushMatrix();
            glTranslatef(14+i, 0, -10-i);
            glScalef(1,2,2);
            tree();
        glPopMatrix();
    }


    /// end north-west
}


void sr_garden()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

        for(int i=0;i<200;i+=9)
        {
            if(i%2==0){
                glPushMatrix();
                glTranslatef(0,0,7+i);
                glScalef(1,2,1);
                tree2();
            glPopMatrix();
            }
            else{
                glPushMatrix();
                glTranslatef(0,0,7+i);
                glScalef(1,2,1);
                tree();
                glPopMatrix();
            }

        }

    glPopMatrix();

}

void sr_gdn_seat_roof1()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
        glTranslatef(10,0,10);
        cylinder(0.4,0.4, 15,     0.1,       0.14, 0.12, 0.07,      false);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(10,15,10);
        cylinder(1,22, 10,     0.1,       0.21, 0.41, 0.45,      false);
    glPopMatrix();
}


void sr_gdn_seat()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    GLfloat base=3.5,length = 8.0,height=2.5,backSide=3.0,legSize =0.25,gap=0.45,baseToleg=0.1;


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    //glTranslatef(5,0,5);
    /// base

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[7]);

    glTranslatef(0,height,0);
    glScalef(base,0.3,length);
    cube(22,surf);
    glPopMatrix();


    glBindTexture(GL_TEXTURE_2D,ID[2]);
    /// leg 1
    glPushMatrix();
    glScalef(legSize,height+backSide,legSize);
    cube(28,surf);
    glPopMatrix();

    /// leg 2
    glPushMatrix();
    glTranslatef(0,0,length-legSize);
    glScalef(legSize,height+backSide,legSize);
    cube(28,surf);
    glPopMatrix();

    /// leg 3

    glPushMatrix();
    glTranslatef(base-legSize,0,0);
    glScalef(legSize,height,legSize);
    cube(28,surf);
    glPopMatrix();

    /// leg 4
    glPushMatrix();
    glTranslatef(base-legSize,0,length-legSize);
    glScalef(legSize,height,legSize);
    cube(28,surf);
    glPopMatrix();


    /// back Side

    glPushMatrix();
    glTranslatef(0,height+gap,legSize);
    glScalef(0.15,legSize*2,length-legSize);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,height+gap*2+legSize*2,legSize);
    glScalef(0.15,legSize*2,length-legSize);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,height+gap*3+legSize*4,legSize);
    glScalef(0.15,legSize*2,length-legSize);
    cube(28,surf);
    glPopMatrix();



    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}


void sr_gdn_seating()
{
    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    /// base
    glPushMatrix();
        glScalef(20,1,20);
        cube(23,surf);
    glPopMatrix();

    /// garden road
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[27]);
    glPushMatrix();
        glTranslatef(-40,-0.4,7.5);
        glScalef(90,1,5);
        cube(22,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-40,-0.4,20+25);
        glScalef(90,1,5);
        cube(22,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-40,-0.4,-25);
        glScalef(90,1,5);
        cube(22,surf);
    glPopMatrix();



    glPushMatrix();
        glTranslatef(7.5,-0.5,60);
        glRotatef(90,0,1,0);
        glScalef(90,1,5);
        cube(22,surf);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(-40,-0.5,60);
        glRotatef(90,0,1,0);
        glScalef(90,1,5);
        cube(22,surf);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(20+25,-0.5,60);
        glRotatef(90,0,1,0);
        glScalef(90,1,5);
        cube(22,surf);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    /// end garden road


    /// end base


    glPushMatrix();
            sr_gdn_seat_roof1();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0,0,6);
        sr_gdn_seat();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(6,0,19);
        glRotatef(90,0,1,0);
        sr_gdn_seat();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(19,0,14);
        glRotatef(180,0,1,0);
        sr_gdn_seat();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(15,0,0);
        glRotatef(-90,0,1,0);
        sr_gdn_seat();
    glPopMatrix();


    /// single seat

    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,10+i);
            sr_gdn_seat();
        glPopMatrix();
    }

    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,-(10+i));
            sr_gdn_seat();
        glPopMatrix();
    }


    glPushMatrix();
    glTranslatef(0,0,20);
    glRotatef(90,0,1,0);
    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,10+i);
            sr_gdn_seat();
        glPopMatrix();
    }

    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,-(10+i));
            sr_gdn_seat();
        glPopMatrix();
    }

    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,0,0);
    glRotatef(180,0,1,0);
    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,10+i);
            sr_gdn_seat();
        glPopMatrix();
    }

    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,-(10+i));
            sr_gdn_seat();
        glPopMatrix();
    }

    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,-15);
    glRotatef(-90,0,1,0);
    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,10+i);
            sr_gdn_seat();
        glPopMatrix();
    }

    for(int i=20;i<=40;i+=20){
        glPushMatrix();
            glTranslatef(-50,0,-(10+i));
            sr_gdn_seat();
        glPopMatrix();
    }

    glPopMatrix();


}

void surrounding()
{


    /// forest 1
    glPushMatrix();
        glTranslatef(-100,0,-110);
        sr_forest();
    glPopMatrix();

    /// forest 2
    glPushMatrix();
        glTranslatef(-180,0,180);
        glRotatef(90,0,1,0);
        sr_forest();
    glPopMatrix();

    /// forest 3
    glPushMatrix();
        glTranslatef(180,0,-130);
        glRotatef(-90,0,1,0);
        sr_forest();
    glPopMatrix();
    /// end forest 3


    /// garden

    glPushMatrix();
        glTranslatef(110,0,90);

        glPushMatrix();
            sr_garden();
        glPopMatrix();

        glPushMatrix();
            glRotatef(90,0,1,0);
            sr_garden();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(150,0,0);
            sr_garden();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,150);
            glRotatef(90,0,1,0);
            sr_garden();
        glPopMatrix();
    glPopMatrix();

    /// garden Seating
    glPushMatrix();
        glTranslatef(110+70, 0, 90+70);
        sr_gdn_seating();
    glPopMatrix();


}

/// end Surrounding





void axes()
{
        /// base, top, back, front, right, left
    bool surf[]={true,true,true,false,true,true};

    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0,surf);
    glPopMatrix();

    for(int i=0;i<50;i++){
        glPushMatrix();
        glTranslatef(i,0,0);
        glScalef(0.25,0.25,0.25);
        cube(22,surf);
        glPopMatrix();
    }

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,surf);
    glPopMatrix();

        for(int i=0;i<50;i++){
        glPushMatrix();
        glTranslatef(0,i,0);
        glScalef(0.25,0.25,0.25);
        cube(22,surf);
        glPopMatrix();
    }

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(2,surf);
    glPopMatrix();

        for(int i=0;i<50;i++){
        glPushMatrix();
        glTranslatef(0,0,i);
        glScalef(0.25,0.25,0.25);
        cube(22,surf);
        glPopMatrix();
    }

}



void flr()
{
        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[4]);


    glTranslatef(0,-1.15,-20.0);
    glScalef(50,1.15,50);
    //glTranslatef(-0.5,-1,-0.5);
    cube(25,surf);
    glPopMatrix();

     glDisable(GL_TEXTURE_2D);


}


void north_wall()
{

       /// base, top, back, front, right, left
    bool surf[]={true,true,true,false,true,true};


    glEnable(GL_TEXTURE_2D);


    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[5]);

    glPushMatrix();
    glTranslatef(-1.15,-1,-20);
    glScalef(1.15,14,44);
    cube(15,surf);
    glPopMatrix();

    // north-east
    glPushMatrix();
    //glRotatef(5,1,0,0);
    glTranslatef(-0.3,0,-1);
    glScalef(0.5,13,10);
    cube(16,surf);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void east_wall()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};
    //vector<bool> surf(ary);

    GLfloat gap=3.5,height=10.0;

    //vector<bool> surf(true,false,true,true,false,false);

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[5]);
    // east 1
//    glPushMatrix();
//    glTranslatef(0,0,6);
//    glScalef(50,13.0,0.5);
//    cube(17,surf);
//    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,6);
    glScalef(18-gap,13.0,0.5);
    cube(17,surf);
    glPopMatrix();

    /// gap
    glPushMatrix();
    glTranslatef(18-gap,height,6);
    glScalef(gap,13.0-height,0.5);
    cube(17,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18,0,6);
    glScalef(gap+8,13.0,0.5); // 29.5
    cube(17,surf);
    glPopMatrix();


    /// 2nd door
    glPushMatrix();
        glTranslatef(29.5,height,6);
        glScalef(gap,13.0-height,0.5);
        cube(17,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(33,0,6);
        glScalef(gap+14.5,13.0,0.5); // 29.5
        cube(17,surf);
    glPopMatrix();







//     ///east 2
//    glPushMatrix();
//    glRotatef(5,0,0,1);
//    glTranslatef(5,0,5.9);
//    glScalef(45,13,0.5);
//    cube(18,surf);
//    glPopMatrix();

    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
}



void west_wall()
{
        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};
/*
    GLfloat gap=3.5,height=10.0;

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[5]);

    glPushMatrix();
    glTranslatef(0,0,-11);
    glScalef(18-gap,13.0,0.5);
    cube(17,surf);
    glPopMatrix();

    /// gap
    glPushMatrix();
    glTranslatef(18-gap,height,-11);
    glScalef(gap,13.0-height,0.5);
    cube(17,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18,0,-11);
    glScalef(gap+29.5,13.0,0.5);
    cube(17,surf);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    */

}


void south_wall()
{
       /// base, top, back, front, right, left
    bool surf[]={true,true,true,false,true,true};


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

        glBindTexture(GL_TEXTURE_2D,ID[5]);

        glPushMatrix();
        glTranslatef(19.7,-1,-20);
        glScalef(0.5,13,26);
        cube(15,surf);
        glPopMatrix();


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void sourth_wall2()
{

          /// base, top, back, front, right, left
    bool surf[]={true,true,true,false,true,true};


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

        glBindTexture(GL_TEXTURE_2D,ID[5]);

        glPushMatrix();
        glTranslatef(27,-1,-20);
        glScalef(0.5,13,26);
        cube(15,surf);
        glPopMatrix();


        // north-wast
        glPushMatrix();
        //glRotatef(5,1,0,0);
        glTranslatef(27.5,0,-14);
        glScalef(0.5,13,10);
        cube(16,surf);
        glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void roof()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
    glTranslatef(-0.5,13,-21.0);
    glScalef(53,1.5,52);

    //glTranslatef(-0.5,9,-0.5);
    cube(23,surf);

    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[6]);
        glTranslatef(-2,15,-22.0);
        glScalef(26,10,44);
        quad(23,surf,0.3);
        //cylinder(50,10,  5.0   ,   4      ,0.21, 0.41, 0.45,    false);
    glPopMatrix();
    glDisable(GL_TEXTURE);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[6]);
        glTranslatef(20,15,-22.0);
        glScalef(32,10,56);
        quad(23,surf,0.3);
        //cylinder(50,10,  5.0   ,   4      ,0.21, 0.41, 0.45,    false);
    glPopMatrix();
    glDisable(GL_TEXTURE);
}


void window()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

        glPushMatrix();
        glTranslatef(0.12,3,0);
        glScalef(0.15,5.5,3.5);
        cube(16,surf);
        glPopMatrix();



        glPushMatrix();
        glTranslatef(0.15,3.25,0.25);
        glScalef(0.2,5,3);
        cube(22,surf);
        glPopMatrix();


    glPushMatrix();
    glTranslatef(0.25,3,1.5);
    glScalef(0.19,5.5,0.15);
    cube(24,surf);
    glPopMatrix();


    for(double v=1.375; v<5.5; v+=1.375)
    {
        glPushMatrix();
        glTranslatef(0.25,3+ v,0);
        glScalef(0.19,0.15,3.5);
        cube(24,surf);
        glPopMatrix();
    }




    glPopMatrix();
}


void north_window()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
    glTranslatef(0,0,-9.5);
    window();
    glPopMatrix();
}

//
//void east_window()
//{
//                /// base, top, back, front, right, left
//    bool surf[]={true,true,true,true,true,true};
//
//    glPushMatrix();
//    glTranslatef(1.35,-0.25,6);
//    glRotatef(90,0,1,0);
//    window();
//    glPopMatrix();
//
//}


void bed()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

    ///lower bed portion
    glPushMatrix();
    glScalef(7,1,-5);
    cube(7,surf);
    glPopMatrix();

/// begin lower portion design
    glPushMatrix();
    glTranslatef(0.15,0.15,-5);
    glScalef(3.2,0.7,-0.1);
    cube(13,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.65,0.15,-5);
    glScalef(3.2,0.7,-0.1);
    cube(13,surf);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(1.25,0.5,-5.1);
    glScalef(1,0.12,-0.1);
    cube(14,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.75,0.5,-5.1);
    glScalef(1,0.12,-0.1);
    cube(14,surf);
    glPopMatrix();
/// end lower portion design





    /// upper bed portion
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[17]);
    glTranslatef(0,1,0);
    glScalef(7,0.5,-5);
    cube(22,surf);  // color-> 8
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// Blanket
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[18]);
    glTranslatef(3.8,1.5,-0.5);
    glScalef(7/2-0.3,0.1,-4);
    cube(22,surf);  // color -> 10
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /// pillow 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[19]);
    glTranslatef(0.2,1.5,-0.5);
    glScalef(2.2,0.4,-2.0);
    cube(22,surf);  // color -> 12
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// Pillow 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[19]);
    glTranslatef(0.2,1.5,-2.8);
    glScalef(2.2,0.4,-2.0);  // x value = 7/2-0.3
    cube(22,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // bed head portion
    glPushMatrix();
    glTranslatef(0.0,1.5,0.0);
    glScalef(0.35,2.0,-5.0);
    cube(13,surf);
    glPopMatrix();


    /// Paposh
    glPushMatrix();

    glTranslatef(4.5,0,-5);

    glPushMatrix();
    glScalef(2,0.12,-1);
    cube(10,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-0.25);
    glScalef(2,0.17,-0.5);
    cube(7,surf);
    glPopMatrix();

    glPopMatrix();
    /// end paposh

    /// carpet
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[20]);
        glTranslatef(11,0.5,-7);
        glScalef(5,0.1,7);
        cube(22,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

}

void fan()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

    //glTranslatef(7,0,-1);

    glPushMatrix();
        glTranslatef(0,8.5,0);
        cylinder(0.4,0.4,  0.5   ,   0.1      ,0.21, 0.41, 0.45,    true);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,8.5,0);
        cylinder(0.1,0.1, 2,     0.1,       0.21, 0.41, 0.45,      true);
    glPopMatrix();

    glPushMatrix();
        glRotatef(fan_rot,0,1,0); // fan rotation
        glTranslatef(0,8.6,0);

    // pakha 1
    glPushMatrix();
        glTranslatef(0.85,0.0,0);
        glScalef(1.7,0.15,0.5);
        glTranslatef(-0.5,-0.5,-0.5);
        cube(27,surf);
    glPopMatrix();

    // pakha 2
    glPushMatrix();
        glRotatef(30,0,1,0);
        glTranslatef(0,0,-0.85);
        glRotatef(90,0,1,0);
        glScalef(1.7,0.15,0.5);
        glTranslatef(-0.5,-0.5,-0.5);
        cube(27,surf);
    glPopMatrix();

    // pakha 3
    glPushMatrix();
        glRotatef(150,0,1,0);
        glTranslatef(0,0,-0.85);
        glRotatef(90,0,1,0);
        glScalef(1.7,0.15,0.5);
        glTranslatef(-0.5,-0.5,-0.5);
        cube(27,surf);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}


void all_fan()
{
    glPushMatrix();
        glTranslatef(7,0,-1);
        fan();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(37.0,0,17.0);
        fan();
    glPopMatrix();


}





void drobe()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

    glPushMatrix();
    glTranslatef(0.5,0,0);
    glScalef(1,3.9,3);
    cube(19,surf);
    glPopMatrix();



    glPushMatrix(); // drawer 1

    glPushMatrix();
    glTranslatef(1.3,0,0.15);
    glScalef(0.4,1.15,2.7);
    cube(20,surf);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.5,0.575,1.15);
    glScalef(0.3,0.15,0.5);
    cube(21,surf);
    glPopMatrix();


    glPopMatrix();



    glPushMatrix(); // start drawer 2

    glPushMatrix();
    glTranslatef(1.3,1.30,0.15);
    glScalef(0.4,1.15,2.7);
    cube(20,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,1.875,1.15);
    glScalef(0.3,0.15,0.5);
    cube(21,surf);
    glPopMatrix();

    glPopMatrix(); // end drawer 2

    glPushMatrix();  // drawer 3


    glPushMatrix();
    glTranslatef(1.3,2.6,0.15);
    glScalef(0.4,1.15,2.7);
    cube(20,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,3.175,1.15);
    glScalef(0.3,0.15,0.5);
    cube(21,surf);
    glPopMatrix();


    glPopMatrix();




    glPopMatrix();
}

void dressing_table()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
    glTranslatef(1.0,0,-10.89);
    glRotatef(-90,0,1,0);

    //lower portion
    glPushMatrix();
    glTranslatef(0,0,0.35);
    glRotatef(90,0,0,1);
    glRotatef(90,0,1,0);
    drobe();
    glPopMatrix();


    // glass-frame of dressing-table
    glPushMatrix();
    glTranslatef(-3.4,2.55,0);
    glScalef(2.9,3+3,0.15);
    cube(19,surf);
    glPopMatrix();


    // glass of dressing-table
    glPushMatrix();
    glTranslatef(-3.15,2.75,-0.15);
    glScalef(2.4,2.5+3,0.15);
    cube(21,surf);
    glPopMatrix();

    glPopMatrix();

}


void wardrobe()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
        glTranslatef(0.5,3.9,2.2-0.075);
        glScalef(1.19,0.075,3.15);
        cube(20,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,2.2);
        drobe();
    glPopMatrix();
}



void bed_side_table()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

    glTranslatef(0.0,0,-8.3);

    // drobe head
    glPushMatrix();
        glTranslatef(0.5,2.75,-0.075);
        glScalef(1.15,0.075,3.15);
        cube(20,surf);
    glPopMatrix();


    // drobe body
    glPushMatrix();
    glTranslatef(0.5,0,0);
    glScalef(1,2.75,3);
    cube(26,surf);
    glPopMatrix();


    glPushMatrix(); // start drawer 1

    glPushMatrix();
    glTranslatef(1.3,1.30,0.15);
    glScalef(0.4,1.15,2.7);
    cube(20,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,1.875,1.15);
    glScalef(0.3,0.15,0.5);
    cube(21,surf);
    glPopMatrix();

    glPopMatrix(); // end drawer 1




    glPushMatrix(); // drawer 2

    glPushMatrix();
    glTranslatef(1.3,0,0.15);
    glScalef(0.4,1.15,2.7);
    cube(20,surf);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.5,0.575,1.15);
    glScalef(0.3,0.15,0.5);
    cube(21,surf);
    glPopMatrix();


    glPopMatrix(); // drawer 2







    glPopMatrix();
}




void solidSphere()
{


    GLfloat no_mat[] = { 0.0, 0.0, 0.0};
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5};
    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {60};



    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(45.0,1.0,12);
    glutSolidSphere (0.5, 20, 16);
    glPopMatrix();

}



void tube_light()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();


    if(lightStatus1==off)
    {
        glPushMatrix();
        glTranslatef(6.0,7.0,5.89);
        glScalef(2.15,0.3,0.15);
        cube(24,surf);

        glPopMatrix();

        glPushMatrix();
        glTranslatef(6.0+0.075,(7.0+0.075),5.87);
        glScalef(2,0.15,0.15);
        cube(24,surf);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(6.0,7.0,5.89);
        glScalef(2.15,0.3,0.15);
        cube(24,surf);

        glPopMatrix();

        glPushMatrix();
        glTranslatef(6.0+0.075,(7.0+0.075),5.87);
        glScalef(2,0.15,0.15);
        cube(22,surf);
        glPopMatrix();

    }



    glPopMatrix();
}


void energylight()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();

    if(lightStatus0)
    {
        glTranslatef(0.15,8.0,-3.25);
        glScalef(0.15,0.3,0.65);
        cube(24,surf);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.17, 8.0+0.075, -3.25+0.075);   //
        glScalef(0.15,0.15,0.5);
        cube(22,surf);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(0.15,8.0,-3.25);
        glScalef(0.15,0.3,0.65);
        cube(24,surf);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.17, 8.0+0.075, -3.25+0.075);   //
        glScalef(0.15,0.15,0.5);
        cube(24,surf);
        glPopMatrix();
    }

    glPopMatrix();

}

void lamp()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glLightfv( GL_LIGHT2, GL_POSITION, light_position2);

    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, coff);


    glPushMatrix();
    glTranslatef(1.0,3.8,-5.8);

        if(lightStatus2==off)
        {
            glPushMatrix();
                cylinder(0.3,0.5,  1.0   ,   0.4      ,0.21, 0.41, 0.45,    false);
            glPopMatrix();
        }
        else{
            glPushMatrix();
                cylinder(0.3,0.5,  1.0   ,   0.4      ,1.00,1.00,1.00,    false);
            glPopMatrix();
        }


        glPushMatrix();
            glTranslatef(0,-1.3,0);
            glScalef(0.1,2,0.1);
            cube(21,surf);
        glPopMatrix();
    glPopMatrix();
}



void setTime(){
   // current date/time based on current system
    time_t now = time(0);

    tm *ltm = localtime(&now);

    angle_second = 360-6*(ltm->tm_sec);
    angle_min = 360-6*(ltm->tm_min-1);
    angle_hour = 360-30*((ltm->tm_hour)%12)-((ltm->tm_min-1)/2);

}



void wall_clock()
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
    glTranslatef(0.2,6.5,-2.5); //5.85


    glPushMatrix();
    glTranslatef(0,-0.5,0.5);
    glScalef(0.075,1.27,-1.0);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-0.35,0.35);
    glScalef(0.1,0.97,-0.7);
    cube(29,surf);
    //cube(17,17,17,17,17,17);
    glPopMatrix();




      // clock hands
                glPushMatrix();
                GLfloat in=0.01;
                //glTranslatef(0.37,0.45,0.05);
                glTranslatef(0.14,0,0);
                    // minute
                    glPushMatrix();
                    glRotatef(angle_min,1,0,0);
                    glScalef(0.015,0.2,0.01+in);
                    cube(24,surf);
                    //cube()
                    glPopMatrix();
                    // hour
                    glPushMatrix();
                    glRotatef(angle_hour,1,0,0);
                    glScalef(0.02,0.15,0.01+in);
                    cube(24,surf);
                    glPopMatrix();
                    // second
                    glPushMatrix();
                    glRotatef(angle_second,1,0,0);
                    glScalef(0.01,0.25,0.01+in);
                    cube(24,surf);
                    glPopMatrix();
                glPopMatrix();



//
//        glPushMatrix();
//            //glRotatef(-(clock_rot-0.05),1,0,0); // clock rotation
//            //glTranslatef(0.25,6.15,-2.48);
//            glTranslatef(0.05,0,0);
//
//
//
//            glPushMatrix();
//                //glTranslatef(0.0,0.3,0.32);
//                glRotatef(-(clock_rot1),1,0,0); // clock rotation
//                glScalef(0.075,0.4,0.075);
//                glTranslatef(-0.1,-0.1,-0.1);
//                cube(24,24,24,24,24,24);
//            glPopMatrix();
//
//        glPushMatrix();
//
//            //glTranslatef(0.0,0.65,0);
//            glRotatef(-(clock_rot2),1,0,0); // clock rotation
//            //glRotatef(90,1,0,0);
//            glScalef(0.075,0.4,0.075);
//            glTranslatef(-0.1,-0.1,-0.1);
//            cube(24,24,24,24,24,24);
//        glPopMatrix();
//
//        glPushMatrix();
//            glRotatef(-(clock_rot3),1,0,0); // clock rotation
//            //glTranslatef(0.0,0.8,0.7);
//            //glRotatef(-160,1,0,0);
//            glScalef(0.075,0.4,0.075);
//            cube(24,24,24,24,24,24);
//        glPopMatrix();
//
//        glPopMatrix();
//
//
//



    glPopMatrix();



}



void air_conditionar()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
        glTranslatef(0.3,10,10);
        glRotatef(-90,0,0,1);
        glScalef(1,1,2);
        quad(17,surf,0.15);
    glPopMatrix();

}


void basic_table(int len)
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    GLfloat width=3.0, length=len, height=3.5;
    glPushMatrix();



    /// table base
    glPushMatrix();



    glTranslatef(0,height,0);
    glScalef(width,0.25,length);
    //cube(22,22,22,22,22,22);
    cube(17,surf);
    glPopMatrix();





    /// table leg 1
    glPushMatrix();
    glTranslatef(0.25,0,0.25);
    glScalef(0.25,height,0.25);
    cube(28,surf);
    glPopMatrix();


    /// table leg 2
    glPushMatrix();
    glTranslatef(width-0.45,0,0.25);
    glScalef(0.25,height,0.25);
    cube(28,surf);
    glPopMatrix();


    /// table leg 3
    glPushMatrix();
    glTranslatef(0.25,0,length-0.45);
    glScalef(0.25,height,0.25);
    cube(28,surf);
    glPopMatrix();


    /// table leg 4
    glPushMatrix();
    glTranslatef(width-0.45,0,length-0.45);
    glScalef(0.25,height,0.25);
    cube(28,surf);
    glPopMatrix();

    glPopMatrix();
}

void dinning_table()
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    GLfloat width=3.0, length=6.0, height=2.7;

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[3]);

    /// table base
    glPushMatrix();
    glTranslatef(0,height,0);
    glScalef(width,0.25,length);
    cube(22,surf);
    glPopMatrix();



    glPushMatrix();

    /// table leg 1
    glPushMatrix();
    glTranslatef(0.15,0,0.65);
    glScalef(width-0.25,height,0.25);
    cube(28,surf);
    glPopMatrix();


    /// table leg 2
    glPushMatrix();
    glTranslatef(0.15,0,length-0.90);
    glScalef(width-0.25,height,0.25);
    cube(28,surf);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void chair()
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    GLfloat base=1.5,height=2.0,backSide=3.0,legSize =0.25,gap=0.45,baseToleg=0.1;


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    //glTranslatef(5,0,5);
    /// base

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[7]);

    glTranslatef(0,height,0);
    glScalef(base,0.3,base);
    cube(22,surf);
    glPopMatrix();


    glBindTexture(GL_TEXTURE_2D,ID[2]);
    /// leg 1
    glPushMatrix();
    glScalef(legSize,height+backSide,legSize);
    cube(28,surf);
    glPopMatrix();

    /// leg 2
    glPushMatrix();
    glTranslatef(0,0,base-legSize);
    glScalef(legSize,height+backSide,legSize);
    cube(28,surf);
    glPopMatrix();

    /// leg 3

    glPushMatrix();
    glTranslatef(base-legSize,0,0);
    glScalef(legSize,height,legSize);
    cube(28,surf);
    glPopMatrix();

    /// leg 4
    glPushMatrix();
    glTranslatef(base-legSize,0,base-legSize);
    glScalef(legSize,height,legSize);
    cube(28,surf);
    glPopMatrix();


    /// back Side

    glPushMatrix();
    glTranslatef(0,height+gap,legSize);
    glScalef(0.15,legSize*2,base-legSize);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,height+gap*2+legSize*2,legSize);
    glScalef(0.15,legSize*2,base-legSize);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,height+gap*3+legSize*4,legSize);
    glScalef(0.15,legSize*2,base-legSize);
    cube(28,surf);
    glPopMatrix();




    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void dinning_room()
{

        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();
        //glTranslatef(0,4.0,0);

    glPushMatrix();

        glTranslatef(6.0,0,12);

        ///table
        glPushMatrix();
        glTranslatef(2,0,0);
        dinning_table();
        glPopMatrix();

        /// table mat
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[26]);

        glPushMatrix();
        glTranslatef(2.0,3.0,1.5);
        glScalef(1.2,0.12,1.2);
        cube(22,surf);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2.0,3.0,3.5);
        glScalef(1.2,0.12,1.2);
        cube(22,surf);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2.0+1.8,3.0,1.5);
        glScalef(1.2,0.12,1.2);
        cube(22,surf);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2.0+1.8,3.0,3.5);
        glScalef(1.2,0.12,1.2);
        cube(22,surf);
        glPopMatrix();

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        /// end table mat

        /// chair 2
        glPushMatrix();
        glTranslatef(0.5,0,1.5);
        chair();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.5,0,3.5);
        chair();
        glPopMatrix();

    /// chair another 2
        glPushMatrix();

            glPushMatrix();
            glTranslatef(1.5+2+3,0,1.5+1.5);
            glRotatef(180,0,1,0);
            chair();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5+2+3,0,3.5+1.5);
            glRotatef(180,0,1,0);
            chair();
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
    /// end dinning table

    /// refrigerator

    glPushMatrix();
    GLfloat reHeight = 5.0+2+0.5,reWidth = 2.0;

    glTranslatef(9.5,0,6.5);
    glRotatef(-90,0,1,0);

    glPushMatrix();
    glScalef(reWidth,reHeight,reWidth);
    cube(15,surf);
    glPopMatrix();

    ///  refrigerator door
    glPushMatrix();
    glTranslatef(reWidth,0,0);
    glScalef(0.15,3+2,reWidth);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(reWidth,3.2+2,0);
    glScalef(0.15,1.8+0.5,reWidth);
    cube(28,surf);
    glPopMatrix();
    /// end door

    /// handle

    glPushMatrix();
    glTranslatef(2.15,3-0.5+2,reWidth-0.15);
    glScalef(0.12,0.45,0.12);
    cube(24,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.15,3+.25+2,reWidth-0.15);
    glScalef(0.12,0.45,0.12);
    cube(24,surf);
    glPopMatrix();

    glPopMatrix();


    /// showcase

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[14]);
        glTranslatef(0.15,7.0,6.5+12);
        glRotatef(90,0,1,0);
        glScalef(2.5,2.5,0.15);
        bool surfm[]={false,false,false,true,false,false};
        cube(22,surfm);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
        air_conditionar();
    glPopMatrix();




    glPushMatrix();
    //glTranslatef(10,7,15);
    glTranslatef(9.5,3.0,17.0);
    glRotatef(90,0,0,1);
    glScalef(0.3,0.4,0.3);
    bottleBezier(flwr_con, L_flwr_con, 0.0,1.0,1.0);
    //showControlPoints();
    glPopMatrix();




    glPopMatrix();


}

void reading_section()
{

        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    /// reading table
    glPushMatrix();
    glTranslatef(13,0,-17);

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D,ID[7]);
        glRotatef(-90,0,1,0);

            basic_table(6);

            glPushMatrix();
                glTranslatef(0,0.5,0);
                glScalef(3,3.0,2.5);
                cube(28,surf);
            glPopMatrix();

            /// leg join
            glPushMatrix();
                glTranslatef(0.25,0.5,6-0.45);
                glScalef(2.5,0.25,0.25);
                cube(28,surf);
            glPopMatrix();

            /// drawer
            glPushMatrix();
                glTranslatef(3,0.6,0.125);
                glScalef(0.12,1.25,2.25);
                cube(27,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(3,1.25+0.6+0.25,0.125);
                glScalef(0.12,1.25,2.25);
                cube(27,surf);
            glPopMatrix();

            /// handle
            glPushMatrix();
                glTranslatef(3,1.25+0.6+0.25+0.5,1.125);
                glScalef(0.15,0.15,0.5);
                cube(24,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(3,1.25,1.125);
                glScalef(0.15,0.15,0.5);
                cube(24,surf);
            glPopMatrix();

        glPopMatrix();

        glDisable(GL_TEXTURE_2D);



    /// reading chair

    glPushMatrix();
        glTranslatef(-5.0,0,4.0);
        glRotatef(90,0,1,0);
        chair();
    glPopMatrix();


    glPopMatrix();


}

void curveflower()
{
    GLfloat lenx = 1,leny =0.5;

    glPushMatrix();

    glTranslatef(2,4,3);
    //glRotatef(45,0,0,1);

    glPushMatrix();
    glRotatef(45,0,0,1);
    glScalef(lenx,leny,leny);
    bottleBezier(flwr, L_flwr, 1.0,1.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90+45,0,0,1);
    glScalef(lenx,leny,leny);
    bottleBezier(flwr, L_flwr, 1.0,1.0,1.0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-45,0,0,1);
    glScalef(lenx,leny,leny);
    bottleBezier(flwr, L_flwr, 1.0,1.0,1.0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-120,0,0,1);
    glScalef(lenx,leny,leny);
    bottleBezier(flwr, L_flwr, 1.0,1.0,0.0);
    glPopMatrix();

    glPopMatrix();
}



void drawing_room()
{

        /// base, top, back, front, right, left
    bool surf[]={false,false,false,false,false,false};

    GLfloat width =3.5,length =3,height=3.0;

    //glEnable(GL_TEXTURE_2D);


    glPushMatrix();

    glTranslatef(35,0,15);

       // glBindTexture(GL_TEXTURE_2D,ID[1]);
       glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glTranslatef(13.5,0,5);
        glRotatef(180,0,1,0);

        glBindTexture(GL_TEXTURE_2D,ID[9]);
        glPushMatrix();


            glPushMatrix();
                glScalef(width,height,length);
                /// base, top, back, front, right, left
                bool surfm1[]={true,true,true,true,true,true};
                cube(22,surfm1);
            glPopMatrix();


            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surfm1);
            glPopMatrix();


        /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

        glPopMatrix();



        /// 2nd sofa

        glPushMatrix();

        glTranslatef(0,0,length+0.75);


            glPushMatrix();
                glScalef(width,height,length);
                cube(22,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surfm1);
            glPopMatrix();


            /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

        //glDisable(GL_TEXTURE_2D);

    /// sofa 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[9]);
        glTranslatef(width+0.5,0,10);
        glRotatef(90,0,1,0);

        glPushMatrix();

            glPushMatrix();
                glScalef(width,height,length);
                cube(22,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surfm1);
            glPopMatrix();


        /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

        glPopMatrix();


        /// 2nd sofa

        glPushMatrix();

        glTranslatef(0,0,length+0.75);

            glPushMatrix();
                glScalef(width,height,length);
                cube(22,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surfm1);
            glPopMatrix();


            /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surfm1);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





        glPushMatrix();

        glTranslatef(5.0,0,0);

            /// tea table
            GLfloat theight=2.0;
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,ID[4]);
                glTranslatef(0,theight,0);
                glScalef(4,0.5,5);
                cube(18,surf);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            ///flower
            glPushMatrix();
                glTranslatef(-1,0+2,5);
                glRotatef(90,0,1,0);
                curveflower();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(2,2.2+2,3);
                cylinder(0.05,0.05,  1.8   ,   0.9      ,0.47, 0.30, 0.17,    true);
            glPopMatrix();


            glPushMatrix();
                glTranslatef(2,2.6,3);
                glRotatef(90,0,0,1);
                glScalef(0.7,0.2,0.2);
                bottleBezier(flwr_con, L_flwr_con, 1.0,0.0,1.0);
                //showControlPoints();
            glPopMatrix();

            /// end flower

            /// stand 1
            glPushMatrix();
                glScalef(0.25,theight,0.25);
                cube(17,surf);
            glPopMatrix();

            /// stand 2
            glPushMatrix();
                glTranslatef(4-0.25,0,0);
                glScalef(0.25,theight,0.25);
                cube(17,surf);
            glPopMatrix();

            /// stand 3
            glPushMatrix();
                glTranslatef(4-0.25,0,5-0.25);
                glScalef(0.25,theight,0.25);
                cube(17,surf);
            glPopMatrix();

            /// stand 4
            glPushMatrix();
                glTranslatef(0,0,5-0.25);
                glScalef(0.25,theight,0.25);
                cube(17,surf);
            glPopMatrix();

            /// leg join 1
             glPushMatrix();
                glTranslatef(0.25,0,0);
                glScalef(4-0.25,0.25,0.25);
                cube(17,surf);
            glPopMatrix();

            /// leg join 2
             glPushMatrix();
                glTranslatef(0.25,0,5-0.25);
                glScalef(4-0.25,0.25,0.25);
                cube(17,surf);
            glPopMatrix();

        glPopMatrix();

        /// end tea table



    /// TV setup




    glPushMatrix();

    glTranslatef(7,0,-8);
    glRotatef(-90,0,1,0);

        /// television
        glPushMatrix();
            glTranslatef(1.5,2,0);

            glPushMatrix();
                glTranslatef(0,3.0,1.5);
                glScalef(0.25,2+1,2+2);
                cube(24,surf);
            glPopMatrix();

            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,ID[15]);
                glTranslatef(0.01,3.0+0.025,1.5+0.025);
                glScalef(0.25,2-0.05+1,2-0.05+2);
                bool surfm[]={false,false,false,false,true,false};
                cube(22,surfm);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();

        /// end television

    glPushMatrix();
        glTranslatef(-1,0,0);

        glPushMatrix();
        glTranslatef(0.5,0,0);
        glScalef(1,3.9-1.15,3+2.0);
        cube(19,surf);
        glPopMatrix();



        glPushMatrix(); // drawer 1

            glPushMatrix();
            glTranslatef(1.3,0,0.15);
            glScalef(0.4,1.15,2.7+2.0);
            cube(20,surf);
            glPopMatrix();


            glPushMatrix();
            glTranslatef(1.5,0.575,1.15);
            glScalef(0.3,0.15,0.5+2.0);
            cube(21,surf);
            glPopMatrix();


        glPopMatrix();


        glPushMatrix(); // start drawer 2

            glPushMatrix();
            glTranslatef(1.3,1.30,0.15);
            glScalef(0.4,1.15,2.7+2.0);
            cube(20,surf);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5,1.875,1.15);
            glScalef(0.3,0.15,0.5+2.0);
            cube(21,surf);
            glPopMatrix();

        glPopMatrix(); // end drawer 2
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();
}


void room2()
{

            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

        glPushMatrix();
            glTranslatef(34,0,-16.5);
            glRotatef(-90,0,1,0);
            bed();
        glPopMatrix();



         /// chester
        glPushMatrix();

                glTranslatef(28,-1,-10.5);

                glPushMatrix();
                    glScalef(2,8+2,6);
                    cube(30,surf);
                glPopMatrix();
                /// glass
                glPushMatrix();
                    glTranslatef(2,0,2);
                    glScalef(0.25,8+2,2);
                    cube(22,surf);
                glPopMatrix();
                /// partition
                glPushMatrix();
                    glTranslatef(2.01,2.5+2,0);
                    glScalef(0.15,0.15,6);
                    cube(24,surf);
                glPopMatrix();

        glPopMatrix();



        /// reading section
        glPushMatrix();
            glTranslatef(33,0,-9);
            glRotatef(-90,0,1,0);
            reading_section();
        glPopMatrix();

        /// book shelf
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D,ID[25]);
            glTranslatef(48,0,-15);
            glScalef(2,10,5);
            /// base, top, back, front, right, left
            bool surfm[]={false,false,false,false,false,true};
            cube(22,surfm);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        /// bed side table
        glPushMatrix();
            glTranslatef(34,0,-16.5);
            glRotatef(-90,0,1,0);
            bed_side_table();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(40,0,-12.0);
            lamp();
        glPopMatrix();

        /// fan
        glPushMatrix();
            glTranslatef(40,2,-10);
            fan();
        glPopMatrix();



    glPopMatrix();

}


void lookAtObject()
{
        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
    glTranslatef(lx,ly,lz);
    glScalef(0.25,0.25,0.5);
    cube(22,surf);
    glPopMatrix();
}


void side_wall()
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();

        /// south side wall
        glPushMatrix();

            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,ID[5]);
                glTranslatef(50,-1,0.0);
                glScalef(1.5,16.0,30);
                cube(25,surf);
            glPopMatrix();

            /// window gap

            glPushMatrix();
                glTranslatef(50,-1,-7.5);
                glScalef(1.5,4.0,8.0);
                cube(25,surf);
            glPopMatrix();
            /// window grill
            glPushMatrix();
                glTranslatef(50.5,3,-3.75);
                glScalef(0.19,9.0,0.15);
                cube(24,surf);
            glPopMatrix();


            for(double v=1.375; v<9.5; v+=1.375)
            {
                glPushMatrix();
                    glTranslatef(50.5,3+ v,-7.5);
                    glScalef(0.19,0.15,7.7);
                    cube(24,surf);
                glPopMatrix();
            }
            /// end window grill
            glPushMatrix();
                glTranslatef(50,12,-7.5);
                glScalef(1.5,2.0,8.0);
                cube(25,surf);
            glPopMatrix();
            /// end window gap


            glPushMatrix();
                glTranslatef(50,-1,-20);
                glScalef(1.5,16.0,13.0);
                cube(25,surf);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();
        /// end south side wall

        /// west side wall
        glPushMatrix();

            glPushMatrix();
                glTranslatef(15,0,-21);
                glRotatef(90,0,1,0);
                window();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(35,0,-21);
                glRotatef(90,0,1,0);
                window();
            glPopMatrix();

            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,ID[5]);
                glTranslatef(0,-1,-20);
                glScalef(50,16.0,1.5);
                cube(25,surf);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();

        /// end west side wall


        /// east side wall
        glPushMatrix();
                glPushMatrix();
                    glTranslatef(10,0,24);
                    glRotatef(-90,0,1,0);
                    window();
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(35,0,32);
                    glRotatef(-90,0,1,0);
                    window();
                glPopMatrix();

                glEnable(GL_TEXTURE_2D);
                glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D,ID[5]);
                    glTranslatef(0,-1,23);
                    glScalef(20,16.0,1.5);
                    cube(25,surf);
                glPopMatrix();

//                glPushMatrix();
//                    glTranslatef(20,10,30);
//                    glScalef(8,6,1.5);
//                    cube(25,surf);
//                glPopMatrix();

                glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D,ID[5]);
                    glTranslatef(20,-1,30);
                    glScalef(30,16.0,1.5);
                    cube(25,surf);
                glPopMatrix();
                glDisable(GL_TEXTURE_2D);

        glPopMatrix();

        /// end east side wall




    glPopMatrix();
}

void door()
{
   /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[21]);

    glTranslatef(20,0,30);

    glPushMatrix();
        if(door_open){
            glTranslatef(0,0,-0.5);
            glRotatef(-90,0,1,0);

        }

        glTranslatef(0,0,-6);
        glScalef(0.5,14,6);
        cube(22,surf);
    glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void area()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
        glTranslatef(-7,-0.5,10);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-6,-0.5,20);
        tree();
    glPopMatrix();




    /// boundary
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[11]);

    glPushMatrix();
        glTranslatef(-15,0,-35);
        glScalef(2.5,5,80);
        cube(10,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(65,0,-35);
        glScalef(2.5,5,80);
        cube(10,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15,0,-35);
        glScalef(80,5,2.5);
        cube(10,surf);
    glPopMatrix();


    /// gap boundary
    glPushMatrix();
        glTranslatef(-15,0,45);
        glScalef(30,5,2.5);
        cube(10,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(35,0,45);
        glScalef(30,5,2.5);
        cube(10,surf);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    road();


}


void house()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[7]);
    glTranslatef(-3,0,-22);
    glScalef(56,3,54);
    cube(25,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glPushMatrix();
    glTranslatef(0,4,0);


        flr();
        roof();
        north_wall();
        east_wall();
        west_wall();


            side_wall();
            door();


        south_wall();
        sourth_wall2();



        north_window();
        //east_window();

        solidSphere();
        bed();

        all_fan();
        reading_section();

        bed_side_table();
        wardrobe();
        dressing_table();

        setTime();
        wall_clock();




        tube_light();
        energylight();


    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,4,0);
        lamp();
        drawing_room();
        dinning_room();
        room2();
    glPopMatrix();


}


void second_house()
{

                      /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();
        glTranslatef(-70,0,-30);


    glPushMatrix();
    glTranslatef(0,4,0);


        flr();
        roof();
        north_wall();
        east_wall();
        west_wall();


            side_wall();
            door();


        south_wall();
        sourth_wall2();



        north_window();
        //east_window();

        solidSphere();
        bed();
        all_fan();
        reading_section();

        bed_side_table();
        wardrobe();
        dressing_table();

        setTime();
        wall_clock();


        tube_light();
        energylight();


    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,4,0);
        lamp();
        drawing_room();
        dinning_room();
        room2();
    glPopMatrix();



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[7]);
    glTranslatef(-3,0,-22);
    glScalef(56,3,54);
    cube(25,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glPopMatrix();

}


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
//    // gluPerspective(60,ar, 2.0, 100.0);
//
//    glOrtho(-8.0, 8.0, -8.0*(GLfloat)height/(GLfloat)width, 8.0*(GLfloat)height/(GLfloat)width, 2.0, 25.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity() ;
//    gluLookAt(ex,ey,ez,lx,ly,lz,hx,hy,hz);



    glViewport(0, 0, width, height);

}







GLfloat difx, dify, difz;
void calculate_move_dir()
{
    GLfloat Rx,Ry,Rz,rx,ry,rz;

    Rx = (lx - ex);
    Ry = (ly - ey);
    Rz = (lz - ez);
    GLfloat value = sqrt(Rx*Rx + Ry*Ry + Rz*Rz);

    rx = Rx / value;
    ry = Ry / value;
    rz = Rz / value;
    printf("calculate_move_dir -> rx ry rz : %f %f %f\n", rx,ry,rz);
    difx = rx;
    dify = ry;
    difz = rz;

}





/// School
void sc_base()
{
     /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();
        glScalef(40,2,110);
        cube(15,surf);
    glPopMatrix();

}

void sc_clr_wall()
{

        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    GLfloat wall_depth = 1.2, wall_height=14, wall_length=30+1.2, door = 8;


    glEnable(GL_TEXTURE_2D);
    /// floor
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[23]);
        glScalef(32,1,32);
        cube(21,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[22]);

    /// wall 1 - z-axis
    glPushMatrix();
        glPushMatrix();
            glScalef(wall_depth,wall_height,wall_length-(11+8));
            cube(22, surf);
        glPopMatrix();

        /// window
        glPushMatrix();
            glScalef(wall_depth,wall_height-9,wall_length);
            cube(22,surf);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,9,0);
            glScalef(wall_depth,wall_height-9,wall_length);
            cube(22,surf);
        glPopMatrix();
        /// end window

        glPushMatrix();
            glTranslatef(0,0,19);
            glScalef(wall_depth,wall_height,wall_length-(11+ 8));
            cube(22,surf);
        glPopMatrix();
    glPopMatrix();

    /// wall 2 - x-axis
    glPushMatrix();
        glScalef(wall_length,wall_height,wall_depth);
        cube(22, surf);
    glPopMatrix();

    /// wall 3 - z-axis
    glPushMatrix();
         glTranslatef(30,0,0);

        glPushMatrix();
            glTranslatef(0,11,0);
            glScalef(wall_depth,3,door);
            cube(22, surf);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,door);
            glScalef(wall_depth,wall_height,wall_length - door);
            cube(22, surf);
        glPopMatrix();
    glPopMatrix();


    /// wall 4 - x-axis
    glPushMatrix();
        glTranslatef(0,0,30);
        glScalef(wall_length,wall_height,wall_depth);
        cube(22, surf);
    glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void sc_tableChair()
{
    glPushMatrix();
        glRotatef(90,0,1,0);
        glPushMatrix();
            basic_table(4);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-0.3,0,1);
            chair();
        glPopMatrix();
    glPopMatrix();

}

void sc_classRoom()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();
        glTranslatef(0,4,0);

        glPushMatrix();
            sc_clr_wall();
        glPopMatrix();

        for(int i=0;i<28;i+=7)
        {
            for(int j=0;j<21;j+=7){
                glPushMatrix();
                    glTranslatef(2+i,0,15+j);
                    sc_tableChair();
                glPopMatrix();
            }

        }


        /// lecture stage
        glPushMatrix();
            glTranslatef(2,1,0);
            glScalef(20,1,8);
            cube(26,surf);
        glPopMatrix();
        /// end lecture stage

        /// lecture stand
        glPushMatrix();
            glTranslatef(4,1,9.5);
            glRotatef(-90,0,1,0);
            glScalef(2,7,2);
            quad(17,surf,0.375,1);
        glPopMatrix();
        /// end lecture stand


        /// white board
        glPushMatrix();
            glTranslatef(4,6,0.5);
            glScalef(15,6,1);
            cube(21,surf);
        glPopMatrix();

    glPopMatrix();




}

void sc_eachFloor()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    /// each_floor_base
    glPushMatrix();
        glTranslatef(0,2,0);
        glScalef(40,2,65);
        cube(15,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30,2,65);
        glScalef(10,2,15);
        cube(15,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,2,80);
        glScalef(40,2,32);
        cube(15,surf);
    glPopMatrix();
    /// end each_floor_base


    glPushMatrix();
        glTranslatef(0,0,2.5);
        sc_classRoom();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,30+2.5);
        sc_classRoom();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,75+1.2*3);
        sc_classRoom();
    glPopMatrix();

}

void sc_stair()
{
    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};
    glPushMatrix();
        glTranslatef(23,0,7.5);
        for(int i=0;i<7;i++){
            glPushMatrix();
                glTranslatef(7-i,i,0);
                glScalef(2,1,7.5);
                cube(16,surf);
            glPopMatrix();
        }
    glPopMatrix();


    /// stair base
    glPushMatrix();
        glTranslatef(0,7,0);
        glScalef(23,1,15);
        cube(16,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(23,8,0);
        for(int i=0;i<7;i++){
            glPushMatrix();
                glTranslatef(i,i,0);
                glScalef(2,1,7.5);
                cube(16,surf);
            glPopMatrix();
        }
    glPopMatrix();

}


void sc_roof()
{
     /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();
        glTranslatef(0,34,0);
        sc_base();
    glPopMatrix();

}

void school_building()
{

    sc_base();

    glPushMatrix();
        sc_eachFloor();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,4,60+1.2*3);
        sc_stair();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0,16,0);
        sc_eachFloor();
    glPopMatrix();

    sc_roof();
}

void sc_boundary()
{
    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[16]);

    /// z - axis
    glPushMatrix();
        glTranslatef(-3,0,-5);
        glScalef(1,15,120);
        cube(23,surf);
    glPopMatrix();
    ///
    glPushMatrix();
        glTranslatef(160,0,-5);
        glScalef(1,15,120);
        cube(23,surf);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3,0,-5);
        glScalef(163,15,1);
        cube(21,surf);
    glPopMatrix();

    glPushMatrix();

        glTranslatef(-3,0,115);
        glPushMatrix();
            glScalef(74,15,1);
            cube(23,surf);
        glPopMatrix();




        ///school gate
        glPushMatrix();
            glTranslatef(73,15,0);
            cylinder(1,1, 4,     0.1,       0.21, 0.41, 0.45,      true);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(74-2.5,15+4,0);
            glScalef(20,7,1);
            cube(23,surf);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(75+15,15,0);
            cylinder(1,1, 4,     0.1,       0.21, 0.41, 0.45,      true);
        glPopMatrix();
        /// end school gate


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D,ID[24]);
            glTranslatef(74+15,0,0);
            glScalef(74,15,1);
            cube(23,surf);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


    glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void school()
{
    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    /// building 1
    glPushMatrix();
        school_building();
    glPopMatrix();

    /// building 2
    glPushMatrix();
        glTranslatef(160,0,0);
        glRotatef(-90,0,1,0);
        school_building();
    glPopMatrix();

    /// school boundary

    sc_boundary();

    /// school road
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, ID[12]);
        glTranslatef(70,0,122);
        glScalef(15,1,48);
        cube(11,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    /// School name
//    glPushMatrix();
//        string str ="GOVT. Science College";
//        drawStrokeText1(str,0,70,0,2);
//    glPopMatrix();
//    /// end school name


}



/// end School




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    const float ar = (float) windowWidth / (float) windowWidth;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-3,3,-3,3, n, 500);  // left, right, bottom, top, near and far distance in negative z axis
    glFrustum(-4,4,-4,4, n, 900);
    //gluPerspective(60,1,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt(ex,ey,ez, lx,ly,lz, hx,hy,hz);  // p0, p-ref, headup-vector 5,8,-10, 0,0,0, 0,1,0

    //glViewport(0, 0, windowWidth, windowHeight);


//    glRotatef(angleX,1.0,0.0,0.0);
//    glRotatef(angleZ,0,0,1);
//    glRotatef(angleY,0,1,0);


    glusphereDraw(1,350,64,32);

    //axes();




    glPushMatrix();
        area();
        house();
    glPopMatrix();


    glPushMatrix();
        second_house();
    glPopMatrix();

    /// third house
    glPushMatrix();
        glTranslatef(140,0,-15);
        glRotatef(-90,0,1,0);
        //area();
        second_house();
    glPopMatrix();


    //door();

    /// School area
    glPushMatrix();
        glTranslatef(-80,0,240);
        glRotatef(90,0,1,0);
        school();
    glPopMatrix();

    /// surrounding

    surrounding();





    lookAtObject();

    fieldDraw();

    /// School name
    glPushMatrix();
        string str ="GOVT. Science College";
        glColor3f(1.0,0.0,1.0);
        glTranslatef(0,0,170);
        glRotatef(90,0,1,0);
        drawStrokeText1(str,0,20,37,2);
    glPopMatrix();
    /// end school name



    glPushMatrix();
    string text = "Welcome to our area";
    glColor3f(0,0,0);
    drawText(text.data(),text.size(),50,100);
    //drawStrokeText1("hi Md Saiful islam",20,40,10);
    glPopMatrix();


    glFlush();
    glutSwapBuffers();
}



void light()
{

    GLfloat globalAmbient[] ={0.0,0.0,0.0,1.0};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);


    glEnable( GL_LIGHT0);

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position3);

// Light 1  activation
    glDisable( GL_LIGHT1);

    glLightfv( GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv( GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1);


// Light 2  activation
    glDisable( GL_LIGHT2);

    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient2);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular2);


    GLfloat spot_direction[] = { 0.0, -10.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);

}



void LoadTexture(const char* filename, unsigned int id)
{

    glBindTexture(GL_TEXTURE_2D, ID[id]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[id]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

string mode ="default";
void myKeyboardFunc( unsigned char key, int x, int y )
{/**<  */
    printf("x: %d, y: %d\n",x,y);
    switch ( key )
    {
    case '5':
        coff+=0.2;
        printf("cutoff in %0.2f\n", coff);
        break;
    case '6':
        coff-=0.2;
        printf("cutoff de %0.2f\n", coff);
        break;




    case '0':
        if(lightStatus0 == off)
        {
            lightStatus0 = on;
            glEnable(GL_LIGHT0);
            printf("light 0 on\n");
        }
        else
        {
            lightStatus0 = off;
            glDisable(GL_LIGHT0);
            printf("light 0 off\n");
        }
        break;
    case '1':
        if(lightStatus1 == off)
        {
            lightStatus1 = on;
            glEnable(GL_LIGHT1);
            printf("light 1 on\n");
        }
        else
        {
            lightStatus1 = off;
            glDisable(GL_LIGHT1);
            printf("light 1 off\n");
        }
        break;
    case '3':
        if(lightStatus2 == off)
        {
            lightStatus2 = on;
            glEnable(GL_LIGHT2);
            printf("light 2 on\n");
        }
        else
        {
            lightStatus2 = off;
            glDisable(GL_LIGHT2);
            printf("light 2 off\n");
        }
        break;



    case 'a':
    case 'A':
        if(lightStatus0)
        {
            if(amStatus0 == off)
            {
                glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0 );
                amStatus0 = on;
                printf("light 0: ambient light on\n");
            }
            else
            {
                glLightfv(GL_LIGHT0, GL_AMBIENT, no_light );
                amStatus0 = off;
                printf("light 0: ambient light OFF\n");
            }
        }

        if(lightStatus1)
        {
            if(amStatus1 == off)
            {
                glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1 );
                amStatus1 = on;
                printf("light 1: ambient light on\n");
            }
            else
            {
                glLightfv(GL_LIGHT1, GL_AMBIENT, no_light );
                amStatus1 = off;
                printf("light 2: ambient light OFF\n");
            }
        }
        if(lightStatus2)
        {
            if(amStatus2 == off)
            {
                glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2 );
                amStatus2 = on;
                printf("light 1: ambient light on\n");
            }
            else
            {
                glLightfv(GL_LIGHT2, GL_AMBIENT, no_light );
                amStatus2 = off;
                printf("light 2: ambient light OFF\n");
            }
        }
        break;

    case 'd':
    case 'D':
        if(lightStatus0)
        {
            if(diffStatus0 == off)
            {
                glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0 );
                diffStatus0 = on;
                printf("light 0: diffuse reflection on\n");
            }
            else
            {
                glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light );
                diffStatus0 = off;
                printf("light 0: diffuse reflection OFF\n");
            }
        }

        if(lightStatus1)
        {
            if(diffStatus1 == off)
            {
                glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1 );
                diffStatus1 = on;
                printf("light 1: diffuse reflection on\n");
            }
            else
            {
                glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light );
                diffStatus1 = off;
                printf("light 2: diffuse reflection OFF\n");
            }
        }
        if(lightStatus2)
        {
            if(diffStatus2 == off)
            {
                glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2 );
                diffStatus2 = on;
                printf("light 1: diffuse reflection on\n");
            }
            else
            {
                glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light );
                diffStatus2 = off;
                printf("light 2: diffuse reflection OFF\n");
            }
        }
        break;

    case 's':
    case 'S':
        if(lightStatus0)
        {
            if(specStatus0 == off)
            {
                glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0 );
                specStatus0 = on;
                printf("light 0: specular reflection on\n");
            }
            else
            {
                glLightfv(GL_LIGHT0, GL_SPECULAR, no_light );
                specStatus0 = off;
                printf("light 0: specular reflection OFF\n");
            }
        }

        if(lightStatus1)
        {
            if(specStatus1 == off)
            {
                glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1 );
                specStatus1 = on;
                printf("light 1: specular reflection on\n");
            }
            else
            {
                glLightfv(GL_LIGHT1, GL_SPECULAR, no_light );
                specStatus1 = off;
                printf("light 2: specular reflection OFF\n");
            }
        }
        if(lightStatus2)
        {
            if(specStatus2 == off)
            {
                glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2 );
                specStatus2 = on;
                printf("light 1: specular reflection on\n");
            }
            else
            {
                glLightfv(GL_LIGHT2, GL_SPECULAR, no_light );
                specStatus2 = off;
                printf("light 2: specular reflection OFF\n");
            }
        }
        break;

    case 'c':
        console_output();
        break;
    case 'e':
    case 'E':
        mode[0] = 'e';
        console_output();
        printf("Eye mode\n");
        break;
    case 'l':
    case 'L':
        mode[0] = 'l';
        console_output();
        printf("Look at mode\n");
        break;
//    case 'h':
//    case 'H':
//        mode[0] = 'h';
//        console_output();
//        printf("Head mode\n");
//        break;
//    case 'n':
//    case 'N':
//        mode[0] = 'n';
//        console_output();
//        printf("Zoom mode\n");
//        break;
//    case 'r':
//    case 'R':
//        mode[0] = 'r';
//        console_output();
//        printf("rotation mode\n");
//        break;

    case 'x':
    case 'X':
    case 'y':
    case 'Y':
    case 'z':
    case 'Z':
        switch (mode[0])
        {
        case 'e':
            if(key<96)
                key+=40;
            mode[1]=key;
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
            break;
        case 'l':
            if(key<96)
                key+=40;
            mode[1]=key;

            printf("Look at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
            break;
//        case 'h':
//            if(key<96)
//                key+=40;
//            mode[1]=key;
//            printf("Head at (%.2f,%.2f,%.2f)\n",hx,hy,hz);
//            break;
//        case 'n':
//            if(key<96)
//                key+=40;
//            mode[1]=key;
//            printf("Zoom out at (%.2f)\n",n);
//            break;
//        case 'r':
//            if(key<96)
//                key+=40;
//            mode[1]=key;
//            printf("angles (%0.2f %0.2f %0.2f) with x,y and z axis.\n",angleX,angleY,angleZ);
//            break;
        }
        break;

    case '+':
        switch ( mode[0] )
        {
        case 'e':
            if(mode[1]=='x')
            {
                //ex += 0.2;
                printf("Eye at (%.2f,%.2f,%.2f) after increasing ez magnitude\n",ex,ey,ez);
            }
            else  if(mode[1]=='y')
            {
                //ey += 0.2;
                printf("Eye at (%.2f,%.2f,%.2f) after increasing ez magnitude\n",ex,ey,ez);
            }
            else  if(mode[1]=='z')
            {
                //ez += 0.2;
                printf("Eye at (%.2f,%.2f,%.2f) after increasing ez magnitude\n",ex,ey,ez);
            }
            break;
        case 'l':
            if(mode[1]=='x')
            {
                //lx += 0.2;
                printf("Look at (%.2f,%.2f,%.2f) after increasing lx magnitude\n",lx,ly,lz);
            }
            else  if(mode[1]=='y')
            {
                //ly += 0.2;
                printf("Look at (%.2f,%.2f,%.2f) after increasing ly magnitude\n",lx,ly,lz);
            }
            else  if(mode[1]=='z')
            {
                //lz += 0.2;
                printf("Look at (%.2f,%.2f,%.2f) after increasing lz magnitude\n",lx,ly,lz);
            }

            break;
//        case 'h':
//            if(mode[1]=='x')
//            {
//                hx += 0.2;
//                printf("Head at (%.2f,%.2f,%.2f) after increasing hx magnitude\n",hx,hy,hz);
//            }
//            else  if(mode[1]=='y')
//            {
//                hy += 0.2;
//                printf("Head at (%.2f,%.2f,%.2f) after increasing hy magnitude\n",hx,hy,hz);
//            }
//            else  if(mode[1]=='z')
//            {
//                hz += 0.2;
//                printf("Head at (%.2f,%.2f,%.2f) after increasing hz magnitude\n",hx,hy,hz);
//            }
//
//            break;
//
//        case 'r':
//            if(mode[1]=='x')
//            {
//                angleX += 0.2;
//                printf("angle of axis (%.2f,%.2f,%.2f) after increasing angleX magnitude\n",angleX,angleY,angleZ);
//            }
//            else  if(mode[1]=='y')
//            {
//                angleY += 0.2;
//                printf("angle of axis (%.2f,%.2f,%.2f) after increasing angleY magnitude\n",angleX,angleY,angleZ);
//            }
//            else  if(mode[1]=='z')
//            {
//                angleZ += 0.2;
//                printf("angle of axis  (%.2f,%.2f,%.2f) after increasing angleZ magnitude\n",angleX,angleY,angleZ);
//            }
//            break;

//        case 'n':
//            n += 0.2;
////            ez += 0.2;
////            ex +=0.2;
//            printf("Zoom in at (%.2f)\n",n);
//            break;
        }
        break;

    case '-':
        switch ( mode[0] )
        {
        case 'e':
//            if(mode[1]=='x')
//            {
//                ex -= 0.2;
//                printf("Eye at (%.2f,%.2f,%.2f) after decreasing ez magnitude\n",ex,ey,ez);
//            }
             if(mode[1]=='y')
            {
                //ey -= 0.5;
                printf("Eye at (%.2f,%.2f,%.2f) after decreasing ey magnitude\n",ex,ey,ez);
            }
//            else  if(mode[1]=='z')
//            {
//                ez -= 0.2;
//                printf("Eye at (%.2f,%.2f,%.2f) after decreasing ez magnitude\n",ex,ey,ez);
//            }
            break;
        case 'l':
            if(mode[1]=='x')
            {
                //lx -= 0.5;
                printf("Look at (%.2f,%.2f,%.2f) after decreasing lx magnitude\n",lx,ly,lz);
            }
//            else  if(mode[1]=='y')
//            {
//                ly -= 0.2;
//                printf("Look at (%.2f,%.2f,%.2f) after decreasing ly magnitude\n",lx,ly,lz);
//            }
//            else  if(mode[1]=='z')
//            {
//                lz -= 0.2;
//                printf("Look at (%.2f,%.2f,%.2f) after decreasing lz magnitude\n",lx,ly,lz);
//            }

            break;
//        case 'h':
//            if(mode[1]=='x')
//            {
//                hx -= 0.2;
//                printf("Head at (%.2f,%.2f,%.2f) after decreasing hx magnitude\n",hx,hy,hz);
//            }
//            else  if(mode[1]=='y')
//            {
//                hy -= 0.2;
//                printf("Head at (%.2f,%.2f,%.2f) after decreasing hy magnitude\n",hx,hy,hz);
//            }
//            else  if(mode[1]=='z')
//            {
//                hz -= 0.2;
//                printf("Head at (%.2f,%.2f,%.2f) after decreasing hz magnitude\n",hx,hy,hz);
//            }
//
//            break;
//
//        case 'r':
//            if(mode[1]=='x')
//            {
//                angleX -= 0.2;
//                printf("angle of axis (%.2f,%.2f,%.2f) after decreasing angleX magnitude\n",angleX,angleY,angleZ);
//            }
//            else  if(mode[1]=='y')
//            {
//                angleY -= 0.2;
//                printf("angle of axis (%.2f,%.2f,%.2f) after decreasing angleY magnitude\n",angleX,angleY,angleZ);
//            }
//            else  if(mode[1]=='z')
//            {
//                angleZ -= 0.2;
//                printf("angle of axis (%.2f,%.2f,%.2f) after decreasing angleZ magnitude\n",angleX,angleY,angleZ);
//            }
//            break;
//        case 'n':
//              n -= 0.2;
////            ez -= 0.2;
////            ex -=0.2;
//            printf("Zoom out at (%.2f)\n",n);
//            break;
        }
        break;
    case 'p':
    case 'P':
        printf("All parameter: \n eye = (%0.2f %0.2f %0.2f)\n look-up vector = (%0.2f %0.2f %0.2f)\n head-up = (%0.2f %0.2f %0.2f)\n Near-plane distance = %0.2f\n angles = (%0.2f %0.2f %0.2f)\n",ex,ey,ez,lx,ly,lz,hx,hy,hz,n,angleX,angleY,angleZ);
        break;

//    case 'B':
//    case 'b':
//        ex=7, ey=7.80, ez=-10.20, lx=0, ly=0, lz=0, hx=0, hy=1, hz=0, n=5, angleX = 9.60, angleY=19.80, angleZ=12.00 ;  //9.60,19.80,12.00
//        mode ="default";
//        console_output();
//        printf("mode default\n");
//        break;

    case 'f':
    case 'F':
        if(fan_flag==off){
            fan_flag = on;
            printf("fan on\n");
            fan_speed = 1.0;
        }
        else if(fan_flag==on)
        {
            fan_flag = off;
            printf("fan off\n");
        }
        break;
    case '*':
        if(fan_flag==on)
        {
            if(fan_speed<10.0)
                fan_speed +=0.5;

            printf("fan speed up %f\n", fan_speed);

        }
    break;
    case '/':
        if(fan_flag==on)
        {
            if(fan_speed>0.0)
                fan_speed -=0.5;
            if(fan_speed <= 0.0)
                fan_speed =0.0;

             printf("fan speed down %f\n", fan_speed);

        }
    break;
    case 'o':
    case 'O':
        if(door_open == off){
            door_open=on;
        }
        else{
            door_open = off;
        }
        break;

    case 'g':
    case 'G':
        ex = -52.85; ey = 10.20; ez = 138.75; lx =-59.66; ly = 10.20; lz = 124.34;
        break;
    case 'H':
    case 'h':
        ex = 3.88; ey = 10.20; ez = 36.78; lx =17.50; ly = 10.20; lz = 28.51;
        break;
    case 27:	// Escape key
        //glutDestroyWindow(window);
        exit(0);
    }
    glutPostRedisplay();
}

void glut_keysFunc(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_RIGHT:
        printf("glut_right key press\n");

        if(mode[0]=='l')
        {
            printf("Right Key -> lookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){

            GLfloat t_lx,t_lz;
            GLfloat o_lx = lx - ex;
            GLfloat o_lz = lz - ez;
            GLfloat angle = 3;
            GLfloat  rd = (angle * PI)/180.0;
            GLfloat n_lx = o_lx * cos(rd) - o_lz * sin(rd);
            GLfloat n_lz = o_lx * sin(rd) + o_lz * cos(rd);
            lx = n_lx + ex;
            lz = n_lz + ez;
            printf("new look at: %f %f %f \n", lx, ly, lz);
            printf("Eye right at (%.2f,%.2f,%.2f)\n",ex,ey,ez);

        }

        break;
    case GLUT_KEY_LEFT:
        printf("glut_left key press\n");


        if(mode[0]=='l')
        {
            printf("Left key-> lookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){

            GLfloat t_lx,t_lz;

            GLfloat o_lx = lx - ex;
            GLfloat o_lz = lz - ez;

            GLfloat angle = -3;

            GLfloat  rd = (angle * PI)/180.0;

            GLfloat n_lx = o_lx * cos(rd) - o_lz * sin(rd);
            GLfloat n_lz = o_lx * sin(rd) + o_lz * cos(rd);

            lx = n_lx + ex;
            lz = n_lz + ez;

            printf("new look at: %f %f %f \n", lx, ly, lz);
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
        }

        break;
    case GLUT_KEY_UP:
        printf("glut_up key press\n");

        if(mode[0]=='l')
        {

            GLfloat up = 0.5;

            ey += up;

            ly += up;

            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
            printf("LookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e')
            {
            calculate_move_dir();
            GLfloat fwd = 0.9;

            ex += (difx * fwd);
            ey += (dify * fwd);
            ez += (difz * fwd);

            lx +=(difx * fwd);
            ly +=(dify * fwd);
            lz +=(difz * fwd);
            //ex--;
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
            printf("LookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }


        break;
    case GLUT_KEY_DOWN:
        printf("glut_down key press\n");
        if(mode[0]=='l')
        {
           GLfloat dwn = 0.5;

            ey -= dwn;

            ly -= dwn;

            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
            printf("LookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){
            //ex++;
            calculate_move_dir();
            GLfloat bwd = 0.7;
            ex -= (difx * bwd);
            ey -= (dify * bwd);
            ez -= (difz * bwd);


            lx -=(difx * bwd);
            ly -=(dify * bwd);
            lz -=(difz * bwd);

            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
            printf("LookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }


        break;
    }
    glutPostRedisplay();
}


void animate()
{
    if (fan_flag == on)
    {
        fan_rot += fan_speed;

        if(fan_rot > 360.0){
            fan_rot -= 360.0*floor(fan_rot/360.0);
        }
    }

    clock_rot1 += 0.1;
    if(clock_rot1 > 360.0){
            clock_rot1 -= 360.0*floor(clock_rot1/360.0);
        }

    clock_rot2 += 0.15;
    if(clock_rot2 > 360.0){
            clock_rot2 -= 360.0*floor(clock_rot2/360.0);
        }

    clock_rot3 += 0.2;
    if(clock_rot3 > 360.0){
            clock_rot3 -= 360.0*floor(clock_rot3/360.0);
        }

    glutPostRedisplay();
}

void console_output()
{
    system("CLS");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("\t........................................Follow the below Instructions........................................\n");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t######### For changing eye position use 'e' or 'E' key to get into eye-mode             ######### \n");
    printf("\t######### For changing lookup position use 'l' or 'L' key to get into lookup-mode       ######### \n");
    printf("\t######### For changing headup position use 'h' or 'H' key to get into headup-mode       ######### \n");
    printf("\t######### For rotating along axis use 'r' or 'R' key to get into rotation-mode          ######### \n");
    printf("\t######### For zooming the screen use 'n' or 'N' key to get into zoom-mode               ######### \n");

    printf("\t-------------------------------------------------------------------------------------------------\n");
    printf("\t-------------------------------------------------------------------------------------------------\n");

    printf("\t######### For turn on light 1,2 and 3; press '1', '2' and '3' respectively              ######### \n");
    printf("\t######### For ambient property of light; press 'a' or 'A' for turn-on/turn-off          ######### \n");
    printf("\t######### For diffuse property of light; press 'd' or 'D' for turn-on/turn-off          ######### \n");
    printf("\t######### For specular property of light; press 's' or 'S' for turn-on/turn-off         ######### \n");

    printf("\t-------------------------------------------------------------------------------------------------\n");
    printf("\t-------------------------------------------------------------------------------------------------\n");

    printf("\t######### For turn on/turn-off electric-fan; press 'f' or 'F'                           ######### \n");
    printf("\t######### For speed up/down of FAN; press '*' or '/' respectively                       ######### \n");



    printf("\n");
    printf("\n");
    printf("\t********* After getting into required mode, select the 'x','y' or 'z' except zoom-mode. ********* \n");
    printf("\t********* then press '+' for increasing and '-' for decreasing the value.               ********* \n");

    printf("\n");
    printf("\n");
    printf("\t_ _ _ _ To check all parameter value , press 'p' or 'P'. _ _ _ _ \n");
    printf("\t_ _ _ _ To return back to initial parameter, press 'b' or 'B'. _ _ _ _ \n");

    printf("\n");
    printf("\n");
    printf("\t!!!!!!! To exit, press 'Esc'. !!!!!!!\n");

    printf("\n");
    printf("\n");
}



void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}

void processMouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag!=1)
        {
            flag=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        cout<<"\nD: "<<x<<" "<<y<<" wcs: "<<wcsClkDn[0]<<" "<<wcsClkDn[1];
            lx = wcsClkDn[0];
            lz = wcsClkDn[1];
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        cout<<"\nU: "<<x<<" "<<y<<" wcs: "<<wcsClkUp[0]<<" "<<wcsClkUp[1];

        clikd=!clikd;
    }
}




//glClearColor(0.76, 0.70, 0.64,1.0);


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1607003 - 3D Building Design - v1.3");

    glGenTextures(30, ID);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\blue_sky.bmp",1);

    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wood_texture.bmp",2);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wood_texture1.bmp",3);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\Light_Wood_floor.bmp",4);

    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wall2.bmp",5);
    //LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\chair_sofa3.bmp",6);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\brick2.bmp",6);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\chair_seat1.bmp",7);
    //LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\footpath2.bmp",7);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wall4.bmp",8);

    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\chair_sofa3.bmp",9);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\field2.bmp",10);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\tree_leave1.bmp",11);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\road1.bmp",12);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\road1_left_right.bmp",13);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\sunset.bmp",14);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\tv_screen.bmp",15);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\brick.bmp",16);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\bed2.bmp",17);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\blanket1.bmp",18);

    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\pillow1.bmp",19);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\carpet1.bmp",20);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\door1.bmp",21);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\school_wall1.bmp",22);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\school_floor1.bmp",23);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\school_wall2.bmp",24);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\book_shelf1.bmp",25);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\dinning_table_mat.bmp",26);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\footpath1.bmp",27);





    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glEnable(GL_LIGHTING);
    light();


    sphere = gluNewQuadric();

    //glDisable(GL_light)



    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //D:\Semester 4.2\LAB\CSE 4208\Lab 04\Project\1607003_3D_Building_Area\Images

    glutReshapeFunc(resize);

    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(glut_keysFunc);
    //glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(processMouse);
    //glutIdleFunc(idle);



    glutDisplayFunc(display);

    ///background color
    //glClearColor(0.529,0.808,0.922,1.0);


    glutIdleFunc(animate);



    console_output();




    glutMainLoop();

    return EXIT_SUCCESS;
}


