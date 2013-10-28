#include "ObjLoader.h"

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

ObjLoader::ObjLoader()
{
}

void ObjLoader::loadObj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements) {
    ifstream in(filename, ios::in);
        if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }
        vector<int> nb_seen;

        string line;
        while (getline(in, line)) {
            if (line.substr(0,2) == "v ") {
                istringstream s(line.substr(2));
                glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0;
                vertices.push_back(v);
            }  else if (line.substr(0,2) == "f ") {
                istringstream s(line.substr(2));
                GLushort a,b,c;
                s >> a; s >> b; s >> c;
                a--; b--; c--;
                elements.push_back(a); elements.push_back(b); elements.push_back(c);
            }
            else if (line[0] == '#') { /* ignoring this line */ }
            else { /* ignoring this line */ }
        }

        normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
        nb_seen.resize(vertices.size(), 0);
        for (unsigned int i = 0; i < elements.size(); i+=3) {
            GLushort ia = elements[i];
            GLushort ib = elements[i+1];
            GLushort ic = elements[i+2];
            glm::vec3 normal = glm::normalize(glm::cross(
                glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
                                                            glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));

            int v[3];  v[0] = ia;  v[1] = ib;  v[2] = ic;
            for (int j = 0; j < 3; j++) {
                GLushort cur_v = v[j];
                nb_seen[cur_v]++;
                if (nb_seen[cur_v] == 1) {
                    normals[cur_v] = normal;
                } else {
                    // average
                    normals[cur_v].x = normals[cur_v].x * (1.0 - 1.0/nb_seen[cur_v]) + normal.x * 1.0/nb_seen[cur_v];
                    normals[cur_v].y = normals[cur_v].y * (1.0 - 1.0/nb_seen[cur_v]) + normal.y * 1.0/nb_seen[cur_v];
                    normals[cur_v].z = normals[cur_v].z * (1.0 - 1.0/nb_seen[cur_v]) + normal.z * 1.0/nb_seen[cur_v];
                    normals[cur_v] = glm::normalize(normals[cur_v]);
                }
            }
        }
}
