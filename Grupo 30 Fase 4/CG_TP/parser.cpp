#include <tuple>
#include "parser.h"

void debug(vector<First*>&  files, Light* light)
{

    cout << "Light" << endl;
    cout << "   Type: " << light->type << endl;
    cout << "   X = " << light->params[0] << " Y = " << light->params[1] << " Z = " << light->params[2] << endl;
    cout << "------------------------------------------" << endl;
    cout << "" << endl;

    for (vector<First*>::iterator iFirst = files.begin(); iFirst != files.end(); iFirst++) {

        First* first = *iFirst;
        cout << "File: " << first->file << endl;

        if(first->texture != NULL)
            cout << "   Texture: " << first->texture << endl;

        if(first->color != NULL){

            cout << "   Color Type: " << first->color->type << endl;
            cout << "   Red: " << first->color->colors[0] << endl;
            cout << "   Green: " << first->color->colors[1] << endl;
            cout << "   Blue: " << first->color->colors[2] << endl;

        }

        vector<Second*> v1 = first->transfs;

        for (vector<Second*>::iterator iSecond = v1.begin(); iSecond != v1.end(); iSecond++) {
            Second* second = *iSecond;
            cout << "   Transformation: " << second->transf << endl;

            Translation* translation = second->translation;

            if (translation) {

                cout << "       Time: " << translation->time << endl;

                vector<coords> v2 = translation->points;
                cout << "       Number of points: " << translation->points.size() << endl;

                for (vector<coords>::iterator iTranslation = v2.begin(); iTranslation != v2.end(); iTranslation++) {

                    coords c = *iTranslation;
                    cout << "           :: X = " << get<0>(c) << " Y = " << get<1>(c) << " Z = " << get<2>(c) << endl;

                }
            }
            else
                cout << "   X = " << second->params[0] << " Y = " << second->params[1] << " Z = " << second->params[2] << " Angle = " << second->params[3] << endl;

            cout << endl;

        }

        cout << "------------------------------------------" << endl;
        cout << "" << endl;

    }
}

void init(Group g)
{
    for (int i = 0; i < 20; i++)
        g[i] = NULL;

}

void addFile(char* file, char* texture, Color* color, Group g, vector<First*>& files)
{
    First* first = new First();
    first->file = new char[15];

    vector<Second*> transfs;

    for (int i = 0; g[i]; i++) {

        Aux* aux;
        for (aux = g[i]; aux; aux = aux->next) {

            Second* second = new Second();

            second->params[0] = aux->params[0];
            second->params[1] = aux->params[1];
            second->params[2] = aux->params[2];
            second->params[3] = aux->params[3];

            second->translation = aux->translation;

            second->transf = new char[15];
            strcpy(second->transf, aux->transf);

            transfs.push_back(second);

        }
    }

    strcpy(first->file, file);

    if(texture != NULL){

        first->texture = (char*) malloc(sizeof(char)*30);
        strcpy(first->texture, texture);

    }
    else
        first->texture = NULL;

    first->npoints = 0;
    first->transfs = transfs;

    if(color != NULL){

        first->color = new Color();
        first->color->type = (char*) malloc(sizeof(char)*20);
        strcpy(first->color->type, color->type);

        first->color->colors[0] = color->colors[0];
        first->color->colors[1] = color->colors[1];
        first->color->colors[2] = color->colors[2];

    }
    else
        first->color = NULL;

    files.push_back(first);

}

void addAux(Group g, int i, char transf[], double x, double y, double z, double angle, Translation* translation)
{
    Aux* old = g[i];

    Aux* aux = (Aux*)malloc(sizeof(struct aux));

    aux->transf = (char*)malloc(sizeof(char) * 15);
    strcpy(aux->transf, transf);
    aux->params[0] = x;
    aux->params[1] = y;
    aux->params[2] = z;
    aux->params[3] = angle;
    aux->translation = translation;
    aux->next = NULL;

    if (g[i] == NULL)
        g[i] = aux;

    else {

        while (old->next != NULL)
            old = old->next;

        old->next = aux;

    }
}

void addPoint(double x, double y, double z, vector<coords>& points){

    coords p = make_tuple(x, y, z);

    points.push_back(p);

}

void groupParser(const XMLElement* scene, Group g, int i, vector<First*>& files)
{

    double x;
    double y;
    double z;
    double angle;
    double time;

    for (const XMLElement* group = scene->FirstChildElement(); group; group = group->NextSiblingElement()) {

        Translation* translation = NULL;

        if (strcmp((char*)group->Value(), "translate") == 0) {

            x = 0;
            y = 0;
            z = 0;

            char transf[15];
            strcpy(transf, (char*)group->Value());

            vector<coords> points;

            if(group->Attribute("time")) {

                char* timeString = (char *) group->Attribute("time");
                time = atof(timeString);

                for(const XMLElement* translate = group->FirstChildElement(); translate; translate = translate->NextSiblingElement()){

                    char* pointX = (char*) translate->Attribute("X");
                    if(pointX != NULL) {
                        x = atof(pointX);
                    }

                    char* pointY = (char*) translate->Attribute("Y");
                    if(pointY != NULL) {
                        y = atof(pointY);
                    }

                    char* pointZ = (char*) translate->Attribute("Z");
                    if(pointZ != NULL) {
                        z = atof(pointZ);
                    }

                    addPoint(x, y, z, points);

                }

                translation = new Translation();
                translation->time = time;
                translation->points = points;

            }
            else {

                char* translateX = (char*) group->Attribute("X");
                if (translateX != NULL)
                    x = atof(translateX);

                char* translateY = (char*) group->Attribute("Y");
                if (translateY != NULL)
                    y = atof(translateY);

                char* translateZ = (char*) group->Attribute("Z");
                if (translateZ != NULL)
                    z = atof(translateZ);

            }

            addAux(g, i, transf, x, y, z, 0, translation);
        }

        if (strcmp((char*)group->Value(), "rotate") == 0) {

            char transf[10];
            strcpy(transf, (char*)group->Value());

            x = 0;
            y = 0;
            z = 0;
            angle = 0;
            vector<coords> points;

            char* rotateX = (char*) group->Attribute("X");
            if (rotateX != NULL) {
                x = atof(rotateX);
            }

            char* rotateY = (char*) group->Attribute("Y");
            if (rotateY != NULL) {
                y = atof(rotateY);
            }

            char* rotateZ = (char*) group->Attribute("Z");
            if (rotateZ != NULL) {
                z = atof(rotateZ);
            }

            if(group->Attribute("time")){

                char* timeString = (char *) group->Attribute("time");
                time = atof(timeString);

                translation = new Translation();
                translation->time = time;
                translation->points = points;

            }
            else{

                char *rotateAngle = (char *) group->Attribute("angle");
                if (rotateAngle != NULL)
                    angle = atof(rotateAngle);

            }

            addAux(g, i, transf, x, y, z, angle, translation);

        }

        if (strcmp((char*)group->Value(), "scale") == 0) {

            char transf[10];
            strcpy(transf, (char*) group->Value());

            x = 0;
            y = 0;
            z = 0;

            char* scaleX = (char*) group->Attribute("X");
            if (scaleX != NULL)
                x = atof(scaleX);

            char* scaleY = (char*) group->Attribute("Y");
            if (scaleY != NULL)
                y = atof(scaleY);

            char* scaleZ = (char*) group->Attribute("Z");
            if (scaleZ != NULL)
                z = atof(scaleZ);

            addAux(g, i, transf, x, y, z, 0, translation);

        }

        if (strcmp((char*)group->Value(), "color") == 0) {

            char transf[10];
            strcpy(transf, (char*) group->Value());

            x = 0;
            y = 0;
            z = 0;

            char* colorR = (char*) group->Attribute("R");
            if (colorR != NULL)
                x = atof(colorR);

            char* colorG = (char*) group->Attribute("G");
            if (colorG != NULL)
                y = atof(colorG);

            char* colorB = (char*) group->Attribute("B");
            if (colorB != NULL)
                z = atof(colorB);

            addAux(g, i, transf, x, y, z, 0, translation);

        }

        if (strcmp((char*)group->Value(), "models") == 0) {

            for (const XMLElement* models = group->FirstChildElement(); models; models = models->NextSiblingElement()) {

                char dir[4] = "../";
                char file[15];

                char* fileName = (char*)models->Attribute("file");
                strcpy(file, fileName);

                char file3d[40];
                file3d[0] = '\0';
                strcat(file3d, dir);
                strcat(file3d, file);

                char* texture = (char*) models->Attribute("texture");
                Color* color1 = NULL;

                char* red;
                char* green;
                char* blue;

                if(models->Attribute("diffR")){

                    Color* color1 = (Color*) malloc(sizeof(struct color));
                    color1->type = (char*) malloc(sizeof(char)*20);

                    strcpy(color1->type, "diffuse");

                    red = (char*) models->Attribute("diffR");
                    color1->colors[0] = atof(red);

                    green = (char*) models->Attribute("diffG");
                    color1->colors[1] = atof(green);

                    blue = (char*) models->Attribute("diffB");
                    color1->colors[2] = atof(blue);

                }

                if(models->Attribute("specR")){

                    color1 = (Color*) malloc(sizeof(struct color));
                    color1->type = (char*) malloc(sizeof(char)*20);

                    strcpy(color1->type, "specular");

                    red = (char*) models->Attribute("specR");
                    color1->colors[0] = atof(red);

                    green = (char*) models->Attribute("specG");
                    color1->colors[1] = atof(green);

                    blue = (char*) models->Attribute("specB");
                    color1->colors[2] = atof(blue);

                }

                if(models->Attribute("emisR")){

                    color1 = (Color*) malloc(sizeof(struct color));
                    color1->type = (char*) malloc(sizeof(char)*20);

                    strcpy(color1->type, "emissive");

                    red = (char*) models->Attribute("emisR");
                    color1->colors[0] = atof(red);

                    green = (char*) models->Attribute("emisG");
                    color1->colors[1] = atof(green);

                    blue = (char*) models->Attribute("emisB");
                    color1->colors[2] = atof(blue);

                }

                if(models->Attribute("ambiR")){

                    color1 = (Color*) malloc(sizeof(struct color));
                    color1->type = (char*) malloc(sizeof(char)*20);

                    strcpy(color1->type, "ambient");

                    red = (char*) models->Attribute("ambiR");
                    color1->colors[0] = atof(red);

                    green = (char*) models->Attribute("ambiG");
                    color1->colors[1] = atof(green);

                    blue = (char*) models->Attribute("ambiG");
                    color1->colors[2] = atof(blue);

                }

                addFile(file3d, texture, color1, g, files);

            }
        }

        if (strcmp((char*)group->Value(), "group") == 0) {

            groupParser(group, g, i + 1, files);

            for (int j = i+1; j < 20; j++)
                g[j] = NULL;

        }
    }
}

void parser(const char* config, vector<First*>& files, vector<Light*>& lights)
{
    int i = 0;
    Group g;
    init(g);

    XMLDocument doc;
    XMLError err = doc.LoadFile(config);

    if (!err) {

        XMLElement* elem = doc.FirstChildElement();
        for (const XMLElement* scene = elem->FirstChildElement(); scene; scene = scene->NextSiblingElement()) {

            if (strcmp(scene->Value(), "lights") == 0) {

                Light* light1 = (Light*) malloc(sizeof(struct light));
                light1->type = (char*) malloc(sizeof(char)*20);

                double x = 0;
                double y = 0;
                double z = 0;

                for(const XMLElement* lightXML = scene->FirstChildElement(); lightXML; lightXML = lightXML->NextSiblingElement()){

                    char* type = (char*)lightXML->Attribute("type");

                    char* posX = (char*)lightXML->Attribute("posX");
                    if(posX != NULL)
                        x = atof(posX);

                    char* posY = (char*)lightXML->Attribute("posY");
                    if(posY != NULL)
                        y = atof(posY);

                    char* posZ = (char*)lightXML->Attribute("posZ");
                    if(posZ != NULL)
                        z = atof(posZ);

                    strcpy(light1->type, type);
                    light1->params[0] = x;
                    light1->params[1] = y;
                    light1->params[2] = z;

                    lights.push_back(light1);

                }
            }

            if (strcmp(scene->Value(), "group") == 0) {


                for (int j = i; j < 20; j++)
                    g[j] = NULL;

                groupParser(scene, g, i, files);

            }
        }
    }
}