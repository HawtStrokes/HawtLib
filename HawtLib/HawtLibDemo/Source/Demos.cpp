#include <iostream>

#include "../../HawtLib/Source/HawtLib.h"

using namespace HawtLib;

void TableDemo() {
	std::cout << __FUNCTION__ << std::endl;
	Tables::Table table;				// Init Table obj
	table.AddRows(3);					// Set number of rows to three

	table.AddCard("Car Model", 0)		// Header
		.AddCard("Color", 0)
		.AddCard("Door Count", 0);

	table.AddCard("Dodge Demon", 1)		// Enrtry 1
		.AddCard("Red", 1)
		.AddCard("two", 1);

	table.AddCard("Nissan Versa", 2)	// Entry 2
		.AddCard("Grey", 2)
		.AddCard("two", 2);

	table.SetTextAlignment(Tables::TxtAlignment::Center);
	table.PrintTable();			// Print Table
	std::cin.get();
}

void TextFormatDemo() {
	std::cout << __FUNCTION__ << std::endl;
	std::string test = "Hello";
	auto x = Text::CenterText(test);
	std::cout << x << std::endl;
	test = "   hello";
	x = std::move(Text::TrimLead(test));
	std::cout << x << std::endl;
	test = "hello       ";
	x = Text::TrimTrail(test);
	std::cout << x << std::endl;
	test = "   hello     ";
	x = Text::Trim(test);
	std::cout << x << std::endl;
	std::cin.get();
}

void CryptoDemo() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << Crypto::DJB2("Hello World") << std::endl;
	std::cout << Crypto::SDBM("Hello World") << std::endl;
	std::cin.get();
}

int main() {
	TableDemo();
	TextFormatDemo();
	CryptoDemo();
}

