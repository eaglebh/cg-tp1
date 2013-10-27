#include "Scene.h"

Scene::Scene()
{
}

void Scene::addObject(Graphical &graphical)
{
    this->objects.insert(graphical);
}

void Scene::removeObject(Graphical &graphical)
{
    this->objects.erase(graphical);
}

long Scene::getObjectCount()
{
    return this->objects.size();
}

set<Graphical>::iterator Scene::getObjectsIteratorBegin()
{
    return this->objects.begin();
}

set<Graphical>::iterator Scene::getObjectsIteratorEnd()
{
    return this->objects.end();
}
