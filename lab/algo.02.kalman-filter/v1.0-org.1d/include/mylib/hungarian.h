#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class HungarianAlgorithm {
public:
    HungarianAlgorithm(const std::vector<std::vector<int>>& costMatrix)
        : costMatrix(costMatrix), n(costMatrix.size()), m(costMatrix[0].size()),
          u(n + 1), v(m + 1), p(m + 1), way(m + 1) {}

    int solve(std::vector<int>& assignment);

private:
    const std::vector<std::vector<int>>& costMatrix;
    int n, m;
    std::vector<int> u, v, p, way;
};