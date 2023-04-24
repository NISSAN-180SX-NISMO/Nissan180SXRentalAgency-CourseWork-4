#include "Manager.h"

DataBase<Client>* Manager::Clients = new AVL;
DataBase<Auto>* Manager::Autos = new MAP;
DataBase<Event>* Manager::Events = new CFL;
std::string Manager::UserInput;
std::string Manager::ClientsPath = "ClientsPrinter.txt";
std::string Manager::AutosPath = "AutosPrinter.txt";
std::string Manager::EventsPath = "EventsPrinter.txt";

std::string Manager::Request::input(const std::string& title, std::function<bool(std::string)> predicat)
{
	while (true) {
		std::cout << title; getline(std::cin, UserInput);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_Util::ToUpperString(UserInput);
		if (predicat(UserInput)) return UserInput;
		else std::cout << "\tНеверный формат записи!!!" << std::endl;
	}
}

Client* Manager::Request::Driver()
{
	Client* current = new Client;
	_Util::ShowConsoleCursor(true);
	current->DriversNumber = input("\tВведите номер водительского удостоверения. Пример: NN AA NNNNNN: ", _Pred::forDriversNumber);
	current->PassportData = input("\tВведите серию и номер паспорта. Пример: NNNN-NNNNNN: ", _Pred::forPassportData);
	current->Name = input("\tВведите ФИО: ", _Pred::forName);
	current->Address = input("\tВведите адрес проживания: ");
	_Util::ShowConsoleCursor(false);
	return current;
}

Auto* Manager::Request::Car()
{
	Auto* current = new Auto;
	_Util::ShowConsoleCursor(true);
	current->AutoNumber = input("\tВведите автомобильный номер. Пример: NAAANN-NN: ", _Pred::forAutosNumber);
	current->Brand = input("\tВведите марку автомобиля: ");
	current->ReleaseYear = atoi(input("\tВведите год выпуска: ", _Pred::forYear).c_str());
	current->Color = input("\tВведите цвет автомобиля: ");
	current->inStock = true;
	_Util::ShowConsoleCursor(false);
	return current;
}

Event* Manager::Request::Trade(std::string DriversNumber, std::string AutoNumber, std::string BeginDate, std::string EndDate)
{
	Event* current = new Event;
	_Util::ShowConsoleCursor(true);
	current->AutoNumber = AutoNumber;
	current->DriversNumber = DriversNumber;
	if (BeginDate.empty() && EndDate.empty()) {
		while (true) {
			current->BeginDate = input("\tВведите дату начала аренды: ", _Pred::forDate);
			if (!_Check::DateIsReal(current->BeginDate)) { std::cout << "\tНевозможная дата!!!" << std::endl; continue; }
			current->EndDate = input("\tВведите дату окончания аренды: ", _Pred::forDate);
			if (!_Check::DateIsReal(current->EndDate)) { std::cout << "\tНевозможная дата!!!" << std::endl; continue; }
			if (_Check::LeftDateIsBigger(current->BeginDate, current->EndDate))
				std::cout << "\tДата начала не может быть больше даты завершения!!!" << std::endl;
			else break;
		}
	}
	else {
		current->BeginDate = BeginDate;
		current->EndDate = EndDate;
	}
	_Util::ShowConsoleCursor(false);
	return current;
}

Client* Manager::Request::FindClient()
{
	_Util::ShowConsoleCursor(true);
	Client* Driver = nullptr;
	while (!Driver) {
		std::string DriversNubmer = input("\tВведите номер водительского удостоверения. Пример: NN AA NNNNNN: ", _Pred::forDriversNumber);
		Driver = Clients->find(_Util::getKey(DriversNubmer));
		if (!Driver) {
			std::cout << "Клиент не найден!!!" << std::endl;
			std::cout << "\t  [1]=--=[Выбрать другого]" << std::endl;
			std::cout << "\t  [2]=--=[Выход]" << std::endl;
			switch (_getch()) { case '1': break; case '2': return nullptr; }
		}
	}
	_Util::ShowConsoleCursor(false);
	return Driver;
}

Auto* Manager::Request::FindAuto()
{
	_Util::ShowConsoleCursor(true);
	Auto* Car = nullptr;
	while (!Car) {
		std::string AutosNumber = input("\tВведите автомобильный номер. Пример: NAAANN-NN: ", _Pred::forAutosNumber);
		Car = Autos->find(_Util::getKey(AutosNumber));
		if (!Car) {
			std::cout << "Авто не найдено!!!" << std::endl;
			std::cout << "\t  [1]=--=[Выбрать другое]" << std::endl;
			std::cout << "\t  [2]=--=[Выход]" << std::endl;
			switch (_getch()) { case '1': break; case '2': return nullptr; }
		}
	}
	_Util::ShowConsoleCursor(false);
	return Car;
}

const bool Manager::DriverIsDebtor(Client* Driver)
{
	bool IsDebtor;
	auto Trades = Events->findAll(Driver->DriversNumber);
	for (auto& Trade : Trades) {
		if (Trade->Event == Event::EVENT::RENTAL) {
			IsDebtor = true;
			for (auto& Event : Trades) {
				if (Trade == Event) continue;
				if (Trade->AutoNumber == Event->AutoNumber && Event->Event == Event::EVENT::RETURN)
					IsDebtor = false;
			}
			if (IsDebtor) return true;
		}
	}
	return false;
}

const uint32_t Manager::size(DBT what)
{
	switch (what) {
	case DBT::CLIENTS: return Clients->getAll().size();
	case DBT::AUTOS: return Autos->getAll().size();
	case DBT::EVENTS: return Events->getAll().size();
	}
}

const void Manager::setRentAnAuto(Auto* Car, Event* Trade)
{
	Car->inStock = false;
	Trade->Event = Event::EVENT::RENTAL;
	Events->insert(_Util::getKey(Trade->AutoNumber), Trade);
}

const void Manager::setReturnAnAuto(Auto* Car)
{
	Car->inStock = true;
	auto Trade = Events->find(_Util::getKey(Car->AutoNumber));
	Event* ReturnTrade = new Event; 
	ReturnTrade->AutoNumber = Trade->AutoNumber;
	ReturnTrade->DriversNumber = Trade->DriversNumber;
	ReturnTrade->BeginDate = Trade->BeginDate;
	ReturnTrade->EndDate = Trade->EndDate;
	ReturnTrade->Event = Event::EVENT::RETURN;
	Events->insert(_Util::getKey(ReturnTrade->AutoNumber), ReturnTrade);
}

const void Manager::setMoveToRepair(Auto* Car)
{
	auto Trade = Events->find(_Util::getKey(Car->AutoNumber));
	Event* RepairTrade = new Event;
	RepairTrade->AutoNumber = Trade->AutoNumber;
	RepairTrade->DriversNumber = Trade->DriversNumber;
	RepairTrade->BeginDate = Trade->BeginDate;
	RepairTrade->EndDate = Trade->EndDate;
	RepairTrade->Event = Event::EVENT::TO_REPAIR;
	Events->insert(_Util::getKey(RepairTrade->AutoNumber), RepairTrade);
}

const void Manager::setBackFromRepair(Auto* Car)
{
	auto Trade = Events->find(_Util::getKey(Car->AutoNumber));
	Event* RepairTrade = new Event;
	RepairTrade->AutoNumber = Trade->AutoNumber;
	RepairTrade->DriversNumber = Trade->DriversNumber;
	RepairTrade->BeginDate = Trade->BeginDate;
	RepairTrade->EndDate = Trade->EndDate;
	RepairTrade->Event = Event::EVENT::FROM_REPAIR;
	Events->insert(_Util::getKey(RepairTrade->AutoNumber), RepairTrade);
}

const bool Manager::removeClient(Client* Driver)
{
	if (DriverIsDebtor(Driver)) return false;
	else Clients->remove(_Util::getKey(Driver->DriversNumber));
	return true;
}

const void Manager::PrintClients()
{
	std::ofstream fout(ClientsPath);
	_Print::print(fout, Clients);
	fout.close();
	std::string start = "start " + ClientsPath;
	system(start.c_str());
}

const void Manager::PrintAutos()
{
	std::ofstream fout(AutosPath);
	_Print::print(fout, Autos);
	fout.close();
	std::string start = "start " + AutosPath;
	system(start.c_str());
}

const void Manager::PrintEvents()
{
	std::ofstream fout(EventsPath);
	_Print::print(fout, Events);
	fout.close();
	std::string start = "start " + EventsPath;
	system(start.c_str());
}

const void Manager::InsertClient()
{
	std::cout << std::endl;
	auto Driver = Request::Driver();
	Clients->insert(_Util::getKey(Driver->DriversNumber), Driver);
	std::cout << "\tКлиент успешно добавлен!" << std::endl;
	_Util::pause();
}

const void Manager::CreateRandClients()
{
	std::cout << std::endl;
	_Util::ShowConsoleCursor(true);
	std::string size = Request::input("\tВведите количество: ", _Pred::forNumber);
	for (size_t i = 0; i < atoi(size.c_str()); i++)
	{
		auto Driver = RandDataCreator::CreateDriver();
		Clients->insert(_Util::getKey(Driver->DriversNumber), Driver);
	}
	std::cout << "\tКлиенты зарегистрированы!" << std::endl;
	_Util::ShowConsoleCursor(false); _Util::pause();
}

const void Manager::InsertAuto()
{
	std::cout << std::endl;
	auto Car = Request::Car();
	Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	std::cout << "\tАвто успешно добавлено!" << std::endl;
	_Util::pause();
}

const void Manager::CreateRandAutos()
{
	std::cout << std::endl;
	_Util::ShowConsoleCursor(true);
	std::string size = Request::input("\tВведите количество: ", _Pred::forNumber);
	for (size_t i = 0; i < atoi(size.c_str()); i++)
	{
		auto Car = RandDataCreator::CreateCar();
		Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	}
	std::cout << "\tАвто зарегистрированы!" << std::endl;
	_Util::ShowConsoleCursor(false); _Util::pause();
}

const void Manager::RentAnAuto()
{
	std::cout << std::endl;
	auto Driver = Request::FindClient();
	if (!Driver) return;
	Auto* Car;
	while (true) {
		Car = Request::FindAuto();
		if (!Car) return;
		if (!Car->inStock)
			std::cout << "\tЭтого авто нет в наличии!!! Выберите другое!!!" << std::endl;
		else break;
	}
	auto Trade = Request::Trade(Driver->DriversNumber, Car->AutoNumber);
	setRentAnAuto(Car, Trade);
	std::cout << "\tАренда успешно оформлена!" << std::endl;
	_Util::pause();
}

const void Manager::ReturnAnAuto()
{
	std::cout << std::endl;
	Auto* Car;
	while (true) {
		Car = Request::FindAuto();
		if (!Car) return;
		if (Car->inStock)
			std::cout << "\tЭто авто в наличии!!! Выберите другое!!!" << std::endl;
		else break;
	}
	setReturnAnAuto(Car);
	std::cout << "\tВозврат успешно оформлена!" << std::endl;
	_Util::pause();
}

const void Manager::MoveToRepair()
{
	std::cout << std::endl;
	auto Car = Request::FindAuto();
	setMoveToRepair(Car);
	std::cout << "\tРемонт успешно оформлен!" << std::endl;
	_Util::pause();
}

const void Manager::BackFromRepair()
{
	std::cout << std::endl;
	auto Car = Request::FindAuto();
	setBackFromRepair(Car);
	std::cout << "\tРемонт успешно окончен!" << std::endl;
	_Util::pause();
}

const void Manager::RemoveClient()
{
	auto Driver = Request::FindClient();
	if (removeClient(Driver)) std::cout << "\tКлиент успешно удалён!" << std::endl;
	else std::cout << "\tДанный клиент не вернул авто!!! Вы не можете его удалить!!!" << std::endl;
	_Util::pause(); 
}

const void Manager::ClearClient()
{
	auto Drivers = Clients->getAll();
	for (auto& Driver : Drivers)
		removeClient(Driver);
	std::cout << "\tСписок очищен!" << std::endl;
	_Util::pause();
}


