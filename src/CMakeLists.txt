add_executable(main main.cpp)
target_link_libraries(main utils ${GL_LIBRARIES} ${APPLE_FRAMEWORKS} ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
