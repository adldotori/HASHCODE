#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int D, I, S, V, F;
int city[10001][10001];      // S * S
int car_count[10001][10001]; // S * S
vector<int> route[1001];     // V

int A;
vector<int> traffic[10001];

queue<int> street_queue[100001]; // S
int street_map[10001][10001];    // S * S
int state[1001][4];              // V * (city, start, end, loc)
int state_traffic[10001];        // I
map<string, pair<int, int>> m;
map<pair<int, int>, string> m_reverse;

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

int main(int argc, char const *argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    ifstream fin2;
    fin2.open(argv[2]);

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
        m.insert(make_pair(street, make_pair(start, end)));
        m_reverse.insert(make_pair(make_pair(start, end), street));
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

            int T;
            fin2 >> T;
            for (int t = 0; t < T; t++)
            {
                traffic[i].push_back(m[tmp].first);
            }
        }
    }

    int score = 0;
    for (int i = 0; i < V; i++)
    {
        state[i][0] = 1;
        state[i][1] = route[i][0];
        state[i][2] = route[i][1];
        state[i][3] = 0;
        street_queue[street_map[route[i][0]][route[i][1]]].push(i);
    }

    update_state_traffic(0);
    if (I < 20)
        print_state(0);

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
                    street_queue[street_map[state[v][1]][state[v][2]]].push(v);
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
                            street_queue[street_map[state[v][1]][state[v][2]]].push(v);

                        check_street_queue[street_num] = 1;
                    }
                }
            }
            if (state[v][0] == route[v].size() - 1 && state[v][2] == route[v].back() && state[v][3] == 0)
            {
                int street_num = street_map[state[v][1]][state[v][2]];
                score += D - t + F;
                // cout << "Score: " << v << " : " << D - t + F << endl;
                state[v][3] = -1;
            }
        }
        update_state_traffic(t);

        if (I < 20)
            print_state(t);
    }

    cout << "score: " << score << endl;
}