图形学与可视化
============

该文件夹是2018-2019秋季图形学与可视化的大作业。

要求
----

作业要求至少两个：
1. [大作业一](https://github.com/TerenceWangh/course/tree/master/cg/src/homework1)
1. [大作业二](https://github.com/TerenceWangh/course/tree/master/cg/src/homework2)
1. [大作业三](https://github.com/TerenceWangh/course/tree/master/cg/src/homework3)
1. [大作业四](https://github.com/TerenceWangh/course/tree/master/cg/src/homework4)
1. [大作业五](https://github.com/TerenceWangh/course/tree/master/cg/src/homework5)

作业说明
-------

### 题目选择
选取了给出被选题的第1个和第3个题目，分别在源代码的`src/homework1/main.c`以及`src/homework3/main.c`中。

### 编译环境
1. Windows10 10.0.17763.0
1. CMake 3.13.0

### 编译方法
1. `mkdir build && cd build && cmake ..`。
1. 进行编译：`msbuild INSTALL.vcxproj /p:Configuration=Release`。
1. 大作业1： `dist\homework1.exe`，大作业2：`dist\homework3.exe`。

参考
----

- 给出的例子：[cgcourse-examples](https://gitee.com/xuejian/cgcourse-examples/)
- [OpenGL](https://www.opengl.org)
- [freeglut](http://freeglut.sourceforge.net)
- [glew](http://glew.sourceforge.net)
- [FreeImage](http://freeimage.sourceforge.net)
- MITK[相关资料](http://www.radiomics.net.cn/platform/index#MITK)