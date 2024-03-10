#ifndef PAGERANK_ADJACENCYLIST_H
#define PAGERANK_ADJACENCYLIST_H
#include <map>
#include <string>
#include <vector>

class AdjacencyList{
private:
    // Stores the map of pages
    std::map<std::string, std::vector<std::pair<std::string, double>>> pageMap;
public:
    // Performs computations on the 'pageMap' based on the given power iterations
    // and returns a map of matching websites to their ranks
    std::map<std::string, double> PageRank(int powerIterations);

    // Map getter
    std::map<std::string, std::vector<std::pair<std::string, double>>>& MapGetter();
};

#endif // PAGERANK_ADJACENCYLIST_H
