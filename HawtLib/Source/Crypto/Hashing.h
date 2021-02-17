#pragma once
#include <string>

namespace HawtLib {
    namespace Crypto {
        unsigned long long DJB2(const std::string& str);
        unsigned long long SDBM(const std::string& str);
	}
}