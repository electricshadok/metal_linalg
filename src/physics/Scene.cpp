#include "Scene.hpp"

void Scene::addObject(std::shared_ptr<ObjectData> object)
{
    objects.push_back(object);
}
