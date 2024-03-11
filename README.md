# Introduction
This project is a simplified version of Google's original PageRanking algorithm using an adjacency list. In basic terms, the algorithm gives a ranking to each site. 
This ranking is based on a number of factors. More incoming connections from other sites can raise the ranking. However, not all the incoming connections are the
same strength. Incoming connection strength is based upon the incoming site's ranking and how many sites this website sends/connects to. A site with a high rank
and only sending to one site will increase that site's ranking a lot, for example. 

Furthermore, Google's original PageRanking algorithm uses something called "power iterations" to calculate ranking at the time of t+1, which is equal to t * matrix.
There is a bit more setup here, but essentially the matrix "r" converges r(t+1)= r(t) based upon a determined power iteration count. This causes the algorithm to
stop. In the case of this project we are simply applying a given and fixed power iteration count.

# Installation
Clone the repo and run from main.

# Runtime Guide
1. The first command will be the "number of command lines to follow" SPACE "number of power iterations".
2. Enter each site to site connection in the format: "outboundSite.com" SPACE "inboundSite.com".
3. The program will then output each site's ranking.

# Constraints
- 1 <= p <= 10,000
- 1 <= n <= 10,000
- 1 <= Unique webpages or |V| <= 10000
