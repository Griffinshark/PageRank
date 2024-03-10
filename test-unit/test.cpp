#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include "AdjacencyList.h"

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

TEST_CASE("Different Capitalization and Zero Connect", "[General]")
{
    std::vector<std::pair<std::string, std::string>> inputHolder =
            {
                {"facebook.com", "apple.com"},
                {"facebook.com", "gmail.com"},
                {"youtube.com", "facebook.com"},
                {"google.com", "facebook.com"},
                {"google.com", "youtube.com"},
                {"apple.com", "youtube.com"},
                {"gmail.com", "youtube.com"},
                {"aPPle.com", "youtube.com"},
                {"aPPle.com", "facebook.com"},
                {"facebook.com", "aPPle.com"}
            };

    std::map<std::string, double> expectedOutput =
                {
                        {"aPPle.com", 1.0/9.0},
                        {"apple.com", 1.0/9.0},
                        {"facebook.com", 19.0/36.0},
                        {"gmail.com", 1.0/9.0},
                        {"google.com", 0.0},
                        {"youtube.com", 5.0/36.0}
                };

    //Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};
    std::string fromPage;
    std::string toPage;

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
    std::map<std::string, double> ranks = generatedList.PageRank(3);

    auto testsIter = expectedOutput.begin();
    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        REQUIRE(testsIter->first == ranksIter->first);
        REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.000000002));

        testsIter++;
    }
}

TEST_CASE("One Connection", "[General]")
{
    std::vector<std::pair<std::string, std::string>> inputHolder =
            {
                    {"facebook.com", "apple.com"}
            };

    std::map<std::string, double> expectedOutput =
            {
                    {"apple.com", 0},
                    {"facebook.com", 0}
            };

    //Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};
    std::string fromPage;
    std::string toPage;

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
    std::map<std::string, double> ranks = generatedList.PageRank(3);

    auto testsIter = expectedOutput.begin();
    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        REQUIRE(testsIter->first == ranksIter->first);
        REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.000000002));

        testsIter++;
    }
}

TEST_CASE("Lots of Power Iterations (p = 20)", "[General]")
{
    std::vector<std::pair<std::string, std::string>> inputHolder =
            {
                    {"facebook.com", "apple.com"},
                    {"facebook.com", "gmail.com"},
                    {"youtube.com", "facebook.com"},
                    {"google.com", "facebook.com"},
                    {"google.com", "youtube.com"},
                    {"apple.com", "youtube.com"},
                    {"gmail.com", "youtube.com"},
                    {"aPPle.com", "youtube.com"},
                    {"aPPle.com", "facebook.com"},
                    {"facebook.com", "aPPle.com"}
            };

    std::map<std::string, double> expectedOutput =
            {
                    {"aPPle.com", 18713899.0/181398528},
                    {"apple.com", 18713899.0/181398528},
                    {"facebook.com", 23361167.0/60466176},
                    {"gmail.com", 18713899.0/181398528},
                    {"google.com", 0.0},
                    {"youtube.com", 3065185.0/10077696}
            };

    //Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};
    std::string fromPage;
    std::string toPage;

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
    std::map<std::string, double> ranks = generatedList.PageRank(20);

    auto testsIter = expectedOutput.begin();
    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        REQUIRE(testsIter->first == ranksIter->first);
        REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.000000002));

        testsIter++;
    }
}

TEST_CASE("p = 1", "[General]")
{
    std::vector<std::pair<std::string, std::string>> inputHolder =
            {
                    {"facebook.com", "apple.com"},
                    {"facebook.com", "gmail.com"},
                    {"youtube.com", "facebook.com"},
                    {"google.com", "facebook.com"},
                    {"google.com", "youtube.com"},
                    {"apple.com", "youtube.com"},
                    {"gmail.com", "youtube.com"},
                    {"aPPle.com", "youtube.com"},
                    {"aPPle.com", "facebook.com"},
                    {"facebook.com", "aPPle.com"}
            };

    std::map<std::string, double> expectedOutput =
            {
                    {"aPPle.com", 1.0/6},
                    {"apple.com", 1.0/6},
                    {"facebook.com", 1.0/6},
                    {"gmail.com", 1.0/6},
                    {"google.com", 1.0/6},
                    {"youtube.com", 1.0/6}
            };

    //Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};
    std::string fromPage;
    std::string toPage;

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
    std::map<std::string, double> ranks = generatedList.PageRank(1);

    auto testsIter = expectedOutput.begin();
    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        REQUIRE(testsIter->first == ranksIter->first);
        REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.000000002));

        testsIter++;
    }
}

TEST_CASE("Numbered and Symbolic Sites", "[General]")
{
std::vector<std::pair<std::string, std::string>> inputHolder =
        {
                {"facebook.com", "apple.com"},
                {"facebook.com", "123Kewl.com"},
                {"123Kewl.com", "twitter.com"},
                {"123Kewl.com", "8814StarTrek.org"},
                {"twitter.com", "8814StarTrek.org"},
                {"twitter.com", "$$$GetRich.net"},
                {"$$$GetRich.net", "facebook.com"},
                {"$$$GetRich.net", "#34Football.com"}
        };

std::map<std::string, double> expectedOutput =
        {
                {"#34Football.com", 1.0/224},
                {"$$$GetRich.net", 1.0/224},
                {"123Kewl.com", 1.0/224},
                {"8814StarTrek.org", 1.0/112},
                {"apple.com", 1.0/224},
                {"facebook.com", 1.0/224},
                {"twitter.com", 1.0/224},
        };

//Create a graph object
AdjacencyList generatedList;

int outDegree{0};
std::string fromPage;
std::string toPage;

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
std::map<std::string, double> ranks = generatedList.PageRank(6);

auto testsIter = expectedOutput.begin();
for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
{
    REQUIRE(testsIter->first == ranksIter->first);
    REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.000000002));

    testsIter++;
}
}

TEST_CASE("Lots of Connects", "[General]")
{
    std::vector<std::pair<std::string, std::string>> inputHolder =
            {
                    {"facebook.com", "myspace.com"},
                    {"facebook.com", "google.com"},
                    {"facebook.com", "twitter.com"},
                    {"facebook.com", "youtube.com"},
                    {"facebook.com", "stocks.com"},
                    {"facebook.com", "IBM.com"},
                    {"youtube.com", "twitter.com"},
                    {"youtube.com", "facebook.com"},
                    {"youtube.com", "myspace.com"},
                    {"youtube.com", "stocks.com"},
                    {"twitter.com", "myspace.com"}
            };

    std::map<std::string, double> expectedOutput =
            {
                    {"facebook.com", 1.0/28},
                    {"google.com", 1.0/42},
                    {"IBM.com", 1.0/42},
                    {"myspace.com", 17.0/84},
                    {"stocks.com", 5.0/84},
                    {"twitter.com", 5.0/84},
                    {"youtube.com", 1.0/42}
            };

//Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};
    std::string fromPage;
    std::string toPage;

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
    std::map<std::string, double> ranks = generatedList.PageRank(2);

    auto testsIter = expectedOutput.begin();
    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        REQUIRE(testsIter->first == ranksIter->first);
        REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.000000002));

        testsIter++;
    }
}

TEST_CASE("Very Large Random", "[General]")
{
    std::vector<std::pair<std::string, std::string>> inputHolder =
            {
                    {"samsung.com", "chase.com"},
                    {"chase.com", "pcbuildinguf.com"},
                    {"samsung.com", "pcbuildinguf.com"},
                    {"python.org", "ufl.edu"},
                    {"reactjs.org", "python.org"},
                    {"getbootstrap.com", "google.com"},
                    {"instagram.com", "python.org"},
                    {"disney.com", "chase.com"},
                    {"github.com", "chase.com"},
                    {"chase.com", "getbootstrap.com"},
                    {"disney.com", "getbootstrap.com"},
                    {"python.org", "google.com"},
                    {"pcbuildinguf.com", "reactjs.org"},
                    {"google.com", "reactjs.org"},
                    {"google.com", "samsung.com"},
                    {"github.com", "ufl.edu"},
                    {"getbootstrap.com", "ufl.edu"},
                    {"getbootstrap.com", "pcbuildinguf.com"},
                    {"samsung.com", "reactjs.org"},
                    {"ufl.edu", "getbootstrap.com"},
                    {"disney.com", "google.com"},
                    {"disney.com", "pcbuildinguf.com"},
                    {"reactjs.org", "disney.com"},
                    {"reactjs.org", "instagram.com"},
                    {"instagram.com", "disney.com"},
                    {"instagram.com", "chase.com"},
                    {"ufl.edu", "python.org"},
                    {"instagram.com", "ufl.edu"},
                    {"google.com", "github.com"},
                    {"chase.com", "samsung.com"},
                    {"disney.com", "samsung.com"}
            };

    std::map<std::string, double> expectedOutput =
            {
                    {"chase.com", 0.07},
                    {"disney.com", 0.06},
                    {"getbootstrap.com", 0.10},
                    {"github.com", 0.04},
                    {"google.com", 0.11},
                    {"instagram.com", 0.05},
                    {"pcbuildinguf.com", 0.09},
                    {"python.org", 0.13},
                    {"reactjs.org", 0.15},
                    {"samsung.com", 0.07},
                    {"ufl.edu", 0.13}
            };

//Create a graph object
    AdjacencyList generatedList;

    int outDegree{0};
    std::string fromPage;
    std::string toPage;

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
    std::map<std::string, double> ranks = generatedList.PageRank(17);

    auto testsIter = expectedOutput.begin();
    for (auto ranksIter = ranks.begin(); ranksIter != ranks.end(); ++ranksIter)
    {
        REQUIRE(testsIter->first == ranksIter->first);
        REQUIRE_THAT(ranksIter->second, Catch::Matchers::WithinAbs(testsIter->second, 0.01));

        testsIter++;
    }
}