package homework3;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class PairsReducer extends Reducer<TextPairWritable, IntWritable, Text, IntWritable> {
    private IntWritable result = new IntWritable();
    private Text text = new Text();

    public void reduce(TextPairWritable key, Iterable<IntWritable> values, Context context)
            throws IOException, InterruptedException {
        int i = 0;

        for (IntWritable localIntWritable : values) {
            i += localIntWritable.get();
        }

        this.result.set(i);
        this.text.set(key.toString());
        context.write(this.text, this.result);
    }
}