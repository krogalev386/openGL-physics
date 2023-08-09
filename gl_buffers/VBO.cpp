#include <VBO.hpp>
#include <glad/glad.h>

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    this->bind();
    this->update(vertices, size); // load data to buffer
}

void VBO::update(GLfloat* vertices, GLsizeiptr size)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STREAM_DRAW);
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
