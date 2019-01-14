import org.apache.spark.sql.SparkSession
import spark.implicits._

val spark=SparkSession.builder().getOrCreate()
val df = spark.read.format("csv").option("sep", ";").option("inferSchema", "true").option("header", "true").load("database.csv")

val count = df.count().toInt
df.printSchema()
df.show(count)

df.sort(df("score").desc).show(count)
df.agg(avg("score")).show()