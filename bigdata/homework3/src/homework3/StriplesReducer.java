package homework3;

import java.io.IOException;
import java.util.Map.Entry;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.mapreduce.Reducer;

public class StriplesReducer extends Reducer<Text, MapWritable, Text, MapWritable> {
    public void reduce(Text key, Iterable<MapWritable> values, Context context)
            throws IOException, InterruptedException {
        MapWritable result = new MapWritable();

        for (MapWritable map : values) {
            for (Entry<Writable, Writable> localEntry : map.entrySet()) {
                Text text = (Text) localEntry.getKey();
                int count = ((IntWritable) localEntry.getValue()).get();

                if (result.containsKey(text)) {
                    count += ((IntWritable) result.get(text)).get();
                }

                result.put(text, new IntWritable(count));
            }
        }

        context.write(key, result);
    }
}