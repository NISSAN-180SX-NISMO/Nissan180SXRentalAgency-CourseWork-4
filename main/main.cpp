#include <Windows.h>
#include <time.h>
#include <locale.h>
#include "ConsoleMenu.h"
#include "Manager.h"


int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	Menu MainMenu;
	MainMenu.push_case("  [1]=--=[Вывести список клиентов]",	KEY::ONE,	Manager::PrintClients);
	MainMenu.push_case("  [2]=--=[Вывести список авто]",		KEY::TWO,	Manager::PrintAutos);
	MainMenu.push_case("  [3]=--=[Вывести список событий]",		KEY::THREE, Manager::PrintEvents);
		Menu* RegistMenu = new Menu;
		RegistMenu->push_case("  [...1]=--=[Зарегистировать клиента]",					KEY::ONE,	Manager::InsertClient);
		RegistMenu->push_case("  [...2]=--=[Зарегистировать несколько клиентов]",		KEY::TWO,	Manager::CreateRandClients);
		RegistMenu->push_case("  [...3]=--=[Зарегистировать авто]",						KEY::THREE, Manager::InsertAuto);
		RegistMenu->push_case("  [...4]=--=[Зарегистировать несколько авто]",			KEY::FOUR,	Manager::CreateRandAutos);
		RegistMenu->push_case("\n  [...5]=--=[Оформить аренду авто]",					KEY::FIVE,	Manager::RentAnAuto);
		RegistMenu->push_case("  [...6]=--=[Оформить возврат авто]",					KEY::SIX,	Manager::ReturnAnAuto);
		RegistMenu->push_case("  [...7]=--=[Оформить отправку в авто-сервис]",			KEY::SEVEN, Manager::MoveToRepair);
		RegistMenu->push_case("  [...8]=--=[Оформить прибытие из авто-сервиса]",		KEY::EIGHT, Manager::BackFromRepair);
	MainMenu.push_case("\n  [4]=--=[Зарегистрировать...]",		KEY::FOUR,	RegistMenu);
		Menu* RemoveMenu = new Menu;
		RemoveMenu->push_case("  [...1]=--=[Удалить клиента из базы данных]",			KEY::ONE,	Manager::RemoveClient);
		RemoveMenu->push_case("  [...2]=--=[Осичтить список клиентов]",					KEY::TWO,	Manager::ClearClients);
		RemoveMenu->push_case("  [...3]=--=[Удалить авто из базы данных]",				KEY::THREE, Manager::RemoveAuto);
		RemoveMenu->push_case("  [...4]=--=[Очистить список авто]",						KEY::FOUR,	Manager::ClearAutos);
	MainMenu.push_case("  [5]=--=[Удалить...]",					KEY::FIVE,	RemoveMenu);
		Menu* SearchMenu = new Menu;
		SearchMenu->push_case("  [...1]=--=[Поиск клиента по номеру удостоверения]",	KEY::ONE,	Manager::FindClient);
		SearchMenu->push_case("  [...2]=--=[Поиск клиента по фрагменту ФИО/адреса]",	KEY::TWO,	Manager::FindClients);
		SearchMenu->push_case("  [...3]=--=[Поиск авто по регистрационному номеру]",	KEY::THREE, Manager::FindAuto);
		SearchMenu->push_case("  [...4]=--=[Поиск авто по названию марки]",				KEY::FOUR,	Manager::FindAutos);
		MainMenu.push_case("  [6]=--=[Поиск...]",				KEY::SIX,	SearchMenu);
	MainMenu.start();
}


