#include <bits/stdc++.h>
using namespace std;

int C, L;
string good_raw[10001][5];
string bad_raw[10001][5];

vector<int> good[10001];
vector<int> bad[10001];
set<string> ingredients_raw;

int graph[10001][10001];

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ofstream fout;
    fout.open(argv[2]);

    fin >> C;
    for (int i = 0; i < C; i++)
    {
        int num;
        fin >> num;
        for (int j = 0; j < num; j++)
        {
            fin >> good_raw[i][j];
            ingredients_raw.insert(good_raw[i][j]);
        }
        fin >> num;
        for (int j = 0; j < num; j++)
        {
            fin >> bad_raw[i][j];
            ingredients_raw.insert(bad_raw[i][j]);
        }
    }
    vector<string> ingredients(ingredients_raw.begin(), ingredients_raw.end());

    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (good_raw[i][j] == "")
            {
                break;
            }
            vector<string>::iterator iter = find(ingredients.begin(), ingredients.end(), good_raw[i][j]);
            int index = distance(ingredients.begin(), iter);
            good[i].push_back(index);
        }
        for (int j = 0; j < 5; j++)
        {
            if (bad_raw[i][j] == "")
            {
                break;
            }
            vector<string>::iterator iter = find(ingredients.begin(), ingredients.end(), bad_raw[i][j]);
            int index = distance(ingredients.begin(), iter);
            bad[i].push_back(index);
        }
    }

    int edge = 0;
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < C; j++)
        {
            for (int k = 0; k < good[i].size(); k++)
            {
                if (find(bad[j].begin(), bad[j].end(), good[i][k]) != bad[j].end())
                {
                    graph[i][j] = 1;
                    edge++;
                }
            }
            for (int k = 0; k < bad[i].size(); k++)
            {
                if (find(good[j].begin(), good[j].end(), bad[i][k]) != good[j].end())
                {
                    graph[i][j] = 1;
                    edge++;
                }
            }
        }
    }
    // cout << "number of edge : " << edge << endl;

    // print graph
    // for (int i = 0; i < C; i++)
    // {
    //     for (int j = 0; j < C; j++)
    //     {
    //         cout << graph[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // degree initialization
    int check[10001];
    int degree[10001];

    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < C; j++)
        {
            degree[i] += graph[i][j];
        }
    }
    // cout << "degree initialization" << endl;

    // remove the vertex of the lowest degree in graph
    int cnt = 0;
    set<int> answer;
    while (true)
    {
        int min_degree = C;
        int min_degree_vertex = 0;
        for (int i = 0; i < C; i++)
        {
            if (check[i] == 1)
                continue;
            if (degree[i] < min_degree)
            {
                min_degree = degree[i];
                min_degree_vertex = i;
            }
        }

        for (int i = 0; i < good[min_degree_vertex].size(); i++)
        {
            answer.insert(good[min_degree_vertex][i]);
        }
        check[min_degree_vertex] = 1;
        for (int i = 0; i < C; i++)
        {
            if (graph[min_degree_vertex][i] == 1)
                check[i] = 1;
        }
        if (min_degree == C)
            break;
        cnt++;
    }
    // cout << cnt << endl;
    fout << answer.size() << " ";

    for (auto a : answer)
        fout << ingredients[a] << " ";
}