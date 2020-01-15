#pragma once

namespace Hazel {
	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
		{
			m_Time = time;
		}

		inline float getSeconds() { return m_Time; }
		inline float getMillSeconds() { return m_Time * 1000.0f; }
		operator float() { return m_Time; }

	private:
		float m_Time;
	};
}
