第二次作业： Hadoop练习
=====================

要求
----

作业内容包括：
* 在自己安装过程，主要步骤截图；
* 安装完成后运行Hadoop自带案例命令行运行截图；
* `uname -a`获取系统信息截图；

解答
----

1. 使用`root`用户新建Hadoop用户及其分组：
  ![第一步](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_1.png)

2. 下载Hadoop安装包：
  ![下载](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_2.png)

3. 将Hadoop解压到`/opt/hadoop`文件夹下，并将环境目录添加到环境中，方便命令的执行。并加入`JAVA_HOME`的环境变量，否则hadoop执行会报错：
  ![安装](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_3.png)

4. 执行命令`hadoop version`命令获取版本信息以及`uname –a`获取系统信息：
  ![版本信息](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_4.png)
  ![系统信息](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_5.png)

5. 设置伪分布式：
    * 修改`etc/hadoop/core-site.xml`文件如下：
      ``` xml
      <configuration>
        <property>
          <name>fs.defaultFS</name>
          <value>hdfs://localhost:9000</value>
        </property>
      </configuration>
      ```
    * 修改`etc/hadoop/hdfs-site.xml`文件如下：
      ``` xml
      <configuration>
        <property>
          <name>dfs.replication</name>
          <value>1</value>
        <property>
      </configuration>
      ```

6. 执行官方案例
    * 执行`hdfs namenode -format`初始化节点
      ![初始化节点](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_6.png)
    * 执行`start-dfs.sh`开启节点
      ![开启节点](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_7.png)
    * 执行`hdfs dfs -mkdir /user`以及`hdfs dfs -mkdir /user/<username>`在节点中新建文件夹
      ![准备文件夹](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_8.png)
    * 拷贝输入文件到节点中，执行`hdfs dfs -put <input> input`
    * 运行案例
      ![运行案例](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_9.png)
    * 查看输出结果
      ![输出结果](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_10.png)
    * 关闭节点
      ![关闭节点](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h2_11.png)
