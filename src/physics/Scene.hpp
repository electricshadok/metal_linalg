#ifndef Scene_hpp
#define Scene_hpp

#include <vector>
#include <memory>
#include "ObjectData.hpp"

class Scene
{
public:
    Scene() = default;

    // Method to add an object to the scene
    void addObject(std::shared_ptr<ObjectData> object);

    // Public member to hold all objects
    std::vector<std::shared_ptr<ObjectData>> objects;
    
    size_t numNodes() const;
};

#endif /* Scene_hpp */
