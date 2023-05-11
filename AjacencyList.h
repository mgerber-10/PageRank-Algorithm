#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class AdjacencyList 
{
 private:
    map<string, vector<string>> webGraph;

 public:

    // Adds directed link from webpage 'from' to another webpage 'to' in webGraph 
    void addLink(const string &from, const string &to)
    {
        webGraph[from].push_back(to);
        if (webGraph.find(to) == webGraph.end()) 
        {
            // Add an empty node for 'to' if it doesn't exist in the graph
            webGraph[to] = {};
        }
    }


    // Returns a vector of strings containing all the nodes (webpages) in webGraph
    vector<string> getNodes()
    {
        vector<string> nodes;
        for (auto &&webpage : webGraph) 
        {
            nodes.push_back(webpage.first);
        }
        return nodes;
    }


    // Returns a vector of strings containing names of all webpages in webGraph w/ links pointing to specified web page 'to'
    vector<string> getLinkTo(const string &to)
    {
        vector<string> linkTo;
        for (auto it = webGraph.begin(); it != webGraph.end(); ++it) 
        {
            const auto &links = it->second;
            if (find(links.begin(), links.end(), to) != links.end()) 
            {
                linkTo.push_back(it->first);
            }
        }
        return linkTo;
    }


    // Returns the index of first occurrence of pagename in the graph
    int getIndex(const string &strin, vector<string> &vec)
    {
        return find(vec.begin(), vec.end(), strin) - vec.begin();
    }


    // Computes the PageRank for each node in a web graph
    void PageRank(int n)
    {
        // Get the names of all nodes in the web graph
        vector<string> names = getNodes();

        // Initialize PageRank scores for all nodes to be EQUAL & store in vector 'rank'
        vector<double> rank(webGraph.size(), 1.0/webGraph.size());

        // Repeat the PageRank computation `n` times
        while (n > 1) 
        {
            auto tempVec = rank;                    // temporary copy of the `rank` vector
            fill(rank.begin(), rank.end(), 0.0);    // Reset the `rank` vector to all zeros for the current iteration

            // Compute the new PageRank scores for all nodes
            for (int i = 0; i < webGraph.size(); ++i) 
            {
                vector<string> linkTo = getLinkTo(names[i]); // Get names of all nodes that link to current node

                // Compute the contribution of each linking node to the PageRank of the current node
                for (auto &&j : linkTo) 
                {
                    int linkIndex = getIndex(j, names);                                       // Get index  of the linking node in the `names` vector
                    double linkContribution = tempVec[linkIndex] * 1.0 / webGraph[j].size();  // Calculate contribution of linking node to the current node's PageRank
                    rank[i] += linkContribution;                                              // Add contribution of linking node to current node's PageRank
                }
            }
            --n;
        }
        // Print the final PageRank scores for all nodes
        int index = 0;
        for (auto &&member : webGraph) 
        {
            cout << member.first << " " << fixed << setprecision(2) << rank[index++] << endl;
        }
    }
};