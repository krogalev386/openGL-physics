#pragma once

#include <glad/glad.h>
#include <VBO.hpp>

class VAO
{
public:
    VAO();

    void linkVBO(VBO& VBO, GLuint layout);
    void bind();
    void unbind();
    void deleteVAO();
    GLuint getID();

private:
    GLuint ID;
};
