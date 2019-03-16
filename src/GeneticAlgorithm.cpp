#include <iostream>
#include "Algorithm.hpp"
#include "MenuHandler.hpp"


int main(int argc, char *argv[])
{
	std::string path = (std::string) argv[1];

	FileHandler file(path);
	MenuHandler handler(file);
	handler.run_menu();


	system("pause");
}
