file=yoooujisung
g++ -o test $file.cpp -std=c++11
mkdir output_data/$file
./test input_data/a_an_example.in.txt output_data/$file/out_a.txt; ./eval input_data/a_an_example.in.txt output_data/$file/out_a.txt
./test input_data/b_basic.in.txt output_data/$file/out_b.txt; ./eval input_data/b_basic.in.txt output_data/$file/out_b.txt
./test input_data/c_coarse.in.txt output_data/$file/out_c.txt; ./eval input_data/c_coarse.in.txt output_data/$file/out_c.txt
./test input_data/d_difficult.in.txt output_data/$file/out_d.txt; ./eval input_data/d_difficult.in.txt output_data/$file/out_d.txt
./test input_data/e_elaborate.in.txt output_data/$file/out_e.txt; ./eval input_data/e_elaborate.in.txt output_data/$file/out_e.txt
