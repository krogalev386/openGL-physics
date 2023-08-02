#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderProgram {
public:
    uint ID; // the program ID

    // cunstructor
    ShaderProgram(const char* vertexShaderPath, 
                  const char* fragmanetShaderPath);
    // destructor
    ~ShaderProgram();
    // use/activate shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloat2(const std::string& name, float value1, float value2) const;
    void setMat4(const std::string& name, glm::mat4& mat4) const;
};