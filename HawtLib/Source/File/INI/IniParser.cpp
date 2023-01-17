#include "../../Text/TextFormatting.h"
#include "IniParser.h"
#include "IniFile.h"
#include "../FileExceptions.h"

#include <fstream>
//#include <exception>

#include <filesystem>

namespace HawtLib {
	namespace File  {
		namespace Parsing {
			//IniParser* IniParser::m_Instance = nullptr;

			IniParser& IniParser::Get() {
				static IniParser instance{};
				return instance;
			}

			void IniParser::UpdateCommentTokens()
			{
				m_Comments.clear();
			}

			void IniParser::UpdateCommentTokens(const std::vector<char>& comments)
			{
				m_Comments = comments;
			}

			void IniParser::ResetCommentTokens()
			{
				m_Comments = { ';', '#' };
			}

			void IniParser::Read(IniFile* iniFile, const std::string& file) {
				if (!std::filesystem::exists(std::filesystem::path(file))) {
					throw FileDoesNotExistError();
				}

				std::ifstream ifs(file);
				std::vector<std::vector<IniParser::Token*>> allTokens;

				// Tokenize
				std::string line;
				while (std::getline(ifs, line)) {
					line = Text::Trim(line);
					auto lineTokens = Internal_Lex(line);
					if (!lineTokens->empty()) allTokens.push_back(*lineTokens);
				}


				if (!iniFile->m_Sections.empty()) iniFile->m_Sections.clear();

				// Fill IniFile construct with data
				Internal_Parse(iniFile, allTokens);
				ifs.close();
			}

			IniParser::IniParser() : m_Comments(std::vector{';', '#'}) {}

			std::unique_ptr<std::vector<IniParser::Token*>> IniParser::Internal_Lex(std::string& line) {
				std::erase(line, '\t');		// Disallow tabs
				line = HawtLib::Text::Trim(line);
				auto tokens = std::make_unique<std::vector<Token*>>();

				if (line.empty())  return tokens;

				size_t lineEnd = line.size() - 1;	// last index we allow to be referenced

				// Remove comments by updating lineEnd
				{
					if (!m_Comments.empty())
					{
						for (const char commentToken : m_Comments)
						{
							const size_t commentTokenIdx = line.find(commentToken);
							if (commentTokenIdx != std::string::npos)
							{
								lineEnd = std::min(lineEnd, commentTokenIdx) == 0 ? 0 : std::min(lineEnd, commentTokenIdx) - 1;;
								if (lineEnd == 0)
								{
									if (line[0] == ' ' || line[0] == commentToken) return tokens;
									throw FileTokenError();
								}
							}
						}
					}

			/*		const size_t commentSIdx = line.find(';');
					const size_t commentHIdx = line.find('#');
					
					if(commentHIdx != std::string::npos || commentSIdx != std::string::npos)
					{
						lineEnd = std::min(commentHIdx, commentSIdx) == 0? 0 : std::min(commentHIdx, commentSIdx) - 1;
						if (lineEnd == 0) {
							if(line[0] == ' ' || line[0] == ';' || line[0] == '#') return tokens;
							throw FileTokenError(); 
						}
					}*/
				}

				// We can't have a line shorter than two characters

				for (size_t i = 0; i <= lineEnd; ++i) {
					// Section
					if (line[0] == '[' && line[lineEnd] == ']') {
						//++tokenBegin;
						tokens->push_back(new IniParser::Token{ IniParser::TokenType::Section,line.substr(1, lineEnd - 1) });	// Add Section 
						break;
					}

					// KeyValue
					if (line[i] == '=') {

						if (i == 0)
						{	// Check for Key
							throw FileTokenError("Key Must Be Present!");
						}

						else if (i == lineEnd)
						{	// Check for Value
							throw FileTokenError("Value Must Be Present!");
						}

						else
						{	// Add Key Value
							tokens->push_back(new Token{ IniParser::TokenType::Key,
								HawtLib::Text::TrimTrail(line.substr(0, i)) });				// Add Key

							//tokenBegin = i + 1;		// Skip equals
							const std::string value = HawtLib::Text::Trim(line.substr(i + 1, lineEnd - i));

							if (value == " ") throw FileTokenError("Value Must Be Present!");
							else tokens->push_back(new Token{ IniParser::TokenType::Value, value }); // Add Value
						}
					}

					
				}
			
				if (tokens->empty())
				{
					for (size_t i = 0; i <= lineEnd; ++i)
					{
						if (line[i] != ' ')
							throw FileTokenError();
					}
					return tokens;
				}

				return tokens;
			}

			void IniParser::Internal_Parse(IniFile* iniFile, std::vector<std::vector<IniParser::Token*>>& allTokens) {
				// loop through each line of tokens
				std::string currentSection;
				for (std::vector<IniParser::Token*>& lineTokens : allTokens) {
					if (lineTokens[0]->type == IniParser::TokenType::Section) {	// Section
						currentSection = lineTokens[0]->data;
						iniFile->CreateSection(lineTokens[0]->data);
					}
					else {	// Key Value
						if (currentSection.empty()) throw FileTokenError("Missing Section Name!");
						iniFile->AddKeyValue(currentSection, lineTokens[0]->data, lineTokens[1]->data);	// Add Key Value
					}
				}
				Internal_CleanTokens(allTokens);
			}

			void IniParser::Internal_CleanTokens(const std::vector<std::vector<IniParser::Token*>>& allTokens) {
				for (size_t y = 0; y < allTokens.size(); ++y) {
					for (size_t x = 0; x < allTokens[y].size(); ++x) {
						delete allTokens[y][x];
					}
				}
			}
		}
	}
}