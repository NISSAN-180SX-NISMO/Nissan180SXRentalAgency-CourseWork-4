#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "Data.h"

template<class Data>
class DataBase {
public:
	DataBase() {};
	~DataBase() = default;
	virtual void insert(uint32_t key, Data* data) = 0;
	virtual void remove(uint32_t key) = 0;
	virtual std::vector<Data*> getAll() = 0;
	virtual Data* find(uint32_t key) = 0;
	virtual std::vector<Data*> findAll(const std::string& value) = 0;
};