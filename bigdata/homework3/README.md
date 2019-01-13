第三次作业
=========

要求
----

实现课程提提的2种关联规则发现算法，自己准备数据集，并进行测试，记录时间和结果。

解答
----

### 编译方式

1. 引入java环境以及Hadoop环境
2. 准备输入数据并且将数据上传到节点中:
    `hadoop dfs -put input /user/<user>`
3. 运行下面命令进行编译:
    ``` bash
    mkdir -p output
    hadoop com.sun.tools.javac.Main src/homework3/*.java -d output/
    cd output && jar cf ../homework3.jar homework3/*.class && cd ..
    ```
4. 在当前目录将会编译出homework3.jar文件。
    * 使用pairs方法进行测试，可使用 `hadoop jar homework3.jar homework3/Program /user/<user>/input /user/<user>/output`命令
    * 使用striples方法需使用`hadoop jar homework3.jar homework3/Program /user/<user>/input /user/<user>/output striples`命令

    > 注意在运行前需要删除节点中的临时文件：`hadoop fs -rm -r /user/<user>/output`。
