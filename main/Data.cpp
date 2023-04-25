#include "Data.h"

bool Event::operator>(const Event& other)
{
	std::string keyL, keyR;
	for (size_t index = 1; index < 4; index++)
	{
		keyL += this->AutoNumber[index];
		keyR += other.AutoNumber[index];
	}
	return atoi(keyL.c_str()) > atoi(keyR.c_str());
}
