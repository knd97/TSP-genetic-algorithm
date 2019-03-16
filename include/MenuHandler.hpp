#ifndef MenuHandler_h_
#define MenuHandler_h_

#include "Algorithm.hpp"
#include <string>
#include <array>

class MenuHandler
{
private:
	double time_;
	double cross_rate_;
	double mutation_rate_;
	int population_size_;
	AdjacencyMatrix matrix_;
	FileHandler handler_;

	const std::array<std::string, 7>main_menu_options_
		{"1 - Wybor pliku", "2 - Wspolczynnik mutacji", "3 - Wspolczynnik krzyzowania", "4 - Czas trwania", "5 - Liczebnosc populacji", "6 - Algorytm genetyczny", "7 - Wyjscie"};
	const std::array < std::string, 4>algorithm_menu{"1 - Swap Order1", "2 - Insert Order1", "3 - Swap One Point", "4 - Insert One Point"};

public:
	MenuHandler(FileHandler &file);
	void run_menu();
	~MenuHandler() = default;
private:
	void set_time(double time);
	void set_cross_rate(double cross_rate);
	void set_mutation_rate(double mutation_rate);
	void set_matrix(AdjacencyMatrix &matrix);
	void set_population_size(int size);
	void clear_screen();
};
#endif // MenuHandler_h_

