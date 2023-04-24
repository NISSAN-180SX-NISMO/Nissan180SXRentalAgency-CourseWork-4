#pragma once
#include <vector>
#include <string>
#include "Data.h"
#include "DataBase.h"
#include "Exceptions.h"

class MAP : public DataBase<Auto> {
private:
#define _Linear_Coef uint32_t(3);
	uint32_t Capacity = 256;
	const uint32_t HashFunction(uint32_t key);
	struct node {
		uint32_t key = NULL;
		Auto* data = nullptr;
		node(uint32_t key, Auto* data);
		const void clear();
		const bool empty();
	};
	std::vector<node*> Table;
	uint32_t Size = 0;
	void resize(uint32_t NewCapacity);
	virtual void insert(uint32_t key, Auto* data) override;
	virtual void remove(uint32_t key) override;
	virtual std::vector<Auto*> getAll() override;
	virtual Auto* find(uint32_t key) override;
	virtual std::vector<Auto*> findAll(const std::string& value) override;
public:
	MAP();
	~MAP();
};
