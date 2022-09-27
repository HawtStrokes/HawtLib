#pragma once
#include "Interfaces/ITimer.h"

namespace HawtLib {
	namespace Profiling {
		class ControlledTimer : public ITimer {
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
			float duration;	// in ns
		public:
			ControlledTimer() = default;
			ControlledTimer(const ControlledTimer&) = delete;
			ControlledTimer operator=(const ControlledTimer&) = delete;
			~ControlledTimer() = default;

		private:
			inline void _Start() noexcept override;

			inline void _Stop() noexcept override;
		public:

			void Start();

			void Stop();

			float GetDuration() const;
		};
	}
}