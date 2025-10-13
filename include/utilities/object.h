#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Object {
public:
    unsigned int VertexBufferID;
    unsigned int VertexArrayID;
    unsigned int programID;
    
    Object(std::vector<float> v, unsigned int proID);
};

#endif // OBJECT_H