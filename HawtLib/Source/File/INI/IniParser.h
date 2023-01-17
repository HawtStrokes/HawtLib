#pragma once

#if defined(BUILD_DLL)
#define SPEC __declspec(dllexport)
#elif defined(BUILD_STATIC)
#define SPEC
#else
#define SPEC __declspec(dllimport)
#endif

#include <vector>
#include <string>
#include <memory>

namespace HawtLib {
	namespace File {

		class IniFile;

		namespace Parsing {

			class SPEC IniParser {
			public:
				enum class TokenType {
					Section = 0,
					Key = 1,
					Value = 2
				};
				struct Token {
					TokenType type;
					std::string data;
				};

			private:
				std::vector<char> m_Comments;
				IniParser();

			private:
				// Tokenize a line
				std::unique_ptr<std::vector<Token*>> Internal_Lex(std::string& line);

				// creates an IniFile object
				void Internal_Parse(IniFile* iniFile, std::vector<std::vector<IniParser::Token*>>&);

				// cleans the std::vector<Token*>* made by Internal_Lex()
				void Internal_CleanTokens(const std::vector<std::vector<IniParser::Token*>>&);

			public:
				IniParser(const IniParser&) = delete;
				IniParser operator=(const IniParser&) = delete;
				IniParser(const IniParser&&) = delete;
				IniParser operator=(const IniParser&&) = delete;

				static IniParser* m_Instance;
				static IniParser& Get();

				void UpdateCommentTokens();
				void UpdateCommentTokens(const std::vector<char>& comments);
				void ResetCommentTokens();

				void Read(IniFile* iniFile, const std::string& file);
			};
		}
	}
}