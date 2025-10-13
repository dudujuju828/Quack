
#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    public:
    unsigned int ID;    // program ID

    Shader(const char* vertexPath, const char* fragmentPath);   // read in file and build shader

    void use();    // use / activate the shader  

    void setBool(const std::string &name, bool value) const;    // utility uniform functions
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif 