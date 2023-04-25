#pragma once
#include <string>
#include <functional>
#include <iostream>

#include "Data.h"
#include "RandDataCreator.h"
#include "DataBase.h"
#include "AVL.h"
#include "MAP.h"
#include "CFL.h"
#include "Utility.h"
#include "Exceptions.h"
#include "Predicats.h"
#include "ConsoleMenu.h"
#define _MenuCase static const void

class Manager {
public:
	static DataBase<Client>* Clients;
	static DataBase<Auto>* Autos;
	static DataBase<Event>* Events;
private:
	static std::string UserInput;
	static std::string ClientsPath;
	static std::string AutosPath;
	static std::string EventsPath;
	struct Request {
		static std::string input(const std::string& title, std::function<bool(std::string)> predicat = [](std::string) { return true; });
		static Client* Driver();
		static Auto* Car();
		static Event* Trade(std::string DriversNumber, std::string AutoNumber, std::string BeginDate = "", std::string EndDate = "");
		static Client* FindClient();
		static Auto* FindAuto();
	};
	static const bool DriverIsDebtor(Client* Driver);
public:
	enum class DBT : uint8_t {CLIENTS, AUTOS, EVENTS}; // Data Base Type
	static const uint32_t size(DBT what);
	static const void setRentAnAuto(Auto* Car, Event* Trade);
	static const void setReturnAnAuto(Auto* Car);
	static const void setMoveToRepair(Auto* Car);
	static const void setBackFromRepair(Auto* Car);
	static const bool removeClient(Client* Driver);
	static const void clearClients(std::vector<Client*> all);
	static const bool removeAuto(Auto* Car);
	static const void clearAutos(std::vector<Auto*> all);

	_MenuCase PrintClients();
	_MenuCase PrintAutos();
	_MenuCase PrintEvents();

	_MenuCase InsertClient();
	_MenuCase CreateRandClients();
	_MenuCase InsertAuto();
	_MenuCase CreateRandAutos();

	_MenuCase RentAnAuto();
	_MenuCase ReturnAnAuto();
	_MenuCase MoveToRepair();
	_MenuCase BackFromRepair();

	_MenuCase RemoveClient();
	_MenuCase ClearClients();
	_MenuCase RemoveAuto();
	_MenuCase ClearAutos();

	_MenuCase FindClient();
	_MenuCase FindClients();
	_MenuCase FindAuto();
	_MenuCase FindAutos();
};

