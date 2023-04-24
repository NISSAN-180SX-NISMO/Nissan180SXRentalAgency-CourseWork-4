#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>
#include "Data.h"
#include "Utility.h"
#define _s(a) std::to_string(a)

struct CreateRand {
	CreateRand();
	static std::vector<std::string> ManNames;
	static std::vector<std::string> ManSurnames;
	static std::vector<std::string> ManPatron;

	static std::vector<std::string> Colors;
	static std::vector<std::string> AVEKMNORSTUH;
	static std::vector<std::string> Brands;
	static std::vector<std::string> Street;
	static std::vector<std::string> City;
	static std::string DriversNumber();
	static std::string Name();
	static std::string PassportData();
	static std::string Address();
	static uint16_t Year(uint16_t down = 1950, uint16_t up = 2020);
	static std::string Brand();
	static std::string AutoNumber();
	static std::string Color();
	static std::string Date();
};

struct RandDataCreator {
	static Client* CreateDriver();
	static Auto* CreateCar();
	static Event* CreateTrade(std::string DriversNumber, std::string AutoNumber);
};
