#pragma once
#include "CFL.h"

CFL::node::node(uint32_t key, Event* data) {
	this->key = key;
	this->data = data;
}

void CFL::remove(node*& current, uint32_t key)
{
	if (!current) return;
	if (current->key == key) {
		if (Head->next == Head) {
			delete Head;
			Head = nullptr;
			return;
		}
		else {
			node* tmp = current;
			current = current->next;
			delete tmp;
			return;
		}
	}
	else if (current->next == Head) return;
	else return remove(current->next, key);
}

void CFL::insert(uint32_t key, Event* data)
{
	if (!Head) {
		Head = new node(key, data);
		Head->next = Head;
	}
	else {
		node* current = Head;
		while (current->next != Head)
			current = current->next;
		current->next = new node(key, data);
		current->next->next = Head;
	}
}

void CFL::remove(uint32_t key)
{
	remove(Head, key);
}

std::vector<Event*> CFL::getAll()
{
	std::vector<Event*> all;
	if (!Head) return all;
	node* current = Head;
	do {
		all.push_back(current->data);
		current = current->next;
	} while (current != Head);
	return all;
}

Event* CFL::find(uint32_t key)
{
	if (!Head) return nullptr;
	node* current = Head;
	do {
		if (current->key == key)
			return current->data;
		current = current->next;
	} while (current != Head);
	return nullptr;
}

std::vector<Event*> CFL::findAll(const std::string& value)
{
	std::vector<Event*> all;
	if (!Head) return all;
	node* current = Head;
	do {
		if (current->data->DriversNumber == value)
			all.push_back(current->data);
		current = current->next;
	} while (current != Head);
	return all;
}

CFL::CFL()
{
}

CFL::~CFL()
{
	while (Head)
		remove(Head, Head->key);
}
