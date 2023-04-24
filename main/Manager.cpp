#include "Manager.h"

DataBase<Client>* Manager::Clients = new AVL;
DataBase<Auto>* Manager::Autos = new MAP;
DataBase<Event>* Manager::Events = new CFL;
std::string Manager::UserInput;
std::string Manager::ClientsPath = "ClientsPrinter.txt";
std::string Manager::AutosPath = "AutosPrinter.txt";
std::string Manager::EventsPath = "EventsPrinter.txt";

std::string Manager::input(const std::string& title, std::function<bool(std::string)> predicat)
{
	while (true) {
		std::cout << title; getline(std::cin, UserInput);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_Util::ToUpperString(UserInput);
		if (predicat(UserInput)) return UserInput;
		else std::cout << "\t�������� ������ ������!!!" << std::endl;
	}
}

Client* Manager::RequestClient()
{
	Client* current = new Client;
	_Util::ShowConsoleCursor(true);
	current->DriversNumber = input("\t������� ����� ������������� �������������. ������: NN AA NNNNNN: ", _Pred::forDriversNumber);
	current->PassportData = input("\t������� ����� � ����� ��������. ������: NNNN-NNNNNN: ", _Pred::forPassportData);
	current->Name = input("\t������� ���: ", _Pred::forName);
	current->Address = input("\t������� ����� ����������: ");
	_Util::ShowConsoleCursor(false);
	return current;
}

Auto* Manager::RequestAuto()
{
	Auto* current = new Auto;
	_Util::ShowConsoleCursor(true);
	current->AutoNumber = input("\t������� ������������� �����. ������: NAAANN-NN: ", _Pred::forAutosNumber);
	current->Brand = input("\t������� ����� ����������: ");
	current->ReleaseYear = atoi(input("\t������� ��� �������: ", _Pred::forYear).c_str());
	current->Color = input("\t������� ���� ����������: ");
	current->inStock = true;
	_Util::ShowConsoleCursor(false);
	return current;
}

Event* Manager::RequestEvent(std::string DriversNumber, std::string AutoNumber)
{
	Event* current = new Event;
	_Util::ShowConsoleCursor(true);
	current->AutoNumber = AutoNumber;
	current->DriversNumber = DriversNumber;
	while (true) {
		current->BeginDate = input("\t������� ���� ������ ������: ", _Pred::forDate);
		if (!_Check::DateIsReal(current->BeginDate)) { std::cout << "\t����������� ����!!!" << std::endl; continue; }
		current->EndDate = input("\t������� ���� ��������� ������: ", _Pred::forDate);
		if (!_Check::DateIsReal(current->EndDate)) { std::cout << "\t����������� ����!!!" << std::endl; continue; }
		if (_Check::LeftDateIsBigger(current->BeginDate, current->EndDate))
			std::cout << "\t���� ������ �� ����� ���� ������ ���� ����������!!!" << std::endl;
		else break;
	}
	_Util::ShowConsoleCursor(false);
	return current;
}

Client* Manager::FindClient()
{
	_Util::ShowConsoleCursor(true);
	Client* Driver = nullptr;
	while (!Driver) {
		std::string DriversNubmer = input("\t������� ����� ������������� �������������. ������: NN AA NNNNNN: ", _Pred::forDriversNumber);
		Driver = Clients->find(_Util::getKey(DriversNubmer));
		if (!Driver) {
			std::cout << "������ �� ������!!!" << std::endl;
			std::cout << "\t  [1]=--=[������� �������]" << std::endl;
			std::cout << "\t  [2]=--=[�����]" << std::endl;
			switch (_getch()) { case '1': break; case '2': return nullptr; }
		}
	}
	_Util::ShowConsoleCursor(false);
	return Driver;
}

Auto* Manager::FindAuto()
{
	_Util::ShowConsoleCursor(true);
	Auto* Car = nullptr;
	while (!Car) {
		std::string AutosNumber = input("\t������� ������������� �����. ������: NAAANN-NN: ", _Pred::forAutosNumber);
		Car = Autos->find(_Util::getKey(AutosNumber));
		if (!Car) {
			std::cout << "���� �� �������!!!" << std::endl;
			std::cout << "\t  [1]=--=[������� ������]" << std::endl;
			std::cout << "\t  [2]=--=[�����]" << std::endl;
			switch (_getch()) { case '1': break; case '2': return nullptr; }
		}
	}
	_Util::ShowConsoleCursor(false);
	return Car;
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
	auto Driver = RequestClient();
	Clients->insert(_Util::getKey(Driver->DriversNumber), Driver);
	std::cout << "\t������ ������� ��������!" << std::endl;
	_Util::pause();
}

const void Manager::CreateRandClients()
{
	std::cout << std::endl;
	_Util::ShowConsoleCursor(true);
	std::string size = input("\t������� ����������: ", _Pred::forNumber);
	for (size_t i = 0; i < atoi(size.c_str()); i++)
	{
		auto Driver = RandDataCreator::CreateDriver();
		Clients->insert(_Util::getKey(Driver->DriversNumber), Driver);
	}
	std::cout << "\t������� ����������������!" << std::endl;
	_Util::ShowConsoleCursor(false); _Util::pause();
}

const void Manager::InsertAuto()
{
	std::cout << std::endl;
	auto Car = RequestAuto();
	Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	std::cout << "\t���� ������� ���������!" << std::endl;
	_Util::pause();
}

const void Manager::CreateRandAutos()
{
	std::cout << std::endl;
	_Util::ShowConsoleCursor(true);
	std::string size = input("\t������� ����������: ", _Pred::forNumber);
	for (size_t i = 0; i < atoi(size.c_str()); i++)
	{
		auto Car = RandDataCreator::CreateCar();
		Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	}
	std::cout << "\t���� ����������������!" << std::endl;
	_Util::ShowConsoleCursor(false); _Util::pause();
}

const void Manager::RentAnAuto()
{
	std::cout << std::endl;
	auto Driver = FindClient();
	if (!Driver) return;
	Auto* Car;
	while (true) {
		Car = FindAuto();
		if (!Car) return;
		if (!Car->inStock)
			std::cout << "����� ���� ��� � �������!!! �������� ������!!!" << std::endl;
		else break;
	}
	Car->inStock = false;
	auto Trade = RequestEvent(Driver->DriversNumber, Car->AutoNumber);
	Trade->Event = Event::EVENT::RENTAL;
	Events->insert(_Util::getKey(Trade->AutoNumber), Trade);
	std::cout << "\t������ ������� ���������!" << std::endl;
	_Util::pause();
}

const void Manager::ReturnAnAuto()
{
	std::cout << std::endl;
	Auto* Car;
	while (true) {
		Car = FindAuto();
		if (!Car) return;
		if (Car->inStock)
			std::cout << "��� ���� � �������!!! �������� ������!!!" << std::endl;
		else break;
	}
	Car->inStock = false;
	auto Trade = Events->find(_Util::getKey(Car->AutoNumber));
	auto ReturnTrade = Trade;
	ReturnTrade->Event = Event::EVENT::RETURN;
	Events->insert(_Util::getKey(ReturnTrade->AutoNumber), ReturnTrade);
	std::cout << "\t������� ������� ���������!" << std::endl;
	_Util::pause();
}

const void Manager::MoveToRepair()
{
	std::cout << std::endl;
	auto Car = FindAuto();
	auto Trade = Events->find(_Util::getKey(Car->AutoNumber));
	auto RepairTrade = Trade;
	RepairTrade->Event = Event::EVENT::TO_REPAIR;
	Events->insert(_Util::getKey(RepairTrade->AutoNumber), RepairTrade);
	std::cout << "\t������ ������� ��������!" << std::endl;
	_Util::pause();
}

const void Manager::BackFromRepair()
{
	std::cout << std::endl;
	auto Car = FindAuto();
	auto Trade = Events->find(_Util::getKey(Car->AutoNumber));
	auto RepairTrade = Trade;
	RepairTrade->Event = Event::EVENT::FROM_REPAIR;
	Events->insert(_Util::getKey(RepairTrade->AutoNumber), RepairTrade);
	std::cout << "\t������ ������� �������!" << std::endl;
	_Util::pause();
}


