#include <bits/stdc++.h>
using namespace std;

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
    for (int i = 0; i < P; i++)
    {
        bool check_i = true;

        int check_person[1001] = {
            0,
        };
        for (auto projskill : projskills[i])
        {
            string skill = projskill.first;
            int need_level = projskill.second;

            int k = 0;
            for (k = 0; k < C; k++)
            {
                if (check_person[k] == 0 && conskills[k][skill] >= need_level)
                {
                    ans[i].push_back(index_to_name[k]);
                    check_person[k] = 1;
                    break;
                }
            }
            if (k == C)
            {
                check_i = false;
                ans[i].clear();
                break;
            }
        }
        if (check_i && ans[i].size() >= 1)
        {
            ans_P++;
        }
    }
    fout << ans_P << endl;
    for (int i = 0; i < P; i++)
    {
        if (ans[i].size() >= 1)
        {
            fout << index_to_proj[i] << endl;
            for (auto a : ans[i])
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
