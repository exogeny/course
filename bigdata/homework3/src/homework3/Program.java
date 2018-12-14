package homework3;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Program
{
  public static void main(String[] args) throws Exception
  {
    Configuration localConfiguration = new Configuration();
    Job localJob = Job.getInstance(localConfiguration, "word count");
    localJob.setJarByClass(Program.class);

    boolean useStriples = false;
    if (args.length > 2)
    {
        useStriples = "striples".equalsIgnoreCase(args[2]);
    }

    if (useStriples)
    {
        localJob.setMapperClass(StriplesMapper.class);
        localJob.setMapOutputKeyClass(Text.class);
        localJob.setMapOutputValueClass(MapWritable.class);
    
        localJob.setReducerClass(StriplesReducer.class);
        
        localJob.setOutputKeyClass(Text.class);
        localJob.setOutputValueClass(MapWritable.class);
    }
    else
    {
        localJob.setMapperClass(PairsMapper.class);
        localJob.setMapOutputKeyClass(TextPairWritable.class);
        localJob.setMapOutputValueClass(IntWritable.class);
    
        localJob.setReducerClass(PairsReducer.class);
        
        localJob.setOutputKeyClass(Text.class);
        localJob.setOutputValueClass(IntWritable.class);
    }

    FileInputFormat.addInputPath(localJob, new Path(args[0]));
    FileOutputFormat.setOutputPath(localJob, new Path(args[1]));
    System.exit(localJob.waitForCompletion(true) ? 0 : 1);
  }
}