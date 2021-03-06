#pragma once


namespace UGE {

	class TimeStep {

	public:
		TimeStep(float time = 0.0f)
			:m_Time(time)
		{};


		inline float getSecond() const { return m_Time; };
		inline float getMillisecond() const { return m_Time * 1000; };

		operator float() const { return m_Time; };

	private:
		float m_Time;


	};





}