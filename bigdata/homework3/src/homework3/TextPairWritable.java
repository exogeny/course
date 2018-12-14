package homework3;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import org.apache.hadoop.io.Text;

public class TextPairWritable implements org.apache.hadoop.io.WritableComparable<TextPairWritable>
{
  private Text key;
  private Text value;
  
  public TextPairWritable()
  {
    set(new Text(), new Text());
  }
  
  public TextPairWritable(String paramString1, String paramString2) {
    set(new Text(paramString1), new Text(paramString2));
  }
  
  public TextPairWritable(Text paramText1, Text paramText2) {
    set(paramText1, paramText2);
  }
  
  public void set(Text paramText1, Text paramText2) {
    this.key = paramText1;
    this.value = paramText2;
  }
  
  public Text getKey() {
    return this.key;
  }
  
  public Text getValue() {
    return this.value;
  }
  
  public boolean differentKV() {
    return !this.key.equals(this.value);
  }
  
  public void write(DataOutput paramDataOutput) throws IOException
  {
    this.key.write(paramDataOutput);
    this.value.write(paramDataOutput);
  }
  
  public void readFields(DataInput paramDataInput) throws IOException
  {
    this.key.readFields(paramDataInput);
    this.value.readFields(paramDataInput);
  }
  
  public int hashCode()
  {
    return this.key.hashCode() * 777 + this.value.hashCode();
  }
  
  public boolean equals(Object paramObject)
  {
    if ((paramObject instanceof TextPairWritable)) {
      TextPairWritable localTextPairWritable = (TextPairWritable)paramObject;
      return (this.key.equals(localTextPairWritable.key)) && (this.value.equals(localTextPairWritable.value));
    }
    return false;
  }
  
  public String toString()
  {
    return this.key.toString() + "->" + this.value.toString();
  }
  
  public int compareTo(TextPairWritable paramTextPairWritable)
  {
    int i = this.key.compareTo(paramTextPairWritable.key);
    return i != 0 ? i : this.value.compareTo(paramTextPairWritable.value);
  }
}