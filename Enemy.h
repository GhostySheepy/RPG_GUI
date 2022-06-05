#pragma once
#include "NPC.h"
#include "Item.h"
#include "Speclist.h"
#include "Include/json.hpp"
#include <string>
#include <memory>

namespace npc
{
	class Enemy
	{
	private:
		std::string m_name;
		std::string m_type;
		Speclist specsEnemy;
		int lvl;
		Item_Search_Plate heritage_item;
	public:
		Enemy();
		~Enemy();
		const std::string& getName();
		const std::string& getType();
		int get_level();
		const double getHealth();
		void setName(const std::string& n);
		void setType(const std::string& t);
		void setLvl(int l);
		void healthCheck();
		Speclist attack();
		void defence(Speclist specsPlayer);
		void showCurrentState();
		bool isAlive();
		Item_Search_Plate inherit_item();

		friend class BuildWarrior;
		friend class BuildArcher;
		friend class BuildMagician;
	};

	class EnemyBuilder
	{
	protected:
		std::shared_ptr<Enemy> enemy;
	public:
		EnemyBuilder();
		virtual ~EnemyBuilder();

		std::shared_ptr<Enemy> getEnemy();
		void createNewEnemy();

		virtual void nameTypeLevel(int lvlOfEnemy) = 0;
		virtual void specsOfEnemy() = 0;
	};

	class BuildWarrior : public EnemyBuilder
	{
	public:
		BuildWarrior();
		~BuildWarrior();
		void nameTypeLevel(int lvlOfEnemy);
		void specsOfEnemy();
	};

	class BuildArcher : public EnemyBuilder
	{
	public:
		BuildArcher();
		~BuildArcher();
		void nameTypeLevel(int lvlOfEnemy);
		void specsOfEnemy();
	};

	class BuildMagician : public EnemyBuilder
	{
	public:
		BuildMagician();
		~BuildMagician();
		void nameTypeLevel(int lvlOfEnemy);
		void specsOfEnemy();
	};

	class Director
	{
	private:
		EnemyBuilder* builder;
	public:
		Director();
		~Director();

		void setBuilder(EnemyBuilder* b);
		std::shared_ptr<Enemy> getEnemy();
		void build(int lvlOfEnemy);
	};

	void createEnemy(Director& director, std::vector<std::shared_ptr<Enemy>>& enemyList, std::pair<std::string, int> typeOfEnemy);
}