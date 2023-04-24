#pragma once
#include <vector>
#include <string>
#include "Data.h"
#include "DataBase.h"
#include "Exceptions.h"

class CFL : public DataBase<Event> { // Cyclic Forward List
private:
	struct node {
		uint32_t key = NULL;
		Event* data = nullptr;
		node* next = nullptr;
		node(uint32_t key, Event* data);
	};
	node* Head = nullptr;
	void remove(node*& current, uint32_t key);
	virtual void insert(uint32_t key, Event* data) override;
	virtual void remove(uint32_t key) override;
	virtual std::vector<Event*> getAll() override;
	virtual Event* find(uint32_t key) override;
	virtual std::vector<Event*> findAll(const std::string& value) override;
public:
	CFL();
	~CFL();
};