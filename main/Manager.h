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
private:
	static DataBase<Client>* Clients;
	static DataBase<Auto>* Autos;
	static DataBase<Event>* Events;
	static std::string UserInput;
	static std::string ClientsPath;
	static std::string AutosPath;
	static std::string EventsPath;
	static std::string input(const std::string& title, std::function<bool(std::string)> predicat = [](std::string) { return true; });
	static Client* RequestClient();
	static Auto* RequestAuto();
	static Event* RequestEvent(std::string DriversNumber, std::string AutoNumber);
	static Client* FindClient();
	static Auto* FindAuto();
public:
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

	//_MenuCase RemoveClient();
};