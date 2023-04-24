#pragma once
#include "Predicats.h"

bool Predicats::forDriversNumber(const std::string& value)
{
	if (value.size() != 12) return false;
	if (regex_match(value.c_str(), std::regex("[0-9]{2} [ÀÂÅÊÌÍÎĞÑÒÓÕ]{2} [0-9]{6}"))) return true;
	else return false;
}

bool Predicats::forPassportData(const std::string& value)
{
	if (value.size() != 11) return false;
	if (regex_match(value.c_str(), std::regex("[0-9]{4}-[0-9]{6}"))) return true;
	else return false;
}

bool Predicats::forName(const std::string& value)
{
	if (regex_match(value.c_str(), std::regex("^[à-ÿÀ-ß¸¨a-zA-Z]{1,}'?-?[à-ÿÀ-ß¸¨a-zA-Z]{2,} ?[à-ÿÀ-ß¸¨a-zA-Z]{2,} ?([à-ÿÀ-ß¸¨a-zA-Z]{1,})?"))) return true;
	else return false;
}

bool Predicats::forAutosNumber(const std::string& value)
{
	if (value.size() != 9) return false;
	if (regex_match(value.c_str(), std::regex("[ÀÂÅÊÌÍÎĞÑÒÓÕ][0-9]{3}[ÀÂÅÊÌÍÎĞÑÒÓÕ]{2}-[0-9]{2}"))) return true;
	else return false;
}

bool Predicats::forYear(const std::string& value)
{
	if (value.size() != 4) return false;
	if (regex_match(value.c_str(), std::regex("[0-9]{4}"))) return true;
	else return false;
}

bool Predicats::forDate(const std::string& value)
{
	if (value.size() != 10) return false;
	if (regex_match(value.c_str(), std::regex("([0-9]{2}(\/)[0-9]{2}(\/)[0-9]{4})"))) return true;
	else return false;
}

bool Predicats::forNumber(const std::string& value)
{
	if (regex_match(value.c_str(), std::regex("[0-9]+"))) return true;
	else return false;
}
