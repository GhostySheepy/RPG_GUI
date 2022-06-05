#include <iostream>
#include "Enemy.h"

npc::Enemy::Enemy() : lvl(0) {}
npc::Enemy::~Enemy() {}

const std::string& npc::Enemy::getName() { return m_name; }
const std::string& npc::Enemy::getType() { return m_type; }

const double npc::Enemy::getHealth()
{ 
	return specsEnemy.get(Spec_Types::Health);
}

void npc::Enemy::setName(const std::string& n)
{
	m_name = n;
}

int npc::Enemy::get_level()
{
	return lvl;
}

void npc::Enemy::setType(const std::string& t)
{
	m_type = t;
}

void npc::Enemy::setLvl(int l)
{
	lvl = l;
}

void npc::Enemy::healthCheck()
{
	std::cout << "Health: " << getHealth() << std::endl;
}

Speclist npc::Enemy::attack()
{
	return specsEnemy;
}

Item_Search_Plate npc::Enemy::inherit_item()
{
	return heritage_item;
}

void npc::Enemy::defence(Speclist specsPlayer)
{
	int health_lost = specsPlayer.get(Spec_Types::Damage);
	health_lost += static_cast<int>( (1 -(specsEnemy.get(Spec_Types::Meele_resist) / 100)) * specsPlayer.get(Spec_Types::Meele_damage));
	health_lost += static_cast<int>( (1 - (specsEnemy.get(Spec_Types::Deafening_resist) / 100)) * specsPlayer.get(Spec_Types::Deafening_damage));
	health_lost += static_cast<int>( (1 - (specsEnemy.get(Spec_Types::Poision_resist) / 100)) * specsPlayer.get(Spec_Types::Poision_damage));
	health_lost /= static_cast<int>(specsEnemy.get(Spec_Types::Damage_resist)) + 1; // ¡Àﬂ“‹ ¡Àﬂ“‹ ¡Àﬂﬂﬂﬂﬂﬂ“‹, ƒ≤À≈ÕÕﬂ Õ¿ 0, “–≈¡¿ ¬—≈ Ã≤Õﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ“‹!!!!!!

	specsEnemy.specs[static_cast<int>(Spec_Types::Health)] -= health_lost;
}

void npc::Enemy::showCurrentState()
{
	std::cout << getType() << " " << getName() << ", " << getHealth() << std::endl;
}

bool npc::Enemy::isAlive()
{
	return getHealth() <= 0 ? 0 : 1;
}

npc::EnemyBuilder::EnemyBuilder() {}

npc::EnemyBuilder::~EnemyBuilder() {}

std::shared_ptr<npc::Enemy> npc::EnemyBuilder::getEnemy()
{
	return enemy;
}

void npc::EnemyBuilder::createNewEnemy()
{
	enemy.reset(new Enemy);
}

npc::BuildWarrior::BuildWarrior() : EnemyBuilder() {}

npc::BuildWarrior::~BuildWarrior() {}

void npc::BuildWarrior::nameTypeLevel(int lvlOfEnemy)
{
	InfNPC obj;
	enemy->setName(obj.m_arrOfNames[rand() % 5]);
	enemy->setType(obj.m_arrOfTypesEnemy[0]);
	enemy->setLvl(lvlOfEnemy);
}
void npc::BuildWarrior::specsOfEnemy()
{
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Agility)] = static_cast<int>(3 + enemy->lvl / static_cast<double>(3));
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Strength)] = static_cast<int>(2 + enemy->lvl / static_cast<double>(3));

	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Health)] = 50;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Max_health)] = 50;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Health_regen)] = 0;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Damage)] = 2;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Crit_chance)] = 25;

	Item weapon( 5, "Rusted Sword");
	enemy->specsEnemy = weapon.useItem(enemy->specsEnemy);
	Item armor( 0, "Formless piece of cloth");
	enemy->specsEnemy = armor.useItem(enemy->specsEnemy);

	if (rand() % 2 == 0) enemy->heritage_item = Item_Search_Plate("5", "Rusted Sword");
	else enemy->heritage_item = Item_Search_Plate("0", "Formless piece of cloth");
}

npc::BuildArcher::BuildArcher() : EnemyBuilder() {}

npc::BuildArcher::~BuildArcher() {}

void npc::BuildArcher::nameTypeLevel(int lvlOfEnemy)
{
	InfNPC obj;
	enemy->setName(obj.m_arrOfNames[rand() % 5]);
	enemy->setType(obj.m_arrOfTypesEnemy[1]);
	enemy->setLvl(lvlOfEnemy);
}
void npc::BuildArcher::specsOfEnemy()
{
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Perception)] = static_cast<int>(3 + enemy->lvl / static_cast<double>(3));
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Strength)] = static_cast<int>(2 + enemy->lvl / static_cast<double>(3));

	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Health)] = 30;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Max_health)] = 30;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Health_regen)] = 0;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Damage)] = 0;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Crit_chance)] = 25;

	Item weapon( 5, "Bow");
	enemy->specsEnemy = weapon.useItem(enemy->specsEnemy);
	Item armor( 0, "Formless piece of cloth");
	enemy->specsEnemy = armor.useItem(enemy->specsEnemy);

	if (rand() % 2 == 0) enemy->heritage_item = Item_Search_Plate("5", "Bow");
	else enemy->heritage_item = Item_Search_Plate("0", "Formless piece of cloth");
}

npc::BuildMagician::BuildMagician() : EnemyBuilder() {}

npc::BuildMagician::~BuildMagician() {}

void npc::BuildMagician::nameTypeLevel(int lvlOfEnemy)
{
	InfNPC obj;
	enemy->setName(obj.m_arrOfNames[rand() % 5]);
	enemy->setType(obj.m_arrOfTypesEnemy[2]);
	enemy->setLvl(lvlOfEnemy);
}
void npc::BuildMagician::specsOfEnemy()
{
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Intelligence)] = static_cast<int>(3 + enemy->lvl / static_cast<double>(3));
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Agility)] = static_cast<int>(1 + enemy->lvl / static_cast<double>(3));

	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Health)] = 20;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Max_health)] = 20;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Health_regen)] = 0;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Damage)] = 1;
	enemy->specsEnemy.specs[static_cast<int>(Spec_Types::Crit_chance)] = 25;

	Item weapon( 5, "Magic Wand");
	enemy->specsEnemy = weapon.useItem(enemy->specsEnemy);
	Item armor( 0, "Formless piece of cloth");
	enemy->specsEnemy = armor.useItem(enemy->specsEnemy);

	if (rand() % 2 == 0) enemy->heritage_item = Item_Search_Plate("5", "Magic Wand");
	else enemy->heritage_item = Item_Search_Plate("0", "Formless piece of cloth");
}

npc::Director::Director() : builder(nullptr) {}
npc::Director::~Director() {}

void npc::Director::setBuilder(EnemyBuilder* b)
{
	builder = b;
}

void npc::Director::build(int lvlOfEnemy)
{
	builder->createNewEnemy();
	builder->nameTypeLevel(lvlOfEnemy);
	builder->specsOfEnemy();
}

std::shared_ptr<npc::Enemy> npc::Director::getEnemy()
{
	return builder->getEnemy();
}

void npc::createEnemy(Director& director,
	std::vector<std::shared_ptr<Enemy>>& enemyList,
	std::pair<std::string, int> typeLvlOfEnemy)
{
		if (typeLvlOfEnemy.first == "W")
		{
			BuildWarrior warriorBuilder;
			director.setBuilder(&warriorBuilder);
			director.build(typeLvlOfEnemy.second);
			enemyList.push_back(director.getEnemy());
		}
		else if (typeLvlOfEnemy.first == "A")
		{
			BuildArcher archerBuilder;
			director.setBuilder(&archerBuilder);
			director.build(typeLvlOfEnemy.second);
			enemyList.push_back(director.getEnemy());
		}
		else if (typeLvlOfEnemy.first == "M")
		{
			BuildMagician magicianBuilder;
			director.setBuilder(&magicianBuilder);
			director.build(typeLvlOfEnemy.second);
			enemyList.push_back(director.getEnemy());
		}
}