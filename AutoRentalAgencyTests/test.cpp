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
	ASSERT_TRUE(_Util::getKey("12 �� 123456") < _Util::getKey("12 �� 123457"));
	ASSERT_TRUE(_Util::getKey("12 �� 123456") != _Util::getKey("21 �� 654321"));
}
TEST(Key, AutosKeyTest) {
	ASSERT_TRUE(_Util::getKey("1���23-45") < _Util::getKey("1���23-46"));
	ASSERT_TRUE(_Util::getKey("1���23-45") != _Util::getKey("1���32-54"));
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
	ASSERT_TRUE(Drivers->getAll().size() == 50);
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
TEST(Manager, ReginstRentAnAutoTest) {
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
TEST(Manager, ReginstReturnAnAutoTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Act
	Manager::setReturnAnAuto(Car);
	// Assert
	ASSERT_EQ(true, Car->inStock);
	ASSERT_EQ(1 + 2, Manager::size(Manager::DBT::EVENTS)); // 1 ������� �� �������� �����
}
TEST(Manager, ReginstMoveToRepairTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Act
	Manager::setReturnAnAuto(Car);	// ������� ������� ����
	Manager::setMoveToRepair(Car);	// ����� ��������� �� ������
	// Assert
	ASSERT_EQ(true, Car->inStock);
	ASSERT_EQ(1 + 2 + 3, Manager::size(Manager::DBT::EVENTS)); // 3 �������� �� �������� �����
}
TEST(Manager, ReginstMoveFromRepairTest) {
	// Arrange
	Client* Driver = RandDataCreator::CreateDriver();
	Auto* Car = RandDataCreator::CreateCar();
	Event* Trade = RandDataCreator::CreateTrade(Driver->DriversNumber, Car->AutoNumber);
	Manager::setRentAnAuto(Car, Trade);
	// Act
	Manager::setMoveToRepair(Car);	// ������� ��������� �� ������
	Manager::setBackFromRepair(Car);// ����� ������� �� �������
	Manager::setReturnAnAuto(Car);	// � ������ ����� ������� ����
	// Assert
	ASSERT_EQ(true, Car->inStock);
	ASSERT_EQ(1 + 2 + 3 + 4, Manager::size(Manager::DBT::EVENTS)); // 6 ��������� �� �������� �����
}
TEST(Manager, RemoveClientTest) {
	// Arrange
	Client* DebtorDriver = RandDataCreator::CreateDriver(); // ����� ���������
	Manager::Clients->insert(_Util::getKey(DebtorDriver->DriversNumber), DebtorDriver);

	Client* Driver = RandDataCreator::CreateDriver(); // �� ����� ���������
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
	ASSERT_TRUE(Manager::removeClient(DebtorDriver)); // ����� ������� ������ ����� ���� ��� ������ ����� �� ��������
	// Assert
	ASSERT_TRUE(Manager::removeClient(Driver)); // � ���� ������ ���� �� ����
}

TEST(Manager, ClearClientTest) {
	// Arrange
	Client* DebtorDriver = RandDataCreator::CreateDriver(); // ����� ���������
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
	Manager::ClearClient();
	// Assert
	ASSERT_EQ(1, Manager::size(Manager::DBT::CLIENTS));
}