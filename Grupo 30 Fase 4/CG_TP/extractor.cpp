#include "extractor.h"

void extractor(int* ntriangles, vector<First*>& files, vector<coords>& triangles, vector<coords>& normals, vector<coords>& textures)
{
    int n = 0;
    double triple[3];
    int nlines = 1;

    for (vector<First*>::iterator it = files.begin(); it != files.end(); it++) {

        First* first = *it;
        ifstream file;
        file.open(first->file);
        string line;

        if (file.is_open()) {

            while (getline(file, line)) {

                string temp;
                for (int i = 0; i <= line.length(); i++) {

                    if (line[i] == ' ' || line[i] == '\0') {

                        triple[n] = stod(temp);
                        temp.clear();
                        n++;

                    }
                    else
                        temp.push_back(line[i]);

                }

                coords point = make_tuple(triple[0], triple[1], triple[2]);

                if(nlines % 3 == 1){

                    triangles.push_back(point);
                    first->npoints++;
                    (*ntriangles)++;

                }
                else if (nlines % 3 == 2)
                    normals.push_back(point);

                    else if (nlines % 3 == 3)
                        textures.push_back(point);

                n = 0;
                nlines++;

            }
        }

        coords end = make_tuple(12345, 12345, 12345);
        triangles.push_back(end);
        normals.push_back(end);
        textures.push_back(end);
        triangles.push_back(end);
        normals.push_back(end);
        textures.push_back(end);
        triangles.push_back(end);
        normals.push_back(end);
        textures.push_back(end);

    }
}