#include <bits/stdc++.h>
using namespace std;

int C, L;
string good[100001][5];
string bad[100001][5];
string ingredients[100001];

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ifstream fin2;
    fin2.open(argv[2]);

    fin >> C;
    for (int i = 0; i < C; i++)
    {
        int num;
        fin >> num;
        for (int j = 0; j < num; j++)
        {
            fin >> good[i][j];
        }
        fin >> num;
        for (int j = 0; j < num; j++)
        {
            fin >> bad[i][j];
        }
    }

    fin2 >> L;
    for (int i = 0; i < L; i++)
    {
        fin2 >> ingredients[i];
    }

    int cnt = 0;
    for (int i = 0; i < C; i++)
    {
        bool clients = true;
        for (int j = 0; j < 5; j++)
        {
            if (good[i][j] == "")
            {
                break;
            }
            bool flag = false;
            for (int k = 0; k < L; k++)
            {
                if (good[i][j] == ingredients[k])
                {
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                clients = false;
                break;
            }
        }
        for (int j = 0; j < 5; j++)
        {
            if (bad[i][j] == "")
            {
                break;
            }
            bool flag = true;
            for (int k = 0; k < L; k++)
            {
                if (bad[i][j] == ingredients[k])
                {
                    flag = false;
                }
            }

            if (!flag)
            {
                clients = false;
                break;
            }
        }
        if (clients)
        {
            cnt++;
        }
    }
    cout << cnt << endl;
}