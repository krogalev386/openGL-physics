add_library(program_base
    ShaderProgram.cpp
    Structure.cpp
    PhysicsHandler.cpp
    Cuboid.cpp
)

target_include_directories(program_base
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(program_base
    PUBLIC
        gl_buffers
        glad
        glm
)
