hadoop fs -rmr /output
javac PacketCount.java -d Count/
javac NodeCount.java -d Count/
cd Count
jar -cvf Count.jar .
hadoop jar Count.jar org.apache.hadoop.networks.PacketCount /input/packet /output/packet
hadoop jar Count.jar org.apache.hadoop.networks.NodeCount /input/node /output/node
