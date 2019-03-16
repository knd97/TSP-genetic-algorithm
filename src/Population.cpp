#include "Population.hpp"

Population::Population(size_t population_size, AdjacencyMatrix & matrix)
	:population_size_{population_size}, matrix_{matrix}
{
	for (size_t i{ 0 }; i < population_size; ++i)
	{
		organisms_.push_back(Organism(matrix));
	}
	sort_organisms();
	population_cost_ = sum_population_cost();
}

Organism& Population::get_organism(const size_t index)
{
	return organisms_[index];
}

const size_t Population::get_population_size() const
{
	return population_size_;
}

void Population::swap_mutation(Population &p)
{
	auto &org = p.random_organism();
	std::swap(org[p.random_chromosome()], org[p.random_chromosome()]);
	org.update_path(org.calc_path_cost(p.matrix_));
	p.sort_organisms();
}

void Population::insertion_mutation(Population &p)
{
	auto &org = p.random_organism();
	std::pair<size_t, size_t>position{ p.random_chromosome() , p.random_chromosome() };
	auto value_at{ org[position.first] };
	
	org.get_path().erase(org.get_path().begin() + position.first);
	org.get_path().insert(org.get_path().begin() + position.second, value_at);

	org.update_path(org.calc_path_cost(p.matrix_));
	p.sort_organisms();
}

void Population::order1_crossover(Organism & org1, Organism & org2, Population &p)
{
	std::pair<size_t, size_t>indexes = std::minmax(p.random_chromosome(), p.random_chromosome());
	auto new_organism_path{ std::vector<unsigned>(org1.get_path_length()) };

	std::copy(org1.get_path().begin() + indexes.first, org1.get_path().begin() + indexes.second,
		new_organism_path.begin() + indexes.first);
	p.fill_with_missing_chromosomes(org2, new_organism_path, indexes.first, indexes.second);
}

void Population::one_point_crossover(Organism & org1, Organism & org2, Population &p)
{
	auto index = p.random_chromosome();
	auto new_organism_path{ std::vector<unsigned>(org1.get_path_length()) };

	std::copy(org1.get_path().begin() + index, org1.get_path().end(),
		new_organism_path.begin() + index);
	p.fill_with_missing_chromosomes(org2, new_organism_path, index, 0);
} 

void Population::fill_with_missing_chromosomes(Organism & org2, std::vector<unsigned> &new_path, 
												size_t index_start, size_t index_end)
{
	auto position{ 1 };
	for (const auto &it : org2.get_path())
	{
		if (auto is_missing = std::find(new_path.begin(), new_path.end(), it); is_missing == new_path.end())
		{
			while (new_path[position] != 0)
			{
				++position;
			}
			new_path[position] = it;
			if (position == index_start - 1 && index_end != 0)
			{
				position = index_end - 1;
			}
			++position;
		}		
	}
	insert_sorted(Organism(matrix_, new_path));						//dodanie nowego osobnika do populacji - nie zakłóca posortowanej populacji
}

double Population::sum_population_cost()
{
	auto sum{ 0.0 };
	for (const auto &it : organisms_)
		sum += it.get_path_cost();

	return sum;
}

double Population::get_population_cost() const
{
	return population_cost_;
}

std::vector<Organism>& Population::get_organisms()
{
	return organisms_;
}

void Population::sort_organisms()
{
	std::sort(organisms_.begin(), organisms_.end(), 
		[&](auto org1, auto org2) {return org1.get_path_cost() < org2.get_path_cost(); });
}

Organism& Population::random_organism()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, organisms_.size() - 1);

	return get_organism(dis(gen));
}

const size_t Population::random_chromosome()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, organisms_[0].get_organism_length() - 2);

	return static_cast<size_t>(dis(gen));
}

void Population::insert_sorted(Organism org)
{
	const auto insert_pos(std::lower_bound(organisms_.begin(), organisms_.end(), org));
	organisms_.insert(insert_pos, org);
	population_cost_ = sum_population_cost();
}

void Population::set_initial_size()
{
	sort_organisms();
	organisms_.erase(organisms_.begin() + population_size_, organisms_.end());
	population_cost_ = sum_population_cost();
}