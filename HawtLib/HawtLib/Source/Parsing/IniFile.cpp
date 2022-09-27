#include "IniFile.h"
#include "IniParser.h"

namespace HawtLib {
	namespace Parsing {
		IniFile::IniFile(const std::string& file) {
			IniParser::Get().Read(this, file);
		}

		IniFile::IniFile(IniFile& other) {
			for (auto& m_Section : m_Sections) {
				other.m_Sections[m_Section.first] = m_Section.second;
			}
		}

		IniFile& IniFile::operator=(IniFile& other) {
			for (auto& otherSection : m_Sections) {
				m_Sections[otherSection.first] = otherSection.second;
			}
			return *this;
		}

		IniFile::~IniFile() {
			_CleanUp();
		}
		
		void IniFile::_CleanUp() {
			for (auto& section : m_Sections) {
				for (auto& keyVal : section.second->keyValues) {
					delete keyVal;
				}
				delete m_Sections[section.first];
			}
		}

		std::map<unsigned long long, IniFile::Section*>& IniFile::GetSections() {
			return m_Sections;
		}
	}
}