#include "Scene.hpp"

void Scene::addObject(std::shared_ptr<ObjectData> object)
{
    objects.push_back(object);
}

size_t Scene::numNodes() const
{
    size_t counter(0);
    
    for (const auto& obj : objects)
    {
        counter += obj->numNodes();
    }
    
    return counter;
}
