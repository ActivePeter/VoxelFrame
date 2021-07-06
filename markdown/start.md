## To All

load the submodules

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

#### 3.vs2017 or vs2019

#### 4.conan c++ lib manager

### Operation：

#### 1.open project

#### 2.open project directory

<img src="https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503203305291.png" alt="image-20210503203305291" style="zoom:50%;" />

#### 3.right click the workspace file，and click open with vscode

<img src="https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503203705074.png" alt="image-20210503203705074" style="zoom: 50%;" />

#### 4.choose tool

<img src="https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503215712461.png" alt="image-20210503215712461" style="zoom:33%;" />

#### 5.Then open setting.json under the root directory

![image-20210503233624341](https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503233624341.png)

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

Recently I tested the ninja, it's very fast

```
"cmake.configureSettings": {
      "CMAKE_MAKE_PROGRAM": "C:/Program Files/ninja-win/ninja"
},
 
"cmake.generator": "Ninja",
```



also you can set the cmake.parallelJobs

also you can set other parameters according to [official instruction](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md)

-----

> #### Then we start building

#### 6.first conan

Make sure you've installed conan.

Then get into the build folder and run

 conan install .. 

it will load necessary libs



#### 7.Then build the mainprj

1. switch to mainprj

   ![image-20210503234307536](https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503234307536.png)

2. 命令面板 cmake build

   ![image-20210503233339025](https://gitee.com/zhongyichen33/wiki-pic-bed/raw/master/image-20210503233339025.png)

3. 

