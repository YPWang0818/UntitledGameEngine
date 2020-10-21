#include "ugepch.h"
#include "UUID.h"


namespace UGE {



	static std::random_device randomDev;  
	static std::mt19937 Gen(randomDev()); 
	static std::uniform_int_distribution<uint64_t> uniformDistribution;

	UUID::UUID()
		:m_ID(uniformDistribution(Gen))
	{

	};

	UUID::UUID(uint64_t ID)
		:m_ID(ID)
	{}

	UUID::UUID(const UUID& other)
		: m_ID(other.m_ID)
	{
	};

	

	bool UUID::operator==(const UUID & other)
	{
		return (this->m_ID == other.m_ID);
	};
	

}