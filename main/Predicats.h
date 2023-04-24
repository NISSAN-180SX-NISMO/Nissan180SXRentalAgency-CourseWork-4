#pragma once
#include <string>
#include <vector>
#include <regex>

#define _Pred Predicats

struct Predicats {
	static bool forDriversNumber(const std::string& value);
	static bool forPassportData(const std::string& value);
	static bool forName(const std::string& value);
	static bool forAutosNumber(const std::string& value);
	static bool forYear(const std::string& value);
	static bool forDate(const std::string& value);
	static bool forNumber(const std::string& value);
};