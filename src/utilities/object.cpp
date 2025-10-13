

#include "../../include/glad/glad.h"
#include "../../include/utilities/object.h"

Object::Object(std::vector<float> v, unsigned int proID) {
    glGenBuffers(1, &VertexBufferID);
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    programID = proID;
}