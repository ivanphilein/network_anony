g++ src/heuristic.cpp src/mapping.cpp -o heu2

./heu2 data/s2_dpInputFile_o_2lab.txt 2 1
#./heu2 data/s2_dpInputFile_o_2lab.txt 4 1
#./heu2 data/s2_dpInputFile_o_2lab.txt 8 1
#./heu2 data/s2_dpInputFile_o_2lab.txt 16 1
#./heu2 data/s2_dpInputFile_o_2lab.txt 32 1
./heu2 data/s2_dpInputFile_o_2lab.txt 16 2 > log.txt
#./heu2 data/s2_dpInputFile_o_2lab.txt 4 2
#./heu2 data/s2_dpInputFile_o_2lab.txt 8 2
#./heu2 data/s2_dpInputFile_o_2lab.txt 16 2
#./heu2 data/s2_dpInputFile_o_2lab.txt 32 2
