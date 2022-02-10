#include <bits/stdc++.h>
using namespace std;

int C, L;
string good_raw[100001][5];
string bad_raw[100001][5];

vector<int> good[100001];
vector<int> bad[100001];
set<string> ingredients_raw;

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
            vector<string>::iterator iter = find(ingredients.begin(), ingredients.end(), good_raw[i][j]);
            int index = distance(ingredients.begin(), iter);
            good[i].push_back(index);
        }
        for (int j = 0; j < 5; j++)
        {
            vector<string>::iterator iter = find(ingredients.begin(), ingredients.end(), bad_raw[i][j]);
            int index = distance(ingredients.begin(), iter);
            bad[i].push_back(index);
        }
    }

    vector<int> check_ingredients(ingredients.size(), 0);
    for (int igd = 0; igd < ingredients.size(); igd++)
    {
        if (check_ingredients[igd] == 1)
            continue;

        int cnt_good = 0, cnt_bad = 0;

        for (int i = 0; i < C; i++)
        {
            if (find(good[i].begin(), good[i].end(), igd) != good[i].end())
                cnt_good++;
            if (find(bad[i].begin(), bad[i].end(), igd) != bad[i].end())
                cnt_bad++;
        }
        if (cnt_good - cnt_bad > 0)
        {
            check_ingredients[igd] = 1;
        }
    }

    fout << count(check_ingredients.begin(), check_ingredients.end(), 1) << " ";
    for (int i = 0; i < check_ingredients.size(); i++)
    {
        if (check_ingredients[i] == 1)
            fout << ingredients[i] << " ";
    }
}