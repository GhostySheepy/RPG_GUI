import re
import os

def replacer(text):
	patterns ='''Coin,
	Expreience,
	Strength,
	Perception,
	Endurance,
	Charisma,
	Intelligence,
	Agility,
	Luck,
	Max_health,
	Health,
	Health_regen,
	Armor_class,
	Crit_reject,
	Damage_resist,
	Meele_resist,
	Deafening_resist,
	Poision_resist,
	Damage,
	Action_points,
	Max_action_points,
	Action_points_regen,
	Meele_damage,
	Deafening_damage,
	Poision_damage,
	Crit_chance,
	Crit_amplif,
	Normal_speed,
	Running_speed,
	Running_time,
	Carry_weight'''
	patterns = patterns.split(',\n\t')
	
	for x in range(len(patterns)):
		patterns[x] = '"'+patterns[x]+'"'
	
	for x in range(len(patterns)):
		result= re.sub(patterns[x],str(x), text)
		text = result
	return text



if __name__ == '__main__':
	for file_name in os.listdir("Readable_data"):
		file = open("Readable_data\\"+file_name, 'r')
		file_data = file.read()
		file.close()

		file_data = replacer(file_data)
		print(file_data)
		file = open("Data\\"+file_name, 'w')
		file.write(file_data)
		file.close()
	