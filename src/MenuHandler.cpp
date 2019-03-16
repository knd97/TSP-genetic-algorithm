#include "MenuHandler.hpp"

MenuHandler::MenuHandler(FileHandler & file)
	:time_{ 0.0 }, cross_rate_{ 0.0 }, mutation_rate_{ 0.0 }, handler_{ file }, population_size_{ 0 }
{
}

void MenuHandler::run_menu()
{
	auto choice{ 0 };

	while (choice != 8)
	{
		std::cout << "\n";
		for (const auto &it : main_menu_options_)
			std::cout << it << "\n";
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				system("cls");
				handler_.checkPath();
				std::string fileName;
				std::cout << "Prosze podac nazwe wybranego pliku testowego: " << std::endl;
				std::cin >> fileName;

				FileHandler file{ fileName };
				AdjacencyMatrix matrix{ file };
				set_matrix(matrix);
				break;
			}
			case 2:
			{
				auto mut_rate{ 0.0 };
				system("cls");
				std::cout << "Prosze podac wspolczynnik mutacji: " << std::endl;
				std::cin >> mut_rate;
				set_mutation_rate(mut_rate);
				break;
			}
			case 3:
			{
				auto cross_rate{ 0.0 };
				system("cls");
				std::cout << "Prosze podac wspolczynnik krzyzowania: " << std::endl;
				std::cin >> cross_rate;
				set_cross_rate(cross_rate);
				break;
			}
			case 4:
			{
				auto time{ 0.0 };
				system("cls");
				std::cout << "Czas trwania: " << std::endl;
				std::cin >> time;
				set_time(time);
				break;
			}
			case 5:
			{
				auto size{ 0 };
				system("cls");
				std::cout << "Rozmiar populacji: " << std::endl;
				std::cin >> size;
				set_population_size(size);
				break;
			}
			case 6:
			{
				system("cls");
				auto choice{ 0 };
				for (const auto &it : algorithm_menu)
					std::cout << it << std::endl;
				std::cin >> choice;
				Algorithm alg(matrix_, mutation_rate_, cross_rate_, time_, population_size_);
				switch (choice)
				{
					case 1:
					{
						//swap order1
						alg.run(std::bind(&Population::swap_mutation, std::placeholders::_1),
								std::bind(&Population::order1_crossover, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					case 2:
					{
						//Insert Order1
						alg.run(std::bind(&Population::insertion_mutation, std::placeholders::_1),
								std::bind(&Population::order1_crossover, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					case 3:
					{
						//swap One Point
						alg.run(std::bind(&Population::swap_mutation, std::placeholders::_1), 
								std::bind(&Population::one_point_crossover, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					case 4:
					{
						//insert One Point
						alg.run(std::bind(&Population::insertion_mutation, std::placeholders::_1), 
								std::bind(&Population::one_point_crossover, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					default:
					{
						break;
					}
				}
				break;
			}
			case 7:
			{
				exit(0);
			}
			default:
			{
				exit(0);
			}
		}
	}
}

void MenuHandler::set_time(double time)
{
	time_ = time;
}

void MenuHandler::set_cross_rate(double cross_rate)
{
	cross_rate_ = cross_rate;
}

void MenuHandler::set_mutation_rate(double mutation_rate)
{
	mutation_rate_ = mutation_rate;
}

void MenuHandler::set_matrix(AdjacencyMatrix & matrix)
{
	matrix_ = matrix;
}

void MenuHandler::set_population_size(int size)
{
	population_size_ = size;
}

void MenuHandler::clear_screen()
{
	#ifdef __linux__
    	system("clear");
	#elif _WIN32
    	system("CLS");
	#endif
}
