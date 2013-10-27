#include "Util.h"
#include <fstream>
#include <sstream>

using namespace std;

Util::Util()
{
}

glm::vec3 Util::positionToGlmVec3(Position position)
{
    return glm::vec3(position.getX(), position.getY(), position.getZ());
}

glm::mat4 Util::transformMatrixToGlmMat4(TransformMatrix transformMatrix)
{
    return transformMatrix.getMatrix();
}

string Util::filetobuf(const char *filename) {
    ifstream ifs(filename);
    string line;
    stringstream ss;

    if (ifs.is_open())
    {
        while ( getline (ifs,line) )
        {
            ss << line << endl;
        }
        ifs.close();
    }

    return ss.str();
}


