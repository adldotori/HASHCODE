#include <bits/stdc++.h>
using namespace std;

int B, L, D;
vector<int> S;
int N[40000];
int T[40000];
int M[40000];

int A;
int Y[40000];
int K[40000];

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ofstream fout;
    fout.open(argv[2]);

    fin >> B >> L >> D;

    for (int b = 0; b < B; b++)
    {
        int s;
        fin >> s;
        S.push_back(s);
    }

    int cnt = 0;
    for (int l = 0; l < L; l++)
    {
        fin >> N[l] >> T[l] >> M[l];
        for (int n = 0; n < N[l]; n++)
        {
            int t;
            fin >> t;
            cnt++;
        }
    }

    fout << L << endl;
    for (int l = 0; l < L; l++)
    {
        int size, tmp = B / L;
        if (l == L - 1)
            size = B - (L - 1) * size;
        else
            size = tmp;

        fout << l << " " << size << endl;
        for (int i = 0; i < size; i++)
        {
            if (i < size - 1)
                fout << l * tmp + i << " ";
            else
                fout << l * tmp + i;
        }
        fout << endl;
    }
}