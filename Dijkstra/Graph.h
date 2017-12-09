#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
struct Pair
{
	int key;
	int value;

	Pair() {};
	Pair(int _key, int _value)
	{
		key = _key;
		value = _value;
	}

	Pair& operator=(Pair& src)
	{
		key = src.key;
		value = src.value;
		return *this;
	}
};

struct DHeap
{
	int n;
	int d;
	Pair* weight;
	int* index;

	int GetIndex(int i)
	{
		for (int i = 0; i < n; i++)
		{
			if (weight[i].key == i)
				return i;
		}
		return -1;
	}

	DHeap(int _n, int _d)
	{
		n = _n;
		d = _d;
		weight = new Pair[n];
		index = new int[n];
		for (int i = 0; i < n; i++)
		{
			index[i] = i;
		}
	}
	~DHeap()
	{
		delete[] weight;
		delete[] index;
	}
	int FirstChild(int i)
	{
		int j = i*d + 1;
		if (j <= n - 1)
			return j;
		else
			return -1;
	}

	int LastChild(int i)
	{
		int j = FirstChild(i);
		if (j == -1)
			return -1;
		else
			return min(j + d - 1, n - 1);
	}

	int Father(int i)
	{
		return (i-1)/d;
	}

	Pair MinChild(int i)
	{
		Pair tmp;
		int kf = FirstChild(i);
		if (kf == -1)
		{
			tmp.key = -1;
			tmp.value = -1;
			return tmp;
		}
		else
		{
			int kl = LastChild(i);
			tmp.key = kf;
			tmp.value = weight[kf].value;
			for (int j = kf + 1; j < kl; j++)
			{
				if (weight[j].value < tmp.value)
				{
					tmp.value = weight[j].value;
					tmp.key = j;
				}
			}
			return tmp;
		}
	}
	void Swap(int frs, int sec)
	{
		Pair buf = weight[frs];
		weight[frs] = weight[sec];
		weight[sec] = buf;
		int fi = weight[frs].key;
		int si = weight[sec].key;
		int ibuf = index[fi];
		index[fi] = index[si];
		index[si] = ibuf;
	}
	void Diving(int i)
	{
		Pair j1(i, weight[i].value);
		Pair j2 = MinChild(j1.key);
		while ((j2.key != -1) && (j1.value > j2.value))
		{
			Swap(j1.key, j2.key);
			j1 = j2;
			j2 = MinChild(j1.key);
		}
	}
	void Emersion(int i)
	{
		Pair j1(i, weight[i].value);
		Pair j2(Father(j1.key),weight[Father(j1.key)].value);
		while ((j1.key != 0) && (j1.value < j2.value))
		{
			Swap(j1.key, j2.key);
			j1 = j2;
			j2.key = Father(j1.key);
			j2.value = weight[j2.key].value;
		}
	}
	Pair GetMin()
	{
		Pair res = weight[0];
		Swap(0, n - 1);
		n = n - 1;
		if(n > 1)
			Diving(0);
		return res;
	}
	void Queue()
	{
		for (int i = n - 1; i >= 0; i--)
			Diving(i);
	}

};


struct Graph
{
	vector<vector<Pair> > graph;
	int size;

	Graph() { size = 0; };
	Graph(Pair root)
	{
		graph = { {root} };
		size = 1;
	}
	~Graph()
	{
		graph.clear();
	}
	void Add(int node)
	{
		vector<Pair> tmp;
		Pair ntmp(node, -1);
		tmp.push_back(ntmp);
		graph.push_back(tmp);
		size = size++;
	}
	void Link(int node, vector<Pair> toNodes)
	{
		for (unsigned int i = 0; i < toNodes.size(); i++)
		{
			//Add this node to other nodes
			Pair tmp(node, toNodes[i].value);
			if (graph[toNodes[i].key][0].value == -1)
				graph[toNodes[i].key].pop_back();
			graph[toNodes[i].key].push_back(tmp);
			//Add other nodes to this node
			tmp.key = toNodes[i].key;
			tmp.value = toNodes[i].value;
			if (graph[node][0].value == -1)
				graph[node].pop_back();
			graph[node].push_back(tmp);
		}
	}
	void SetEdge(int node_1, int node_2, int weight)
	{
		if (GetValue(node_1, node_2) == -1)
		{
			if (graph[node_1][0].value == -1)
				graph[node_1].pop_back();
			graph[node_1].push_back(Pair(node_2, weight));
			if (graph[node_2][0].value == -1)
				graph[node_2].pop_back();
			graph[node_2].push_back(Pair(node_1, weight));
		}
	}
	void Print()
	{
		for (unsigned int i = 0; i < graph.size(); i++)
		{
			cout << i << " linked to: ";
			for (unsigned int j = 0; j < graph[i].size(); j++)
			{
				cout <<"("<< graph[i][j].key << ":" << graph[i][j].value<<") ";
			}
			cout << endl;
		}
	}
	
	int GetValue(int node_1, int node_2)
	{
		for (int i = 0; i < graph[node_1].size(); i++)
		{
			if (graph[node_1][i].key == node_2)
				return graph[node_1][i].value;
		}
		return -1;
	}

	void Generate(Graph& G, int size, int edge_numbers, int max_weight)
	{
		int m = edge_numbers;
		srand(time(0));
		for (int i = 0; i < size; i++)
		{
			G.Add(i);
		}
		while (m)
		{
			for (int i = 0; i < size; i++)
			{
				SetEdge(i, min(i + rand() % size, size - 1), rand() % max_weight + 1);
				m = m--;
				/*for (int j = i + 1; j < size; j++)
				{
					if ((rand() % 2 == 1) && (m != 0))
					{
						SetEdge(i, j, rand() % max_weight + 1);
						m = m--;
					}
				}*/
			}
		}
	}
};