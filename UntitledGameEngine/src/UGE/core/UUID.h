#pragma once
#include "stdint.h"

// A UUID (universally unique identifier) class for various purpose. Currently it will generated a random 64bit number. 
// TODO: ID collision detection. 

namespace UGE {


	class UUID {

	public:
		UUID();
		UUID(uint64_t ID);
		UUID(const UUID& other);

		operator uint64_t() { return m_ID; };
		operator const uint64_t() const { return m_ID; }

		bool operator==(const UUID& other);

	private:
		uint64_t m_ID;
	};





}

// Costum Hash function for unordered map

namespace std {
	template<>
	struct hash<UGE::UUID>
	{
		std::size_t operator()(const UGE::UUID & uuid) const noexcept
		{
			return std::hash<uint64_t>{}((uint64_t)uuid);
		};
	};
}