#ifndef CG_TP_PARSER_H
#define CG_TP_PARSER_H

#include <iostream>
#include "tinyxml2.h"
#include <string.h>
#include <vector>

using namespace tinyxml2;
using namespace std;

typedef tuple<double, double, double> coords;

typedef struct color{
    char* type;
    double colors[3];
} Color;

typedef struct translation {
    double time;
    vector<coords> points;
} Translation;

typedef struct aux {
    char* transf;
    double params[4];
    Translation* translation;
    struct aux* next;
} Aux;

typedef struct second {
    char* transf;
    double params[4];
    Translation* translation;
} Second;

typedef struct first {
    char* file;
    char* texture;
    int npoints;
    Color* color;
    vector<Second*> transfs;
} First;

typedef struct light{
    char* type;
    double params[3];
} Light;

typedef Aux* Group[20];

void init(Group g);

void addAux(Group g, int i, char transf[], double x, double y, double z, double angle, Translation* translation);

void addPoint(double x, double y, double z, vector<coords>& points);

void addFile(char* file, char* texture, Color* color, Group g, vector<First*>& files);

void debug(vector<First*>& files, Light* light);

void groupParser(const XMLElement* scene, Group g, int i, vector<First*>& files);

void parser(const char* config, vector<First*>& files, vector<Light*>& light);

#endif
