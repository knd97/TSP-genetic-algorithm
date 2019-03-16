#include "Organism.hpp"


Organism::Organism(AdjacencyMatrix & matrix):
	length_{matrix.size() + 1}, path_(matrix.size() + 1)
{
	init_organism(matrix);
	randomize_organism();
	path_cost_ = calc_path_cost(matrix);
}

Organism::Organism(AdjacencyMatrix & matrix, std::vector<unsigned> path):
	length_{ path.size() }
{
	path_ = path;
	path_cost_ = calc_path_cost(matrix);
}

const size_t Organism::get_organism_length() const
{
	return length_;
}

inline void Organism::init_organism(AdjacencyMatrix &matrix)
{
	std::iota(path_.begin(), path_.end() - 1, 0);
	path_cost_ = calc_path_cost(matrix);
}

inline void Organism::randomize_organism()
{
	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(path_.begin() + 1, path_.end() - 1, generator);
}

std::vector<unsigned>& Organism::get_path()
{
	return path_;
}

void Organism::update_path(const double new_cost)
{
	path_cost_ = new_cost;
}

double Organism::calc_path_cost(AdjacencyMatrix &matrix) const
{
	double cost{ 0.0 };
	for (size_t i{ 0 }; i < get_path_length() - 1; ++i)
	{
		cost += matrix.getWeight(path_[i], path_[i + 1]);
	}
	return cost;
}

double Organism::get_path_cost() const
{
	return path_cost_;
}

const size_t Organism::get_path_length() const
{
	return length_;
}

void Organism::display_path() const
{
	std::cout << "Minimalny znaleziony koszt przejscia wynosi: " << path_cost_ << "\n";
	std::copy(path_.begin(), path_.end(), std::ostream_iterator<int>(std::cout, ";"));
	std::cout << "\n";
}
