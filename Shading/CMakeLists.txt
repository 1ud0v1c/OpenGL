
### Creating an executable
add_executable(shading shading.cpp)
target_link_libraries(shading utils ${GL_LIBRARIES} ${APPLE_FRAMEWORKS} ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
