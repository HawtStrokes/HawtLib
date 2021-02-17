#pragma once
#include "Table.h"

namespace HawtLib {

	namespace Tables {
		struct Card {
			Table* parentT;
			std::string text;
			TxtAlignment txtAlignment;
			char Bcap;
			
			explicit Card(Table* parent,
				const std::string& text,
				TxtAlignment txtAlignmnt = TxtAlignment::Left,
				char Bcap = '|');

			void Print();
		};
	}
}
