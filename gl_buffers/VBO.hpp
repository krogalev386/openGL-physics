#pragma once

#include <glad/glad.h>

class VBO
{
public:
    VBO(GLfloat* vertices, GLsizeiptr size);

    void bind();
    void unbind();
    void deleteVBO();
    GLuint getID();

private:
    GLuint ID;
};
