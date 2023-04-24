#pragma once
#include <stdexcept>
#include <string>

class MenuFailure : public std::exception {
public:
	virtual ~MenuFailure() = default;
	virtual const std::string getmore() = 0;
};

class CaseIsMissing : public MenuFailure {
private:
	std::string more;
public:
	CaseIsMissing(const char* error) : more(error) {}
	virtual const std::string getmore() override { return this->more; }
};

class SubMenuIsEmpty : public MenuFailure {
private:
	std::string more;
public:
	SubMenuIsEmpty(const char* error) : more(error) {}
	virtual const std::string getmore() override { return this->more; }
};

class DublicateKey : public MenuFailure {
private:
	std::string more;
public:
	DublicateKey(const char* error, char code) : more(error + ' ' + std::to_string(code)) {}
	virtual const std::string getmore() override { return this->more; }
};

