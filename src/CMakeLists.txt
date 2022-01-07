target_include_directories(example
PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_sources(example
PUBLIC
    ShaderProgram.cpp
    Structure.cpp
    PhysicsHandler.cpp
)