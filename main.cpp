#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <VAO.hpp>
#include <VBO.hpp>
#include <EBO.hpp>

#include <ShaderProgram.hpp>
#include <PhysicsHandler.hpp>

// Escape key handler
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};

int main(){
    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window object
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Switch window as a current context
    glfwMakeContextCurrent(window);

    // GLAD initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    // Set size of the draw area inside window 
    glViewport(0,0,800,600);

    // Trigger callback by window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

/////////////////////////// Physics initialization //////////////////////////

    PhysicsHandler& physicsHandler = PhysicsHandler::getInstance();

    ptr_vec<Structure> structures;
    ptr_vec<Surface> surfaces;
    structures.emplace_back(std::make_shared<Structure>(Structure()));
    surfaces.emplace_back(std::make_shared<Surface>(Surface(0.1,-0.1,1.0,3.0)));

    physicsHandler.setEnviroment(structures, surfaces, -9.8);

    float vertices[8*3];

    structures[0]->getPositions(vertices);

/////////////////////////////////////////////////////////////////////////////

    // Set vertices
    //float vertices[] = {
    //    -0.5f, -0.5f, -0.5f,
    //    -0.5f, -0.5f,  0.5f,
    //    -0.5f,  0.5f,  0.5f,
    //    -0.5f,  0.5f, -0.5f,
    //    
    //     0.5f, -0.5f, -0.5f,
    //     0.5f, -0.5f,  0.5f,
    //     0.5f,  0.5f,  0.5f,
    //     0.5f,  0.5f, -0.5f,
    //
    //};

    uint indices[] = {
        0,1,2,  // 1  triangle
        1,2,3,  // 2  triangle
        4,5,6,  // 3  triangle
        5,6,7,  // 4  triangle
        0,1,4,  // 5  triangle
        1,4,5,  // 6  triangle
        2,3,6,  // 7  triangle
        3,6,7,  // 8  triangle
        0,3,4,  // 9  triangle
        3,4,7,  // 10 triangle
        1,2,5,  // 11 triangle
        2,5,6   // 12 triangle
    };

    // Vertex array object initialization
    VAO VAO1;
    VAO1.bind();

    // Initialize vertex buffer object
    VBO VBO1(vertices, sizeof(vertices));
    VBO1.bind();

    // Element buffer initialization
    EBO EBO1(indices, sizeof(indices));
    EBO1.bind();

    // Link VBO with VAO
    VAO1.linkVBO(VBO1, 0);

    VAO1.unbind();
    VBO1.unbind();

    // Wireframe mode;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // create shader program
    ShaderProgram shaderProgram("../shaders/shader.vs", "../shaders/shader.fs");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f)); 

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    double last_time = glfwGetTime();
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        //Input
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);

        shaderProgram.use();

        VAO1.bind();
        VBO1.bind();

        double dt = glfwGetTime() - last_time;
        last_time = glfwGetTime();
        for (int i = 0; i < 100; i++){
            physicsHandler.makeTimeStep(dt/100);
        }
        structures[0]->getPositions(vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        VBO1.unbind();
        VAO1.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    EBO1.unbind();
    //VBO1.unbind();
    //VAO1.unbind();

    VAO1.deleteVAO();
    VBO1.deleteVBO();
    // Close session
    glfwTerminate();    
    return 0;
}
