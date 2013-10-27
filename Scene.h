#ifndef SCENE_H
#define SCENE_H

#include <set>

#include "Graphical.h"

using namespace std;

class Scene
{
private:
    set<Graphical> objects;

public:
    Scene();
    void addObject(Graphical &graphical);
    void removeObject(Graphical &graphical);
    long getObjectCount();
    set<Graphical>::iterator getObjectsIteratorBegin();
    set<Graphical>::iterator getObjectsIteratorEnd();
};

#endif // SCENE_H
