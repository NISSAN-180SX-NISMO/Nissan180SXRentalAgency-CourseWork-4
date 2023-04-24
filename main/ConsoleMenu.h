#pragma once
#include <iostream>
#include <conio.h>		  
#include <string>
#include <functional>
#include <vector>
#include "Utility.h"

#include "ConsoleMenuFailures.h"

using std::string;
using std::function;

const char BUFFER = 256;

enum class KEY
{
	Esc = 27, ZERO = 48, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
};

class Menu;

struct Case {
	~Case() = default;
	string title;
	char code;
	virtual Menu* Do() = 0;
};

class Menu {
private:
	struct FunctionCase : public Case {
		function<void()> ExeFunc;
		FunctionCase(const string title, KEY key, function<void()> ExeFunc = nullptr);
		virtual Menu* Do() override;
	};

	struct SubMenuCase : public Case {
		Menu* SubMenu;
		SubMenuCase(const string title, KEY key, Menu* SubMenu = nullptr);
		virtual Menu* Do() override;
	};
	Case* menu[256];
	void start(Menu* SubMenu);
public:
	Menu();
	void push_case(string title, KEY key, function<void()> ExeFunc);
	void push_case(string title, KEY key, Menu* SubMenu);
	void start() { start(this); }
};