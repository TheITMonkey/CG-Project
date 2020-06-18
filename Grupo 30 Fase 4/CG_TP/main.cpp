#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

// #include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#endif

/* Library Includes. */
#include <IL/il.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <tuple>

/* Personal Includes. */
#include "parser.h"
#include "extractor.h"

using namespace std;

typedef tuple<double, double, double> coords;

// Global variables
float alpha = 1, beta = 1, radius = 400;
double red = 0.6, green = 0.8, blue = 1;
double step = 0;

double** vbo;
double *vs, *ns, *ts;
int ntriangles = 0;

vector<First*> files;
vector<coords> triangles;
vector<coords> normals;
vector<coords> textures;
vector<Light*> lights;

GLuint buffers[1];
GLuint norms[1];
GLuint txts[1];
GLuint* ids;


void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0) h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// m[1][4] * n[4][4] = res[1][4]
void multiplication1(double m[1][4], double n[4][4], double res[1][4])
{
    res[0][0] = m[0][0] * n[0][0] + m[0][1] * n[1][0] + m[0][2] * n[2][0] + m[0][3] * n[3][0];
    res[0][1] = m[0][0] * n[0][1] + m[0][1] * n[1][1] + m[0][2] * n[2][1] + m[0][3] * n[3][1];
    res[0][2] = m[0][0] * n[0][2] + m[0][1] * n[1][2] + m[0][2] * n[2][2] + m[0][3] * n[3][2];
    res[0][3] = m[0][0] * n[0][3] + m[0][1] * n[1][3] + m[0][2] * n[2][3] + m[0][3] * n[3][3];
}

// m[1][4] * n[4][1] = res
void multiplication2(double m[1][4], double n[4][1], double* res)
{
    *res = m[0][0] * n[0][0] + m[0][1] * n[1][0] + m[0][2] * n[2][0] + m[0][3] * n[3][0];
}

// m[4][4] * n[4] = res[4]
void multiplication3(float *m, float *v, float *res)
{
    for (int i = 0; i < 4; ++i) {

        res[i] = 0;
        for (int j = 0; j < 4; ++j) {

            res[i] += v[j] * m[i*4+j];

        }
    }
}

void dynamicRotation(int x, Second* second, double timer){

    double static angle[20];
    angle[x] += 360 / (timer * 1000);

    glRotated(angle[x], second->params[0], second->params[1], second->params[2]);


}

void getCatmullRomPoint(double t, double* p0, double* p1, double* p2, double* p3, double* pos, float *deriv)
{
    double x, y, z;

    double res[1][4];

    double matrixT[1][4] = { { powf(t,3), powf(t,2), t, 1 } };

    // Matrix Catmull-Rom
    double m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                       { 1.0f, -2.5f,  2.0f, -0.5f},
                       {-0.5f,  0.0f,  0.5f,  0.0f},
                       { 0.0f,  1.0f,  0.0f,  0.0f} };

    double px[4][1] = { { p0[0] }, { p1[0] }, { p2[0] }, { p3[0] } };
    double py[4][1] = { { p0[1] }, { p1[1] }, { p2[1] }, { p3[1] } };
    double pz[4][1] = { { p0[2] }, { p1[2] }, { p2[2] }, { p3[2] } };

    multiplication1(matrixT, m, res);

    multiplication2(res, px, &x);
    multiplication2(res, py, &y);
    multiplication2(res, pz, &z);

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;

    float a[4][4] = { 0 };

    float arrayPX[4];
    float arrayPY[4];
    float arrayPZ[4];

    float dt[4] = { 3 * powf(t,2), static_cast<float>(2 * t), 1, 0 };

    arrayPX[0] = px[0][0];
    arrayPX[1] = px[1][0];
    arrayPX[2] = px[2][0];
    arrayPX[3] = px[3][0];
    arrayPY[0] = py[0][0];
    arrayPY[1] = py[1][0];
    arrayPY[2] = py[2][0];
    arrayPY[3] = py[3][0];
    arrayPZ[0] = pz[0][0];
    arrayPZ[1] = pz[1][0];
    arrayPZ[2] = pz[2][0];
    arrayPZ[3] = pz[3][0];

    multiplication3(reinterpret_cast<float *>(*m), arrayPX, a[0]);
    multiplication3(reinterpret_cast<float *>(*m), arrayPY, a[1]);
    multiplication3(reinterpret_cast<float *>(*m), arrayPZ, a[2]);

    multiplication3(*a, dt, deriv);
}

void getGlobalCatmullRomPoint(float gt, double pos[4], float *deriv, double curve[][3], int size)
{
    double t = gt * size;
    int index = floor(t);
    t = t - index;

    int indices[4];
    indices[0] = (index + size-1) % size;
    indices[1] = (indices[0]+1) % size;
    indices[2] = (indices[1]+1) % size;
    indices[3] = (indices[2]+1) % size;

    getCatmullRomPoint(t, curve[indices[0]], curve[indices[1]], curve[indices[2]], curve[indices[3]], pos, deriv);

}

int fillCurve(vector<coords>& points, double curve[][3])
{
    int res = 0;
    vector<coords>::iterator i;

    for (i = points.begin(); i != points.end(); i++) {

        coords aux = *i;

        curve[res][0] = get<0>(aux);
        curve[res][1] = get<1>(aux);
        curve[res][2] = get<2>(aux);

        res++;

    }

    return res; // returns the number of points in the curve
}

void renderCatmullRomCurve(int x, Second* second)
{

    int size;

    static double tt[20];
    static double time = 0;
    static double elapsedTime[20];

    Translation* translation = second->translation;
    double curve[translation->points.size()][3];

    size = fillCurve(translation->points, curve);

    double pos[4];
    float deriv[4];
    int npoints = 80;


    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < npoints; i++) {

        getGlobalCatmullRomPoint((double) i/npoints, pos, deriv, curve, size);
        glColor3f(0.2, 0.2, 0.2);
        glVertex3d(pos[0], pos[1], pos[2]);

    }

    glEnd();

    getGlobalCatmullRomPoint(tt[x], pos, deriv, curve, size);

    if (time < files.size()) {

        elapsedTime[x] = 1 / (translation->time*1000);
        time++;

    }

    tt[x] += elapsedTime[x];

    glTranslated(pos[0], pos[1], pos[2]);

}

void addColor(Color* color)
{

    GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat dif[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat spec[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat emis[4] = {0.0, 0.0, 0.0, 1.0};

    if (strcmp(color->type, "diffuse") == 0) {
        dif[0] = static_cast<GLfloat>(color->colors[0]);
        dif[1] = static_cast<GLfloat>(color->colors[1]);
        dif[2] = static_cast<GLfloat>(color->colors[2]);
        dif[3] = 1;

        glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
    }

    if (strcmp(color->type, "specular") == 0) {
        spec[0] = static_cast<GLfloat>(color->colors[0]);
        spec[1] = static_cast<GLfloat>(color->colors[1]);
        spec[2] = static_cast<GLfloat>(color->colors[2]);
        spec[3] = 1;

        glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    }

    if (strcmp(color->type, "emissive") == 0) {
        emis[0] = static_cast<GLfloat>(color->colors[0]);
        emis[1] = static_cast<GLfloat>(color->colors[1]);
        emis[2] = static_cast<GLfloat>(color->colors[2]);
        emis[3] = 1;

        glMaterialfv(GL_FRONT, GL_EMISSION, emis);
    }

    if (strcmp(color->type, "ambient") == 0) {
        amb[0] = static_cast<GLfloat>(color->colors[0]);
        amb[1] = static_cast<GLfloat>(color->colors[1]);
        amb[2] = static_cast<GLfloat>(color->colors[2]);
        amb[3] = 1;

        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    }

}

bool checkEnding(coords firstTriangle, coords secondTriangle, coords thirdTriangle)
{
    coords end = make_tuple(12345, 12345, 12345);

    return (firstTriangle == end && secondTriangle == end && thirdTriangle == end);
}

void drawVBOs(void)
{

    int x = 0;
    vector<First*>::iterator iFirst;
    vector<Second*>::iterator iSecond;

    iFirst = files.begin();

    while (iFirst != files.end()) {

        First* first = *iFirst;
        glPushMatrix();

        iSecond = first->transfs.begin();

        while (iSecond != first->transfs.end()) {

            Second* second = *iSecond;

            if (strcmp(second->transf, "translate") == 0) {

                if(second->translation == nullptr)
                    glTranslated(second->params[0], second->params[1], second->params[2]);

                else
                    renderCatmullRomCurve(x, second);

            }

            if (strcmp(second->transf, "rotate") == 0) {

                if(second->translation == nullptr)
                    glRotated(second->params[3], second->params[0], second->params[1], second->params[2]);

                else{

                    double timer = second->translation->time;
                    dynamicRotation(x, second, timer);
                }

            }

            if (strcmp(second->transf, "scale") == 0)
                glScaled(second->params[0], second->params[1], second->params[2]);

            if (strcmp(second->transf, "color") == 0)
                glColor3d(second->params[0], second->params[1], second->params[2]);

            iSecond++;

        }

        if (first->color != NULL)
            addColor(first->color);

        //glBindTexture(GL_TEXTURE_2D, ids[x]);
        glDrawArrays(GL_TRIANGLES, (x * first->npoints), first->npoints);
        //glBindTexture(GL_TEXTURE_2D, 0);

        glPopMatrix();

        x++;
        iFirst++;

    }
}

void addLight(){

    GLfloat pos[4] = {0.0, 0.0, 1.0, 0.0};
    GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat spotDir[3] = {0.0, 0.0, -1.0};

    Light* l = lights.front();

    pos[0] = static_cast<GLfloat>(l->params[0]);
    pos[1] = static_cast<GLfloat>(l->params[1]);
    pos[2] = static_cast<GLfloat>(l->params[2]);
    pos[3] = 1;

    if(strcmp(l->type, "POINT") == 0){

        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

    }

    else if(strcmp(l->type, "DIRECTIONAL") == 0){

        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

    }

    else if(strcmp(l->type, "SPOTLIGHT") == 0){

        spotDir[0] = static_cast<GLfloat>(l->params[0]);
        spotDir[1] = static_cast<GLfloat>(l->params[1]);
        spotDir[2] = static_cast<GLfloat>(l->params[2]);

        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);

    }

}

void renderScene(void)
{
	// clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(radius * cos(beta) * sin(alpha), radius * sin(beta), radius * cos(beta) * cos(alpha),
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    addLight();

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_DOUBLE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, norms[0]);
    glNormalPointer(GL_DOUBLE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ids[0]);
    glTexCoordPointer(2, GL_DOUBLE, 0, 0);

    // put drawing instructions here
    drawVBOs();

    //drawOrbits();

    float amb[4] = {0.2, 0.2, 0.2, 1.0};
    float dif[4] = {1.0, 1.0, 1.0, 1.0};
    float spec[4] = {0.0, 0.0, 0.0, 1.0};
    float emi[4] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_EMISSION, emi);

	// End of frame
	glutSwapBuffers();
}

// Camera zoom
void processKeys(unsigned char key, int xx, int yy)
{

    // put code to process regular keys in here
    if(key == 'w') radius-=12;
    if(key == 's') radius+=12;

    glutPostRedisplay();

}

// Camera movement
void processSpecialKeys(int key, int xx, int yy)
{
    switch (key) {
        case GLUT_KEY_RIGHT:
            alpha += 0.05;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            alpha -= 0.05;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(beta < M_PI/2)
                beta += 0.05;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(beta > -M_PI/2)
                beta -= 0.05;
            glutPostRedisplay();
            break;
        default:
            cout << "Command not recognized!" << "\n";
    }
}

void fillArrays(){

    glGenBuffers(1, buffers);
    glGenBuffers(1, norms);
    glGenBuffers(1, txts);

    int nv = 0;
    int nn = 0;
    int nt = 0;
    bool flag;

    vs = (double*) malloc(sizeof(double)*ntriangles*3);
    ns = (double*) malloc(sizeof(double)*ntriangles*3);
    ts = (double*) malloc(sizeof(double)*ntriangles*2);

    vector<coords>::iterator iTriangles;
    vector<coords>::iterator iNormals;
    vector<coords>::iterator iTextures;

    iTriangles = triangles.begin();
    iNormals = normals.begin();
    iTextures = textures.begin();

    while(iTriangles != triangles.end()){

        flag = false;

        while(!flag){

            coords triangle1 = *iTriangles;
            iTriangles++;
            coords triangle2 = *iTriangles;
            iTriangles++;
            coords triangle3 = *iTriangles;
            iTriangles++;

            coords normal1 = *iNormals;
            iNormals++;
            coords normal2 = *iNormals;
            iNormals++;
            coords normal3 = *iNormals;
            iNormals++;

            coords texture1 = *iTextures;
            iTextures++;
            coords texture2 = *iTextures;
            iTextures++;
            coords texture3 = *iTextures;
            iTextures++;

            if(!checkEnding(triangle1, triangle2, triangle3)){

                vs[nv++] = get<0>(triangle1);
                vs[nv++] = get<1>(triangle1);
                vs[nv++] = get<2>(triangle1);

                ns[nn++] = get<0>(normal1);
                ns[nn++] = get<1>(normal1);
                ns[nn++] = get<2>(normal1);

                ts[nt++] = get<0>(texture1);
                ts[nt++] = get<1>(texture1);
                ts[nt++] = get<2>(texture1);

                vs[nv++] = get<0>(triangle2);
                vs[nv++] = get<1>(triangle2);
                vs[nv++] = get<2>(triangle2);

                ns[nn++] = get<0>(normal2);
                ns[nn++] = get<1>(normal2);
                ns[nn++] = get<2>(normal2);

                ts[nt++] = get<0>(texture2);
                ts[nt++] = get<1>(texture2);
                ts[nt++] = get<2>(texture2);

                vs[nv++] = get<0>(triangle3);
                vs[nv++] = get<1>(triangle3);
                vs[nv++] = get<2>(triangle3);

                ns[nn++] = get<0>(normal3);
                ns[nn++] = get<1>(normal3);
                ns[nn++] = get<2>(normal3);

                ts[nt++] = get<0>(texture3);
                ts[nt++] = get<1>(texture3);
                ts[nt++] = get<2>(texture3);


            }
            else
                flag = true;

        }

    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, ntriangles*8*3, vs, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, norms[0]);
    glBufferData(GL_ARRAY_BUFFER, ntriangles*8*3, ns, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, txts[0]);
    glBufferData(GL_ARRAY_BUFFER, ntriangles*8*2, ts, GL_STATIC_DRAW);


}

int load(string txt){

    unsigned int t, tw, th;
    unsigned char *data;
    unsigned int id;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)txt.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    data = ilGetData();

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return id;

}

int main(int argc, char** argv)
{

    parser("../config.xml", files, lights);

    extractor(&ntriangles, files, triangles, normals, textures);

    //debug(files, lights.front());

    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 900);
	glutCreateWindow("CGTP - Fase 4");
		
    // Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

#ifndef __APPLE__
    glewInit();
#endif

    fillArrays();

    int i = 0;
    ids = (GLuint*) malloc(sizeof(GLuint) * files.size());
    vector<First*>::iterator itFiles;

    for(itFiles = files.begin(); itFiles != files.end(); itFiles++){

        First* first = *itFiles;

        if(first->texture != NULL){

            char file[50] = "../tex/";
            char* txt = strcat(file, first->texture);
            ids[i] = load(string(txt));

        }

        i++;

    }

    // OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    // enter GLUT's main cycle
	glutMainLoop();

	return 1;

}
