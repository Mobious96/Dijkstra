#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

string IntToString(int a)
{
	ostringstream temp;
	temp << a;
	return temp.str();
}
int* DijkstraMark(Graph G, int node_start)
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
	delete[] labels;
	return dist;
}


int* DijkstraHeap(Graph G, int node_start, int heap_size)
{
	DHeap tree(G.size, 9);
	int* dist = new int[G.size];
	for (int i = 0; i < G.size; i++)
	{
		dist[i] = INT_MAX;
		tree.weight[i].key = i;
		tree.weight[i].value = INT_MAX;
	}
	int ind;
	tree.weight[node_start].value = 0;
	tree.Queue();
	Pair res;
	while (tree.n > 0)
	{
		res = tree.GetMin(); //root;
		int tmp;
		tmp = res.key;
		dist[tmp] = res.value;


		for (int i = 0; i < G.graph[tmp].size(); i++)
		{
			Pair edge = G.graph[tmp][i];
			if (edge.value + dist[tmp] < tree.weight[tree.index[edge.key]].value)
			{
				tree.weight[tree.index[edge.key]].value = edge.value + dist[tmp];
				tree.Emersion(tree.index[edge.key]);
			}
		}
	}
	return dist;
}

void main()
{
	ofstream output1;
	ofstream output2;
	Graph G;
	clock_t time;
	int step = 100;
	int size;
	int start = 0;
	int* dist1;
	int* dist2;

	output1.open("output1_l.txt");
	output2.open("output1_h.txt");
	cout << "[ Generating full graph ]" << endl;

	for (int i = 10; i < 10000; i = i + step)
	{
		size = 1000;
		Graph G1;
		G1.Generate(G1, size, pow(size, 2)/10, 10);
		time = clock();
		dist1 = DijkstraMark(G1, start);
		output1 << i << " " << float(clock() - time) / CLOCKS_PER_SEC * 1000 << endl;

		time = clock();
		dist2 = DijkstraHeap(G1, start, 9);
		output2 << i << " " << float(clock() - time) / CLOCKS_PER_SEC * 1000 << endl;
	}
	output1.close();
	output2.close();

	output1.open("output2_l.txt");
	output2.open("output2_h.txt");
	cout << "[ Generating linear graph ]" << endl;

	for (int i = 100; i < 5000; i = i+step)
	{
		size = i;
		Graph G2;
		G2.Generate(G2, size, size * 3, 10);
		time = clock();
		dist1 = DijkstraMark(G2, start);
		output1 << i << " " << float(clock() - time) / CLOCKS_PER_SEC * 1000 << endl;


		time = clock();
		dist2 = DijkstraHeap(G2, start, 9);
		output2 << i << " " << float(clock() - time) / CLOCKS_PER_SEC * 1000 << endl;
	}
	output1.close();
	output2.close();

	output1.open("output3_l.txt");
	output2.open("output3_h.txt");
	cout << "[ Generating log graph ]" << endl;
	for (int i = 100; i < 2500; i = i+ step)
	{
		size = i;
		Graph G3;
		time_t time_generate;
		time_generate = clock();
		G3.Generate(G3, size, pow(size, 2), 10);
		time = clock();
		dist1 = DijkstraMark(G3, start);
		output1 << i << " " << float(clock() - time) / CLOCKS_PER_SEC * 1000 << endl;
		time = clock();
		dist2 = DijkstraHeap(G3, start, 9);
		output2 << i << " " << float(clock() - time) / CLOCKS_PER_SEC * 1000 << endl;
	}
	output1.close();
	output2.close();


	//for (int i = 0; i < 4; i++)
	//	cout << dist2[i] << endl;

	/*bool Equal = true;
	for (int i = 0; i < size; i++)
	{
		if (dist1[i] != dist2[i])
			Equal == false;
	}
	if (Equal)
	{
		cout << "Output: labels == heap" << endl;
	}
	else
	{
		cout << "Output: labels != heap" << endl;
	}*/
		//cout << "Shortest from " << start << " to " << finish << " is " << DijkstraHeap(G, start, finish,9) << endl;
}