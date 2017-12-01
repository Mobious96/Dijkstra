#pragma once
#include <vector>
#include <iostream>
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
};
struct Graph
{
	vector<vector<Pair> > graph;

	Graph() {};
	Graph(Pair root)
	{
		graph = { {root} };
	}

	void Add(int node)
	{
		vector<Pair> tmp;
		Pair ntmp(node, -1);
		tmp.push_back(ntmp);
		graph.push_back(tmp);
	}
	void Link(int node, vector<Pair> toNodes)
	{
		for (unsigned int i = 0; i < toNodes.size(); i++)
		{
			Pair tmp(node, toNodes[i].value);
			if (graph[toNodes[i].key][0].value == -1)
				graph[toNodes[i].key].pop_back();
			graph[toNodes[i].key].push_back(tmp);

			tmp.key = toNodes[i].key;
			tmp.value = toNodes[i].value;
			if (graph[node][0].value == -1)
				graph[node].pop_back();
			graph[node].push_back(tmp);
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
};