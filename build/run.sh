make
echo "clear the log\n"
cd ../log
rm -rf inputPackets.txt
cd node
rm -rf *.txt
cd ../packet
rm -rf *.txt
cd ../../Bulk_Config_File/file
rm -rf *.txt
cd ../
echo "create the idle capacity of link\n"
python truncate.py
cd ../build
echo "start the simulation, the time is 100000 seconds\n"
setsid ./Simulation 100000 300 ../Bulk_Config_File/world.txt ../Bulk_Config_File/session.txt
#./Simulation 100000 300 ../Bulk_Config_File/world.txt ../Bulk_Config_File/session.txt
