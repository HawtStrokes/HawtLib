#include "IniFile.h"
#include "IniParser.h"
#include <iostream>

namespace HawtLib {
	namespace Parsing {
		// ctor and dtor
		IniFile::IniFile(const std::string& file) {
			IniParser::Get().Read(this, file);
		}


		IniFile::IniFile(IniFile& other) {
			other.m_Sections.reserve(m_Sections.size());
			for (Section* m_Section : m_Sections) {
				Section* section = new Section{ m_Section->name};
				std::vector<KeyValue*> keyValues{};
				keyValues.reserve(m_Section->keyValues.size());
				for (size_t i = 0; i < m_Section->keyValues.size(); ++i) {
					keyValues.emplace_back(new KeyValue{ m_Section->keyValues[i]->key,
						m_Section->keyValues[i]->value });
				}
				other.m_Sections.emplace_back(section);
			}
		}

		IniFile& IniFile::operator=(IniFile& other) {
			m_Sections.reserve(other.m_Sections.size());
			for (Section* otherSection : other.m_Sections) {
				Section* section = new Section{ otherSection->name };
				std::vector<KeyValue*> keyValues{};
				keyValues.reserve(otherSection->keyValues.size());
				for (size_t i = 0; i < otherSection->keyValues.size(); ++i) {
					keyValues.emplace_back(new KeyValue{ otherSection->keyValues[i]->key,
						otherSection->keyValues[i]->value });
				}
				m_Sections.emplace_back(section);
			}
			return *this;
		}

		IniFile::~IniFile() {
			_CleanUp();
		}
		
		void IniFile::_CleanUp() {
			for (size_t i = 0; i < m_Sections.size(); ++i) {
				for (size_t j = 0; j < m_Sections[i]->keyValues.size(); ++j) {
					delete m_Sections[i]->keyValues[j];
				}
				delete m_Sections[i];
			}
		}

		
		std::vector<IniFile::Section*>& IniFile::GetSections() {
			return m_Sections;
		}
	}
}