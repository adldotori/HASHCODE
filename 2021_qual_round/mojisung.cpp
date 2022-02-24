#include <bits/stdc++.h>
using namespace std;

int D, I, S, V, F;
int city[10001][10001];      // S * S
int car_count[10001][10001]; // S * S
vector<int> route[1001];     // V

int A;
vector<int> traffic[10001]; // S * D

queue<int> street_queue[100001]; // S
int street_map[10000][10000];
int state[1000][4];       // V * (city, start, end, loc)
int state_traffic[10001]; // I
map<string, pair<int, int>> m;
map<pair<int, int>, string> m_reverse;

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ofstream fout;
    fout.open(argv[2]);

    fin >> D >> I >> S >> V >> F;

    for (int s = 0; s < S; s++)
    {
        int start, end, length;
        fin >> start >> end;
        string street;
        fin >> street;
        fin >> length;

        city[start][end] = length;
        street_map[start][end] = s;
        m_reverse.insert(make_pair(make_pair(start, end), street));
        m.insert(make_pair(street, make_pair(start, end)));
    }

    for (int i = 0; i < V; i++)
    {
        int num;
        fin >> num;
        for (int j = 0; j < num; j++)
        {
            string tmp;
            fin >> tmp;

            pair<int, int> idx = m[tmp];
            if (j == 0)
                route[i].push_back(idx.first);
            route[i].push_back(idx.second);
            car_count[idx.first][idx.second] += 1;
        }
    }
    cout << "read";

    int out_I = 0;
    float sum[10001] = {
        0,
    };
    for (int i = 0; i < I; i++)
    {
        vector<int> inc;
        for (int j = 0; j < I; j++)
            if (car_count[j][i] > 0)
            {
                inc.push_back(j);
                sum[i] += car_count[j][i];
            }
        sum[i] /= (float)inc.size();
        if (inc.empty())
            continue;
        out_I++;
    }

    fout << out_I << endl;
    for (int i = 0; i < I; i++)
    {
        vector<int> inc;
        vector<float> count;
        for (int j = 0; j < I; j++)
        {
            if (car_count[j][i] > 0)
            {
                inc.push_back(j);
                count.push_back((float)car_count[j][i]);
            }
        }
        if (inc.empty())
            continue;
        fout << i << endl;
        fout << inc.size() << endl;
        for (int j = 0; j < inc.size(); j++)
        {
            fout << m_reverse[make_pair(inc[j], i)] << " ";
            int ans = (int)(count[j] / sum[i]);
            if (ans == 0)
                ans = 1;
            fout << ans << endl;
        }
    }
}
