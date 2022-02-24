file=moojisung
g++ -o test $file.cpp -std=c++11
mkdir out/$file
./test in/a.txt out/$file/a.txt;./eval in/a.txt out/$file/a.txt
./test in/b.txt out/$file/b.txt;./eval in/b.txt out/$file/b.txt
./test in/c.txt out/$file/c.txt;./eval in/c.txt out/$file/c.txt
./test in/d.txt out/$file/d.txt;./eval in/d.txt out/$file/d.txt
./test in/e.txt out/$file/e.txt;./eval in/e.txt out/$file/e.txt
./test in/f.txt out/$file/f.txt;./eval in/f.txt out/$file/f.txt
# cd google-hashcode-score-2021
# cargo run --release -- ../in/a.txt ../in/b.txt ../in/c.txt ../in/d.txt ../in/e.txt ../in/f.txt -o ../out/$file/a.txt ../out/$file/b.txt ../out/$file/c.txt ../out/$file/d.txt ../out/$file/e.txt ../out/$file/f.txt;cd ..
