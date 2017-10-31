package org.apache.hadoop.networks;
import java.io.IOException;
import java.util.*;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.hadoop.util.*;
import org.apache.log4j.pattern.LogEvent;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class PacketCount extends Configured implements Tool {
	public static class Map extends Mapper<LongWritable, Text, IntWritable, IntWritable> {
		private final static IntWritable one = new IntWritable(1);
		private static Logger logger= LoggerFactory.getLogger(PacketCount.class);
		private IntWritable word = new IntWritable();
		public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
			if (key.toString().equals("0")) {
				return;
			}
			String line = value.toString();
			StringTokenizer tokenizerLine = new StringTokenizer(line, ",");
			while (tokenizerLine.hasMoreTokens()) {
				//StringTokenizer tokenizerLine = new StringTokenizer(tokenizerLine.nextToken(), ",");
				String sessionId = tokenizerLine.nextToken();
				int startTime = Integer.parseInt(tokenizerLine.nextToken());
				int endTime = Integer.parseInt(tokenizerLine.nextToken());
				String hopNum = tokenizerLine.nextToken();
				String sourceId = tokenizerLine.nextToken();
				String sinkId = tokenizerLine.nextToken();
				//System.err.println(Integer.toString(endTime - startTime));
				word.set(endTime - startTime);
				context.write(word, one);
			}
		}
	}

	public static class Reduce extends Reducer<IntWritable, IntWritable, IntWritable, IntWritable> {
		public void reduce(IntWritable key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
			int sum = 0;
			for (IntWritable val: values) {
				sum += val.get();
			}
			context.write(key, new IntWritable(sum));
		}
	}

	public int run(String [] args) throws Exception {
		Job job = new Job(getConf());
		job.setJarByClass(PacketCount.class);
		job.setJobName("packetcount");

		job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(IntWritable.class);

		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);

		job.setInputFormatClass(TextInputFormat.class);	
		job.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		boolean success = job.waitForCompletion(true);
		return success ? 0: 1;
	}

	public static void main(String[] args) throws Exception {
		int ret = ToolRunner.run(new PacketCount(), args);
		System.exit(ret);
	}
}
