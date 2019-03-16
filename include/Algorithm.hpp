#pragma once
#include <chrono>
#include <functional>
#include "Population.h"

class Algorithm
{
private:
	const double mutation_rate_;
	const double crossover_rate_;
	const double time_diff_;
	Population population_;
	
public:

	Algorithm(AdjacencyMatrix &matrix, double mutation_rate, double crossover_rate, double time_diff, size_t population_size);
	void run(std::function<void(Population&)> mutation, std::function<void(Organism&, Organism&, Population &p)>crossover);

	~Algorithm() = default;
private:
	std::pair<Organism &, Organism &>roulette_wheel_selection();
	double fitness_complement();
	double rand_probability();
	std::vector<double>calc_probability();
};
