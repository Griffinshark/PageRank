#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iomanip>
#include "AdjacencyList.h"

bool IsPageMapped(std::string element, std::map<std::string, std::vector<std::pair<std::string, double>>>& pageMap);

int DegreeCounter(std::vector<std::pair<std::string, std::string>>& inputHolder, std::string page);

int main()
{
    int no_of_lines, power_iterations;
    std::string fromPage;
    std::string toPage;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;
    std::vector<std::pair<std::string, std::string>> inputHolder;


    // Parse and Store Input
    for (size_t i = 0; i < no_of_lines; i++)
    {
        std::cin >> fromPage;
        std::cin >> toPage;

        inputHolder.emplace_back(fromPage, toPage);
    }

    //Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};

    // Go through input and generate map / adjacency list
    for (size_t i = 0; i < inputHolder.size(); ++i)
    {
        fromPage = inputHolder[i].first;
        toPage = inputHolder[i].second;

        // Grab 'out degree' of 'fromPage'
        outDegree = DegreeCounter(inputHolder, fromPage);

        // Add to map with 'toPage' key the 'fromPage' and it's 'd'
        generatedList.MapGetter()[toPage].emplace_back(fromPage, 1.0/outDegree);
    }

    //Created_Graph.PageRank(power_iterations);
    std::map<std::string, double> ranks = generatedList.PageRank(power_iterations);

    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << ranksIter->first << " " << ranksIter->second << '\n';
    }
}

bool IsPageMapped(std::string element, std::map<std::string, std::vector<std::pair<std::string, double>>>& pageMap)
{
    if (pageMap.find(element) == pageMap.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

int DegreeCounter(std::vector<std::pair<std::string, std::string>>& inputHolder, std::string page)
{
    int count{0};

    for (size_t i = 0; i < inputHolder.size(); ++i)
    {
        if (inputHolder[i].first == page)
        {
            ++count;
        }
    }

    return count;
}

