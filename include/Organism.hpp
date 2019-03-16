#ifndef Organism_h_
#define Organism_h_

#include <iostream>
#include <vector>
#include <random>
#include "AdjacencyMatrix.hpp"

class Organism
{
private:
	std::vector<unsigned>path_;
	size_t length_;
	double path_cost_;

public:
	explicit Organism(AdjacencyMatrix &matrix);
	explicit Organism(AdjacencyMatrix &matrix, std::vector<unsigned>path);

	const size_t get_organism_length() const;
	double get_path_cost() const;
	const size_t get_path_length() const;

	std::vector<unsigned>& get_path();
	void update_path(const double new_cost);
	double calc_path_cost(AdjacencyMatrix &matrix) const;	
	void display_path() const;

	unsigned& operator[](const size_t index){ return path_[index];	}
	bool operator<(const Organism &org) const { return path_cost_ < org.path_cost_; }
	bool operator==(const Organism &org) const { return path_cost_ < org.path_cost_; }
	bool operator!=(const Organism &org) const { return path_cost_ < org.path_cost_; }

	~Organism() = default;

private:
	inline void init_organism(AdjacencyMatrix &matrix);
	inline void randomize_organism();
};
#endif // Organism_h_

