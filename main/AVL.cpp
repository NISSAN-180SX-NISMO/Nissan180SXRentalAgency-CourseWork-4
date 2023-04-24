#pragma once
#include "AVL.h"

AVL::node::node(uint32_t key, Client* data)
{
	this->key = key;
	this->data = data;
	this->left = this->right = nullptr;
	height = 1;
}

uint8_t AVL::height(node* current)
{
	return current ? current->height : 0;
}

int32_t AVL::bfactor(node* current)
{
	return height(current->right) - height(current->left);
}

void AVL::fixheight(node* current)
{
	uint8_t hl = height(current->left);
	uint8_t hr = height(current->right);
	current->height = (hl > hr ? hl : hr) + 1;
}

AVL::node* AVL::rotateright(node* current) // правый поворот вокруг current
{
	node* current_left = current->left;
	current->left = current_left->right;
	current_left->right = current;
	fixheight(current);
	fixheight(current_left);
	return current_left;
}

AVL::node* AVL::rotateleft(node* current)// левый поворот вокруг current
{
	node* current_right = current->right;
	current->right = current_right->left;
	current_right->left = current;
	fixheight(current);
	fixheight(current_right);
	return current_right;
}

AVL::node* AVL::balance(node* current)// балансировка узла current
{
	fixheight(current);
	if (bfactor(current) == 2)
	{
		if (bfactor(current->right) < 0)
			current->right = rotateright(current->right);
		return rotateleft(current);
	}
	if (bfactor(current) == -2)
	{
		if (bfactor(current->left) > 0)
			current->left = rotateleft(current->left);
		return rotateright(current);
	}
	return current; // балансировка не нужна
}

AVL::node* AVL::insert(node* current, uint32_t key, Client* data)// вставка ключа kye в дерево с корнем current
{
	if (!current) return new node(key, data);
	if (current->key == key) throw DuplicateKey(key);
	if (key < current->key) current->left = insert(current->left, key, data);
	else current->right = insert(current->right, key, data);
	return balance(current);
}

AVL::node* AVL::findmin(node* current)// поиск узла с минимальным ключом в дереве p 
{
	return current->left ? findmin(current->left) : current;
}

AVL::node* AVL::removemin(node* current)// удаление узла с минимальным ключом из дерева p
{
	if (!current->left)
		return current->right;
	current->left = removemin(current->left);
	return balance(current);
}

AVL::node* AVL::remove(node* current, uint32_t key) // удаление ключа key из дерева current
{
	if (!current) return 0;
	if (key < current->key)
		current->left = remove(current->left, key);
	else if (key > current->key)
		current->right = remove(current->right, key);
	else //  key == current->key 
	{
		node* current_left = current->left;
		node* current_right = current->right;
		delete current;
		if (!current_right) return current_left;
		node* min = findmin(current_right);
		min->right = removemin(current_right);
		min->left = current_left;
		return balance(min);
	}
	return balance(current);
}

void AVL::getAll(node* current, std::vector<Client*>& all) // Прямой обход
{
	if (!current) return;
	if (current) all.push_back(current->data);
	if (current->left) getAll(current->left, all);
	if (current->right) getAll(current->right, all);
}

Client* AVL::find(node* current, uint32_t key)
{
	if (!current) return nullptr;
	if (current->key == key) return current->data;
	if (key < current->key) return find(current->left, key);
	else return find(current->right, key);
}

void AVL::findAll(node* current, std::vector<Client*>& all, const std::string& value)
{
	if (!current) return;
	if (current && _Tool::SubStringSearch(current->data->Name + current->data->Address, value)) all.push_back(current->data);
	if (current->left) findAll(current->left, all, value);
	if (current->right) findAll(current->right, all, value);
}

void AVL::insert(uint32_t key, Client* data)
{
	Head = insert(Head, key, data);
}

void AVL::remove(uint32_t key)
{
	Head = remove(Head, key);
}

std::vector<Client*> AVL::getAll()
{
	std::vector<Client*> all;
	getAll(Head, all);
	return all;
}

Client* AVL::find(uint32_t key)
{
	return find(Head, key);
}

std::vector<Client*> AVL::findAll(const std::string& value)
{
	std::vector<Client*> all;
	findAll(Head, all, value);
	return all;
}

AVL::AVL() : DataBase()
{
}

AVL::~AVL()
{
	while (Head) {
		Head = remove(Head, Head->key);
	}
}
