#ifndef PAGERANK_ADJACENCYLIST_H
#define PAGERANK_ADJACENCYLIST_H

#include <map>
#include <string>
#include <vector>


class AdjacencyList{
private:
    std::map<std::string, std::vector<std::pair<std::string, double>>> pageMap;
public:
    void ageRank(int n);
    std::map<std::string, std::vector<std::pair<std::string, double>>>& MapGetter();
    std::map<std::string, double> PageRank(int powerIterations);
};



#endif //PAGERANK_ADJACENCYLIST_H
