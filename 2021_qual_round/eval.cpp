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

    ifstream fin2;
    fin2.open(argv[2]);

    fin >> D >> I >> S >> V >> F;

    vector<int> start_list;
    vector<int> end_list;
    vector<string> street_name_list;

    for (int i = 0; i < S; i++)
    {
        int start, end, length;
        fin >> start >> end;
        string street;
        fin >> street;
        fin >> length;

        city[start][end] = length;
        start_list.push_back(start);
        end_list.push_back(end);
        street_name_list.push_back(street);
    }

    for (int i = 0; i < V; i++)
    {
        int num;
        fin >> num;
        for (int j = 0; j < num; j++)
        {
            string tmp;
            fin >> tmp;

            int idx = find(street_name_list.begin(), street_name_list.end(), tmp) - street_name_list.begin();
            if (j == 0)
                route[j].push_back(start_list[idx]);
            route[i].push_back(end_list[idx]);
        }
    }

    fin2 >> A;
    for (int a = 0; a < A; a++)
    {
        int i, num_s;
        fin2 >> i;
        fin2 >> num_s;

        for (int j = 0; j < num_s; j++)
        {
            string tmp;
            fin2 >> tmp;

            int idx = find(street_name_list.begin(), street_name_list.end(), tmp) - street_name_list.begin();
            int T;
            fin2 >> T;
            for (int t = 0; t < T; t++)
                traffic[i].push_back(start_list[idx]);
        }
        int size = traffic[i].size();
        for (int tmp = 0; tmp < size; tmp++)
            traffic[i].push_back(traffic[i][tmp]);
    }

    int score = 0;
    for (int v = 0; v < V; v++)
    {
        int t = 0;
        int before = -1;
        // cout << v << ":";
        for (auto r : route[v])
        {
            if (before == -1)
            {
                before = r;
                continue;
            }

            t += city[before][r];
            int tmp = 0;
            if (!traffic[r].empty())
                tmp = t % (int(traffic[r].size()) / 2);
            else
            {
                t = D + 1;
                break;
            }

            int wait = find(traffic[r].begin() + tmp, traffic[r].end(), before) - traffic[r].begin();
            wait -= tmp;

            t += wait;
            // cout << "(" << r << ":" << before << "->" << r << "|" << wait << "," << t << ") ";

            before = r;
        }
        // cout << endl;

        if (D >= t)
            score += F + D - t;
    }
    cout << "score: " << score << endl;
}