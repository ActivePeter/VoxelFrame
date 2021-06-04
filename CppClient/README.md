这是我当前主要在开发的VoxelFrame的客户端部分，使用的cpp和opengl

## 当前测验可以直接编译的开发环境

windows下还是推荐使用MSVC

![image-20210205154227006](https://gitee.com/zhongyichen33/testtupian/raw/master/20210205154227.png)

~~windows下的mingw和msvc均可编译~~

网络库接口支持的是 _WIN32_WINNT>=0x0600，vista及后来的win版本，像我的qt的gcc里面描述的就是0x0520，会导致编译不过，需要手动修改编译工具包的环境

![image-20210204153852935](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20210204153852935.png)

## 必要的操作

1，有像glfw等一些依赖的子模块，需要执行

```
git submodule update --init
```

来加载子模块

2.resource文件夹要和exe在同一目录下

3.windows环境需要有mingw编译器

## 开发工具

vscode 

#### 安装一些必要的插件

​        

## 使用了的库

glfw

glad

imgui

protobuf

