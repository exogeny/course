package homework3;

import java.io.IOException;
import java.util.ArrayList;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class PairsMapper extends Mapper<Object, Text, TextPairWritable, IntWritable> {
    private static final IntWritable one = new IntWritable(1);

    public void map(Object key, Text values, Context context) throws IOException, InterruptedException {
        String line = values.toString().toLowerCase();
        line = line.replaceAll("\\p{Punct}", "").replaceAll("\\pP", "");
        StringTokenizer tokenizer = new StringTokenizer(line);
        ArrayList<String> array = new ArrayList<>();

        while (tokenizer.hasMoreTokens()) {
            array.add(tokenizer.nextToken());
        }

        for (int i = 0; i < array.size() - 1; i++) {
            TextPairWritable pair = new TextPairWritable((String) array.get(i), (String) array.get(i + 1));
            context.write(pair, one);
        }
    }
}