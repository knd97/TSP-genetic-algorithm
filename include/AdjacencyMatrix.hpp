#ifndef AdjacencyMatrix_h_
#define AdjacencyMatrix_h_

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <limits>
#include <numeric>
#include "FileHandler.hpp"

class AdjacencyMatrix
{
private:
	std::vector<std::vector<double>>adjacencyMatrix_;
	size_t vertices_;

public:
	AdjacencyMatrix() = default;
	explicit AdjacencyMatrix(FileHandler& handler);

	bool isEdge(const size_t start, const size_t end) const;
	double getWeight(const size_t start, const size_t end) const;
	size_t size() const;

	~AdjacencyMatrix() = default;
};
#endif //AdjacencyMatrix_h_
