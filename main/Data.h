#pragma once
#include <string>
#include <vector>
#include <cmath>

struct Client {
	std::string DriversNumber;		// format: "RR AA NNNNNN"
	std::string Name;				// format: "Name Second-Name Patronymic"
	std::string PassportData;		// format: "NNNN-NNNNNN"
	std::string Address;			// format: "ул. Название Улицы д. 123"
};

struct Auto  {
	std::string Brand;				// format: "Just brand"
	std::string AutoNumber;			// format: "ANNNAA-NN"
	std::string Color;				// format: "Just colour"
	uint16_t ReleaseYear;			// format: "NNNN"
	bool inStock;
};

struct Event {
	enum class EVENT : uint8_t {
		RENTAL,						// Взятие в аренду
		RETURN,						// Возврат из аренды
		TO_REPAIR,					// Отправка на ремонт
		FROM_REPAIR					// Прибытие с ремонта
	};
	EVENT Event;
	std::string AutoNumber;			// format: "ANNNAA-NN"
	std::string DriversNumber;		// format: "RR AA NNNNNN"
	std::string BeginDate;			// format: "DD/MM/YYYY"
	std::string EndDate;			// format: "DD/MM/YYYY"
};




