#include <iostream>
#include <fstream>
#include <sstream>

#include "HawtLib/HawtLib.h"

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

void GeneralTreeDemo() {
	std::cout << __FUNCTION__ << std::endl;
	using namespace HawtLib::DataStructures;
	NodeTree<int> nodeTree;
	//auto rootId = nodeTree.AddNode(1);
	nodeTree.AddNode(1);
	nodeTree.AddNode(1);
	nodeTree.AddNode(1);
	nodeTree.AddNode(1);
	nodeTree.MoveHeadChild(0);
	nodeTree.AddNode(2);
	nodeTree.AddNode(2);
	nodeTree.AddNode(2);
	nodeTree.AddNode(2);
	nodeTree.MoveHeadChild(0);
	nodeTree.AddNode(3);
	nodeTree.AddNode(3);
	nodeTree.AddNode(3);
	nodeTree.AddNode(3);
	nodeTree.MoveHeadParent();
	nodeTree.MoveHeadParent();
	nodeTree.TraverseFromTop([](Node<int>* node) {
		std::cout << node->data.value() << std::endl;
		});
	std::cin.get();
	nodeTree.TraverseFromBottom([](Node<int>* node) {
		std::cout << node->data.value() << std::endl;
		});
}

void IniParserDemo() {
	std::cout << __FUNCTION__ << std::endl;
	// create sample ini file
	std::ofstream ofs("iniSample.ini");
	std::stringstream ss;
	std::string IniSample =
		R"([section0]
name = John
age = 40
[section0]
name = Titor
age = 50
; this is a comment
# this is another comment
[section1]
first name = John
last name = Wick)";
	ss << IniSample;
	std::string line;
	while (std::getline(ss, line)) {
		ofs << line << '\n';
	}
	ofs.close();

	// read inifile and store in inifile construct
	Parsing::IniParser& parser = Parsing::IniParser::Get();
	Parsing::IniFile iniFile;
	parser.Read(&iniFile, "iniSample.ini");

	const auto& sections = iniFile.GetSections();

	for (const auto& section : sections) {
		printf("Section(%s)\n", section.second->name.c_str());
		for (const auto& keyVal : section.second->keyValues) {
			printf("Key(%s), Value(%s)\n", keyVal->key.c_str(), keyVal->value.c_str());
		}
	}
	std::cin.get();
}

void CryptoDemo() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << Crypto::DJB2("Hello World") << std::endl;
	std::cout << Crypto::SDBM("Hello World") << std::endl;
	std::cin.get();
}

int main() {
	GeneralTreeDemo();
	IniParserDemo();
	TableDemo();
	TextFormatDemo();
	CryptoDemo();
}

