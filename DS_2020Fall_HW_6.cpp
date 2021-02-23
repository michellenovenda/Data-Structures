#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

int V;
int** r;
int** arr;
int** arr_v2;
double** new_arr;
int** tmp;
double* dist;
bool* boolean;
double dis[201];
int path[201];
int diameter;
int e1, e2;
double ac_vert = -1;

const int INF = 0x3f3f3f3f;
using namespace std;

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_index()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            r[i][j] = j;

        for (int j = 0; j < V; j++)
        {
            for (int k = j + 1; k < V; k++)
            {
                if (arr[i][r[i][j]] > arr[i][r[i][k]])
                {
                    swap(&r[i][j], &r[i][k]);
                }
            }
        }
    }
}

void floyd_warshall()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            for (int k = 0; k < V; k++)
                arr[j][k] = min(arr[j][k], arr[j][i] + arr[i][k]);
        }
    }

    sort_index();
}

void add(int src, int dst, int weight)
{
    arr[src][dst] = weight;
    arr[dst][src] = weight;
    arr_v2[src][dst] = weight;
    arr_v2[dst][src] = weight;
    tmp[src][dst] = weight;
    tmp[dst][src] = weight;
}

void add_new(int src, int dst, double weight)
{
    new_arr[src][dst] = weight;
    new_arr[dst][src] = weight;
}

void delete_edge(int src, int dst)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            arr[i][j] = tmp[i][j];
            arr_v2[i][j] = tmp[i][j];
        }
    }

    arr[src][dst] = (src == dst) ? 0 : INF;
    arr[dst][src] = (src == dst) ? 0 : INF;
    arr_v2[src][dst] = (src == dst) ? 0 : INF;
    arr_v2[dst][src] = (src == dst) ? 0 : INF;
    tmp[src][dst] = (src == dst) ? 0 : INF;
    tmp[dst][src] = (src == dst) ? 0 : INF;

    floyd_warshall();
}

void delete_edge_new(int src, int dst)
{
    new_arr[src][dst] = (src == dst) ? 0 : INF;
    new_arr[dst][src] = (src == dst) ? 0 : INF;
}

void solve(int u, int v)
{
    vector<pair<int, int>> temp;
    vector<pair<int, int>> vec;

    for (int i = 0; i < V; i++)
        temp.push_back({ arr[u][r[u][i]], arr[v][r[u][i]] });

    int sz = temp.size();
    for (int i = 0; i < sz; i++)
    {
        while (!vec.empty() && (vec.back().second < temp[i].second))
            vec.pop_back();

        vec.push_back(temp[i]);
    }

    int dim = INF;
    double a = 0;

    if (vec.size() == 1)
    {
        if (vec[0].first > vec[0].second)
        {
            a = arr_v2[u][v];
            dim = 2 * vec[0].second;
        }

        else
        {
            a = 0;
            dim = 2 * vec[0].first;
        }
    }

    else
    {
        int vec_sz = vec.size();
        for (int i = 0; i < vec_sz - 1; i++)
        {
            int vs = vec[i + 1].second;
            int vf = vec[i].first;

            if (dim > (arr_v2[u][v] + vf + vs))
            {
                a = (double)((arr_v2[u][v] + vs - vf) / 2.0);
                dim = arr_v2[u][v] + vf + vs;
            }
        }
    }

    if (dim < diameter)
    {
        diameter = dim;
        e1 = u, e2 = v;

        dis[u] = a;
        dis[v] = arr_v2[u][v] - a;
    }
}

void find_diameter()
{
    diameter = INF;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (arr_v2[i][j] < INF)
                solve(i, j);
        }
    }
}

void find_ac()
{
    find_diameter();

    for (int i = 0; i < V; i++)
    {
        if (i != e1 && i != e2)
            dis[i] = 1000000000;
    }

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({ dis[e1], e1 });
    pq.push({ dis[e2], e2 });

    path[e1] = -1;
    path[e2] = -1;

    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();

        int u = it.second;

        if (it.first > dis[u])
            continue;

        for (int v = 0; v < V; v++)
        {
            if ((INF > arr_v2[u][v]) && (dis[v] > (dis[u] + arr_v2[u][v])) && (v != u))
            {
                path[v] = u;
                dis[v] = dis[u] + arr_v2[u][v];
                pq.push({ dis[v], v });
            }
        }
    }

    if (e1 != e2)
    {
        if (dis[e2] == 0 && V >= 2)
            ac_vert = e2;
        else if (dis[e1] == 0 && V >= 2)
            ac_vert = e1;
        else if (e1 > e2)
            swap(e1, e2);
    }

    else
        ac_vert = e1;
}

void traverse(int idx, bool visited[])
{
    visited[idx] = true;

    queue<int> q;
    q.push(idx);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < V; i++)
        {
            if (arr[i][u] != INF)
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
}

bool check_connectivity()
{
    bool* visited = new bool[V];

    for (int u = 0; u < V; u++)
    {
        for (int i = 0; i < V; i++)
            visited[i] = false;

        traverse(u, visited);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                return false;
        }
    }
    return true;
}

int min_distance(double* dist, bool* boolean)
{
    double min = INF;
    int min_index = 0;

    if (ac_vert != -1)
    {
        for (int v = 0; v < V; v++)
        {
            if (boolean[v] == false && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    else
    {
        for (int v = 0; v < V + 1; v++)
        {
            if (boolean[v] == false && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }
}

void total_weight(double* dist)
{
    double sospd = 0;

    if (ac_vert != -1)
    {
        for (int i = 0; i < V; i++)
            sospd += dist[i];
    }

    else
    {
        for (int i = 0; i < V + 1; i++)
            sospd += dist[i];
    }

    cout << sospd << endl;
}

void dijkstra(double** graph, int src)
{
    if (ac_vert == -1)
    {
        for (int i = 0; i < V + 1; i++)
        {
            dist[i] = INF;
            boolean[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < V; count++)
        {
            int u = min_distance(dist, boolean);

            boolean[u] = true;

            for (int v = 0; v < V + 1; v++)
            {
                if (!boolean[v] && graph[u][v] && (dist[u] != INF) && (dist[u] + graph[u][v] < dist[v]))
                    dist[v] = dist[u] + graph[u][v];
            }
        }

        total_weight(dist);
    }

    else
    {
        for (int i = 0; i < V; i++)
        {
            dist[i] = INF;
            boolean[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < V - 1; count++)
        {
            int u = min_distance(dist, boolean);

            boolean[u] = true;

            for (int v = 0; v < V; v++)
            {
                if (!boolean[v] && graph[u][v] && (dist[u] != INF) && (dist[u] + graph[u][v] < dist[v]))
                    dist[v] = dist[u] + graph[u][v];
            }
        }

        total_weight(dist);
    }
}

void printSolution()
{
    printf("Vertex \t\t Distance from Source\n");
    if (ac_vert != -1)
    {
        for (int i = 0; i < V; i++)
            cout << i << "\t\t" << dist[i] << endl;
    }

    else
    {
        for (int i = 0; i < V + 1; i++)
            cout << i << "\t\t" << dist[i] << endl;
    }
}

int main()
{
    string cmd;
    int src, dst, weight;
    cin >> V;

    arr = new int* [V];
    arr_v2 = new int* [V];
    new_arr = new double* [V + 1];

    tmp = new int* [V];
    for (int i = 0; i < V; i++)
    {
        arr[i] = new int[V];
        arr_v2[i] = new int[V];
        tmp[i] = new int[V];
    }
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            arr[i][j] = (i == j) ? 0 : INF;
            arr_v2[i][j] = (i == j) ? 0 : INF;
            tmp[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < V + 1; i++)
        new_arr[i] = new double[V + 1];
    for (int i = 0; i < V + 1; i++)
    {
        for (int j = 0; j < V + 1; j++)
            new_arr[i][j] = (i == j) ? 0 : INF;
    }

    r = new int* [V];
    for (int i = 0; i < V; i++)
        r[i] = new int[V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            r[i][j] = j;
    }

    dist = new double[V + 1];
    boolean = new bool[V + 1];

    while (cin >> cmd)
    {
        if (cmd == "Add")
        {
            cin >> src >> dst >> weight;
            add(src, dst, weight);
            add_new(src, dst, weight);
        }

        else if (cmd == "Delete")
        {
            cin >> src >> dst;
            delete_edge(src, dst);
            delete_edge_new(src, dst);
        }

        else if (cmd == "Diameter")
        {
            if (check_connectivity())
            {
                floyd_warshall();
                find_ac();

                if (ac_vert != -1)
                {
                    add_new(ac_vert, e1, dis[e1]);
                    add_new(ac_vert, e2, dis[e2]);
                }

                else
                {
                    add_new(V, e1, dis[e1]);
                    add_new(V, e2, dis[e2]);
                }

                find_diameter();
                cout << diameter << endl;
            }

            else
                cout << "Not connected graph" << endl;
        }

        else if (cmd == "AC")
        {
            if (check_connectivity())
            {
                floyd_warshall();
                find_ac();

                if (ac_vert != -1)
                {
                    cout << ac_vert << endl;
                    add_new(ac_vert, e1, dis[e1]);
                    add_new(ac_vert, e2, dis[e2]);
                }

                else
                {
                    cout << e1 << " " << e2 << endl;
                    add_new(V, e1, dis[e1]);
                    add_new(V, e2, dis[e2]);
                }
                //cout << "dis " << dis[e1] << " " << dis[e2] << endl;
            }

            else
                cout << "Not connected graph" << endl;
        }

        else if (cmd == "SOSPD")
        {
            if (check_connectivity())
            {
                floyd_warshall();
                find_ac();
                add_new(V, e1, dis[e1]);
                add_new(V, e2, dis[e2]);
                find_diameter();

                if (ac_vert != -1)
                {
                    add_new(ac_vert, e1, dis[e1]);
                    add_new(ac_vert, e2, dis[e2]);
                    //cout << "ac_vert " << ac_vert << endl;
                    dijkstra(new_arr, ac_vert);
                }

                else
                {
                    add_new(V, e1, dis[e1]);
                    add_new(V, e2, dis[e2]);
                    dijkstra(new_arr, V);
                }
            }

            else
                cout << "Not connected graph" << endl;
        }

        else if (cmd == "print")
            printSolution();
    }
    delete[]tmp;
    delete[]arr;
    delete[]arr_v2;
    delete[] new_arr;
    delete[]r;
    delete dist;
    delete boolean;
}






