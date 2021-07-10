# cmake最低版本号要求
cmake_minimum_required (VERSION 3.0)
# cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME ThirdParty)

project (${PROJECT_NAME})

set (CMAKE_CXX_STAND 11)

# include(../CMAKE_COMPILER.cmake)

#########################################
#sdl
add_subdirectory(SDL)
#########################################
#imgui
set (IMGUI_DIR vf_imgui)
add_subdirectory(${IMGUI_DIR})
# include_directories (${IMGUI_DIR}/imgui)
# set (thirdLinks ${thirdLinks} imgui)
#########################################
# glad
include_directories (glad/include)
add_library (glad glad/src/glad.c)
# set (thirdLinks ${thirdLinks} glad)
#########################################
#reactphysics3d
# SET (reactphysics3d_DIR ${3RD_DIR}/reactphysics3d)
add_subdirectory(reactphysics3d)
# include_directories(${reactphysics3d_DIR}/include)
# set (thirdLinks ${thirdLinks} reactphysics3d)
#########################################
# paecs
# set (PAECS_DIR ${3RD_DIR}/paecs)
add_subdirectory(paecs) 
# include_directories (${PAECS_DIR}/src)
# set (thirdLinks ${thirdLinks} paecs)