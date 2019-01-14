第五次作业： Spark练习
====================

要求
----

* 自己准备一个学生成绩的数据txt文件，至少包含id、name、age、score等字段，不少于20行记录
* 数据文件加载到spark中
* 按成绩排序，并输出结果
* 求全班平均成绩，并输出结果
* 对结果进行记录，并记录几张程序执行后的系统截图

解答
----

1. 数据准备：数据格式为`csv`格式，和第四次练习的数据一致，单格式变成csv格式。需要将该文件加载到`HDFS`的`/user/<username>/database.csv`文件中。文件参考[database.csv](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/database.csv)
    ``` csv
    id;name;age;score
    1;郝航;22;95
    2;王文博;25;43
    3;陶思;24;76
    4;王越彬;23;87
    5;薛泽洋;22;64
    6;冯峻熙;26;73
    7;黎鹏涛;24;53
    8;方思淼;23;70
    9;李明轩;23;82
    10;袁驰;22;76
    11;余志泽;23;89
    12;龙乐驹;24;91
    13;宋昊然;23;67
    14;沈鹏涛;23;61
    15;石峻熙;24;49
    16;田鸿煊;22;89
    17;阎耀杰;23;73
    18;汪浩然;22;82
    19;叶明轩;23;63
    20;严鑫磊;23;92
    21;赖正豪;23;74
    22;曹钰轩;22;69
    23;傅擎宇;24;83
    24;孟建辉;24;58
    25;秦鹭洋;23;79
    ```

2. Spark的运行信息：
    ![运行信息](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h5_1.png)

3. 准备`SparkSession`：
    ``` scala
    import org.apache.spark.sql.SparkSession
    import spark.implicits._

    val spark=SparkSession.builder().getOrCreate()
    ```
    ![Session](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h5_2.png)

4. 将数据载入到`DataFrame`中：
    ``` scala
    val df = spark.read.format("csv")
        .option("sep", ";")
        .option("inferSchema", "true")
        .option("header", "true")
        .load("database.csv")
    ```
    ![载入数据](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h5_3.png)

5. 列出数据集中所有的数据信息：
    ![数据信息](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h5_4.png)

6. 对数据按照成绩排名并显示`df.sort(df("score").desc).show(count)`：
    ![排序](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h5_5.png)

7. 求全班平均成绩`df.agg(avg("score")).show()`：
    ![平均成绩](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h5_6.png)