#pragma once

enum class Spec_Types {
	Coin,
	Expreience,

	/*				S.P.E.C.I.A.L. LIST
*At start of game each spec is changable and = 5, also player has 5 adittional points to spread between theese*/

	Strength, //influences health, carry_weight and dmg in close combat with some weapons
	Perception, // influenses dmg in distant combat(????)
	Endurance, // endurance is endurance. Changes resist to everything, running time, health regen, etc...
	Charisma, // need to change dialogues, less chances of solving situation with fight, changes prices
	Intelligence, // also changes dialogues, stupid player would not have abilities to get some hard side quests because of neural potato in his head 
	Agility, //  
	Luck,// changes loot in chests, ampifies chances of doing ANYTHING even WITHOUT having other specs in needed level

/*		PROTECTION SPECS		*/
	Max_health,// 15 + strength + 2*endurance
	Health, 
	Health_regen, // enduranse / 3, but not less, than 1 (may be % of max health)
	Armor_class, // %, starts with agility, changes with armor, amplifies chances of enemy to fully miss

	Crit_reject, //% chances of rejecting crit attack

	Damage_resist, //% how less dmg will player get, range 0%-85%, default -- 0
	Meele_resist,
	Deafening_resist,
	Poision_resist, //% = endurance*5

/*			ATACK SPECS			*/
	Damage, // Default dmg bonus to all types of weapons 
	Action_points, // how much mooves you could do in fight, inventory opening, drinking potions, etc also counts
	Max_action_points, // (5 + agility)/2
	Action_points_regen, // how much poits you will get at start of your turn

	Meele_damage,//"Урон холодным оружием",addition to eqipped weapon dmg, == strength - 5, but not less, than 1
	Deafening_damage,//"Урон оглушением"
	Poision_damage,

/*May be adding some more of dmg addons to different types of weapons*/

	Crit_chance, // = luck
	Crit_amplif, // strength / 2

/*			OTHER			*/
	Normal_speed, //
	Running_speed, //
	Running_time, //

	Carry_weight, // 25+(strength*2) (or 25+(strength*25))

	END
};

class Speclist
{
public:
	double specs[static_cast<int>(Spec_Types::END)];

	Speclist() {
		for (int x = 0; x < static_cast<int>(Spec_Types::END); x++) {
			specs[x] = 0;
		}
	}

	double get(Spec_Types spec) {
		return specs[static_cast<int>(spec)];
	}

	void calculate_secondary_stats() { // Apply that function to list with known S.P.E.C.I.A.L`s to fill other dependant stuff
		specs[static_cast<int>(Spec_Types::Max_health)] = 20 + get(Spec_Types::Strength) + 2 * get(Spec_Types::Endurance);

		specs[static_cast<int>(Spec_Types::Health)] = get(Spec_Types::Max_health);

		specs[static_cast<int>(Spec_Types::Health_regen)] = get(Spec_Types::Endurance) / 2;
		if (get(Spec_Types::Health_regen) < 1) specs[static_cast<int>(Spec_Types::Health_regen)] = 1;

		specs[static_cast<int>(Spec_Types::Armor_class)] = get(Spec_Types::Agility);

		specs[static_cast<int>(Spec_Types::Crit_reject)] = get(Spec_Types::Agility) / 2;
		if (get(Spec_Types::Crit_reject) < 1) specs[static_cast<int>(Spec_Types::Crit_reject)] = 1;

		specs[static_cast<int>(Spec_Types::Damage_resist)] = 1;

		specs[static_cast<int>(Spec_Types::Meele_resist)] = 1;

		specs[static_cast<int>(Spec_Types::Deafening_resist)] = get(Spec_Types::Perception)*2;

		specs[static_cast<int>(Spec_Types::Poision_resist)] = get(Spec_Types::Endurance) * 2;

		specs[static_cast<int>(Spec_Types::Damage)] = get(Spec_Types::Strength) / 2;
		if (get(Spec_Types::Damage) < 1) specs[static_cast<int>(Spec_Types::Damage)] = 1;

		specs[static_cast<int>(Spec_Types::Max_action_points)] = static_cast<int>((5 + get(Spec_Types::Agility)) / 2);
		if (get(Spec_Types::Max_action_points) < 1) specs[static_cast<int>(Spec_Types::Max_action_points)] = 1;

		specs[static_cast<int>(Spec_Types::Action_points)] = get(Spec_Types::Max_action_points);

		specs[static_cast<int>(Spec_Types::Action_points_regen)] = static_cast<int>((5 + get(Spec_Types::Agility)) / 2);
		if (get(Spec_Types::Action_points_regen) < 1) specs[static_cast<int>(Spec_Types::Action_points_regen)] = 1;

		specs[static_cast<int>(Spec_Types::Meele_damage)] = get(Spec_Types::Agility) - 5 ;
		if (get(Spec_Types::Meele_damage) < 1) specs[static_cast<int>(Spec_Types::Meele_damage)] = 1;

		specs[static_cast<int>(Spec_Types::Deafening_damage)] = get(Spec_Types::Strength) - 5;
		if (get(Spec_Types::Deafening_damage) < 1) specs[static_cast<int>(Spec_Types::Deafening_damage)] = 1;

		specs[static_cast<int>(Spec_Types::Poision_damage)] = get(Spec_Types::Intelligence) - 5;
		if (get(Spec_Types::Poision_damage) < 1) specs[static_cast<int>(Spec_Types::Poision_damage)] = 1;

		specs[static_cast<int>(Spec_Types::Crit_chance)] = get(Spec_Types::Luck);

		specs[static_cast<int>(Spec_Types::Crit_amplif)] = get(Spec_Types::Strength)/2;

		specs[static_cast<int>(Spec_Types::Normal_speed)] = static_cast<int>(5);

		specs[static_cast<int>(Spec_Types::Running_speed)] = static_cast<int>(7);
		
		specs[static_cast<int>(Spec_Types::Running_time)] = static_cast<int>(10);

		specs[static_cast<int>(Spec_Types::Carry_weight)] = get(Spec_Types::Strength) + get(Spec_Types::Endurance) + 20;

	}
};