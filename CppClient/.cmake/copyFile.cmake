# 复制资源文件到生成目录
# EXECUTE_PROCESS(
#     COMMAND rm -rf E:/pa_files/project/cs_big_prjs/VoxelFrame/CppClient/build/Debug/resource/* 
# )
if(MSVC)
    file(REMOVE_RECURSE ${VoxelFrame_BINARY_DIR}/bin/resource)
    # file(REMOVE_RECURSE ${VoxelFrame_BINARY_DIR}/Release/resource)

    file(COPY ${PROJECT_SOURCE_DIR}/resource DESTINATION ${VoxelFrame_BINARY_DIR}/bin)
    # file(COPY ${PROJECT_SOURCE_DIR}/resource DESTINATION ${VoxelFrame_BINARY_DIR}/Release)
else()
    file(REMOVE_RECURSE ${VoxelFrame_BINARY_DIR}/resource)
    file(MAKE_DIRECTORY ${VoxelFrame_BINARY_DIR}/resource)
    file(COPY ${PROJECT_SOURCE_DIR}/resource DESTINATION ${VoxelFrame_BINARY_DIR})
endif()