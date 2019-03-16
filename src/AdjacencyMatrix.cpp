#include "AdjacencyMatrix.hpp"

AdjacencyMatrix::AdjacencyMatrix(FileHandler& handler) : adjacencyMatrix_{}
{
	handler.readDataFromFile(adjacencyMatrix_);
	vertices_ = adjacencyMatrix_.size();
}

bool AdjacencyMatrix::isEdge(const size_t start, const size_t end) const
{
	return (adjacencyMatrix_.at(start).at(end) >= 0);
}

double AdjacencyMatrix::getWeight(const size_t start, const size_t end) const
{
	return (isEdge(start, end) ? adjacencyMatrix_[start][end] : -1);
}

size_t AdjacencyMatrix::size() const
{
	return vertices_;
}