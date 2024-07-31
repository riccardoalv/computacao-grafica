cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FreeGLUT_Animation)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Find OpenGL package
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Find GLUT package
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
