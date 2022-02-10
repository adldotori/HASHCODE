#include <bits/stdc++.h>
using namespace std;

int C, L;
string good_raw[100001][5];
string bad_raw[100001][5];

vector<int> good[100001];
vector<int> bad[100001];
set<string> ingredients_raw;

int eval(set<int> answer)
{
    int cnt = 0;
    for (int i = 0; i < C; i++)
    {
        bool clients = true;
        for (int j = 0; j < good[i].size(); j++)
            if (answer.find(good[i][j]) == answer.end())
                clients = false;
        for (int j = 0; j < bad[i].size(); j++)
            if (answer.find(bad[i][j]) != answer.end())
                clients = false;
        if (clients)
            cnt++;
    }
    return cnt;
}

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

    set<int> answer;
    for (int igd = 0; igd < ingredients.size(); igd++)
    {
        if (find(answer.begin(), answer.end(), igd) != answer.end())
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
            answer.insert(igd);
    }

    int real = eval(answer);
    for (int i = 0; i < 30; i++)
    {
        set<int> copy = answer;
        for (auto ans : copy)
        {
            answer.erase(ans);
            int score = eval(answer);

            if (score <= real)
                answer.insert(ans);
            else
            {
                real = score;
                break;
            }
        }
    }
    cout << "[+]: " << eval(answer) << endl;

    for (int i = 0; i < 30; i++)
    {
        for (int igd = 0; igd < ingredients.size(); igd++)
        {
            if (answer.find(igd) != answer.end())
                continue;
            answer.insert(igd);
            int score = eval(answer);

            if (score < real)
            {
                answer.erase(igd);
            }
            else
            {
                real = score;
                break;
            }
        }
    }
    cout << "[+]: " << eval(answer) << endl;

    fout << answer.size() << " ";

    for (auto a : answer)
        fout << ingredients[a] << " ";
}