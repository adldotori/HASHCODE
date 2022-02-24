#include <bits/stdc++.h>
using namespace std;

int D, I, S, V, F;
int city[10001][10001];      // S * S
int car_count[10001][10001]; // S * S
vector<int> route[1001];     // V

int A;
vector<int> traffic[10001]; // I * I

queue<int> street_queue[100001]; // S
int street_map[10000][10000];
int state[1000][4];       // V * (city, start, end, loc)
int state_traffic[10001]; // I
map<string, pair<int, int>> m;
map<pair<int, int>, string> m_reverse;
int score[10001][10001]; // S * S

void update_state_traffic(int t)
{
    for (int i = 0; i < I; i++)
    {
        if (traffic[i].size() > 0)
            state_traffic[i] = traffic[i][t % traffic[i].size()];
        else
            state_traffic[i] = -1;
    }
}

void print_state(int t)
{
    cout << "======" << t << "======\n";
    for (int v = 0; v < V; v++)
    {
        if (state[v][0] == route[v].size() - 1 && state[v][2] == route[v].back() && state[v][3] == 0)
        {
            cout << v << "번째 사람 성공!  +" << D - t + F << endl;
        }
        else
            cout << v << "번째 사람: " << state[v][1] << "에서 " << state[v][2] << "로 이동, " << state[v][3] << "만큼 남음\n";
    }

    cout << "--------------------\n";
    for (int i = 0; i < I; i++)
    {
        cout << state_traffic[i] << " => " << i << " : " << i << "번째 intersection 은 " << state_traffic[i] << " 으로!!\n";
    }
}

void initialize(void)
{
    for (int i = 0; i < I; i++)
        traffic[i] = vector<int>();
}

int scoring(void)
{
    for (int i = 0; i < V; i++)
    {
        state[i][0] = 1;
        state[i][1] = route[i][0];
        state[i][2] = route[i][1];
        state[i][3] = 0;
        street_queue[street_map[route[i][0]][route[i][1]]].push(i);
        score[state[i][1]][state[i][2]] = max(score[state[i][1]][state[i][2]], (int)street_queue[street_map[route[i][0]][route[i][1]]].size());
    }

    update_state_traffic(0);
    if (I < 20)
        print_state(0);

    int tmp_score = 0;
    for (int t = 1; t <= D; t++)
    {
        int check_street_queue[100001] = {
            0,
        };
        for (int v = 0; v < V; v++)
        {
            if (state[v][3] > 0)
            {
                state[v][3] -= 1; // 한 칸 전진!
                if (state[v][0] < route[v].size() - 1 && state[v][3] == 0)
                {
                    int idx = street_map[state[v][1]][state[v][2]];
                    street_queue[idx].push(v);
                    score[state[v][1]][state[v][2]] = max(score[state[v][1]][state[v][2]], (int)street_queue[idx].size());
                }
            }
            else if (state[v][3] == 0)
            {

                if (state[v][0] < route[v].size() - 1 && state_traffic[state[v][2]] == state[v][1]) // 초록불!
                {
                    int street_num = street_map[state[v][1]][state[v][2]];
                    if (!check_street_queue[street_num] && !street_queue[street_num].empty() && street_queue[street_num].front() == v) // 내가 첫번째 대기자라면 다음 스트릿으로 전진!
                    {
                        street_queue[street_num].pop();
                        state[v][0] += 1;
                        state[v][1] = state[v][2];
                        state[v][2] = route[v][state[v][0]];
                        state[v][3] = city[state[v][1]][state[v][2]] - 1;
                        if (state[v][0] < route[v].size() - 1 && state[v][3] == 0)
                        {
                            int idx = street_map[state[v][1]][state[v][2]];
                            street_queue[idx].push(v);
                            score[state[v][1]][state[v][2]] = max(score[state[v][1]][state[v][2]], (int)street_queue[idx].size());
                        }

                        check_street_queue[street_num] = 1;
                    }
                }
            }
            if (state[v][0] == route[v].size() - 1 && state[v][2] == route[v].back() && state[v][3] == 0)
            {
                int street_num = street_map[state[v][1]][state[v][2]];
                tmp_score += D - t + F;
                state[v][3] = -1;
            }
        }
        update_state_traffic(t);

        if (I < 20)
            print_state(t);
    }
    return tmp_score;
}
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

    int count[100001] = {
        0,
    };
    for (int i = 0; i < V; i++)
    {
        state[i][0] = 1;
        state[i][1] = route[i][0];
        state[i][2] = route[i][1];
        state[i][3] = 0;
        street_queue[street_map[route[i][0]][route[i][1]]].push(i);
        // traffic[route[i][1]].push_back(route[i][0]);
        score[route[i][0]][route[i][1]]++;
        cout << route[i][0] << route[i][1];
        // score[state[i][1]][state[i][2]] = max(score[state[i][1]][state[i][2]], (int)street_queue[street_map[route[i][0]][route[i][1]]].size());
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
        for (int j = 0; j < inc.size(); j++)
        {
            int ans = (int)(count[j] / sum[i]);
            if (ans == 0)
                ans = 1;
            if (score[inc[j]][j] == 0)
                score[inc[j]][i] = ans;
        }
        if (inc.empty())
            continue;

        vector<int> inc_tmp;
        int check[10001] = {
            0,
        };
        for (int j = 0; j < inc.size(); j++)
        {
            int max_index = -1;
            int max_score = 0;
            for (int k = 0; k < inc.size(); k++)
            {
                if (check[k] == 1)
                    continue;
                if (max_score < score[inc[k]][i])
                {
                    max_index = k;
                    max_score = score[inc[k]][i];
                }
            }
            if (max_score >= 1)
            {
                inc_tmp.push_back(max_index);
                check[max_index] = 1;
            }
        }
        fout << i << endl;
        fout << inc_tmp.size() << endl;
        for (int j = 0; j < inc_tmp.size(); j++)
        {
            cout << inc_tmp[j] << " " << i << endl;
            fout << m_reverse[make_pair(inc_tmp[j], i)] << " ";
            fout << score[inc_tmp[j]][i] << endl;
        }
    }

    for (int i = 0; i < I; i++)
    {
        for (int j = 0; j < I; j++)
        {
            cout << score[i][j] << " ";
        }
        cout << endl;
    }
}