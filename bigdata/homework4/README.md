第四次作业： Hive练习
===================

要求
----

* 自己准备一个学生成绩的数据txt文件，至少包含id、name、age、score等字段，不少于20行记录
* 数据文件加载到hive中
* 编写一个按成绩排序的HQL
* 编写一个求全班平均成绩的HQL
* 对HQL和结果进行记录，并记录几张程序执行后的系统截图

解答
----

1. 数据请参考[database.txt](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/database.txt)。文件中的姓名随机产生。
2. Hive版本信息
    ![版本信息](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h4_1.png)
3. 加载文件到hive中。注意分隔符问题：https://cwiki.apache.org/confluence/display/Hive/LanguageManual+DML。
    ![加载文件](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h4_2.png)
4. 按成绩排序的HQL：`select * from students order by grade desc;`
    ![排序](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h4_3.png)
5. 求全班平均成绩的HQL： `select avg(grade) from students;`
    ![平均成绩](https://github.com/TerenceWangh/course/blob/master/bigdata/dist/h4_4.png)