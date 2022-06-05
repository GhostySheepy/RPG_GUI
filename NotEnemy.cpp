#include "NotEnemy.h"
#include <cstdlib>

npc::NotEnemy::NotEnemy()
{
	InfNPC data;
	m_name = data.m_arrOfNames[rand() % 5];
	m_type = data.m_arrOfTypesNEnemy[rand() % 3];
}

npc::NotEnemy::~NotEnemy() {}

const std::string& npc::NotEnemy::getName()
{
	return m_name;
}

const std::string& npc::NotEnemy::getType()
{
	return m_type;
}

int npc::NotEnemy::moneyForHeal()
{
	Player* player = Player::getInstance();
	return (player->getMaxHealth() - player->getHealth());
}

void npc::NotEnemy::heal()
{
	Player* player = Player::getInstance();
	player->setHealth(player->getMaxHealth());
}