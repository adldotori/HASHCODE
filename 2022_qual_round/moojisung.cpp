#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef pair<int, int> ii;

int C, P;
map<string, int> human_to_index;
map<string, int> proj_to_index;
map<int, string> index_to_name;
map<int, string> index_to_proj;
map<string, int> conskills[1501];
vector<pair<string, int>> projskills[19414];
int proj_info[19414][4];
set<string> skill_list;
map<string, int> who_has_skill;

map<string, int> humanskill_maximum;
map<string, int> projskill_maximum;

int score = 0;

bool cmp(int i, int j)
{
    if (proj_info[i][2] != proj_info[j][2])
        return proj_info[i][2] < proj_info[j][2];
    return proj_info[i][1] > proj_info[j][1];
}
int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ofstream fout;
    fout.open(argv[2]);

    fin >> C >> P;
    for (int i = 0; i < C; i++)
    {
        string name;
        fin >> name;
        human_to_index.insert(make_pair(name, i));
        index_to_name.insert(make_pair(i, name));

        int num_of_skills;
        fin >> num_of_skills;
        for (int j = 0; j < num_of_skills; j++)
        {
            string skill_name;
            fin >> skill_name;
            skill_list.insert(skill_name);
            int level;
            fin >> level;
            // cout << skill_name << level;

            conskills[i].insert(make_pair(skill_name, level));
            if (humanskill_maximum.find(skill_name) == humanskill_maximum.end() || humanskill_maximum[skill_name] < level)
                humanskill_maximum[skill_name] = level;
            if (who_has_skill.find(skill_name) == who_has_skill.end())
                who_has_skill[skill_name] = 0;
            who_has_skill[skill_name]++;
        }
    }
    for (int i = 0; i < P; i++)
    {
        string project;
        fin >> project;
        proj_to_index.insert(make_pair(project, i));
        index_to_proj.insert(make_pair(i, project));
        int d, s, b, r;
        fin >> d >> s >> b >> r;
        proj_info[i][0] = d;
        proj_info[i][1] = s;
        proj_info[i][2] = b;
        proj_info[i][3] = r;
        score += s;
        for (int j = 0; j < r; j++)
        {
            string skill_name;
            fin >> skill_name;
            skill_list.insert(skill_name);
            int level;
            fin >> level;
            projskills[i].push_back(make_pair(skill_name, level));
            if (projskill_maximum.find(skill_name) == projskill_maximum.end() || projskill_maximum[skill_name] < level)
                projskill_maximum[skill_name] = level;
            // if (who_has_skill.find(skill_name) == who_has_skill.end())
            //     who_has_skill[skill_name] = 0;
            // who_has_skill[skill_name]++;
        }
    }

    cout << score << endl;
    // for (auto v : skill_list)
    // {
    //     cout << v << " : " << humanskill_maximum[v] << " || " << projskill_maximum[v] << endl;
    // }
    // cout << skill_list.size();
    // for (auto v : who_has_skill)
    // {
    //     cout << v.first << " " << v.second << endl;
    // }

    // cout << skill_list.size();

    int check[20000] = {
        0,
    };
    int ans_P = 0;
    vector<string> ans[20000];
    map<int, int> timer; // ?????? index => ??????

    for (int i = 0; i < C; i++)
        timer[i] = 0;

    vector<int> P_tmp;
    for (int i = 0; i < P; i++)
    {
        P_tmp.push_back(i);
    }
    sort(P_tmp.begin(), P_tmp.end(), cmp);
    for (int i = 0; i < P; i++)
    {
        vector<ii> v(timer.begin(), timer.end());

        sort(v.begin(), v.end(), [](ii a, ii b)
             { return a.second < b.second; });
        // for (ii it : v)
        //     cout << it.first << ":" << it.second << " ";
        // cout << endl
        //      << endl
        //      << endl;
        // cout << v.size() << endl;

        bool check_i = true;

        int check_person[1001] = {
            0,
        };
        for (auto projskill : projskills[P_tmp[i]])
        {
            string skill = projskill.first;
            int need_level = projskill.second;

            // cout << skill;
            int k = 0;
            for (k = 0; k < C; k++)
            {
                // cout << v.size() << " " << v[k].first << " " << v[k].second << " " << conskills[v[k].first][skill] << endl;
                if (check_person[v[k].first] == 0 && conskills[v[k].first][skill] >= need_level)
                {
                    ans[P_tmp[i]].push_back(index_to_name[v[k].first]);
                    // cout << "sdfdsf" << endl;
                    timer[v[k].first] += proj_info[P_tmp[i]][0];
                    check_person[v[k].first] = 1;
                    break;
                }
                // cout << k << endl;
            }
            if (k == C)
            {
                check_i = false;
                ans[P_tmp[i]].clear();
                break;
            }
        }

        if (check_i && ans[P_tmp[i]].size() >= 1)
        {
            ans_P++;
        }
    }
    fout << ans_P << endl;
    for (int i = 0; i < P; i++)
    {
        if (ans[P_tmp[i]].size() >= 1)
        {
            fout << index_to_proj[P_tmp[i]] << endl;
            for (auto a : ans[P_tmp[i]])
            {
                fout << a << " ";
            }
            fout << endl;
        }
    }
    // fout << P;
    // for (int i = 0; i < P; i++)
    // {
    //     fout << index_to_proj[i];
    // }
}
