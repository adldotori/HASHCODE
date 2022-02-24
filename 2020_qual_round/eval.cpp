#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int B, L, D;
int S[100001];
int N[30001];
int T[30001];
int M[30001];

int A;
int Y[30001];
int K[30001];

int ship[30001][100001];

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ifstream fin2;
    fin2.open(argv[2]);

    fin >> B >> L >> D;

    for (int b = 0; b < B; b++)
    {
        int s;
        fin >> s;
        S[b] = s;
    }

    for (int l = 0; l < L; l++)
    {
        fin >> N[l] >> T[l] >> M[l];
        for (int n = 0; n < N[l]; n++)
        {
            int t;
            fin >> t;
        }
    }

    fin2 >> A;
    int signup = 0;
    int score = 0;
    for (int a = 0; a < A; a++)
    {
        fin2 >> Y[a] >> K[a];
        signup += Y[a];

        vector<int> scan;
        for (int k = 0; k < K[a]; k++)
        {
            int s;
            fin2 >> s;
            scan.push_back(s);
        }

        for (int i = 0; i < max((D - signup) * M[Y[a]], (int)scan.size()); i++)
            score += S[scan[i]];
    }
    cout << score;
}