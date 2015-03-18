
### Creating an executable
add_executable(textures textures.cpp)
target_link_libraries(textures utils ${GL_LIBRARIES} ${APPLE_FRAMEWORKS}  ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
