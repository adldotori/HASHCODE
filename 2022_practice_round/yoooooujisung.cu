#include <bits/stdc++.h>
#include <cuda.h>
#include <cuda_runtime.h>
#define gpuErrchk(ans)                        \
    {                                         \
        gpuAssert((ans), __FILE__, __LINE__); \
    }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
    if (code != cudaSuccess)
    {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
    }
}
using namespace std;

int C, L;
string good_raw[10001][5];
string bad_raw[10001][5];

vector<int> good[10001];
vector<int> bad[10001];

set<string> ingredients_raw;

int graph[10001][10001];

__global__ void eval_cu(int *answer_cu, int *answer, int answer_len, int *good_cu, int *bad_cu, int *good_len, int *bad_len, int C)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < C)
    {
        int clients = 1;
        for (int j = 0; j < good_len[i]; j++)
        {
            bool check = true;
            for (int k = 0; k < answer_len; k++)
            {
                if (answer[k] == good_cu[i * 10 + j])
                    check = false;
            }
            if (check)
                clients = 0;
        }
        for (int j = 0; j < bad_len[i]; j++)
        {
            bool check = false;
            for (int k = 0; k < answer_len; k++)
            {
                if (answer[k] == bad_cu[i * 10 + j])
                    check = true;
            }
            if (check)
                clients = 0;
        }
        answer_cu[i] = clients;
    }
}

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

    int *good_cu;
    int *bad_cu;
    int *good_len;
    int *bad_len;

    cudaMallocManaged(&good_cu, 10 * C * sizeof(int));
    cudaMallocManaged(&bad_cu, 10 * C * sizeof(int));
    cudaMallocManaged(&good_len, C * sizeof(int));
    cudaMallocManaged(&bad_len, C * sizeof(int));

    for (int i = 0; i < C; i++)
    {
        int num;
        fin >> num;
        good_len[i] = num;
        for (int j = 0; j < num; j++)
        {
            fin >> good_raw[i][j];
            ingredients_raw.insert(good_raw[i][j]);
        }
        fin >> num;
        bad_len[i] = num;
        for (int j = 0; j < num; j++)
        {
            fin >> bad_raw[i][j];
            ingredients_raw.insert(bad_raw[i][j]);
        }
    }
    vector<string> ingredients(ingredients_raw.begin(), ingredients_raw.end());

    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < good_len[i]; j++)
        {
            vector<string>::iterator iter = find(ingredients.begin(), ingredients.end(), good_raw[i][j]);
            int index = distance(ingredients.begin(), iter);
            good[i].push_back(index);
            good_cu[i * 10 + j] = index;
        }
        for (int j = 0; j < bad_len[i]; j++)
        {
            vector<string>::iterator iter = find(ingredients.begin(), ingredients.end(), bad_raw[i][j]);
            int index = distance(ingredients.begin(), iter);
            bad[i].push_back(index);
            bad_cu[i * 10 + j] = index;
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
    cout << "number of edge : " << edge << endl;

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
    int check[10001] = {
        0,
    };
    int degree[10001] = {
        0,
    };

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
    set<int> vertex;

    while (true)
    {
        int min_degree = C;
        int min_degree_vertex = -1;
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
        if (min_degree == C)
            break;

        // cout << "D:" << min_degree << " " << min_degree_vertex << " ";
        vertex.insert(min_degree_vertex);
        for (int i = 0; i < good[min_degree_vertex].size(); i++)
        {
            answer.insert(good[min_degree_vertex][i]);
        }
        check[min_degree_vertex] = 1;
        for (int i = 0; i < C; i++)
        {
            if (check[i] == 0 && graph[min_degree_vertex][i] == 1)
            {
                check[i] = 1;
                for (int j = 0; j < C; j++)
                {
                    if (check[j] == 0 && graph[i][j] == 1)
                        degree[j]--;
                }
            }
        }
        cnt++;
    }
    cout << cnt << endl;

    int real = eval(answer);

    int *answer_copy;
    int *d_eval;
    cudaMallocManaged(&answer_copy, C * sizeof(int));
    cudaMallocManaged(&d_eval, C * sizeof(int));

    for (int cnt = 0; cnt < 10; cnt++)
    {

        float start = clock();
        for (int i = 0; i < 30; i++)
        {
            set<int> copy = answer;
            for (auto ans : copy)
            {
                answer.erase(ans);

                // CUDA
                int j = 0;
                for (auto it = answer.begin(); it != answer.end(); ++it)
                    answer_copy[j++] = *it;

                eval_cu<<<512, 32>>>(d_eval, answer_copy, int(answer.size()), good_cu, bad_cu, good_len, bad_len, C);
                gpuErrchk(cudaDeviceSynchronize());

                int score = 0;
                for (int j = 0; j < C; j++)
                {
                    if (d_eval[j] == 1)
                        score++;
                }

                // CPU
                // int score = eval(answer);

                if (score <= real)
                    answer.insert(ans);
                else
                {
                    real = score;
                    break;
                }
            }
        }
        float end = clock();
        float time = (end - start) / CLOCKS_PER_SEC;

        printf("time: %f\n", time);
        cout << "[+]: " << eval(answer) << endl;

        for (int i = 0; i < 30; i++)
        {
            for (int igd = 0; igd < ingredients.size(); igd++)
            {
                if (answer.find(igd) != answer.end())
                    continue;
                answer.insert(igd);

                // CUDA
                int j = 0;
                for (auto it = answer.begin(); it != answer.end(); ++it)
                    answer_copy[j++] = *it;

                eval_cu<<<512, 32>>>(d_eval, answer_copy, int(answer.size()), good_cu, bad_cu, good_len, bad_len, C);
                gpuErrchk(cudaDeviceSynchronize());

                int score = 0;
                for (int j = 0; j < C; j++)
                {
                    if (d_eval[j] == 1)
                        score++;
                }

                // CPU
                // int score = eval(answer);

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
    }
    fout << answer.size() << " ";

    for (auto a : answer)
        fout << ingredients[a] << " ";

    cudaFree(good_cu);
    cudaFree(bad_cu);
    cudaFree(good_len);
    cudaFree(bad_len);
    cudaFree(answer_copy);
    cudaFree(d_eval);
}