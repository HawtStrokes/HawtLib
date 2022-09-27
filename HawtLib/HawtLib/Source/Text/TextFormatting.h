#pragma once

// undefined behavior

//namespace std { 
//	template <class _Ty, class _Alloc = allocator<_Ty>> class vector;
//	using string = basic_string<char, char_traits<char>, allocator<char>>;
//}

#include <string>
#include <vector>

namespace HawtLib {

	namespace Text {
		std::string CenterText(const std::string& inStr, size_t space = 120);
		std::string RightText(const std::string& inStr, size_t space = 120);
		std::string ToLower(const std::string& inStr);
		char ToLower(char inC);
		std::string ToUpper(const std::string& inStr);
		char ToUpper(char inC);
		std::string Title(const std::string& inStr);
		std::vector<std::string> SplitString(const std::string& inStr, char delim = ' ');
		std::string TrimLead(const std::string& str);
		std::string TrimTrail(const std::string& str);
		std::string Trim(const std::string& str);
		// std::string SurroundString(const std::string& str);
	}
}
