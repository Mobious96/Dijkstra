#include "Graph.h"
#include <algorithm>
int DijkstraMark(Graph G, int node_start, int node_finish)
{
	//Initialization
	int size = G.graph.size();
	int* labels = new int[size];
	int* dist = new int[size];//array of distances
	for (int i = 0; i < size; i++)
	{
		dist[i] = INT_MAX;
		labels[i] = 0;
	}
	dist[node_start] = 0;

	//Main loop
	int current = node_start;
	while (labels[current] == 0)
	{
		//Recalculating neighbor node's distance
		for (int i = 0; i < G.graph[current].size(); i++)
		{
			int node_key = G.graph[current][i].key;//neighbor node for current node
			if (labels[node_key] == 0)
			{
				dist[node_key] = std::min(dist[node_key], dist[current] + G.GetValue(node_key, current));
			}
		}
		labels[current] = 1;

		//Jump to another node with minimal distance
		int NextNeighbor;
		int tmp_min = INT_MAX;
		for (int i = 0; i < size; i++)
		{
			if ((tmp_min > dist[i]) && (labels[i] == 0))
			{
				tmp_min = dist[i];
				NextNeighbor = i;
			}
		}
		if (tmp_min != INT_MAX)
			current = NextNeighbor;
		else
			break;
	}
	return dist[node_finish];
}

void main()
{
	Graph G;
	for (int i = 0; i < 5; i++)
	{
		G.Add(i);
	}
	vector<Pair> tmp = { {1,1},{2,3},{3,1} };
	G.Link(0, tmp); //connect 0_node to 1_node with weight = 1, to 2_node with weight = 3, to 3_node with weight = 1;
	tmp = { { 2,2 },{ 3,1 },{ 4,1 } };
	G.Link(1, tmp);
	tmp = { {4,2} };
	G.Link(2, tmp);
	G.Print();
	int start = 0;
	int finish = 4;
	cout << "Shortest from "<<start<<" to "<<finish<<" is " << DijkstraMark(G, start, finish) << endl;
}