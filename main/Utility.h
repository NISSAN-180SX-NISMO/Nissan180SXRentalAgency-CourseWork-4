#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include "CFL.h"

#define _Util Utility::UsfulFunctions
#define _Tool Utility::Algorithms
#define _Check Utility::Checking
#define _Print Utility::Printer

struct Utility {
	struct UsfulFunctions {
		static const void pause(const std::string& PreTitle = "");
		static const void ToUpperString(std::string& source);
		static const void ShowConsoleCursor(bool showFlag);
		static const uint32_t getKey(const std::string& value);
	};
	struct Algorithms {
		static Event* findMin(DataBase<Event>* source);
		static Event* findMax(DataBase<Event>* source);
		static const bool SubStringSearch(const std::string& source, const std::string& chunk);
		static DataBase<Event>* DistributionSort(DataBase<Event>* source); 
	};
	struct Checking {
		static std::vector<uint16_t> DateToVector(const std::string& date);
		static bool LeftDateIsBigger(const std::string& LeftDate, const std::string& RightDate);
		static bool DateIsReal(const std::string& date);
	};
	struct Printer {
	private:
		static std::string line(uint16_t size, const char* what);
		static const void showDriversHeader(std::ostream& out);
		static const void showAutosHeader(std::ostream& out);
		static const void showEventsHeader(std::ostream& out);
		static const void showDriver(std::ostream& out, Client* data);
		static const void showAuto(std::ostream& out, Auto* data);
		static const void showEvent(std::ostream& out, Event* data);
	public:
		static const void print(std::ostream& out, std::vector<Client*> elements);
		static const void print(std::ostream& out, std::vector<Auto*> elements);
		static const void print(std::ostream& out, std::vector<Event*> elements);
	};
};