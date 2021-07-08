## To All

load the submodules

加载子模块

```
git submodule update --init
```

## Windows（current developing

### Tools：

#### 1.vscode and extensions in it

1. ![image-20210205004832320](https://gitee.com/zhongyichen33/testtupian/raw/master/20210205004832.png)
2. ![image-20210205004850848](https://gitee.com/zhongyichen33/testtupian/raw/master/20210205004850.png)
3. ![image-20210205004947972](https://gitee.com/zhongyichen33/testtupian/raw/master/20210205004948.png)
4. ![image-20210205004918480](https://gitee.com/zhongyichen33/testtupian/raw/master/20210205004918.png)
5. ![image-20210205154117520](https://gitee.com/zhongyichen33/testtupian/raw/master/20210205154117.png)
6. ![image-20210610195339763](https://hanbaoaaa.xyz/tuchuang/images/2021/06/10/image-20210610195339763.png)

#### 2.cmake and cmake extensions in vscode above

#### 3.vs2017 or vs2019 |Ninja if you want fast compiling.

#### 4.conan c++ lib manager(load the opencv and sdl2 lib easily

### Operation：

- #### 1.Open project

- #### 2.Open project directory

  <img src="https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503203305291.png" alt="image-20210503203305291" style="zoom:50%;" />

- #### 3.Right click the workspace file，and click open with vscode

  <img src="https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503203705074.png" alt="image-20210503203705074" style="zoom: 50%;" />

- #### 4.Choose a kit

  <img src="https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503215712461.png" alt="image-20210503215712461" style="zoom:33%;" />

- #### 5.Then cmake settings are in  

  #### VoxelFrameCppClient.code-workspace

  ![](https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503233624341.png)

  setting generator

  > 版本对应 
  >
  > Visual Studio 15   vs2017 x86
  >
  > Visual Studio 15 Win64   vs2017 x64
  >
  > Visual Studio 16   vs2019 x86
  >
  > Visual Studio 16 Win64   vs2019 x64

  Recently I tested the ninja, which is very fast. So Ninja is very recommended.

  ```
  "cmake.configureSettings": {
        "CMAKE_MAKE_PROGRAM": "C:/Program Files/ninja-win/ninja"
  },
   
  "cmake.generator": "Ninja",
  "cmake.parallelJobs": 30,
  ```

  also you can set the cmake.parallelJobs

  also you can set other parameters according to [official instruction](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md)

  -----

  > #### Then we start building

- #### 6.First, load libs with conan

  Make sure you've installed conan.

  Then get into the build folder and run

   conan install .. 

  it will load necessary libs

- #### 7.Second, build the third parties

  - ![image-20210707233216886](https://hanbaoaaa.xyz/tuchuang/images/2021/07/07/image-20210707233216886.png)

  - ![image-20210707233258508](https://hanbaoaaa.xyz/tuchuang/images/2021/07/07/image-20210707233258508.png)

  - switch to **third** workspace folder

  - switch to **release** build mode ![image-20210707233418586](https://hanbaoaaa.xyz/tuchuang/images/2021/07/07/image-20210707233418586.png)

  - run cmake build

    ![image-20210707233600813](https://hanbaoaaa.xyz/tuchuang/images/2021/07/07/image-20210707233600813.png)

- #### 8.Then build the mainprj

  1. switch to **mainproject**

     ![image-20210503234307536](https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503234307536.png)

  2. 命令面板 cmake build

     ![image-20210503233339025](https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503233339025.png)

     




