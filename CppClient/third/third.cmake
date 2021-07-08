##########################################
#   need pre build
##########################################
    link_directories(third/build)
    #########################################
    #sdl
    link_directories(third/build/SDL)
    include_directories (third/SDL/include)
    set (3RDLib ${3RDLib} SDL2-static SDL2main gdi32 user32 winmm shell32 version)
    #########################################
    #imgui
    link_directories(third/build/vf_imgui)
    include_directories (third/vf_imgui/imgui)
    set (3RDLib ${3RDLib} imgui)
    #########################################
    #glad
    include_directories (third/glad/include)
    set (3RDLib ${3RDLib} glad)
    #########################################
    #reactphysics3d
    link_directories(third/build/reactphysics3d)
    include_directories (third/reactphysics3d/include)
    set (3RDLib ${3RDLib} reactphysics3d)
    #########################################
    #paecs
    link_directories(third/build/paecs)
    include_directories (third/paecs/src)
    set (3RDLib ${3RDLib} paecs)
    #########################################


##########################################
#   header only
##########################################
    # GLM
    set (GLM_DIR third/glm)
    include_directories (${GLM_DIR}/include)
    ##########################################
    #stb
    set (STB_DIR third/stb_image)
    include_directories(${STB_DIR}/include)
    ##########################################
    #brynet
    set (BRYNET_DIR third/brynet)
    add_subdirectory(${BRYNET_DIR}) 
    include_directories (${BRYNET_DIR}/include)
    ##########################################
    # parallel_hashmap
    set (parallel_hashmap_dir third/parallel-hashmap)
    include_directories (${parallel_hashmap_dir})
    ##########################################
    # ThreadPool
    set (ThreadPool_dir third/ThreadPool)
    include_directories(${ThreadPool_dir})
    ##########################################
