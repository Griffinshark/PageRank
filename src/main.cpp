#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iomanip>
#include "AdjacencyList.h"

// References:
// https://github.com/catchorg/Catch2/blob/devel/docs/comparing-floating-point-numbers.md
// https://en.cppreference.com/w/cpp/container/map

// Takes a map and checks it for the given element
bool IsPageMapped(std::string element, std::map<std::string, std::vector<std::pair<std::string, double>>>& pageMap);

// Takes in the input and desired page to check to find the page's out degree
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
    for (int i = 0; i < no_of_lines; i++)
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

        // Ensure from page is mapped
        if (!IsPageMapped(fromPage, generatedList.MapGetter()))
        {
            generatedList.MapGetter()[fromPage];
        }
    }

    //Created_Graph.PageRank(power_iterations);
    std::map<std::string, double> ranks = generatedList.PageRank(power_iterations);

    // Print the ranks
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

    // Go through all the input and see how many times page is the first keyword, indicating its out degree
    for (size_t i = 0; i < inputHolder.size(); ++i)
    {
        if (inputHolder[i].first == page)
        {
            ++count;
        }
    }

    return count;
}

