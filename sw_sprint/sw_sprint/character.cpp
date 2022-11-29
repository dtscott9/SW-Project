#include "character.h"

character::character(Value _name, Value _id, Value _species, Value _gender, Value _homeWorld)
{
	name = _name;
	id = _id;
	species = _species;
	gender = _gender;
	homeWorld = _homeWorld;
}

void character::displayInfo()
{
	cout << "\nID: " << id << "\nName: " << name << "\nSpecies: " << species << "\nGender: " << gender << "\nHome World: " << homeWorld << "\n";
}
