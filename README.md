# VoxelFrame

![image-20210609143052106](https://hanbaoaaa.xyz/tuchuang/images/2021/06/09/image-20210609143052106.png)

## Important! 

Recently I decided to move the project 2 ue4, this project may be paused.

最近我决定将项目转移到ue4上了，这个项目将会被暂停

ue4 version repo: [https://github.com/ActivePeter/VoxelFrame_UE4](https://github.com/ActivePeter/VoxelFrame_UE4)

## Introduction（介绍

- I likes playing minecraft very much and it's always been my dream to write a mc.

  我非常喜欢玩minecraft，写一个mc是我长久以来一直想做到的事


## Organization（组织

- [VoxelFrame (github.com)](https://github.com/VoxelFrame)   

  To store related projects.

  用于存储相关项目

## Language（语言

- c++(client), rust~~golang~~(server)


## Current Progress Preview（进度预览

- [ ] put and dig a block (raycast check with chunk)

  放置和挖掘方块（跟区块的射线碰撞检测）

- [x] Event System (publisher & listener)

  事件系统（发布者和监听者）

- [x] Switched to sdl2 from glfw.

  切换到了sdl平台

- [x] Walking on ground is available now.

  可以在区块地面上走路了


![image-20210707185242601](https://hanbaoaaa.xyz/tuchuang/images/2021/07/07/image-20210707185242601.png)

## Development Record（开发记录

- [all](./markdown/record.md)

## Start Development（开发

1. This repo relays on other libs through submodule,so you need to launch it using following command

   这个仓库通过子模块管理其他依赖库，所以请在开始时执行一下命令

   ```
   git submodule update --init
   ```

2. [client dev（客户端开发](./markdown/client_start.md)

## Related Projects（相关项目

- I'm also trying to implement a ecs lib and use it in my mc

  我也在尝试实现一个ecs库并用在我的mc里

  [ActivePeter/paecs: simple implementation of ECS game model (github.com)](https://github.com/ActivePeter/paecs)

## Old (unity version)/旧版本（unity版

- This part was written in my high school period.

  这部分是我高中时候做的

  [VoxelFrame/VoxelFrame_Abandoned (github.com)](https://github.com/VoxelFrame/VoxelFrame_Abandoned)

  #### video（视频:

  https://www.bilibili.com/video/BV1d7411n7nK/