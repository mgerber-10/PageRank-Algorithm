#include "AjacencyList.h"

using namespace std;

int main()
{
    AdjacencyList adjList;
    int numLines;
    int powerIterations;
    string from;
    string to;

    cin >> numLines;
    cin >> powerIterations;

    for (int i = 0; i < numLines; ++i) 
    {
        cin >> from;
        cin >> to;

        // insert into graph
        adjList.addLink(from, to);
    }

    // create graph object
    adjList.PageRank(powerIterations);
}