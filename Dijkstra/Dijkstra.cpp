#include "Graph.h"


void main()
{
	Graph G;
	for (int i = 0; i < 5; i++)
	{
		G.Add(i);
	}
	vector<Pair> tmp = { {1,1},{2,3},{3,1} };
	G.Link(0, tmp);
	tmp = { { 2,2 },{ 3,1 },{ 4,1 } };
	G.Link(1, tmp);
	G.Print();
}