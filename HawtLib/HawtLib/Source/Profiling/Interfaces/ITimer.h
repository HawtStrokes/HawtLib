#pragma once
#include <chrono>

namespace HawtLib {
	namespace Profiling {
		class ITimer {
		private:
			virtual inline void _Start() noexcept = 0;
			virtual inline void _Stop() noexcept = 0;
		public:
			virtual ~ITimer() = default;
		};
	}
}