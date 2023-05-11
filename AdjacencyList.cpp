#include "AdjacencyList.h"

void AdjacencyList::addLink(const string &from, const string &to)
{
    webGraph[from].push_back(to);
    if (webGraph.find(to) == webGraph.end()) 
    {
        webGraph[to] = {};
    }
}

    vector<string> getNodes()
    {
        vector<string> nodes;
        for (auto &&webpage : webGraph) 
        {
            nodes.push_back(webpage.first);
        }
        return nodes;
    }

    vector<string> getLinkTo(const string &to)
    {
        vector<string> linkTo;
        for (auto &&webpage : webGraph) 
        {
            if (find(webpage.second.begin(), webpage.second.end(), to) != webpage.second.end()) 
            {
                linkTo.push_back(webpage.first);
            }
        }
        return linkTo;
    }

    int getIndex(const string &strin, vector<string> &vec)
    {
        return find(vec.begin(), vec.end(), strin) - vec.begin();
    }

    void PageRank(int n)
    {
        vector<string> names = getNodes();
        vector<double> rank(webGraph.size(), 1.0/webGraph.size());

        for (; n > 1; --n) 
        {
            auto tempVec = rank;
            fill(rank.begin(), rank.end(), 0.0);
            for (int i = 0; i < webGraph.size(); ++i) 
            {
                for (auto &&j : getLinkTo(names[i])) 
                {
                    rank[i] += tempVec[getIndex(j, names)] * 1.0/webGraph[j].size();
                }
            }
        }

        int index = {};

        // print name and corresponding rank
        for (auto &&member : webGraph) 
        {
            cout << member.first << " " << fixed << setprecision(2) << rank[index++] << endl;
        }
    }
};