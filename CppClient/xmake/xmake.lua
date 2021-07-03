add_requires("glfw")
add_requires("conan::glm/0.9.9.8",{alias="glm"})
add_requires("conan::parallel-hashmap/1.33",{alias="phmap"})
add_requires("conan::opencv/4.5.0",{alias = "opencv"})

target("VoxelFrame")
    set_kind("binary")
    set_languages("c++11")
    
    if is_plat("windows") then
        add_syslinks("ws2_32")
    end

    add_packages(
        "glfw","glm","phmap","opencv"
    )

    -- main
    add_files("../src/**.cpp")
    add_includedirs("../src")

    -- glad
    add_files("../third/glad/src/**")
    add_includedirs("../third/glad/include")

    -- imgui
    add_files("../third/vf_imgui/imgui/imgui.cpp",
                "../third/vf_imgui/imgui/imgui_draw.cpp")
    add_includedirs("../third/vf_imgui/imgui")

    -- rp3d
    add_files("../third/reactphysics3d/src/**")
    add_includedirs("../third/reactphysics3d/include")
    
    -- paecs
    add_files("../third/paecs/src/**.cpp")
    add_includedirs("../third/paecs/src")

    -- brynet
    add_includedirs("../third/brynet/include")

    -- ThreadPool
    add_includedirs("../third/ThreadPool")