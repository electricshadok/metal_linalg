#ifndef CubeMesh_hpp
#define CubeMesh_hpp

#include "ObjectData.hpp"

class CubeMesh : public ObjectData
{
public:
    CubeMesh();

private:
    void initializeNodes();
    void initializeTriangles();
};

#endif /* CubeMesh_hpp */
