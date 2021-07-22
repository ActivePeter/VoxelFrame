新建个文件专门用来记录 开发过程。遇到的问题。相关知识

## 7.14

要检测射线和面的交点，首先要获取到射线起点到面的距离（距离可以先用行列式算体积，），然后根据法线与射线夹角算出交点，然后判断交点是否于三角形内

- 这是计算平面焦点的证明过程

  ![image-20210715003749585](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210715003749585.png)

- 这是判断是否在三角形内的代码

  ```c++
  // Determine whether point P in triangle ABC
  bool PointinTriangle(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
  {
      Vector3 v0 = C - A ;
      Vector3 v1 = B - A ;
      Vector3 v2 = P - A ;
  
      float dot00 = v0.Dot(v0) ;
      float dot01 = v0.Dot(v1) ;
      float dot02 = v0.Dot(v2) ;
      float dot11 = v1.Dot(v1) ;
      float dot12 = v1.Dot(v2) ;
  
      float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;
  
      float u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
      if (u < 0 || u > 1) // if u out of range, return directly
      {
          return false ;
      }
  
      float v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
      if (v < 0 || v > 1) // if v out of range, return directly
      {
          return false ;
      }
  
      return u + v <= 1 ;
  }
  ```

  

## 7.10

前几天先是实现了一下整体的事件系统（Listener, Publisher

今天开始写放置和挖掘方块的逻辑

## 7.7

改变了cmake的整体编译结构，首先是进入third workspace folder, 总体编译第三方lib，然后再回到项目进行后续操作

## 7.4

今天思考写放置方块的逻辑的时候突然想到，射线出来可能经过的方块碰撞器是不一定规则的。这个时候如果还是动态加载区块的话似乎并不太合适，所以可能得把区块碰撞器的加载改成全部加载qaq

## 7.2

成功编译通，之前写的逻辑一点问题也没有，太稳了



## 7.1

这波逻辑量确实有点大，码了好久，之后还要测试bug

今晚就先把之前player 控制部分转移完吧

## 6.30

思考如何计算感兴趣范围，

从一维上分析

![image-20210630181403312](https://hanbaoaaa.xyz/tuchuang/images/2021/06/30/image-20210630181403312.png)

a，b为对边界外扩取整后的边界坐标，可以发现映射到方块坐标。就是a，b-1

然后进一步总结就是对边界往负向取整的坐标

下一步是要处理的是，将取整后的范围分成不同区块

​		即计算区块范围（和计算方块范围道理一样，计算边界的区块坐标即为区块范围，依然是向负取证

​		这样可以获得到一组chunk的指针。

​		分别再每个chunk范围内遍历范围内的方块，生成bitset

- 如何获取区块内的感兴趣范围

  ![image-20210701015502297](https://hanbaoaaa.xyz/tuchuang/images/2021/06/30/image-20210701015502297.png)

，然后操作区块中方块active状态的bitset



## 6.29

加入了updateAfterPhysic接口

chunk碰撞更新思路：

```
//1。算出感兴趣的范围，（区块坐标和方块序列

//2.根据方块序列设置区块中方块的active状态
/**
* 由于得遍历完所有chunkrelated才能确定最终的chunk状态，所以这里只进行active状态的存储。存入一个bitset
* 然后在这些system执行完之后，（beforePhysic接口）遍历一遍bitset，具体设置chunk中rigid的active状态
*/

//3.之后就可以交给物理系统安心的碰撞了。
```



## 6.28

斟酌怎么进行区块的碰撞检测，、

当前思路：

 一个区块，保存一系列方块碰撞器指针，每帧都会检测实体是否移动，若发生移动，就进行区块的setActive



玩家控制还是放回单例里（在update physic之前

还有一个是同步physic结果给摄像头，在update physic之后这个也放单例里，



## 6.27

试了一下，胶囊体非常符合我的预期，它是不会发生旋转的物体

## 6.26

- [x] 将player的position操作换入了ecs里

  这样就避免了从player处随机访问entity的需求了，

- [ ] 胶囊碰撞器

- [ ] 射线碰撞检测

胶囊跟区块的碰撞我的思路是在胶囊所占用的方块出构造方块collider。

不过这个要看物理引擎是不是擅长实时的创建collider，如果物理引擎是基于ecs的，那么实时创建collider可能不是那么合适，当然实时修改collider的坐标也是不错的方法

目前感觉物理引擎还是不太合适。再多看看吧

静态rigid适合做地面，没问题，

player 可以用 setLinerVelocity来实时的移动，

同时锁死它的角速度和

## 6.25

- [x] ecs组件的随机访问，
- [ ] 胶囊碰撞器
- [ ] 

## 6.24

- [x] 注册回调做一些调整
- [x] 完成点击锁定 esc 解锁

碰撞实现

既然要考虑碰撞了，之前写的ecs也要用起来了

~~怎么样让mainplayer单例的坐标数据跟ecs组件绑定起来，目前想到的是让mainplayer 直接存放raw archtype的地址，然后确保这个数据不被销毁（可以添加一个createFinalEntity的函数~~

~~或者存放ecs的entity_id，通过map进行随机访问~~



## 6.23

下一步，碰撞检测bullet3，or 光照

~~选中窗口将鼠标隐藏，按退出键恢复鼠标~~

rendering api 抽象 （

## 6.22

> 前段时间写机械臂去了

区块使用线程池加载已经完成了，但是存在些许bug，

1. ~~纵向移动至区块加载后会卡死，无论是否为多线程。~~

   上面的bug解决了，是遍历list的时候没有++迭代器...

2. ~~bug2，区块加载中心偏移。应该是正负的原因~~

   已解决

3. ~~bug3，shader会把被遮挡的也渲染出来~~

   已解决，是没有开启深度测试的原因

- [x] 鼠标锁定



## 6.11

### todo

- [x] game周期回调注册
- [x] 为了提高范围遍历性能。在初始化将范围内区块的相对坐标预存到一个数组里
- [x] 将chunk Manager文件分离
- [ ] 

---

销毁检测要低频率，所以要搞一个周期回调注册的功能

销毁要细分为网格销毁和数据销毁，网格销毁为出了视角范围就做销毁，数据销毁在出更大范围时销毁

## 6.10

#### todo

- [x] 添加io register（注册回调
- [x] 添加mainplayer
- [x] 将向前声明移入头文件，解决了需要反复向前声明的问题

----

下一步实现下动态的mesh加载吧。

创建一个函数 在轮询中检查玩家的区块坐标变化，如果变化

重新计算范围内区块的一组，（每次只会绘制范围内的）然后将范围外区块加入销毁队列，

函数内循环对销毁队列进行扫描，每次减少一个倒计时，直到倒计时为0，此时销毁区块

---

销毁区块的具体行为：

清除区块中的顶点信息以及~~方块信息~~，（释放内存

方块信息在更大的范围时才去删除、

清除操作的扫描频率可以降低、

---

> 在这些之前，我要在game下加入一个player的类，用来抽象玩家
>
> 同时他会去绑定graph里的camera，至此要约定一下程序运行流程graph的信息要在game之前初始化

---



## 6.9

材质已经绘制出了

![image-20210609124342573](https://hanbaoaaa.xyz/tuchuang/images/2021/06/09/image-20210609124342573.png)

----

下一步：整理代码结构，去除混乱的include关系

## 6.8

![image-20210609124406146](https://hanbaoaaa.xyz/tuchuang/images/2021/06/09/image-20210609124406146.png)

昨天完成了顶点构建方式的修改，接下来要考虑怎么样设计材质绑定了

首先是我目前的做法是将mc地面分为无穷个三维区块，每次绘制一一个区块为一个单元，遍历方块数据并且构造网格。

------

opengl会先要加载纹理，那么之后任意个chunk，应该都可以共用这一个纹理，

绘制之前，执行glBindTexture

----

然后是顶点坐标了。

再次之前说一下chunk构建的细节

有一个block manager 里面有block id -》blockinfo的一个数组（vector

blockInfo是一个基础类型，它描述了标准的方块的顶点添加信息（多数方块的共性

chunk构建时调用blockinfo内的函数就可以往chunk中增加对应block需要的面

----

但是每种方块就算顶点都一样，其材质肯定是不一样的，所以具体的材质坐标操作需要去重新描述，我目前想的就是继承blockInfo 加入不同的材质坐标添加函数

![image-20210608024352380](https://hanbaoaaa.xyz/tuchuang/images/2021/06/07/image-20210608024352380.png)

现有这个函数已借完成了往网格添加顶点和顶点索引

我们还需要做的就是给顶点设置材质uv 这是一个类似查表的过程，不同的面，对应 四个点，不同的材质uv坐标

## 6.7

昨天已经完成网格绘制了，不过今天研究opengl贴图的时候发现opengl 顶点坐标，贴图坐标，得在一起对应一个顶点，而不能单独的建立顶点索引和贴图索引，所以之前的思路得换，

> 之前的思路是一次性表达完一个区块内的所有顶点，然后用索引去一个个访问，但是现在一个顶点，可能对应有不同的纹理坐标了，比如一个草方块，一个点同时会占有顶面材质坐标和侧面材质坐标

