#pragma once

#include <vector>
#include <string>
#include <utility>

//#include "IniParser.h"
#include "SharedStructures.h"

namespace HawtLib {
	namespace Parsing {
		class IniParser;

		class IniFile {
		public:
			struct Section {
				std::string name;
				std::vector<KeyValue*> keyValues;
			};
		private:
			std::vector<Section*> m_Sections;

		private:
			void _CleanUp();
		public:
			// ctor and dtor
			IniFile() = default;
			IniFile(const std::string& file);
			~IniFile();

			// copy and move semantics
			IniFile(IniFile&);
			IniFile& operator=(IniFile&);

			IniFile(IniFile&&) = default;
			IniFile& operator=(IniFile&&) = default;

		public:
			std::vector<Section*>& GetSections();
			friend class IniParser;
		};
	}
}