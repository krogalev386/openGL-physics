#include <ShaderProgram.hpp>

ShaderProgram::ShaderProgram(const char* vertexShaderPath, 
                             const char* fragmenShaderPath){

    /**
     * Load GLSL source code
     * 
     */
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmenShaderPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER_FILE_NOT_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    /**
     * Compile shaders
     * 
     */
    uint vertexID, fragmentID;
    int success;
    char infoLog[512];

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vShaderCode, NULL);
    glCompileShader(vertexID);
    // print errors if any
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_VERTEX_COMPILATION_FAILED: " << infoLog << std::endl;
    };
    
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fShaderCode, NULL);
    glCompileShader(fragmentID);
    // print errors if any
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_VERTEX_COMPILATION_FAILED: " << infoLog << std::endl;
    };
    
    // link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);
    // errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
    };

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(ID);
}

void ShaderProgram::use(){
    glUseProgram(ID);
}

void ShaderProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat2(const std::string& name, float value1, float value2) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void ShaderProgram::setMat4(const std::string& name, glm::mat4& mat4) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}

