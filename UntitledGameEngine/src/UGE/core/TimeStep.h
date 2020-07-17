#pragma once


namespace UGE {

	class TimeStep {

	public:
		TimeStep(double time = 0.0f)
			:m_Time(time)
		{};


		inline double getSecond() const { return m_Time; };
		inline double getMillisecond() const { return m_Time * 1000; };

		operator double() const { return m_Time; };

	private:
		double m_Time;


	};





}