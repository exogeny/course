package homework3;

import java.io.IOException;
import java.util.ArrayList;

import java.util.HashSet;
import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class StriplesMapper extends Mapper<Object, Text, Text, MapWritable> {
    public void map(Object key, Text values, Context context)
            throws IOException, InterruptedException {
        String line = values.toString().toLowerCase();
        line = line.replaceAll("\\p{Punct}", "").replaceAll("\\pP", "");
        StringTokenizer tokenizer = new StringTokenizer(line);
        ArrayList<String> array = new ArrayList<>();

        while (tokenizer.hasMoreTokens()) {
            array.add(tokenizer.nextToken());
        }
        HashSet<String> set = new HashSet<>(array);

        for (String s : set) {
            MapWritable map = new MapWritable();
            for (int i = 1; i < array.size(); i++) {
                if (((String) array.get(i - 1)).equals(s)) {
                    Text text = new Text((String) array.get(i));
                    if (map.containsKey(text)) {
                        IntWritable localIntWritable = (IntWritable) map.get(text);
                        localIntWritable.set(localIntWritable.get() + 1);
                    } else {
                        map.put(text, new IntWritable(1));
                    }
                }
            }

            if (map.size() > 0) {
                context.write(new Text(s), map);
            }
        }
    }
}