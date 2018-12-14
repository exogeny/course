# Homework 3

## Compile

1. Source the environment of java home and hadoop.
2. Prepare the input file, just put the input folder to the hdfs:
    `hadoop dfs -put input /user/<user>`
3. Run the command to compile source files to a jar:
    ``` bash
    mkdir -p output
    hadoop com.sun.tools.javac.Main src/homework3/*.java -d output/
    cd output && jar cf ../homework3.jar homework3/*.class && cd ..
    ```
4. Then there will generate a homework3.jar in current folder. Run the pairs method just use `hadoop jar homework3.jar homework3/Program /user/<user>/input /user/<user>/output`. and run the striples method should use `hadoop jar homework3.jar homework3/Program /user/<user>/input /user/<user>/output striples`. Attention that the output foulder may exist, so use `hadoop fs -rm -r /user/<user>/output` to delete it.
