#pragma once
#include <stdexcept>

class DataBaseExceptions : public std::exception {
public:
	virtual const uint32_t getKey() const noexcept = 0;
	virtual const char* what() const noexcept override = 0;
};

class DuplicateKey : public DataBaseExceptions {
private:
	uint32_t key;
public:
	DuplicateKey(uint32_t key);
	virtual const uint32_t getKey() const noexcept override;
	virtual const char* what() const noexcept override;
};