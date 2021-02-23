#include <iostream>
#include<list>
#include<string.h>

#include<algorithm>
#include<vector>

using namespace std;

typedef struct {
    int airline, price, dst;
}Edge;

class Graph {
    list<Edge>* graph;
    int v;
public:
    Graph(int n)
    {
        v = n;
        graph = new list<Edge>[n];
    }
    ~Graph() {}
    void Add(int from, int to, int p, int a);
    void Delete(int from, int to, int a);
    int Request(int from, int to, int budget);
    int minDistance(int dist[], bool sptSet[]);
    void printprice();
};

void Graph::printprice()
{
    list<Edge>::iterator it;
    for (int i = 0; i < v; ++i)
    {
        cout << "\Price list of city "
            << i << "\nhead ";
        for (it = graph[i].begin(); it != graph[i].end(); it++)
            cout << "-> " << it->price;
        cout << endl;
    }
}

void Graph::Add(int from, int to, int p, int a)
{
    Edge tmp;

    if (to <= v)
    {
        tmp.price = p;
        tmp.airline = a;
        tmp.dst = to;
        graph[from].push_back(tmp);
    }
}

void Graph::Delete(int from, int to, int a)
{
    Edge g;
    list<Edge>::iterator it;

    it = graph[from].begin();
    while (it != graph[from].end())
    {
        if (it->airline == a && it->dst == to)
        {
            it = graph[from].erase(it);
        }

        else
            it++;
    }
}

int Graph::minDistance(int dist[], bool sptSet[])
{
    int min = 2147483647;
    int min_idx = -1;
    for (int i = 0; i < v; i++)
    {
        if (sptSet[i] == false && dist[i] <= min)
        {
            min = dist[i];
            min_idx = i;
        }
    }
    return min_idx;
}

int Graph::Request(int from, int to, int budget)
{
    int* prev_air = new int[v];
    int* dist = new int[v];
    bool* sptSet = new bool[v];

    if (from == to)
        return 0;

    if (from >= v || to >= v || graph[from].begin() == graph[from].end())
        return -1;

    for (int i = 0; i < v; i++)
    {
        prev_air[i] = -1;
        dist[i] = 2147483647;
        sptSet[i] = false;
    }
    dist[from] = 0;

    for (int count = 0; count <= v; count++)
    {
        if (minDistance(dist, sptSet) == -1)
            break;

        else
        {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            list<Edge>::iterator it;

            it = graph[u].begin();
            for (it = graph[u].begin(); it != graph[u].end(); it++)
            {
                if (prev_air[u] == -1)
                {
                    prev_air[it->dst] = it->airline;

                    int cheapest = 2147483647;
                    int i = u;

                    list<Edge>::iterator iter;
                    list<Edge>::iterator ite;
                    int idx = 0;
                    for (iter = graph[i].begin(); iter != graph[i].end(); iter++) {
                        int idx_2 = 0;
                        for (ite = graph[i].begin(); ite != graph[i].end(); ite++) {
                            if (idx != idx_2)
                            {
                                cheapest = (iter->dst == ite->dst && iter->airline == ite->airline) ? min(cheapest, ite->price) : ite->price;

                                //if (iter->dst == ite->dst && iter->airline == ite->airline)
                                //    cheapest = min(cheapest, ite->price);

                                //else
                                //    cheapest = ite->price;
                            }

                            else
                            {
                                cheapest = it->price;

                                if (cheapest != 2147483647)
                                    break;
                            }
                            idx_2++;
                        }
                        idx++;
                    }
                    dist[it->dst] = dist[u] + cheapest;
                }

                else
                {
                    if (dist[u] + it->price + 5 < dist[it->dst] && it->airline != prev_air[u])
                    {
                        //cout << "hello" << endl;
                        prev_air[it->dst] = it->airline;

                        int cheapest = 2147483647;
                        int i = u;
                        list<Edge>::iterator iter;
                        list<Edge>::iterator ite;
                        int idx = 0;
                        for (iter = graph[i].begin(); iter != graph[i].end(); iter++)
                        {
                            int idx_2 = 0;
                            for (ite = graph[i].begin(); ite != graph[i].end(); ite++)
                            {
                                if (idx != idx_2)
                                {
                                    cheapest = (iter->dst == ite->dst && iter->airline == ite->airline) ? min(cheapest, ite->price) : ite->price;

                                    //if (iter->dst == ite->dst && iter->airline == ite->airline)
                                    //    cheapest = min(cheapest, ite->price);

                                    //else
                                    //    cheapest = ite->price;
                                }

                                else
                                {
                                    cheapest = it->price;
                                }
                                idx_2++;
                            }
                            idx++;
                        }
                        dist[it->dst] = dist[u] + cheapest + 5;
                    }

                    else if (dist[u] + it->price < dist[it->dst] && it->airline == prev_air[u])
                    {
                        prev_air[it->dst] = it->airline;

                        int cheapest = 2147483647;
                        int i = u;
                        list<Edge>::iterator iter;
                        list<Edge>::iterator ite;

                        int idx = 0;
                        for (iter = graph[i].begin(); iter != graph[i].end(); iter++)
                        {
                            int idx_2 = 0;
                            for (ite = graph[i].begin(); ite != graph[i].end(); ite++)
                            {
                                if (idx != idx_2)
                                {
                                    cheapest = (iter->dst == ite->dst && iter->airline == ite->airline) ? min(cheapest, ite->price) : ite->price;

                                    //if (iter->dst == ite->dst && iter->airline == ite->airline)
                                    //    cheapest = min(cheapest, ite->price);

                                    //else
                                    //    cheapest = ite->price;
                                }

                                else
                                {
                                    cheapest = it->price;
                                }
                                idx_2++;
                            }
                            idx++;
                        }
                        dist[it->dst] = dist[u] + cheapest;
                    }
                }
            }
        }
    }

    if (dist[to] > budget || dist[to] == 2147483647)
        return -1;
    else
        return dist[to];
}

int main()
{
    int cities, from, to, p, a;
    cin >> cities;
    Graph g(cities);

    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "Add")
        {
            cin >> from >> to >> p >> a;
            g.Add(from, to, p, a);
        }

        else if (cmd == "Delete")
        {
            cin >> from >> to >> a;
            g.Delete(from, to, a);
        }

        else if (cmd == "Request")
        {
            cin >> from >> to >> p;
            cout << g.Request(from, to, p) << endl;
        }

        else if (cmd == "printprice")
        {
            g.printprice();
        }
    }
}