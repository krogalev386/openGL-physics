#include <VAO.hpp>
#include <VBO.hpp>
#include <glad/glad.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO& VBO, GLuint layout)
{
    VBO.bind();
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0); 
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::deleteVAO()
{
    glDeleteVertexArrays(1, &ID);
}
