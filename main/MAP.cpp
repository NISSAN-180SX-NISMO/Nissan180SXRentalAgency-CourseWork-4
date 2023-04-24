#pragma once
#include "MAP.h"

MAP::node::node(uint32_t key, Auto* data) {
    this->key = key;
    this->data = data;
}

const void MAP::node::clear()
{
    this->key = NULL;
    this->data = nullptr;
}

const bool MAP::node::empty()
{
    if (!this->data) return true;
    else return false;
}

const uint32_t MAP::HashFunction(uint32_t key)
{
    const float A = 0.6180339887; // Константа А - золотое сечение
    float scaled_key = key * A;   // Масштабирование ключа
    float fractional_part = scaled_key - floor(scaled_key); // Получение дробной части от масштабированного ключа
    uint32_t index = static_cast<uint32_t>(fractional_part * Capacity);    // Получение индекса
    return index;
}

void MAP::resize(uint32_t NewCapacity) {  // увеличивает размер таблицы
    Capacity = NewCapacity;               // если она занята более чем на 75%
    std::vector<node*> tmp = Table;
    Table.clear(); Table.resize(NewCapacity, nullptr);
    Size = 0;
    for (node*& el : tmp) if (el) insert(el->key, el->data);    // все ключи хешируются заново
    tmp.clear();
}

void MAP::insert(uint32_t key, Auto* data)
{
    if (Size >= 0.75 * Capacity) resize(Capacity <<= 2);
    uint32_t index = HashFunction(key);
    uint64_t i = 0;
    while (true) {
        if (!Table[index]) {
            Table[index] = new node(key, data);
            ++Size;
            break;
        }
        else {
            if (Table[index]->key == key) throw DuplicateKey(key);
            ++i; index += i * _Linear_Coef; index %= Capacity; // линейное опробование
        }
    }
}

void MAP::remove(uint32_t key)
{
    uint32_t index = HashFunction(key);
    uint64_t i = 0;
    while (true) {
        if (!Table[index]) return;
        if (Table[index]->key == key) {
            Table[index]->clear();
            --Size;
            break;
        }
        else {
            ++i; index += i * _Linear_Coef; index %= Capacity; // линейное опробование
        }
    }
}

std::vector<Auto*> MAP::getAll()
{
    std::vector<Auto*> all;
    for (size_t index = 0; index < Capacity; index++)
    {
        if (Table[index] && !Table[index]->empty())
            all.push_back(Table[index]->data);
    }
    return all;
}

Auto* MAP::find(uint32_t key)
{
    uint32_t index = HashFunction(key);
    uint64_t i = 0;
    while (true) {
        if (!Table[index]) return Table[index]->data;
        if (Table[index]->key == key)
            return Table[index]->data;
        else {
            ++i; index += i * _Linear_Coef; index %= Capacity; // линейное опробование
        }
    }
}

std::vector<Auto*> MAP::findAll(const std::string& value)
{
    std::vector<Auto*> all;
    for (size_t index = 0; index < Capacity; index++)
    {
        if (Table[index] && !Table[index]->empty() && Table[index]->data->Brand == value)
            all.push_back(Table[index]->data);
    }
    return all;
}

MAP::MAP()
{
    Table.resize(Capacity, nullptr);
}

MAP::~MAP()
{
    for (size_t index = 0; index < Capacity; index++)
    {
        if (Table[index]) {
            Table[index]->clear();
            Table[index] = nullptr;
        }
    }
}
