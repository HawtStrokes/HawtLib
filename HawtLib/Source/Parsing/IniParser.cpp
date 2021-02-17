#include <fstream>
#include <string>

#include "IniParser.h"
#include "IniFile.h"

#include "../Crypto/Hashing.h"
#include "../Text/TextFormatting.h"

namespace HawtLib {
	namespace Parsing {
		IniParser& IniParser::Get() {
			static IniParser* instance = nullptr;
			return *instance;
		}

		void IniParser::Read(IniFile* iniFile, const std::string& file) {
			std::ifstream ifs(file);
			if (!ifs) {
				// throw error here
				__debugbreak();
			}

			std::vector<std::vector<IniParser::Token*>> allTokens;

			std::string line;
			while (std::getline(ifs, line)) {
				line = std::move(Text::Trim(line));
				std::vector<IniParser::Token*>* lineTokens = _Lex(line);
				allTokens.push_back(*lineTokens);
			}

			if (!iniFile->m_Sections.empty()) iniFile->_CleanUp();	// clean if not empty
			_Parse(iniFile, allTokens);	// fill iniFile construct with new data
			ifs.close();
		}

		std::vector<IniParser::Token*>* IniParser::_Lex(std::string& line) {
			bool openSection = false;
			bool shouldEscape = false;
			bool keyPresent = false;
			size_t tokenBegin = 0;
			size_t lineEnd = line.size();
			std::vector<IniParser::Token*>* tokens = new std::vector<IniParser::Token*>;

			// comment remover
			auto CommentRemover = [&line, &lineEnd]() -> void {
				for (size_t i = line.find(';'); i != line.npos; i = line.substr(i + 1, line.size() - (i + 1)).find(';')) {
					if (i == 0) {
						lineEnd = 0;
						break;
					}
					if (line[i - 1] == '\\') continue;
					lineEnd = i;
					break;
				}
				for (size_t i = line.find('#'); i != line.npos; i = line.substr(i + 1, line.size() - (i + 1)).find('#')) {
					if (i == 0) {
						lineEnd = 0;
						break;
					}
					if (line[i - 1] == '\\') continue;
					lineEnd = i;
					break;
				}
			};
			CommentRemover();

			for (size_t i = 0; i < lineEnd; ++i) {
				// check if escapeNext is currently true
				if (shouldEscape) {
					line.erase(i - 1, 1);	// erase escape character				
					i -= 1;
					lineEnd -= 1;
					shouldEscape = false;
					// continue;
				}

				else if (line[i] == '\\') shouldEscape = true;

				else if (line[i] == '[') {
					++tokenBegin;
					openSection = true;
				}

				else if (line[i] == ']' && openSection == true) {
					tokens->push_back(new IniParser::Token{ IniParser::TokenType::Section,
						line.substr(tokenBegin, (i - tokenBegin + 1) - 1) });
					openSection = false;
					tokenBegin = i;

					break;	// Ignore the following chars; therefore,
							// it will be discarded and treated as a comment
				}
				// check if keyvalue
				else if (line[i] == '=') {
					if (i == 0) {
						// throw Error key name must be present
						__debugbreak();
					}
					tokens->push_back(new Token{ IniParser::TokenType::Key, line.substr(tokenBegin, i) });
					keyPresent = true;
					tokenBegin = i + 1; // skip equals
					// tokens->push_back(new Token{ IniParser::TokenType::Value, line.substr(tokenBegin, lineEnd - tokenBegin) });
				}

				else if (i == lineEnd - 1 && keyPresent) {
					tokens->push_back(new Token{ IniParser::TokenType::Value, line.substr(tokenBegin, lineEnd - tokenBegin) });
				}
			}

			return tokens;
		}


	
		void IniParser::_Parse(IniFile* iniFile, std::vector<std::vector<IniParser::Token*>>& allTokens) {
			unsigned long long currentSectionId = 0;
			for (std::vector<IniParser::Token*>& lineTokens : allTokens) {
				for (size_t i = 0; i < lineTokens.size(); ++i) {
					if (lineTokens[i]->type == IniParser::TokenType::Section) {
						currentSectionId = Crypto::DJB2(lineTokens[i]->data);
						IniFile::Section* section = new IniFile::Section{lineTokens[i]->data};
						iniFile->m_Sections[currentSectionId] = new IniFile::Section{ lineTokens[i]->data };
					}
					else if (lineTokens[i]->type == IniParser::TokenType::Key) {	// might change this to else later
						if(i < lineTokens.size() && lineTokens[i + 1]->type == IniParser::TokenType::Value) {
							iniFile->m_Sections[currentSectionId]->keyValues.push_back(new KeyValue{Text::Trim(lineTokens[i]->data),
								Text::Trim(lineTokens[i + 1]->data)});
							++i;	// skip next
						}
						else __debugbreak();
					}
				}
			}


			_CleanTokens(allTokens);
		}

		void IniParser::_CleanTokens(std::vector<std::vector<IniParser::Token*>>& allTokens) {
			for (size_t y = 0; y < allTokens.size(); ++y) {
				for (size_t x = 0; x < allTokens[y].size(); ++x) {
					delete allTokens[y][x];
				}
			}
		}
	}
}