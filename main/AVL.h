#pragma once
#include <string>
#include <vector>
#include "Data.h"
#include "DataBase.h"
#include "Exceptions.h"
#include "Utility.h"

class AVL : public DataBase<Client> {
private:
	struct node // структура для представления узлов дерева
	{
		uint32_t key;
		Client* data;
		uint8_t height;
		node* left;
		node* right;
		node() { left = right = nullptr; height = 1; }
		node(uint32_t key, Client* data);
	};
	node* Head = nullptr;
	uint8_t height(node* current);
	int32_t bfactor(node* current);
	void fixheight(node* current);
	node* rotateright(node* current);
	node* rotateleft(node* current);
	node* balance(node* current);
	node* insert(node* current, uint32_t key, Client* data);
	node* findmin(node* current);
	node* removemin(node* current);
	node* remove(node* current, uint32_t key);
	void getAll(node* current, std::vector<Client*>& all);
	Client* find(node* current, uint32_t key);
	void findAll(node* current, std::vector<Client*>& all, const std::string& value);

	virtual void insert(uint32_t key, Client* data) override;
	virtual void remove(uint32_t key) override;
	virtual std::vector<Client*> getAll() override;
	virtual Client* find(uint32_t key) override;
	virtual std::vector<Client*> findAll(const std::string& value) override;
public:
	AVL();
	~AVL();
};