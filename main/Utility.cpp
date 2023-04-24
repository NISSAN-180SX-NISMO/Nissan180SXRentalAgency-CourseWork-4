#pragma once
#include "Utility.h"

const void Utility::UsfulFunctions::pause(const std::string& PreTitle)
{
	std::cout << PreTitle << "\tƒÎˇ ÔÓ‰ÓÎÊÂÌËˇ Ì‡ÊÏËÚÂ Î˛·Û˛ ÍÌÓÔÍÛ...";
	_getch();
}

const void Utility::UsfulFunctions::ToUpperString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), [](unsigned char c) { return c == 'ˇ' ? 'ﬂ' : std::toupper(c); });
}

const void Utility::UsfulFunctions::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility 
	SetConsoleCursorInfo(out, &cursorInfo);
}

const uint32_t Utility::UsfulFunctions::getKey(const std::string& value)
{
	uint32_t key = 0;
	for (size_t index = 0; index < value.size(); index++)
	{
		if (value[index] != ' ' && value[index] != '-')
		{
			key += static_cast<uint8_t>(value[index])
				* static_cast<uint32_t>(std::pow(3, value.size() - index));
		}
	}
	return key;
}

std::vector<uint16_t> Utility::Checking::DateToVector(const std::string& date)
{
	// ‡Á‰ÂÎˇÂÚ ÒÚÓÍÛ Ì‡ Ï‡ÒÒË‚ ËÁ ‰‰/ÏÏ/„„„„
	std::vector<uint16_t> DATE;
	std::string buff = "";
	for (auto i = date.begin(); i <= date.end(); ++i) {
		if (i == date.end()) { DATE.push_back(atoi(buff.c_str())); break; }
		else if (*i == '/') { DATE.push_back(atoi(buff.c_str())); buff = ""; }
		else { buff += *i; }
	}
	return DATE;
}

bool Utility::Checking::LeftDateIsBigger(const std::string& LeftDate, const std::string& RightDate)
{
	// Ò‡‚ÌË‚‡ÂÚ ‰‡Ú˚ (ÌÛÊÌÓ ‰Îˇ ÔÓ‚ÂÍË Ì‡ ‚‚Ó‰)
	constexpr auto DAY = 0;
	constexpr auto MONTH = 1;
	constexpr auto YEAR = 2;
	std::vector<uint16_t> L = DateToVector(LeftDate);
	std::vector<uint16_t> R = DateToVector(RightDate);

	if (L[YEAR] < R[YEAR]) return false;
	if (L[YEAR] > R[YEAR]) return true;
	else
		if (L[MONTH] < R[MONTH]) return false;
	if (L[MONTH] > R[MONTH]) return true;
	else
		if (L[DAY] < R[DAY]) return false;
		else return true;
}

bool Utility::Checking::DateIsReal(const std::string& date)
{
	enum MONTHS { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
	constexpr auto DAY = 0; constexpr auto MONTH = 1; constexpr auto YEAR = 2;
	int DAYS[]{ -1,31,29,31,30,31,30,31,31,30,31,30,31 };
	std::vector<uint16_t> DATE = DateToVector(date);
	if (DATE[MONTH] < 1 || DATE[MONTH] > 12) return false;
	if (DATE[DAY] < 1 || DATE[DAY] > DAYS[DATE[MONTH]]) return false;
	if (DATE[YEAR] < 1900 || DATE[YEAR] > 2023) return false;
	if (DATE[DAY] == 29 && DATE[MONTH] == int(MONTHS::FEBRUARY))
		if (!(DATE[YEAR] % 4 == 0 && ((DATE[YEAR] % 400 == 0 && DATE[YEAR] % 100 == 0) || (DATE[YEAR] % 100 != 0)))) return false;
	return true;
}

const bool Utility::Algorithms::SubStringSearch(const std::string& source, const std::string& chunk)
{
	int sourceSize = source.size();
	int chunkgSize = chunk.size();

	for (int i = 0; i <= sourceSize - chunkgSize; i++) {
		int j;
		for (j = 0; j < chunkgSize; j++)
			if (source[i + j] != chunk[j])
				break;
		if (j == chunkgSize)
			return true;
	}
	return false;
}

const CFL* Utility::Algorithms::DistributionSort(DataBase<Event>* source)
{
	return nullptr; /////////////////
}

std::string Utility::Printer::line(uint16_t size, const char* what)
{
	std::string line;
	for (uint16_t i = 0; i < size; ++i)
		line += what;
	return line;
}

const void Utility::Printer::showDriversHeader(std::ostream& out)
{
	out << " " << line(200, "-") << std::endl;
	out << "| ¬Œƒ»“≈À‹— Œ≈ ”ƒŒ—“Œ¬≈–≈Õ»≈ π "
		<< "| —≈–»ﬂ » ÕŒÃ≈– œ¿—œŒ–“¿ "
		<< "| ‘»Œ" << line(60, " ")
		<< "| ¿ƒ–≈— œ–Œ∆»¬¿Õ»ﬂ" << line(62, " ")
		<< "|" << std::endl;
	out << " " << line(200, "-") << std::endl;
}

const void Utility::Printer::showAutosHeader(std::ostream& out)
{
	out << " " << line(116, "-") << std::endl;
	out << "| –≈√»—“–¿÷»ŒÕÕ€… π "
		<< "| Ã¿– ¿ ¿¬“Œ" << line(20, " ")
		<< "| ÷¬≈“  ”«Œ¬¿" << line(20, " ")
		<< "| √Œƒ ¬€œ”— ¿ "
		<< "| œ–»«Õ¿  Õ¿À»◊»ﬂ "
		<< "|" << std::endl;
	out << " " << line(116, "-") << std::endl;
}

const void Utility::Printer::showEventsHeader(std::ostream& out)
{
	out << " " << line(91, "-") << std::endl;
	out << "| ¬Œƒ»“≈À‹— Œ≈ ”ƒŒ—“Œ¬≈–≈Õ»≈ π "
		<< "| –≈√»—“–¿÷»ŒÕÕ€… π "
		<< "| œ≈–»Œƒ ¿–≈Õƒ€" << line(14, " ")
		<< "| œ–Œ÷≈ƒ”–¿ "
		<< "|" << std::endl;
	out << " " << line(91, "-") << std::endl;
}

const void Utility::Printer::showDriver(std::ostream& out, Client* Driver)
{
	out << "| " << Driver->DriversNumber << line(17, " ")
		<< "| " << Driver->PassportData << line(12, " ")
		<< "| " << Driver->Name << line(std::abs(int(63 - Driver->Name.size())), " ")
		<< "| " << Driver->Address << line(std::abs(int(78 - Driver->Address.size())), " ")
		<< "|" << std::endl;
	out << " " << line(200, "-") << std::endl;
}

const void Utility::Printer::showAuto(std::ostream& out, Auto* Auto)
{
	out << "| " << Auto->AutoNumber << line(9, " ")
		<< "| " << Auto->Brand << line(std::abs(int(30 - Auto->Brand.size())), " ")
		<< "| " << Auto->Color << line(std::abs(int(31 - Auto->Color.size())), " ")
		<< "| " << Auto->ReleaseYear << line(8, " ")
		<< "| " << (Auto->inStock ? "≈—“‹ ¬ Õ¿À»◊»»  " : "Õ≈“ ¬ Õ¿À»◊»»   ")
		<< "|" << std::endl;
	out << " " << line(116, "-") << std::endl;
}

const void Utility::Printer::showEvent(std::ostream& out, Event* Event)
{
	out << "| " << Event->DriversNumber << line(17, " ")
		<< "| " << Event->AutoNumber << line(9, " ")
		<< "| " << "— " << Event->BeginDate << " œŒ " << Event->BeginDate << " ";
	switch (Event->Event) {
	case Event::EVENT::RENTAL: out << "| ¿–≈Õƒ¿    |" << std::endl; break;
	case Event::EVENT::RETURN: out << "| ¬Œ«¬–¿“   |" << std::endl; break;
	case Event::EVENT::TO_REPAIR: out << "| Õ¿ –≈ÃŒÕ“ |" << std::endl; break;
	case Event::EVENT::FROM_REPAIR: out << "| — –≈ÃŒÕ“¿ |" << std::endl; break;
	}
	out << " " << line(91, "-") << std::endl;
}

const void Utility::Printer::print(std::ostream& out, DataBase<Client>* DataBase)
{
	auto elements = DataBase->getAll();
	showDriversHeader(out);
	for (auto& element : elements)
		showDriver(out, element);
}

const void Utility::Printer::print(std::ostream& out, DataBase<Auto>* DataBase)
{
	auto elements = DataBase->getAll();
	showAutosHeader(out);
	for (auto& element : elements)
		showAuto(out, element);
}

const void Utility::Printer::print(std::ostream& out, DataBase<Event>* DataBase)
{
	auto elements = DataBase->getAll();
	showEventsHeader(out);
	for (auto& element : elements)
		showEvent(out, element);
}



