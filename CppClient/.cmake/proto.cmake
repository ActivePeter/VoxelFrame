set (PROTOBUF_PROTOC_EXECUTABLE ${PROTO_DIR}/protoc-3.15.5-win64/bin/protoc.exe)
set (PROTO_FILES_DIR ${PROJECT_SOURCE_DIR}/src/impl/Protos)
file(GLOB protobuf_files
        ${PROTO_FILES_DIR}/*.proto
        )
# SET(${PROTO_FILES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
LIST(APPEND PROTO_FLAGS -I${PROTO_FILES_DIR})

# 移除原来生成的proto源文件
# EXECUTE_PROCESS(
#     COMMAND rm -f ${PROTO_FILES_DIR}/src/* 
# )
file(REMOVE_RECURSE ${PROTO_FILES_DIR}/src)
file(MAKE_DIRECTORY ${PROTO_FILES_DIR}/src)
# 遍历并生成proto源文件
FOREACH(FIL ${protobuf_files})

    GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)

    set(PROTO_SRCS "${PROTO_FILES_DIR}/src/${FIL_WE}.pb.cc")
    set(PROTO_HDRS "${PROTO_FILES_DIR}/src/${FIL_WE}.pb.h")

    
    EXECUTE_PROCESS(
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I${PROTO_FILES_DIR} --cpp_out=${PROTO_FILES_DIR}/src ${FIL}
    )

ENDFOREACH()