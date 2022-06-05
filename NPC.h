#pragma once
#include <string>

namespace npc
{
	struct InfNPC
	{
	private:
		std::string m_arrOfNames[5] = { "Shinji", "Wolfgang", "John", "Hector", "Nick" };
		std::string m_arrOfTypesEnemy[3] = { "Warrior", "Archer", "Magician" };
		std::string m_arrOfTypesNEnemy[3] = { "Merchant", "Forgemaster", "Nurse" };
	public:
		friend class NotEnemy;
		friend class BuildWarrior;
		friend class BuildArcher;
		friend class BuildMagician;
	};
}