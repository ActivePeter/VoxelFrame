# cmake最低版本号要求
cmake_minimum_required (VERSION 3.0)
# cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME VoxelFrame)

project (${PROJECT_NAME})

set (CMAKE_CXX_STAND 11)

if(NOT MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14  -g")
else()
    add_definitions("/W4")
endif()

####################################################################
# libs
    ##########################################
    #conan
    include(${VoxelFrame_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
    ##########################################
    include(third/third.cmake)
####################################################################

##########################################################################
# operations
    include(.cmake/proto.cmake)
    include(.cmake/copyFile.cmake)
#######################################################################

# 设置MSVC编译编码
if(MSVC)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
endif()

# 添加一个可编译的目标到工程
# aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)
include_directories (${SRC_DIR})
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.cc)
add_executable (${PROJECT_NAME} ${SRC_FILES})

if(MSVC)
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
    )
    # conan的库默认全为md，所以强制mdd改为md
    foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MDd" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
    
    target_link_libraries (${PROJECT_NAME} 
        general 
        # glfw glad imgui
        ws2_32
        ${thirdLinks} 
        #   paecs 
        ${CONAN_LIBS}
        ${3RDLib}
        # SDL_main
        # reactphysics3d
        # ${protolibs}
        # debug ${protolibsd}
        # optimized ${protolibs}
    )
endif()
# message(${protolib})
# 设置工作目录
# set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY 
#     ${CMAKE_SOURCE_DIR}/resources
# )

# 添加链接库



# target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# # 复制库到工作目录
# add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${IRRKLANG_BIN_DIR}
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>
# )

# # 复制资源文件到工作目录
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/resources
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
# )

# if(APPLE)
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND install_name_tool -change /usr/local/lib/libirrklang.dylib @executable_path/libirrklang.dylib ${PROJECT_NAME}
#     )
# endif()

