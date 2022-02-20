#include <bits/stdc++.h>
using namespace std;

int D, I, S, V, F;
int city[10001][10001];  // S * S
vector<int> route[1001]; // V

int A;
vector<int> traffic[10001]; // S * D

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ofstream fout;
    fout.open(argv[2]);

    fin >> D >> I >> S >> V >> F;

    vector<int> start_end_list;
    vector<string> street_name_list;

    for (int s = 0; s < S; s++)
    {
        int start, end, length;
        fin >> start >> end;
        string street;
        fin >> street;
        fin >> length;

        city[start][end] = length;
        start_end_list.push_back(start * 10000 + end);
        street_name_list.push_back(street);
    }

    fout << "0";
}
