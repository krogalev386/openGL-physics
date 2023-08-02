add_library(gl_buffers
    VAO.cpp
    VBO.cpp
    EBO.cpp
)

target_link_libraries(gl_buffers
    PUBLIC
        glad
)

target_include_directories(gl_buffers
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)