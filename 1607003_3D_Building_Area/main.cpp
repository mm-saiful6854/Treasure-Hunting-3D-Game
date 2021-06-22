
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

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=800, windowWidth=800;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;

//double ex=18.80, ey=11.80, ez=-14.80, lx=-0.40, ly=1.60, lz=0.80, hx=0, hy=1, hz=0, n=9.40, angleX = 9.60, angleY=19.80, angleZ=12.00; // 5,8,-10, 0,0,0, 0,1,0 x=15, y=30,z=15
double ex=13.80, ey=16.20, ez=86.20, lx=23.40, ly=3.60, lz=-2.20, hx=0, hy=1, hz=0, n=9.40, angleX = 9.60, angleY=19.80, angleZ=12.00; // 5,8,-10, 0,0,0, 0,1,0 x=15, y=30,z=15

void console_output();

float fan_rot =0.0,fan_speed = 0.2;

float clock_rot1 =0.0, clock_rot2 =0.0, clock_rot3 =0.0;

unsigned int ID[30];


GLfloat angle_second, angle_min,angle_hour;

enum status
{
    off = false, on = true
} lightStatus0=off, lightStatus1 = off, lightStatus2=off, amStatus0=on, amStatus1=on, amStatus2=on, diffStatus0 = on, diffStatus1 = on, diffStatus2 = on, specStatus0 = on, specStatus1 = on, specStatus2 = on;


status fan_flag=off;
// No light property
GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

// Light 0 properties
GLfloat light_ambient0[]  = {0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse0[]  = { 1.0, 1.0, 1.0,1.0 };
GLfloat light_specular0[] = { 1.0, 1.0, 1.0,1.0};
GLfloat light_position0[] = { 0.0, 8.075, -3.175, 1.0};
// Light 1 properties
GLfloat light_ambient1[]  = {0.0, 0.0, 0.0,1.0};
GLfloat light_diffuse1[]  = { 1.0, 1.0, 1.0,1.0};
GLfloat light_specular1[] = { 1.0, 1.0, 1.0,1.0};
GLfloat light_position1[] = {6.075, 7.075 ,5.0, 1.0}; //5.87

// Light 2 (spotlight) properties
GLfloat light_ambient2[]  = {0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse2[]  = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_position2[] = { 3.0,5.0,-6, 1.0 };


GLfloat light_position3[] = {20, 30 ,20.0, 1.0}; //5.87
GLfloat light_position4[] = {-20, 30 , 20.0, 1.0}; //5.87

float coff = 63.80;

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


static GLfloat v_quad[8][3] = {
    {0.0, 0.0, 0.0}, // 1 origin
    {1.0, 0.0, 0.0}, // 2 x

    {0.375, 1.0, 0.375}, // 3 y

    {0.0, 0.0, 1.0}, // 4 z


    { 1 - 0.375, 1.0, 0.375}, // 5 xy plane
    {0.375, 1.0, 1-0.375}, // 6 yz plane
    {1.0, 0.0, 1.0}, // 7 zx plane

    {1-0.375, 1.0, 1-0.375}  // 8 xyz
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

void quad(int c_index,bool surf[], float top_curve = 0.375,int plane = 0)
{
    if(plane==0)
    {
        GLfloat v_quad[8][3] = {
    {0.0, 0.0, 0.0}, // 1 origin
    {1.0, 0.0, 0.0}, // 2 x

    {top_curve, 1.0, top_curve}, // 3 y

    {0.0, 0.0, 1.0}, // 4 z


    { 1 - top_curve, 1.0, top_curve}, // 5 xy plane

    {top_curve, 1.0, 1-top_curve}, // 6 yz plane
    {1.0, 0.0, 1.0}, // 7 zx plane

    {1-top_curve, 1.0, 1-top_curve}  // 8 xyz

};

    }
    if(plane ==1 )
     GLfloat v_quad[8][3] = {
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

if(plane == 2)
{
    GLfloat v_quad[8][3] = {
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
                glTexCoord2f(1,1);

            glVertex3fv(&v_Cube[p_Indices[i][1]][0]);
            if(surf[i]==true)
            glTexCoord2f(1,0);

            glVertex3fv(&v_Cube[p_Indices[i][2]][0]);
            if(surf[i]==true)
            glTexCoord2f(0,0);

            glVertex3fv(&v_Cube[p_Indices[i][3]][0]);
            if(surf[i]==true)
            glTexCoord2f(0,1);

        //}
    }
    glEnd();

}

void quad()
{

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

void ownTranslatef(GLfloat dx, GLfloat dy, GLfloat dz)
{

    GLfloat m[16];

    m[0] = 1;
    m[4] = 0;
    m[8] = 0;
    m[12] = dx;
    m[1] = 0;
    m[5] = 1;
    m[9] = 0;
    m[13] = dy;
    m[2] = 0;
    m[6] = 0;
    m[10] = 1;
    m[14] = dz;
    m[3] = 0;
    m[7] = 0;
    m[11] = 0;
    m[15] = 1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}



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
    glScalef(1.15,14,42);
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


    //vector<bool> surf(true,false,true,true,false,false);

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D,ID[5]);
    // east 1
    glPushMatrix();
    glTranslatef(0,0,6);
    glScalef(50,13.0,0.5);
    cube(17,surf);
    glPopMatrix();

    // east 2
    glPushMatrix();
    //glRotatef(5,0,0,1);
    glTranslatef(5,0,5.9);
    glScalef(45,13,0.5);
    cube(18,surf);
    glPopMatrix();

    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
}



void west_wall()
{
        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    GLfloat gap=3.5,height=7.0;

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
        glScalef(0.5,13,40);
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
        glScalef(0.5,13,30);
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
        quad(23,surf,0.1);
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


void east_window()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
    glTranslatef(1.35,-0.25,6);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();

}


void bed()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

    //lower bed portion
    glPushMatrix();
    glScalef(7,1,-5);
    cube(7,surf);
    glPopMatrix();

// begin lower portion design
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
// end lower portion design





    // upper bed portion
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(7,0.5,-5);
    cube(8,surf);
    glPopMatrix();

    // Blanket
    glPushMatrix();
    glTranslatef(3.8,1.5,-0.5);
    glScalef(7/2-0.3,0.15,-4);
    cube(10,surf);
    glPopMatrix();


    // balish 1
    glPushMatrix();
    glTranslatef(0.2,1.5,-0.5);
    glScalef(7/2-0.3,0.2,-2.0);
    cube(12,surf);
    glPopMatrix();

    // balish 2
    glPushMatrix();
    glTranslatef(0.2,1.5,-2.8);
    glScalef(7/2-0.3,0.2,-2.0);
    cube(12,surf);
    glPopMatrix();

    // bed head portion
    glPushMatrix();
    glTranslatef(0.0,1.5,0.0);
    glScalef(0.35,2.0,-5.0);
    cube(13,surf);
    glPopMatrix();


    // Paposh
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


    glPopMatrix();

}

void fan()
{
                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

    glTranslatef(7,0,-1);

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




void room2()
{

            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();

        glPushMatrix();
            glTranslatef(34,0,-10.5);
            glRotatef(-90,0,1,0);
            bed();
        glPopMatrix();



         /// chester
        glPushMatrix();

                glTranslatef(28,0,-10.5);

                glPushMatrix();
                    glScalef(2,8,6);
                    cube(30,surf);
                glPopMatrix();
                /// glass
                glPushMatrix();
                    glTranslatef(2,0,2);
                    glScalef(0.25,8,2);
                    cube(22,surf);
                glPopMatrix();
                /// partition
                glPushMatrix();
                    glTranslatef(2.01,2.5,0);
                    glScalef(0.15,0.15,6);
                    cube(24,surf);
                glPopMatrix();

        glPopMatrix();

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
    glTranslatef(10,0,5.89);

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
    glScalef(2.9,3,0.15);
    cube(19,surf);
    glPopMatrix();


    // glass of dressing-table
    glPushMatrix();
    glTranslatef(-3.15,2.75,-0.15);
    glScalef(2.4,2.5,0.15);
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
    glTranslatef(2.0,3.0,-2.0);
    glutSolidSphere (1.0, 20, 16);
    glPopMatrix();

}


void light()
{

    GLfloat globalAmbient[] ={0.0,0.0,0.0,1.0};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

// Light 0  activation

    glEnable(GL_LIGHT3);

    glLightfv( GL_LIGHT3, GL_AMBIENT,  light_ambient0);
    glLightfv( GL_LIGHT3, GL_DIFFUSE,  light_diffuse0);
    glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular0);
    glLightfv( GL_LIGHT3, GL_POSITION, light_position3);


    glEnable(GL_LIGHT4);

    glLightfv( GL_LIGHT4, GL_AMBIENT,  light_ambient0);
    glLightfv( GL_LIGHT4, GL_DIFFUSE,  light_diffuse0);
    glLightfv( GL_LIGHT4, GL_SPECULAR, light_specular0);
    glLightfv( GL_LIGHT4, GL_POSITION, light_position4);




    glDisable( GL_LIGHT0);

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular0);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position0);

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


    GLfloat spot_direction[] = { 0.0, -5.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);






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



//void air_conditionar()
//{
//    glBegin(GL_QUAD_STRIP);
//
//    glEnd();
//
//
//}


void basic_table()
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    GLfloat width=3.0, length=6.0, height=3.5;
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

    glPushMatrix();

        glTranslatef(10.0,0,12);

        ///table
        glPushMatrix();
        glTranslatef(2,0,0);
        dinning_table();
        glPopMatrix();

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
    GLfloat reHeight=5.0,reWidth=2.0;

    glTranslatef(14.5,0,7);
    glRotatef(-90,0,1,0);

    glPushMatrix();
    glScalef(reWidth,reHeight,reWidth);
    cube(15,surf);
    glPopMatrix();

    /// door
    glPushMatrix();
    glTranslatef(reWidth,0,0);
    glScalef(0.15,3,reWidth);
    cube(28,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(reWidth,3.2,0);
    glScalef(0.15,1.8,reWidth);
    cube(28,surf);
    glPopMatrix();

    /// handle

    glPushMatrix();
    glTranslatef(2.15,3-0.5,reWidth-0.15);
    glScalef(0.12,0.45,0.12);
    cube(24,surf);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.15,3+.25,reWidth-0.15);
    glScalef(0.12,0.45,0.12);
    cube(24,surf);
    glPopMatrix();

    glPopMatrix();


    /// showcase

    glPushMatrix();
        glTranslatef(4.0,5.0,-11.25);
        glScalef(2,2,0.15);
        cube(22,surf);
    glPopMatrix();





    glPopMatrix();


}

void reading_section()
{

        /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    /// reading table
    glPushMatrix();
    glTranslatef(13,0,-10);

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D,ID[7]);
        glRotatef(-90,0,1,0);

            basic_table();

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

    /// computer


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
    glPushMatrix();

        glPushMatrix();

            glPushMatrix();
                glScalef(width,height,length);
                cube(28,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surf);
            glPopMatrix();


        /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

        glPopMatrix();


        /// 2nd sofa

        glPushMatrix();

        glTranslatef(0,0,length+0.75);

            glPushMatrix();
                glScalef(width,height,length);
                cube(28,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surf);
            glPopMatrix();


            /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();

        //glDisable(GL_TEXTURE_2D);

    /// sofa 2

    glPushMatrix();

        glTranslatef(width+0.5,0,10);
        glRotatef(90,0,1,0);

        glPushMatrix();

            glPushMatrix();
                glScalef(width,height,length);
                cube(28,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surf);
            glPopMatrix();


        /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

        glPopMatrix();


        /// 2nd sofa

        glPushMatrix();

        glTranslatef(0,0,length+0.75);

            glPushMatrix();
                glScalef(width,height,length);
                cube(28,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,height+0.10,0);
                glScalef(1.0,height-0.5,length);
                cube(17,surf);
            glPopMatrix();


            /// handle

            glPushMatrix();
                glTranslatef(0,0,-0.75);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,length);
                glScalef(width,height+1,0.75);
                cube(17,surf);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();





        glPushMatrix();

        glTranslatef(7.0,0,0);

            /// tea table
            GLfloat theight=2.0;
            glPushMatrix();
                glTranslatef(0,theight,0);
                glScalef(4,0.5,5);
                cube(18,surf);
            glPopMatrix();


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



    /// TV setup




    glPushMatrix();

    glTranslatef(7,0,-8);
    glRotatef(-90,0,1,0);

        /// television

        glPushMatrix();
            glTranslatef(0,3.0,1.5);
            glScalef(0.25,2,2);
            cube(24,surf);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.01,3.0+0.025,1.5+0.025);
            glScalef(0.25,2-0.05,2-0.05);
            cube(22,surf);
        glPopMatrix();

        /// end television


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

GLUquadric* sphere;

void glusphereDraw(int id, float radius, int a, int b)
{
    GLfloat sky_length = 300;

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


void side_wall()
{
            /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};


    glPushMatrix();

        glPushMatrix();

            glPushMatrix();
                glTranslatef(52,0,0);
                window();
            glPopMatrix();

            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,ID[5]);
                glTranslatef(50,-1,-20);
                glScalef(1.5,16.0,50);
                cube(25,surf);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();


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
                    glTranslatef(0,-1,22);
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




    glPopMatrix();
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
}


void area()
{

    /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};

    glPushMatrix();
        glTranslatef(-6,-0.5,10);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4,-0.5,20);
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





    /// road
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[12]);
        glTranslatef(-200,0,60);
        glScalef(400,1,15);
        cube(17,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,ID[13]);
        glTranslatef(90,0,-200);
        glScalef(15,1,400);
        cube(17,surf);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void house()
{

                /// base, top, back, front, right, left
    bool surf[]={true,true,true,true,true,true};



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[6]);
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


        south_wall();
        sourth_wall2();



        north_window();
        east_window();

        solidSphere();
        bed();
        fan();
        reading_section();

        bed_side_table();
        wardrobe();
        dressing_table();

        setTime();
        wall_clock();




        tube_light();
        energylight();
        lamp();

        dinning_room();


        /// drawing room

        drawing_room();


        room2();

glPopMatrix();


}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-3,3,-3,3, n, 500);  // left, right, bottom, top, near and far distance in negative z axis
    glFrustum(-7,7,-7,7, n, 500);
    //gluPerspective(60,1,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex,ey,ez, lx,ly,lz, hx,hy,hz);  // p0, p-ref, headup-vector 5,8,-10, 0,0,0, 0,1,0

    //glViewport(0, 0, windowWidth, windowWidth);



//    glRotatef(angleX,1.0,0.0,0.0);
//    glRotatef(angleZ,0,0,1);
//    glRotatef(angleY,0,1,0);


    glusphereDraw(1,200,64,32);

    axes();


    area();


    house();




    lookAtObject();

    fieldDraw();

    glFlush();
    glutSwapBuffers();
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
{
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


    case '1':
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
    case '2':
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
    case 'h':
    case 'H':
        mode[0] = 'h';
        console_output();
        printf("Head mode\n");
        break;
    case 'n':
    case 'N':
        mode[0] = 'n';
        console_output();
        printf("Zoom mode\n");
        break;
    case 'r':
    case 'R':
        mode[0] = 'r';
        console_output();
        printf("rotation mode\n");
        break;

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
        case 'h':
            if(key<96)
                key+=40;
            mode[1]=key;
            printf("Head at (%.2f,%.2f,%.2f)\n",hx,hy,hz);
            break;
        case 'n':
            if(key<96)
                key+=40;
            mode[1]=key;
            printf("Zoom out at (%.2f)\n",n);
            break;
        case 'r':
            if(key<96)
                key+=40;
            mode[1]=key;
            printf("angles (%0.2f %0.2f %0.2f) with x,y and z axis.\n",angleX,angleY,angleZ);
            break;
        }
        break;

    case '+':
        switch ( mode[0] )
        {
        case 'e':
            if(mode[1]=='x')
            {
                ex += 0.2;
                printf("Eye at (%.2f,%.2f,%.2f) after increasing ez magnitude\n",ex,ey,ez);
            }
            else  if(mode[1]=='y')
            {
                ey += 0.2;
                printf("Eye at (%.2f,%.2f,%.2f) after increasing ez magnitude\n",ex,ey,ez);
            }
            else  if(mode[1]=='z')
            {
                ez += 0.2;
                printf("Eye at (%.2f,%.2f,%.2f) after increasing ez magnitude\n",ex,ey,ez);
            }
            break;
        case 'l':
            if(mode[1]=='x')
            {
                lx += 0.2;
                printf("Look at (%.2f,%.2f,%.2f) after increasing lx magnitude\n",lx,ly,lz);
            }
            else  if(mode[1]=='y')
            {
                ly += 0.2;
                printf("Look at (%.2f,%.2f,%.2f) after increasing ly magnitude\n",lx,ly,lz);
            }
            else  if(mode[1]=='z')
            {
                lz += 0.2;
                printf("Look at (%.2f,%.2f,%.2f) after increasing lz magnitude\n",lx,ly,lz);
            }

            break;
        case 'h':
            if(mode[1]=='x')
            {
                hx += 0.2;
                printf("Head at (%.2f,%.2f,%.2f) after increasing hx magnitude\n",hx,hy,hz);
            }
            else  if(mode[1]=='y')
            {
                hy += 0.2;
                printf("Head at (%.2f,%.2f,%.2f) after increasing hy magnitude\n",hx,hy,hz);
            }
            else  if(mode[1]=='z')
            {
                hz += 0.2;
                printf("Head at (%.2f,%.2f,%.2f) after increasing hz magnitude\n",hx,hy,hz);
            }

            break;

        case 'r':
            if(mode[1]=='x')
            {
                angleX += 0.2;
                printf("angle of axis (%.2f,%.2f,%.2f) after increasing angleX magnitude\n",angleX,angleY,angleZ);
            }
            else  if(mode[1]=='y')
            {
                angleY += 0.2;
                printf("angle of axis (%.2f,%.2f,%.2f) after increasing angleY magnitude\n",angleX,angleY,angleZ);
            }
            else  if(mode[1]=='z')
            {
                angleZ += 0.2;
                printf("angle of axis  (%.2f,%.2f,%.2f) after increasing angleZ magnitude\n",angleX,angleY,angleZ);
            }
            break;

        case 'n':
            n += 0.2;
//            ez += 0.2;
//            ex +=0.2;
            printf("Zoom in at (%.2f)\n",n);
            break;
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
                ey -= 0.5;
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
                lx -= 0.5;
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
        case 'h':
            if(mode[1]=='x')
            {
                hx -= 0.2;
                printf("Head at (%.2f,%.2f,%.2f) after decreasing hx magnitude\n",hx,hy,hz);
            }
            else  if(mode[1]=='y')
            {
                hy -= 0.2;
                printf("Head at (%.2f,%.2f,%.2f) after decreasing hy magnitude\n",hx,hy,hz);
            }
            else  if(mode[1]=='z')
            {
                hz -= 0.2;
                printf("Head at (%.2f,%.2f,%.2f) after decreasing hz magnitude\n",hx,hy,hz);
            }

            break;

        case 'r':
            if(mode[1]=='x')
            {
                angleX -= 0.2;
                printf("angle of axis (%.2f,%.2f,%.2f) after decreasing angleX magnitude\n",angleX,angleY,angleZ);
            }
            else  if(mode[1]=='y')
            {
                angleY -= 0.2;
                printf("angle of axis (%.2f,%.2f,%.2f) after decreasing angleY magnitude\n",angleX,angleY,angleZ);
            }
            else  if(mode[1]=='z')
            {
                angleZ -= 0.2;
                printf("angle of axis (%.2f,%.2f,%.2f) after decreasing angleZ magnitude\n",angleX,angleY,angleZ);
            }
            break;
        case 'n':
              n -= 0.2;
//            ez -= 0.2;
//            ex -=0.2;
            printf("Zoom out at (%.2f)\n",n);
            break;
        }
        break;
    case 'p':
    case 'P':
        printf("All parameter: \n eye = (%0.2f %0.2f %0.2f)\n look-up vector = (%0.2f %0.2f %0.2f)\n head-up = (%0.2f %0.2f %0.2f)\n Near-plane distance = %0.2f\n angles = (%0.2f %0.2f %0.2f)\n",ex,ey,ez,lx,ly,lz,hx,hy,hz,n,angleX,angleY,angleZ);
        break;

    case 'B':
    case 'b':
        ex=7, ey=7.80, ez=-10.20, lx=0, ly=0, lz=0, hx=0, hy=1, hz=0, n=5, angleX = 9.60, angleY=19.80, angleZ=12.00 ;  //9.60,19.80,12.00
        mode ="default";
        console_output();
        printf("mode default\n");
        break;

    case 'f':
    case 'F':
        if(fan_flag==off){
            fan_flag = on;
            printf("fan on\n");
            fan_speed =0.2;
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
            if(fan_speed<0.9)
                fan_speed +=0.1;

            printf("fan speed up\n");

        }
    break;
    case '/':
        if(fan_flag==on)
        {
            if(fan_speed>0.0)
                fan_speed -=0.1;
            if(fan_speed <= 0.0)
                fan_speed =0.0;

             printf("fan speed down\n");

        }
    break;

    case 27:	// Escape key
        exit(1);
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
            lz--;
            printf("lookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){
            ez--;
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
        }
        //ex -=0.075;

        //lx -=0.075;
        //lz -=0.2;



        break;
    case GLUT_KEY_LEFT:
        printf("glut_left key press\n");


        if(mode[0]=='l')
        {
            lz++;
            printf("lookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){
            ez++;
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
        }

        break;
    case GLUT_KEY_UP:
        printf("glut_up key press\n");
        if(mode[0]=='l')
        {
            ly++;
            printf("lookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){
            ex--;
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
        }

        break;
    case GLUT_KEY_DOWN:
        printf("glut_down key press\n");
        if(mode[0]=='l')
        {
            ly--;
            printf("lookAt at (%.2f,%.2f,%.2f)\n",lx,ly,lz);
        }
        if(mode[0]=='e'){
            ex++;
            printf("Eye at (%.2f,%.2f,%.2f)\n",ex,ey,ez);
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
int oldMouseX=0,oldMouseY=0;
void mouseMove(int mouseX, int mouseY)
{
    printf("x: %d, y= %d\n",mouseX,mouseY);

//    if(abs(pre_x-x)==10 || abs(pre_y-y)==10){
//        ly = x%20;
//        lz = y%20;
//        pre_x = x;
//        pre_y = y;
//    }
//    //ly = x%20;
//    //lz = y%20;

    // save old mouse coordinates


			// get mouse coordinates from Windows


			// these lines limit the camera's range
			if (mouseX < 60)
				mouseX = 60;
			if (mouseX > 1000)
				mouseX = 1000;

            if (mouseY < 60)
				mouseY = 60;
			if (mouseY > 1000)
				mouseY = 1000;

			if ((mouseX - oldMouseX) > 0)		// mouse moved to the right
				ly += 0.05f;
			else if ((mouseX - oldMouseX) < 0)	// mouse moved to the left
				ly -= 0.05f;


            if ((mouseY - oldMouseY) > 0)		// mouse moved to the right
				lz += 0.5f;
			else if ((mouseY - oldMouseY) < 0)	// mouse moved to the left
				lz -= 0.5f;

            if(lz>10){
                lz=10;
			}
			if(lz<-10)
                lz=-10;


            oldMouseX = mouseX;
			oldMouseY = mouseY;

			if(ly>10){
                ly=10;
			}
			if(ly<0.2)
                ly=0.2;


    glutPostRedisplay();
}

//glClearColor(0.76, 0.70, 0.64,1.0);


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1607003 - 3D Building Design");

    glGenTextures(30, ID);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\blue_sky.bmp",1);

    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wood_texture.bmp",2);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wood_texture1.bmp",3);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\Light_Wood_floor.bmp",4);

    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wall2.bmp",5);
    //LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\chair_sofa3.bmp",6);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\brick2.bmp",6);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\chair_seat1.bmp",7);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\wall4.bmp",8);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\chair_sofa2.bmp",9);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\field2.bmp",10);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\tree_leave1.bmp",11);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\road1.bmp",12);
    LoadTexture("D:\\Semester 4.2\\LAB\\CSE 4208\\Final Project\\1607003_3D_Building_Area\\Images\\road1_left_right.bmp",13);



    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glEnable(GL_LIGHTING);


    sphere = gluNewQuadric();

    //glDisable(GL_light)

    light();

    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //D:\Semester 4.2\LAB\CSE 4208\Lab 04\Project\1607003_3D_Building_Area\Images


    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(glut_keysFunc);
    //glutPassiveMotionFunc(mouseMove);



    glutDisplayFunc(display);

    ///background color
    //glClearColor(0.529,0.808,0.922,1.0);


    glutIdleFunc(animate);



    console_output();


    glutMainLoop();

    return EXIT_SUCCESS;
}


