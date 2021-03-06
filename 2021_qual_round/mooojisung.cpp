#include <bits/stdc++.h>
using namespace std;

int D, I, S, V, F;
int city[10001][10001];  // S * S
vector<int> route[1001]; // V

int A;
vector<int> traffic[10001]; // S * D

queue<int> street_queue[100001]; // S
int street_map[10000][10000];
int state[1000][4];       // V * (city, start, end, loc)
int state_traffic[10001]; // I

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ofstream fout;
    fout.open(argv[2]);

    fin >> D >> I >> S >> V >> F;

    vector<pair<int, int>> street_info;
    vector<string> street_name_list;

    for (int s = 0; s < S; s++)
    {
        int start, end, length;
        fin >> start >> end;
        string street;
        fin >> street;
        fin >> length;

        city[start][end] = -length;
        street_info.push_back(make_pair(start, end));
        street_map[start][end] = s;
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
                route[i].push_back(street_info[idx].first);
            route[i].push_back(street_info[idx].second);
            city[street_info[idx].first][street_info[idx].second] = abs(city[street_info[idx].first][street_info[idx].second]);
        }
    }

    int out_I = 0;
    for (int i = 0; i < I; i++)
    {
        vector<int> inc;
        for (int j = 0; j < I; j++)
            if (city[j][i] > 0)
                inc.push_back(j);
        if (inc.empty())
            continue;
        out_I++;
    }

    fout << out_I << endl;
    for (int i = 0; i < I; i++)
    {
        vector<int> inc;
        for (int j = 0; j < I; j++)
        {
            if (city[j][i] > 0)
            {
                inc.push_back(j);
            }
        }
        if (inc.empty())
            continue;
        fout << i << endl;
        fout << inc.size() << endl;
        for (int j = 0; j < inc.size(); j++)
        {
            int idx = find(street_info.begin(), street_info.end(), make_pair(inc[j], i)) - street_info.begin();
            fout << street_name_list[idx] << " ";
            fout << 1 << endl;
        }
    }
}
