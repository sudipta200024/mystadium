// Base Code For Assignment - 3
#include <windows.h>

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <cmath>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "BmpLoader.h"
unsigned int ID;


GLboolean redFlag = true, switchOne = false, switchTwo=false, switchLamp=false, amb1=true, diff1=true, spec1=true, amb2=true, diff2=true, spec2=true, amb3=true, diff3=true, spec3=true;
static int slices = 10;
static int stacks = 7;


double windowHeight=800, windowWidth=600;
double eyeX=2.0, eyeY=2.0, eyeZ=600.0, refX = 0, refY=0,refZ=0;
double theta = 180.0, y = 1.36, z = 7.97888, a=2;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


static GLfloat colors[6][3] =
{
    {0.4, 0.1, 0.0}, //bottom
    {0.6, 0.0, 0.7}, //top
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.3, 0.6, 0.7}
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

void drawCube(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=70)
{
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = {shine};
glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
glBegin(GL_QUADS);
for (GLint i = 0; i <6; i++)
{
getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
glVertex3fv(&v_cube[quadIndices[i][0]][0]);
glVertex3fv(&v_cube[quadIndices[i][1]][0]);
glVertex3fv(&v_cube[quadIndices[i][2]][0]);
glVertex3fv(&v_cube[quadIndices[i][3]][0]);
}
glEnd();}


void Cube(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=70)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
            glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
            glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
            glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
        }
    }
    glEnd();
}



void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void table()
{
  // Legs
//glColor3f(0.8, 0.7, 0.4);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,2);
  glPushMatrix();
  glTranslatef(-1, -2, 0.8);
  glScalef(0.1, 1, 0.001);
  drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glPushMatrix();
  glTranslatef(2.2, -2, 0.8);
  glScalef(0.1, 1, 0.001);
  drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1, -2, 5);
  glScalef(0.1, 1, 0.001);
  drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2.2, -2, 5);
  glScalef(0.1, 1, 0.001);
  drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
  glPopMatrix();


  // Tabletop
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,2);
  glPushMatrix();
  glTranslatef(-0.98, 1, 1);
  glScalef(1.2, 0.05, 1.5);
  Cube(1,1,1,1,1,1);
  glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void chair(){
    //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);  // Seat

    glTranslatef(0.0, 3.0, 0.0);
      glScalef(0.9, 0.1, 0.8);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);  // Backrest

    glTranslatef(0.0, -1.0, 1.5);

    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);  // Back left leg

    glTranslatef(3.0, 0.0, 0.0);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);  // Back right leg

    glTranslatef(0.0, 0.0, -3.0);

    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);  // Front right leg

    glTranslatef(-3.0, 0.0, 0.0);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);  // Front left leg

    glPopMatrix();
}


void window()
{
    //Window ********************************************

    //window white open
    //glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9); //0.5,1,9.6
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, .6, .3);
    drawCube(1.0,1.0,1.0,1.0,1.0,1.0);
    glPopMatrix();

    //window side corner
    //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.04, 0.6, 0.0001);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    //window left side corner
    //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    glTranslatef(-0.9,1,9.8);
    glScalef(0.04, 0.6, 0.0001);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();


     //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    glTranslatef(-0.9,1,9.8);
    glScalef(0.04, 0.6, 0.0001);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    //window upper side corner
    //glColor3f(0.7,0.6,0.5);
    glPushMatrix();
    glTranslatef(-0.8,2.7,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.05, 0.4);
    drawCube(0.7,0.6,0.5,0.7,0.6,0.5);
    glPopMatrix();


    //window lower side corner
    //glColor3f(0.7,0.6,0.5);
    glPushMatrix();
    glTranslatef(-0.8,1.02,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.02, 0.34);
    drawCube(0.7,0.6,0.5,0.7,0.6,0.5);
    glPopMatrix();

    //window vertical bar 1
    //glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.87,2.1,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.02, 0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //window vertical bar 2
    //glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.87,1.6,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.02, 0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //window horizontal bar
    //glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.87,1,9.3);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.6, 0.02);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();
}

void cellight(){

    }

    void light1()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 12.0, 8.0, 15.0, 1.0 }; //5 5 10

    //glEnable( GL_LIGHT0);

    if(amb1 == true){glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}

    if(diff1 == true){glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);}

    if(spec1 == true){glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void light2()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 10.0, 5.0, -15.0, 1.0 }; //5 5 10

    //glEnable( GL_LIGHT1);

    if(amb1 == true){glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);}

    if(diff1 == true){glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);}

    if(spec1 == true){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}


void fulltable(){
  glPushMatrix();
  glTranslatef(0.0, 0, 2.0); // Adjust the position of the table
  glScalef(0.6,0.6,0.6);
  table(); // DRAW THE TABLE
  glPopMatrix();


  glPushMatrix();
  glTranslatef(1.5,-1, 3.5); // Adjust the position of the table
  glScalef(0.20,0.30,0.20);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  glRotatef(180.0, 1.0, 0.0, 0.0);
  glColor3f(0.5, 0.5, 0.5);
  chair(); // DRAW THE TABLE
  glPopMatrix();




  glPushMatrix();
  glTranslatef(1.5,-1, 4.5); // Adjust the position of the table
  glScalef(0.20,0.30,0.20);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  glRotatef(180.0, 1.0, 0.0, 0.0);
  glColor3f(0.5, 0.5, 0.5);
  chair(); // DRAW THE TABLE
  glPopMatrix();



  glPushMatrix();
  glTranslatef(-0.5,-1, 3); // Adjust the position of the table
  glScalef(0.20,0.30,0.20);
  glRotatef(90.0, 0.0, 0.0, 1.0);
 // glRotatef(180.0, 1.0, 0.0, 0.0);
  glColor3f(0.5, 0.5, 0.5);
  chair(); // DRAW THE TABLE
  glPopMatrix();




  glPushMatrix();
  glTranslatef(-0.5,-1, 4); // Adjust the position of the table
  glScalef(0.20,0.30,0.20);
  glRotatef(90.0, 0.0, 0.0, 1.0);
  //glRotatef(180.0, 1.0, 0.0, 0.0);
  glColor3f(0.5, 0.5, 0.5);
  chair(); // DRAW THE TABLE
  glPopMatrix();


}

void fan()
{
    glPushMatrix();
    glTranslatef(3,4,8);

    //stand
    //glColor3f(0.2,0.1,0.1);
    glPushMatrix();
    glTranslatef(0.1,0,0.09);
    glScalef(0.01,0.4,0.01);
    //glTranslatef(-1.5,-1.5,-1.5);
    drawCube(0.2,0.1,0.1,0.2,0.1,0.1);
    glPopMatrix();

    //fan cube
    //glColor3f(0.2,0.1,0.5);
    glPushMatrix();
    glScalef(0.1,0.05,0.1);
    glTranslatef(-1.5,-1.5,-1.5);
    drawCube(0.2,0.1,0.5,0.2,0.1,0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(a, 0,1,0);

    //blade 1 blue
    //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    //glRotatef(a, 0,1,0);
    glScalef(0.5,0.01,0.1);
    glTranslatef(-1.5,-1.5,-1.5);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    //blade 2 purple
    //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    //glRotatef(a, 0,1,0);
    glScalef(0.1,0.01,0.5);
    glTranslatef(-1.5,-1.5,-1.5);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}

    void lightBulb0()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1.000, 1,1, 0.0};

    glPushMatrix();
    glTranslatef (1, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    if(switchOne == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }

    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

    void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};

    glPushMatrix();
    glTranslatef (10,5,8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchTwo == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void spotBulb()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};

    glPushMatrix();
    glTranslatef (4.61, -0.5, 6.98);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchLamp == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lampLight()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -15.4, 9.1, 15.5, 1.0 };  //0.7, 4.5, 9.0

    //glEnable( GL_LIGHT2);

    if(amb3 == true){glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);}

    if(diff3 == true){glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);}

    if(spec3 == true){glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.3, -1, -1 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
    glPopMatrix();
}

//void light0()
//{
//    //top right farthest corner

//    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
//    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_position[] = { 5.0, 5.0, -10.0, 1.0 };
//    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
//    glEnable( GL_LIGHT0);
//}
void freezer()
{
    //freezer ***************

       //freezer
       //glColor3f(1,1,1);


       glPushMatrix();
       glTranslatef(0,0,4);
       glScalef(0.35, 1.22, 0.5);
       Cube(1,1,1,1,1,1);
       glPopMatrix();


       //Freezer left stripline


       glPushMatrix();
       glTranslatef(1.02,0,5.5);
       glScalef(0.01, 1.22, 0.0001);
       Cube(1,1,1,1,1,1);
       glPopMatrix();


       //Freezer  middle stripline
       //glColor3f(0.1f, 0.1f, 0.1f);
       glPushMatrix();
       glTranslatef(1.09,2.2,5.5);
       glRotatef(-90, 1,0,0);
       glScalef(0.001, 0.5, 0.01);
       drawCube(0.1f, 0.1f, 0.1f,0.6, 0.6, 0.4);
       glPopMatrix();



        //Freezer 1st handle
       //glColor3f(0.1f, 0.1f, 0.1f);
//       glPushMatrix();
//       glTranslatef(1.06,1.3,5.3);
//       glScalef(0.01, 0.12, 0.01);
//       drawCube(0.1f, 0.1f, 0.1f,0.6, 0.6, 0.4);
//       glPopMatrix();


        //Freezer 2nd handle
       //glColor3f(0.1f, 0.1f, 0.1f);
//       glPushMatrix();
//       glTranslatef(1.06,2.3,5.3);
//       glScalef(0.01, 0.12, 0.01);
//       drawCube(0.1f, 0.1f, 0.1f,0.6, 0.6, 0.4);
//       glPopMatrix();
}
void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere (3.0, 20, 16);
}


void sphericalObject()
{
    //table top part
    glPushMatrix();
    glTranslatef(5, 0.2, 10);
    glScalef(0.1, 0.02, 0.1);
    drawSphere(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();

    //table leg
    glColor3f(0.2,0.1,0.1); //0.2,0.1,0.1
    glPushMatrix();
    glTranslatef(4.98,-0.1,10);
    glScalef(0.02, 0.1, 0.02);
    drawCube(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //base
    glPushMatrix();
    glTranslatef(5, -0.1, 10);
    glScalef(0.05, 0.01, 0.05);
    drawSphere(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();
}

//Drawing pyramid *************************
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}


void drawerTable()
{
    //Dressing table ************************************************

        //dressing table left body
        glPushMatrix();
        glTranslatef(5.9,0,4.6);
        glScalef(0.2, 0.2, 0.2);
        drawCube(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
        glPopMatrix();

     /*   //dressing table left body left stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(5.9,0,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.01, 0.3, 0.0001);
        drawCube();
        glPopMatrix();

        //dressing table left body right stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(6.5,0,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.01, 0.2, 0.0001);
        drawCube();
        glPopMatrix();

        //dressing table left body bottom stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(5.9,0,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.2, 0.01, 0.0001);
        drawCube();
        glPopMatrix();  */

        //dressing table right body
        glPushMatrix();
        glTranslatef(7,0,4.6);
        glScalef(0.2, 0.2, 0.2);
        drawCube(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
        glPopMatrix();

   /*     //dressing table right body left stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(7,0,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.01, 0.2, 0.0001);
        drawCube();
        glPopMatrix();

        //dressing table right body right stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(7.6,0,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.01, 0.3, 0.0001);
        drawCube();
        glPopMatrix();

        //dressing table right body bottom stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(7,0,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.2, 0.01, 0.0001);
        drawCube();
        glPopMatrix(); */

        //dressing table upper body
        glPushMatrix();
        glTranslatef(5.9,0.6,4.6);
        glScalef(0.57, 0.1, 0.2);
        drawCube(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
        glPopMatrix();

        //dressing table upper body bottom stripe
        glPushMatrix();
        glTranslatef(5.9,0.6,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.57, 0.01, 0.0001);
        drawCube(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        //dressing table upper body upper stripe
        glPushMatrix();
        glTranslatef(5.9,0.9,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.57, 0.01, 0.0001);
        drawCube(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        //dressing table upper body handle
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(6.5,0.75,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.16, 0.02, 0.0001);
        drawCube(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        //dressing table left body handle
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(6.4,0.1,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.02, 0.13, 0.0001);
        drawCube(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        //dressing table right body handle
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(7.1,0.1,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.02, 0.13, 0.0001);
        drawCube(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();





}

void tree(){
    //glColor3f(0.4, 0.1, 0.0);
//    glPushMatrix();
//    glTranslatef(0.0,-0.5,0.0);
//    glScalef(0.22, 0.3, 0.20);//(0.04, 0.6, 0.0001);
//    drawCube(0.4, 0.1, 0.0,0.4, 0.1, 0.0);
//    glPopMatrix();

           //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(0.3,0.2,0.3);
       glScalef(0.03, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

           //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.2,0.8,0.2);
    glScalef(0.1, 0.05, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();

               //glColor3f(0.6, 0.8, 0.1);
    glPushMatrix();
    glTranslatef(0.1,0.9,0.1);
    glScalef(0.15, 0.2, 0.15);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.8, 0.1,0.6, 0.8, 0.1);
    glPopMatrix();

               //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.2,1.4,0.2);
    glScalef(0.1, 0.08, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();
}

void DrawShelf() {

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glShadeModel(GL_SMOOTH);
    GLfloat mat_specular[] = {0.521, 0.376, 0.247, 1.0};
    GLfloat mat_diffuse[] = {0.521, 0.376, 0.247, 1.0};
    GLfloat mat_ambient[] = {0.521, 0.376, 0.247, 1.0};
    GLfloat mat_shininess = 5.0;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    /// shelf backside
    glPushMatrix();
    glColor3d(0,0,1);
    glTranslatef(0,3,-9.8);
    glScalef(5,3,0.5);
    glutSolidCube(1);
    glPopMatrix();

    /// left plank
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslatef(-2.5,3,-9);
    glScalef(0.05,3,1.5);
    glutSolidCube(1);
    glPopMatrix();

    /// right plank
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslatef(2.5,3,-9);
    glScalef(0.05,3,1.5);
    glutSolidCube(1);
    glPopMatrix();

    /// upper plank
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslatef(0,4.5,-9);
    glScalef(5,0.05,1.5);
    glutSolidCube(1);
    glPopMatrix();

    /// middle plank
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslatef(0,3,-9);
    glScalef(5,0.05,1.5);
    glutSolidCube(1);
    glPopMatrix();

    /// lower plank
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslatef(0,1.5,-9);
    glScalef(5,0.05,1.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();


}

void drawBook() {
    // Draw Book Cover
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(0.6, 0.8, 0.1);
    glColor3f(0.8, 0.6, 0.4);  // Brown color for the book cover
    glutSolidCube(1.0);  // You can replace glutSolidCube with your drawCube function
    glPopMatrix();

    // Draw Book Pages
    glPushMatrix();
    glTranslatef(0, 0, 0.05);  // Slightly in front of the book cover
    glScalef(0.58, 0.78, 0.09);
    glColor3f(1.0, 1.0, 1.0);  // White color for the book pages
    glutSolidCube(1.0);  // You can replace glutSolidCube with your drawCube function
    glPopMatrix();

    // Draw Book Spine
    glPushMatrix();
    glTranslatef(-0.3, 0, 0);
    glRotatef(90, 0, 1, 0);  // Rotate 90 degrees around the y-axis for the spine
    glScalef(0.1, 0.8, 0.1);
    glColor3f(0.4, 0.6, 0.8);  // Blue color for the book spine
    glutSolidCube(1.0);  // You can replace glutSolidCube with your drawCube function
    glPopMatrix();
}




void allwindow(){

    glPushMatrix();
    glTranslatef(11,0,1.7); //window 1
    glRotatef(-90, 0, 1, 0);
    window();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(17,0,1.7); //window 1
    glRotatef(-90, 0, 1, 0);
    window();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.2,0,0); //window 1
    window();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.2,0,-6); //window 3
    window();
    glPopMatrix();


}

void decoration(){
    glPushMatrix();
    allwindow();
    glPopMatrix();






  glPushMatrix();
  //glTranslatef(0.0, 0, 2.0); // Adjust the position of the table
  glScalef(0.75,0.75,0.75);
  fulltable(); // DRAW THE TABLE 1
  glPopMatrix();



  glPushMatrix();
  glTranslatef(0.0, 0, 7.0); // Adjust the position of the table
  glScalef(0.65,0.65,0.65);
  fulltable(); // DRAW THE TABLE 3
  glPopMatrix();



   glPushMatrix();
  glTranslatef(4.0, 0, 4.0); // Adjust the position of the table
  glScalef(0.75,0.75,0.75);
  fulltable(); // DRAW THE TABLE 4
  glPopMatrix();





  glPushMatrix();
  glTranslatef(8.0, 0, 0.0); // Adjust the position of the table
  glScalef(0.75,0.75,0.75);
  fulltable(); // DRAW THE TABLE 5
  glPopMatrix();



  glPushMatrix();
  glTranslatef(8.0, 0, 7.0); // Adjust the position of the table
  glScalef(0.75,0.75,0.75);
  fulltable(); // DRAW THE TABLE 5
  glPopMatrix();


//fan1
   glPushMatrix();
   glTranslatef(-3.0, 0, -5.0);
   fan();
   glPopMatrix();
//fan3
   glPushMatrix();
   glTranslatef(1.5, 0, -1.5);
   fan();
   glPopMatrix();
//fan5
   glPushMatrix();
   glTranslatef(5.0, 0, -5.5);
   fan();
   glPopMatrix();

//fan7
   glPushMatrix();
   glTranslatef(-3.0, 0, 1.0);
   fan();
   glPopMatrix();


//fan9
   glPushMatrix();
   glTranslatef(5.0, 0, 1.5);
   fan();
   glPopMatrix();

    glPushMatrix();
   glTranslatef(-1.5, -1, 1.5);
   freezer();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-1.5, -1, 7.5);
   freezer();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(10, -1, 2);
   glRotated(-90,0,1,0);
   freezer();
   glPopMatrix();


   glPushMatrix();
   glTranslatef(-0.6,0.6, -3);
   sphericalObject();
    glPopMatrix();

    lightBulb0();
    lightBulb1();

    glPushMatrix();
   glTranslatef(-0.2,1.5, 0);
    spotBulb();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, -0.5, 7.0); // Adjust the position of the table
    glScalef(0.75,0.75,0.75);
    glRotatef(-90,0,1,0);
    drawerTable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, -0.5, 8.0); // Adjust the position of the table
    glScalef(0.75,0.75,0.75);
    glRotatef(-90,0,1,0);
    drawerTable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, -0.5, 9.0); // Adjust the position of the table
    glScalef(0.75,0.75,0.75);
    glRotatef(-90,0,1,0);
    drawerTable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, -0.5, 10.0); // Adjust the position of the table
    glScalef(0.75,0.75,0.75);
    glRotatef(-90,0,1,0);
    drawerTable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, -0.5, 11.0); // Adjust the position of the table
    glScalef(0.75,0.75,0.75);
    glRotatef(-90,0,1,0);
    drawerTable();
    glPopMatrix();



     glPushMatrix();
    glTranslatef(4,-2.5,5);
    glRotated(-90,0,1,0);
    glScalef(0.75,0.75,0.75);
    DrawShelf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-0.4,5);
    glRotated(-90,0,1,0);
    glScalef(0.75,0.75,0.75);
    DrawShelf();
    glPopMatrix();




}
void torus(){
// torus
    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.4,1.3,slices,stacks);
    glPopMatrix();

//    glPushMatrix();
//        glTranslated(2.4,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireTorus(0.2,0.8,slices,stacks);
//    glPopMatrix();

}
void torus2(){
// torus
    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.4,0.7,slices,stacks);
    glPopMatrix();

//    glPushMatrix();
//        glTranslated(2.4,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireTorus(0.2,0.8,slices,stacks);
//    glPopMatrix();

}
void torusshade(){
    //top torus
    glPushMatrix();
    glTranslatef(-5, -1, 27);  // Position slightly above ground
    glScalef(4,1.2,4);
    glRotatef(30,1,0,0);
//    glRotatef(180,0,1,0);
    torus2();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-5, -22.5, 27);  // Position slightly above ground
    glScalef(4,5.5,4);
    glRotatef(30,1,0,0);
//    glRotatef(180,0,1,0);
    torus();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //connect piller
    glPushMatrix();
    glTranslatef(0, 2, 6.5);
    glRotatef(-45,0,0,1);
    glScalef(0.2, 1, 0.1);
    drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
    glPopMatrix();
    //connect piller2
    glPushMatrix();
    glTranslatef(9.5, 1.5, 6.8);
    glRotatef(45,0,0,1);
    glScalef(0.2, 1, 0.1);
    drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
    glPopMatrix();

        //connect piller3

    glPushMatrix();
    glTranslatef(9.5, 1.5, 10);
    glRotatef(45,0,0,1);
    glScalef(0.2, 1, 0.1);
    drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
    glPopMatrix();

    //connect piller3

    glPushMatrix();
    glTranslatef(0,2,10);
    glRotatef(-45,0,0,1);
    glScalef(0.2, 1, 0.1);
    drawCube(0.8, 0.7, 0.4,0.8, 0.7, 0.4);
    glPopMatrix();
}
void base()
{
     //front wall
//    glColor3f(0.8, 0.9, 0.9);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-2.1,-1,.5);
    glScalef(8, 10, 0.1);
    Cube(1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//     left wall
//    glColor3f(0.5, 0.5, 0.6);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-2.4,-1,0);
    glScalef(0.1, 10, 7);
    Cube(1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    right wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(21,-1,0);
    glScalef(0.1, 10, 7);
    Cube(1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



   //ceiling
    //glColor3f(0.8, 0.8, 0.9);

//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,3);
//    glPushMatrix();
//    glTranslatef(-2.1,10,0);
//    glScalef(8, 0.1, 7);
//    //drawCube(1, 1, 1,1, 1, 1);
//    Cube(1,1,1,1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);



     // surface
    //glColor3f(0.8, 0.8, 0.9);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glPushMatrix();
    glTranslatef(-2.8,-1,0);
    glScalef(8, 0.1, 7);
    Cube(1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void standlight(){
    //glColor3f(0.4, 0.1, 0.0);
    glPushMatrix();
    glTranslatef(0.0,-0.5,0.0);
    glScalef(0.8, 0.5, 0.1);//(0.04, 0.6, 0.0001);pot
    drawCube(0.4, 0.1, 0.0,0.4, 0.1, 0.0);
    glPopMatrix();

    //glColor3f(0.8,0.6,0.4);stand
    glPushMatrix();
    glTranslatef(1.2,0.2,0.1);
    glScalef(0.03, 0.8, 0.03);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();
//light col 1
    glPushMatrix();
    glTranslatef(-0.7,-5.3,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7,-4.8,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7,-4.3,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    //col 2
    //light
    glPushMatrix();
    glTranslatef(0.1,-5.3,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,-4.8,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,-4.3,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    //col 3
    //light
    glPushMatrix();
    glTranslatef(1,-5.3,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-4.8,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-4.3,-7.78);
    glScalef(1,1,1);
    lightBulb0();
    glPopMatrix();

}
void stadiumlight(){
    //    stadium light
    glPushMatrix();
    glTranslatef(3, 2, 10);  // Position slightly above ground
    glRotatef(180,1,0,0);
    glRotatef(180,0,1,0);
    standlight();
    glPopMatrix();
}
void feildblock(){
//seat-backup
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(1, 1, 8);
    glScalef(0.8, 0.05, 0.9);
    Cube(1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void seatblock(){
//seat-backup
    glPushMatrix();
    glTranslatef(0, -0.1, 1.7);
    glScalef(1,0.3,0.5);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.5, 1);
    glScalef(1,0.3,0.5);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.2, 0.3);
    glScalef(1,0.3,0.5);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.8, -0.2);
    glScalef(1,0.3,0.5);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();


}
void seatfst(){
    glPushMatrix();
    glTranslatef(3,-0.7,4.7);
    glScalef(0.7,0.9,0.5);
    seatblock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-0.7,5.4);
    glScalef(0.29,0.9,0.4);
    glRotatef(30,0,1,0);
    seatblock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.3,-0.7,6.5);
    glScalef(0.25,0.9,0.4);
    glRotatef(85,0,1,0);
    seatblock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-0.7,4.7);
    glScalef(0.7,0.9,0.5);
    seatblock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.9,-0.7,4.8);
    glScalef(0.7,0.9,0.5);
    glRotatef(-15,0,1,0);
    seatblock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.7,-0.7,5.1);
    glScalef(0.29,0.9,0.4);
    glRotatef(-30,0,1,0);
    seatblock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.6,-0.7,5.8);
    glScalef(0.25,0.9,0.4);
    glRotatef(-90,0,1,0);
    seatblock();
    glPopMatrix();

}


void thewhole(){

        //    field
    glPushMatrix();
    glTranslatef(0.3, -1.83, -1);
    glScalef(2,1,1);
    feildblock();
    glPopMatrix();
// light 1
    glPushMatrix();
    glTranslatef(18,0,6.7);
    glRotatef(-90,0,1,0);
    stadiumlight();
    glPopMatrix();

// light 2

    glPushMatrix();
    glTranslatef(-8.5,0,10.2);
    glRotatef(90,0,1,0);
    stadiumlight();
    glPopMatrix();

    //field block

    //glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    glTranslatef(5,-1,10);
    glScalef(0.6,0.4,0.05);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-1,10);
    glScalef(0.6,0.4,0.05);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-1,6.5);
    glScalef(0.6,0.4,0.05);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-1,6.5);
    glScalef(0.6,0.4,0.05);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-1,10);
    glRotatef(90,0,1,0);
    glScalef(1.1,0.4,0.05);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.2,-1,10);
    glRotatef(90,0,1,0);
    glScalef(1.1,0.4,0.05);
    drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
    glPopMatrix();


}
void building(){
    glPushMatrix();//for building
    glTranslatef(0,0,-2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(20,-1,-35);
    glScalef(1,1,10);
    freezer();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(19,-3.39,125);
    glRotatef(180,0,1,0);
    glScalef(1,2.2,12);
    window();
    glPopMatrix();

    glPopMatrix();//for building

    glPushMatrix();//building2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(17,-1,-2.3);
    glScalef(3,1,1.3);
    freezer();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(46.5,-3,6);
    glScalef(3,2,1);
    glRotatef(-90,0,1,0);
    window();
    glPopMatrix();

    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();//building2
    glTranslatef(37,0,21);
    glRotatef(-180,0,1,0);
    glPushMatrix();
    glTranslatef(17,-1,-2.3);
    glScalef(3,1,1.3);
    freezer();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(-10,-3,2);
    glScalef(3,2,1);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9,-3,3);
    glScalef(3,2,1);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,-3,16.1);
    glScalef(3,2,1);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();




    glPopMatrix();
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60,1,1,1500);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0

    //glViewport(0, 0, 800, 600);

    glPushMatrix();
    glScalef(10,10,10);


    building();

    glPushMatrix();
    glTranslatef(19,0,20);
    glRotatef(180,0,1,0);
    building();
    glPopMatrix();






    base();  // DRAW THE BASE OF THE HOUSE

    glPushMatrix();
    glTranslatef(7,0,0);
    glScalef(1,0.7,1);
    torusshade();
    thewhole();
    seatfst();
    glPushMatrix();
    glTranslatef(10,0,16.5);
    glRotatef(185,0,1,0);
    seatfst();
    glPopMatrix();

    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,-2,0);
    glScalef(3,5,5);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-2,0);
    glScalef(3,5,5);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5,-2,16);
    glScalef(3,5,5);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-2,16);
    glScalef(3,5,5);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2,13);
    glScalef(3,5,5);
    tree();
    glPopMatrix();

////    ROad

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(2.3,-0.9,0);
    glScalef(1,0.1,7);
    Cube(1,1,1,1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1,-0.9,21);
    glRotatef(90,0,1,0);
    glScalef(1,0.1,7);
    Cube(1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,6);
//    glPushMatrix();
//    glTranslatef(0,0,5);
//    glScalef(1.5,0.6,0.1);
//    glRotatef(180,0,1,0);
//    Cube(1,1,1,1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);


    glPopMatrix();



//    seats

//

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            break;
        case 'q': //back to default eye point and ref point
                eyeX=7.0; eyeY=2.0; eyeZ=15.0;
                refX=0.0; refY=0.0; refZ=0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'b': // move ref point left along X axis
            refX-=3.0;
            break;
        case 'm': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'k':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'l': //move ref point towards screen/ along z axis
            refZ-=1;
            break;
        case '1': //to turn on and off light one
            if(switchOne == false)
            {
                switchOne = true; amb1=true; diff1=true; spec1=true;
                glEnable( GL_LIGHT0); break;
            }
            else if(switchOne == true)
            {
                switchOne = false; amb1=false; diff1=false; spec1=false; glDisable( GL_LIGHT0); break;
            }
        case '2': //to turn on and off light two
            if(switchTwo == false)
            {
                switchTwo = true; amb2=true; diff2=true; spec2=true;
                glEnable( GL_LIGHT1); break;
            }
            else if(switchTwo == true)
            {
                switchTwo = false; amb2=false; diff2=false; spec2=false;
                glDisable( GL_LIGHT1); break;
            }
        case '3': //to turn on and off light one
            if(switchLamp == false)
            {
                switchLamp = true; amb3=true; diff3=true; spec3=true;
                glEnable( GL_LIGHT2); break;
            }
            else if(switchLamp == true)
            {
                switchLamp = false; amb3=false; diff3=false; spec3=false;
                glDisable( GL_LIGHT2); break;
            }
        case'4': //turn on/off ambient light 1
            if(amb1 == false) {amb1=true; break;}
            else{amb1=false; break;}
        case'5':
            if(diff1 == false) {diff1=true; break;}
            else{diff1=false; break;}
        case'6':
            if(spec1 == false) {spec1=true; break;}
            else{spec1=false; break;}
        case'7': //turn on/off ambient light 2
            if(amb2 == false) {amb2=true; break;}
            else{amb2=false; break;}
        case'8':
            if(diff2 == false) {diff2=true; break;}
            else{diff2=false; break;}
        case'9':
            if(spec2 == false) {spec2=true; break;}
            else{spec2=false; break;}
        case'e': //turn on/off ambient lamp light
            if(amb3 == false) {amb3=true; break;}
            else{amb3=false; break;}
        case'r':
            if(diff3 == false) {diff3=true; break;}
            else{diff3=false; break;}
        case't':
            if(spec3 == false) {spec3=true; break;}
            else{spec3=false; break;}
        case 27:    // Escape key
            exit(1);
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    std::cout<<"To move Eye point:"<< std::endl;
    std::cout<<"w: up"<<std::endl;
    std::cout<<"s: down"<<std::endl;
    std::cout<<"a: left"<<std::endl;
    std::cout<<"d: right"<<std::endl;
    std::cout<<"i: zoom in"<<std::endl;
    std::cout<<"o: zoom out"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"To move Camera point:"<< std::endl;
    std::cout<<"j: up"<<std::endl;
    std::cout<<"n: down"<<std::endl;
    std::cout<<"b: left"<<std::endl;
    std::cout<<"m: right"<<std::endl;
    std::cout<<"l: move nearer"<<std::endl;
    std::cout<<"k: move far"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Press q to move to default position"<<std::endl;
    std::cout<<"      "<<std::endl;


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("stadium");
    LoadTexture("E:\\7th_sem\\CGIPL\\my_stadium\\bmp\\600x600.bmp");
    LoadTexture("E:\\7th_sem\\CGIPL\\my_stadium\\bmp\\surface.bmp");
    LoadTexture("E:\\7th_sem\\CGIPL\\my_stadium\\bmp\\clouds.bmp");
    LoadTexture("E:\\7th_sem\\CGIPL\\my_stadium\\bmp\\Road.bmp");
    LoadTexture("E:\\7th_sem\\CGIPL\\my_stadium\\bmp\\buildings.bmp");
    LoadTexture("E:\\7th_sem\\CGIPL\\my_stadium\\bmp\\premier.bmp");






    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    light1();
    light2();
    lampLight();

    glPushMatrix();
    glTranslatef(1.0, 1.0, 1.0);  // Light position

    glBegin(GL_QUADS);
    glVertex3f(-0.1, -0.1, 0.0); // Bottom-left corner
    glVertex3f(0.1, -0.1, 0.0);  // Bottom-right corner
    glVertex3f(0.1, 0.1, 0.0);   // Top-right corner
    glVertex3f(-0.1, 0.1, 0.0);  // Top-left corner
    glEnd();

    glPopMatrix();


    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutMainLoop();

    return 0;
}
