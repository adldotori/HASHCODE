#include <bits/stdc++.h>
using namespace std;

int C, P;
map<string, int> human_to_index;
map<string, int> proj_to_index;
map<int, string> index_to_name;
map<int, string> index_to_proj;
vector<pair<string, int>> conskills[1501];
vector<pair<string, int>> projskills[19414];
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

            conskills[i].push_back(make_pair(skill_name, level));
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
    // for (int i = 0; i < P; i++)
    // {
    //     bool check = false;
    //     for (int j = 0; j < proj)
    // }

    // fout << P;
    // for (int i = 0; i < P; i++)
    // {
    //     fout << index_to_proj[i];
    // }
}
