#include "AdjacencyList.h"

std::map<std::string, double> AdjacencyList::PageRank(int powerIterations)
{
    // Initialize strings to ranks of (1/V)
    std::map<std::string, double> ranks;
    for (auto mapIter = pageMap.begin(); mapIter != pageMap.end(); ++mapIter)
    {
        ranks[mapIter->first] = 1.0 / pageMap.size();
    }

    // Base case
    if (powerIterations == 1)
    {
        return ranks;
    }

    // Stores the parents and their degrees for the current page
    std::vector<std::pair<std::string, double>> currentPageParents;
    // Iterates through the 'pageMap'
    auto mapIter = pageMap.begin();
    // Used to tally up ranking for the current page
    double intermediateRanking{0};
    // Used to either store the final map of ranks or act as an intermediate map for computation
    std::map<std::string, double> finalRanks;

    for (int i = 1; i < powerIterations; ++i)
    {
        // One power iteration
        // Go through each rank
        for (auto rankIter = ranks.begin(); rankIter != ranks.end(); ++rankIter)
        {

            currentPageParents = mapIter->second;

            // Go through each parent of the current page and use their degrees * ranks['their name']
            for (auto parentIter = currentPageParents.begin(); parentIter
                                                               != currentPageParents.end(); ++parentIter)
            {
                // Calculate and add to ranking
                intermediateRanking += parentIter->second * ranks[parentIter->first];
            }

            // Set new ranking
            finalRanks[mapIter->first] = intermediateRanking;

            // Reset
            intermediateRanking = 0;

            // Increment 'mapIter' to grab next page
            ++mapIter;
        }

        // Not on the last power iteration
        if (i != powerIterations - 1)
        {
            // Clear 'ranks'
            ranks.clear();

            // Set 'ranks' to 'finalRanks' for another iteration
            for (auto transferIter = finalRanks.begin(); transferIter != finalRanks.end(); ++transferIter)
            {
                ranks[transferIter->first] = transferIter->second;
            }

            // Clear 'finalRanks'
            finalRanks.clear();
        }

        // Reset
        mapIter = pageMap.begin();
    }

    return finalRanks;
}

std::map<std::string, std::vector<std::pair<std::string, double>>>& AdjacencyList::MapGetter() { return this->pageMap; }

