#include "pch.h"

#include "../main/Exceptions.cpp"
#include "../main/RandDataCreator.cpp"
#include "../main/Utility.cpp"
#include "../main/AVL.cpp"
#include "../main/MAP.cpp"
#include "../main/CFL.cpp"
#include "../main/Manager.cpp"
#include "../main/Predicats.cpp"

TEST(Key, DriversKeyTest) {
	ASSERT_TRUE(_Util::getKey("12 АВ 123456") < _Util::getKey("12 АВ 123457"));
	ASSERT_TRUE(_Util::getKey("12 АВ 123456") != _Util::getKey("21 ВА 654321"));
}
TEST(Key, AutosKeyTest) {
	ASSERT_TRUE(_Util::getKey("1ААА23-45") < _Util::getKey("1ААА23-46"));
	ASSERT_TRUE(_Util::getKey("1ААА23-45") != _Util::getKey("1ААА32-54"));
}
TEST(AVL, InsertTest) {
	// Arrange
	DataBase<Client>* Drivers = new AVL;
	// Act
	for (size_t i = 0; i < 50; i++)
	{
		try {
			Client* Driver = RandDataCreator::CreateDriver();
			Drivers->insert(_Util::getKey(Driver->DriversNumber), Driver);
		}
		catch (DuplicateKey& ex) { --i; }
	}
	// Assert
	ASSERT_EQ(50, Drivers->getAll().size());
}
TEST(AVL, FindTest) {
	// Arrange
	DataBase<Client>* Drivers = new AVL;
	std::vector<Client*> all;
	for (size_t i = 0; i < 50; i++)
	{
		try {
			Client* Driver = RandDataCreator::CreateDriver();
			all.push_back(Driver);
			Drivers->insert(_Util::getKey(Driver->DriversNumber), Driver);
		}
		catch (DuplicateKey& ex) { --i; }
	}
	// Act
	auto FindedDriver = Drivers->find(_Util::getKey(all[10]->DriversNumber));
	// Assert
	ASSERT_EQ(FindedDriver, all[10]);
}
TEST(AVL, FindAllTest) {
	// Arrange
	DataBase<Client>* Drivers = new AVL;

	Client* Driver_1 = RandDataCreator::CreateDriver();
	Driver_1->Address = "УЛ ПОТАПЕНКО";
	Drivers->insert(_Util::getKey(Driver_1->DriversNumber), Driver_1);

	Client* Driver_2 = RandDataCreator::CreateDriver();
	Driver_2->Name = "ПОТАПОВ МАКАР ЗАХАР";
	Drivers->insert(_Util::getKey(Driver_2->DriversNumber), Driver_2);

	Client* Driver_3 = RandDataCreator::CreateDriver();
	Driver_3->Name = "МОСКВА СИТИ";
	Driver_3->Address = "ИВАН ГОРОД";
	Drivers->insert(_Util::getKey(Driver_3->DriversNumber), Driver_3);
	// Act
	auto FindedDrivers = Drivers->findAll("ПОТ");
	// Assert
	ASSERT_EQ(2, FindedDrivers.size());
}
TEST(MAP, InsertTest) {
	// Arrange
	DataBase<Auto>* Cars = new MAP;
	// Act
	for (size_t i = 0; i < 50; i++)
	{
		try {
			Auto* Car = RandDataCreator::CreateCar();
			Cars->insert(_Util::getKey(Car->AutoNumber), Car);
		}
		catch (DuplicateKey& ex) { --i; }
	}
	// Assert
	ASSERT_TRUE(Cars->getAll().size() == 50);
}
TEST(MAP, FindTest) {
	// Arrange
	DataBase<Auto>* Cars = new MAP;
	std::vector<Auto*> all;
	for (size_t i = 0; i < 50; i++)
	{
		try {
			Auto* Car = RandDataCreator::CreateCar();
			all.push_back(Car);
			Cars->insert(_Util::getKey(Car->AutoNumber), Car);
		}
		catch (DuplicateKey& ex) { --i; }
	}
	// Act
	auto FindedCar = Cars->find(_Util::getKey(all[10]->AutoNumber));
	// Assert
	ASSERT_EQ(FindedCar, all[10]);
}
TEST(MAP, FindAllTest) {
	// Arrange
	DataBase<Auto>* Cars = new MAP;

	Auto* Car_1 = RandDataCreator::CreateCar();
	Car_1->Brand = "MAZDA";
	Cars->insert(_Util::getKey(Car_1->AutoNumber), Car_1);

	Auto* Car_2 = RandDataCreator::CreateCar();
	Car_2->Brand = "MAZDA";
	Cars->insert(_Util::getKey(Car_2->AutoNumber), Car_2);

	Auto* Car_3 = RandDataCreator::CreateCar();
	Car_3->Brand = "NISSAN";
	Cars->insert(_Util::getKey(Car_3->AutoNumber), Car_3);
	// Act
	auto FindedCars = Cars->findAll("MAZDA");
	// Assert
	ASSERT_EQ(2, FindedCars.size());
}
TEST(CFL, InsertTest) {
	// Arrange
	DataBase<Event>* Trades = new CFL;
	// Act
	for (size_t i = 0; i < 50; i++)
	{
		try {
			Client* Driver = RandDataCreator::CreateDriver();
			Auto* Car = RandDataCreator::CreateCar();
			Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
			Trades->insert(_Util::getKey(Trade->AutoNumber), Trade);
		}
		catch (DuplicateKey& ex) { --i; }
	}
	// Assert
	ASSERT_TRUE(Trades->getAll().size() == 50);
}

TEST(CFL, SortTest) {
	// Arrange
	DataBase<Event>* Events = new CFL;
	std::vector<Event*> test;
	for (size_t i = 0; i < 10; i++)
	{
		auto Event = RandDataCreator::CreateTrade(RandDataCreator::CreateDriver()->DriversNumber,RandDataCreator::CreateCar()->AutoNumber);
		Events->insert(_Util::getKey(Event->AutoNumber), Event);
		test.push_back(Event);
	}
	// Act
	DataBase<Event>* SortedTest = _Tool::DistributionSort(Events);
	for (int i = 0; i < test.size(); i++) {
		for (int j = 0; j < test.size() - 1; j++) {
			if (_Util::getKey(test[j]->AutoNumber) > _Util::getKey(test[j + 1]->AutoNumber)) {
				Event* tmp = test[j];
				test[j] = test[j + 1];
				test[j + 1] = tmp;
			}
		}
	}
	// Assert
	auto all = SortedTest->getAll();
	for (size_t i = 0; i < all.size(); i++)
	{
		ASSERT_EQ(all[i]->AutoNumber, test[i]->AutoNumber);
	}
}

TEST(Manager, RegistRentAnAutoTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	// Act
	Manager::setRentAnAuto(Car, Trade);
	// Assert
	ASSERT_EQ(false, Car->inStock);
	ASSERT_EQ(1, Manager::size(Manager::DBT::EVENTS));
}

TEST(Manager, RegistReturnAnAutoTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Act
	Manager::setReturnAnAuto(Car);
	// Assert
	ASSERT_EQ(true, Car->inStock);
	ASSERT_EQ(1 + 2, Manager::size(Manager::DBT::EVENTS)); // 1 элемент из прошлого теста
}

TEST(Manager, RegistMoveToRepairTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Act
	Manager::setReturnAnAuto(Car);	// Сначала вернули авто
	Manager::setMoveToRepair(Car);	// Затем отправили на ремонт
	// Assert
	ASSERT_EQ(true, Car->inStock);
	ASSERT_EQ(1 + 2 + 3, Manager::size(Manager::DBT::EVENTS)); // 3 элемента из прошлого теста
}

TEST(Manager, RegistMoveFromRepairTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Act
	Manager::setMoveToRepair(Car);	// Сначала отправили на ремонт
	Manager::setBackFromRepair(Car);// Затем вернули из ремонта
	Manager::setReturnAnAuto(Car);	// И только потом вернули авто
	// Assert
	ASSERT_EQ(true, Car->inStock);
	ASSERT_EQ(1 + 2 + 3 + 4, Manager::size(Manager::DBT::EVENTS)); // 6 элементов из прошлого теста
}
TEST(Manager, RemoveClientTest) {
	// Arrange
	Client* DebtorDriver = RandDataCreator::CreateDriver(); // Будет должником
	Manager::Clients->insert(_Util::getKey(DebtorDriver->DriversNumber), DebtorDriver);

	Client* Driver = RandDataCreator::CreateDriver(); // не будет должником
	Manager::Clients->insert(_Util::getKey(Driver->DriversNumber), Driver);

	Auto* Car = RandDataCreator::CreateCar();
	Manager::Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	// Act
	Event* Trade = RandDataCreator::CreateTrade(DebtorDriver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade); 
	ASSERT_FALSE(Manager::removeClient(DebtorDriver));
	Manager::setMoveToRepair(Car);	
	ASSERT_FALSE(Manager::removeClient(DebtorDriver));
	Manager::setBackFromRepair(Car);
	ASSERT_FALSE(Manager::removeClient(DebtorDriver));
	Manager::setReturnAnAuto(Car);
	ASSERT_TRUE(Manager::removeClient(DebtorDriver)); // Можно удалить только после того как вернул тачку на прокачку
	// Assert
	ASSERT_TRUE(Manager::removeClient(Driver)); // А этот просто ниче не брал
}
TEST(Manager, ClearClientsTest) {
	// Arrange
	Client* DebtorDriver = RandDataCreator::CreateDriver(); // Будет должником
	Manager::Clients->insert(_Util::getKey(DebtorDriver->DriversNumber), DebtorDriver);

	for (size_t i = 0; i < 50; i++) {
		Client* Driver = RandDataCreator::CreateDriver();
		Manager::Clients->insert(_Util::getKey(Driver->DriversNumber), Driver);
	}

	Auto* Car = RandDataCreator::CreateCar();
	Manager::Autos->insert(_Util::getKey(Car->AutoNumber), Car);

	Event* Trade = RandDataCreator::CreateTrade(DebtorDriver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Assert
	ASSERT_EQ(51, Manager::size(Manager::DBT::CLIENTS));
	// Act
	Manager::clearClients(Manager::Clients->getAll());
	// Assert
	ASSERT_EQ(1, Manager::size(Manager::DBT::CLIENTS));
}
TEST(Manager, RemoveAutoTest) {
	// Arrange
	Client* DebtorDriver = RandDataCreator::CreateDriver(); // Будет должником
	Manager::Clients->insert(_Util::getKey(DebtorDriver->DriversNumber), DebtorDriver);

	Auto* Car = RandDataCreator::CreateCar();
	Manager::Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	// Act
	Event* Trade = RandDataCreator::CreateTrade(DebtorDriver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	ASSERT_FALSE(Manager::removeAuto(Car));
	Manager::setMoveToRepair(Car);
	ASSERT_FALSE(Manager::removeAuto(Car));
	Manager::setBackFromRepair(Car);
	ASSERT_FALSE(Manager::removeAuto(Car));
	Manager::setReturnAnAuto(Car);
	ASSERT_TRUE(Manager::removeAuto(Car)); // Можно удалить только после того как вернул тачку на прокачку
}
TEST(Manager, ClearAutosTest) {
	// Arrange
	Client* DebtorDriver = RandDataCreator::CreateDriver(); // Будет должником
	Manager::Clients->insert(_Util::getKey(DebtorDriver->DriversNumber), DebtorDriver);

	Auto* Car = RandDataCreator::CreateCar();
	Manager::Autos->insert(_Util::getKey(Car->AutoNumber), Car);

	for (size_t i = 0; i < 50; i++) {
		Auto* Car = RandDataCreator::CreateCar();
		Manager::Autos->insert(_Util::getKey(Car->AutoNumber), Car);
	}

	Event* Trade = RandDataCreator::CreateTrade(DebtorDriver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Assert
	ASSERT_EQ(1 + 1 + 51, Manager::size(Manager::DBT::AUTOS));	// 2 машинки с предыдущих тестов...
	// Act														// да, я уже понял что не надо было всё статиком делать...
	Manager::clearAutos(Manager::Autos->getAll());
	// Assert
	ASSERT_EQ(1 + 1, Manager::size(Manager::DBT::AUTOS));
}