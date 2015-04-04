cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(TP0)

###  Settings  ###{{{
set(CMAKE_CXX_FLAGS "-std=c++0x -DGL_GLEXT_PROTOTYPES -I/opt/X11/include ") # Don't forget to define GL_GLEXT_PROTOTYPES to ensure that the glCreateShader and other prototypes are declared. Note we could do it in the main file via "#define GL_GLEXT_PROTOTYPES" before "#include <GL/glext.h>"
## setting build type to debug
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_BUILD_TYPE DEBUG)
LINK_DIRECTORIES("~/local_install/lib")
LINK_DIRECTORIES("/usr/local/lib")
FIND_LIBRARY(IRRKLANG_LIB NAMES libIrrKlang.so ikpMP3.so ikpFlac.so PATHS "./lib")
INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES("irrklang")
INCLUDE_DIRECTORIES("~/local_install/include")
INCLUDE_DIRECTORIES("./3rd-parties/")
###  Settings  ###}}}

###  OpenGL  ###{{{
find_package(OpenGL)
if (OPENGL_FOUND)
   include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
    message("OpenGL environment missing")
endif (OPENGL_FOUND)
set(GL_LIBRARIES ${OPENGL_LIBRARIES} GLEW)
if(APPLE)
 set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
 SET(APPLE_FRAMEWORKS "-framework Cocoa -framework IOkit -framework CoreVideo")
endif(APPLE)
###  OpenGL  ###}}}

###  GLFW3  ###{{{
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:$ENV{HOME}/local_install/lib/pkgconfig")
FIND_PACKAGE( PkgConfig REQUIRED )
PKG_SEARCH_MODULE( GLFW3 REQUIRED glfw3 ) # sets GLFW3 as prefix for glfw vars
# now ${GLFW3_INCLUDE_DIR}, ${GLFW3_LIBRARIES} and ${GLFW3_STATIC_LIBRARIES} 
# are set
INCLUDE_DIRECTORIES( ${GLFW3_INCLUDE_DIR} )
###  GLFW3  ###}}}

###  ASSIMP  ###{{{
PKG_SEARCH_MODULE( ASSIMP REQUIRED assimp ) 
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
###  ASSIMP  ###}}}

###  The executable  ###{{{
add_executable(glfwMinimal glfwMinimal.cpp utils.cpp camera.cpp vertex.cpp mesh.cpp game.cpp scene.cpp gameObject.cpp gameSphere.cpp timer.cpp player.cpp gameText.cpp hud.cpp level.cpp gameCube.cpp skybox.cpp box.cpp particle.cpp particles.cpp)
target_link_libraries(glfwMinimal ${GL_LIBRARIES}  ${GLFW3_STATIC_LIBRARIES} ${APPLE_FRAMEWORKS}) # this is to save an image (for screenshots)
target_link_libraries(glfwMinimal ${GL_LIBRARIES}  ${GLFW3_STATIC_LIBRARIES} ${IRRKLANG_LIB}) # this is to save an image (for screenshots)
###  The executable  ###}}}



###  Copying resources (shaders, images,...)  ###{{{
macro(copy_files GLOBPAT DESTINATION)
  file(GLOB COPY_FILES
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${GLOBPAT})
  foreach(FILENAME ${COPY_FILES})
    message("*** COPYING: " ${FILENAME})
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/resources/${FILENAME}")
    set(DST "${DESTINATION}/${FILENAME}")
    configure_file(${SRC} ${DST} COPYONLY)
  endforeach(FILENAME)
endmacro(copy_files)

### Copying resources in the runtime directory (images, shaders,...)
copy_files("resources/*.tga" ${CMAKE_BINARY_DIR})
copy_files("resources/*.obj" ${CMAKE_BINARY_DIR})
copy_files("resources/*.glsl" ${CMAKE_BINARY_DIR})
copy_files("resources/*.DDS" ${CMAKE_BINARY_DIR})
copy_files("resources/*.mp3" ${CMAKE_BINARY_DIR})
copy_files("resources/*.ogg" ${CMAKE_BINARY_DIR})
copy_files("resources/level/*.txt" ${CMAKE_BINARY_DIR})
###  Copying resources (shaders, images,...)  ###}}}

