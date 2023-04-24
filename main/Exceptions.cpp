#pragma once
#include "Exceptions.h"

DuplicateKey::DuplicateKey(uint32_t key)
{
	this->key = key;
}

const uint32_t DuplicateKey::getKey() const noexcept
{
	return this->key;
}

const char* DuplicateKey::what() const noexcept
{
	return "Дубликат ключа!!!";
}
