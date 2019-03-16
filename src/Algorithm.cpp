#include "Algorithm.hpp"


Algorithm::Algorithm(AdjacencyMatrix & matrix, double mutation_rate,
	 double crossover_rate, double time_diff, size_t population_size)
	:mutation_rate_{mutation_rate}, crossover_rate_{crossover_rate},
	 time_diff_{time_diff}, population_(population_size, matrix)
{
}

void Algorithm::run(std::function<void(Population&)> mutation, 
					std::function<void(Organism&, Organism&, Population &p)>crossover)
{
	auto start{ std::chrono::system_clock::now() };
	std::chrono::system_clock::time_point end{};

	while (std::chrono::duration<double>(end - start).count() < time_diff_)
	{
		for (size_t i{ 0 }; i < 5; ++i)
		{
			if (rand_probability() < mutation_rate_)
			{
				mutation(population_);
			}
			if (rand_probability() < crossover_rate_)
			{
				std::pair<Organism&, Organism&>to_cross = { roulette_wheel_selection() };
				crossover(to_cross.first, to_cross.second, population_);
			}
		}
		population_.set_initial_size();
		end = std::chrono::system_clock::now();
	}
	population_.get_organism(0).display_path();
}

std::pair<Organism&, Organism&> Algorithm::roulette_wheel_selection()
{
	std::pair<size_t, size_t> selected_organisms{ 0, 0 };
	std::vector<double>probability{ calc_probability() };
	while (selected_organisms.first == selected_organisms.second)
	{
		std::pair<double, double> random_pobability{ rand_probability(), rand_probability() };
		auto org_1 = std::upper_bound(probability.begin(), probability.end(), random_pobability.first);
		auto org_2 = std::upper_bound(probability.begin(), probability.end(), random_pobability.second);

		selected_organisms = { org_1 - probability.begin(), org_2 - probability.begin() };
	}
	return { population_.get_organism(selected_organisms.first), 
			population_.get_organism(selected_organisms.second) };
}

double Algorithm::fitness_complement()
{
	auto total{ 0.0 };
	for (const auto &it : population_.get_organisms())
		total += population_.get_population_cost() - it.get_path_cost();
		
	return total;
}

double Algorithm::rand_probability()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	return dis(gen);
}

std::vector<double> Algorithm::calc_probability()
{
	auto complement{ fitness_complement() };
	auto size{ population_.get_organisms().size() };
	auto chances{ std::vector<double>(size) };

	auto temp{ 0.0 };																
	for (size_t i{ 0 }; i < size; ++i)
	{
		chances[i] = ((population_.get_population_cost() 
						- population_.get_organism(i).get_path_cost()) / complement) + temp;
		temp = chances[i];
	}
	return chances;
}