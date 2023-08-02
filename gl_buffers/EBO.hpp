#pragma once

#include <glad/glad.h>

class EBO
{
public:
    EBO(GLuint* indices, GLsizeiptr size);

    void bind();
    void unbind();
    void deleteEBO();
    GLuint getID();

private:
    GLuint ID;
};
