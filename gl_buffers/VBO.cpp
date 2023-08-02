#include <VBO.hpp>
#include <glad/glad.h>

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STREAM_DRAW); // load data to buffer
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO()
{
    glDeleteBuffers(1, &ID);
}
