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
	MainMenu.push_case("  [1]=--=[Вывести список клиентов]", KEY::ONE, Manager::PrintClients);
	MainMenu.push_case("  [2]=--=[Вывести список авто]", KEY::TWO, Manager::PrintAutos);
	MainMenu.push_case("  [3]=--=[Вывести список событий]", KEY::THREE, Manager::PrintEvents);
		Menu* RegistMenu = new Menu;
		RegistMenu->push_case("  [...1]=--=[Зарегистировать клиента]", KEY::ONE, Manager::InsertClient);
		RegistMenu->push_case("  [...2]=--=[Зарегистировать несколько клиентов]", KEY::TWO, Manager::CreateRandClients);
		RegistMenu->push_case("  [...3]=--=[Зарегистировать авто]", KEY::THREE, Manager::InsertAuto);
		RegistMenu->push_case("  [...4]=--=[Зарегистировать несколько авто]", KEY::FOUR, Manager::CreateRandAutos);
		RegistMenu->push_case("  [...5]=--=[Оформить аренду авто]", KEY::FIVE, Manager::RentAnAuto);
		RegistMenu->push_case("  [...6]=--=[Оформить возврат авто]", KEY::SIX, Manager::ReturnAnAuto);
		RegistMenu->push_case("  [...7]=--=[Оформить отправку в авто-сервис]", KEY::SEVEN, Manager::MoveToRepair);
		RegistMenu->push_case("  [...8]=--=[Оформить прибытие из авто-сервиса]", KEY::EIGHT, Manager::BackFromRepair);
	MainMenu.push_case("  [4]=--=[Зарегистрировать...]", KEY::FOUR, RegistMenu);
		Menu* RemoveMenu = new Menu;
		RemoveMenu->push_case("  [...1]=--=[Удалить клиента из базы данных]", KEY::ONE, Manager::RemoveClient);
		RemoveMenu->push_case("  [...2]=--=[Осичтить список клиентов]", KEY::ONE, Manager::ClearClient);
		//RemoveMenu->push_case("  [...1]=--=[Удалить авто из базы данных]", KEY::ONE, Manager::RemoveAuto);
		//RemoveMenu->push_case("  [...1]=--=[Очистить список авто]", KEY::ONE, Manager::ClearAuto);
	MainMenu.push_case("  [5]=--=[Удалить...]", KEY::FIVE, RemoveMenu);

	MainMenu.start();
}


