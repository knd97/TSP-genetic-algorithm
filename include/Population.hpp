#define Population_h_
#define Population_h_

#include <iostream>
#include <memory>
#include <algorithm>
#include "Organism.hpp"

class Population
{
private:
	const size_t population_size_;
	std::vector<Organism>organisms_;
	AdjacencyMatrix matrix_;
	double population_cost_;

public:
	explicit Population(size_t population_size, AdjacencyMatrix &matrix);
	Organism& get_organism(const size_t index);
	const size_t get_population_size() const;

	static void swap_mutation(Population &p);
	static void insertion_mutation(Population &p);
	static void order1_crossover(Organism &org1, Organism & org2, Population &p);
	static void one_point_crossover(Organism &org1, Organism &org2, Population &p);

	double sum_population_cost();
	double get_population_cost() const;
	std::vector<Organism>& get_organisms();
	void set_initial_size();
	Organism& random_organism();

	~Population() = default;

private:
	void sort_organisms();
	const size_t random_chromosome();
	void insert_sorted(Organism org);	
	void fill_with_missing_chromosomes(Organism &org2, std::vector<unsigned>&new_path, size_t index_start, size_t index_end);
	
};
#endif // Population_h_