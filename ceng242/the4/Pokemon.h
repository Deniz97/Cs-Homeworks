#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "Enums.h"

class Pokemon
{
public:
	// Public Methods

	Pokemon(int pokemonID, const std::string& name){
		this->pokemonID = pokemonID;
		this->name = name;
		burning=false;
		rooted=false;
		electrified=false;
		drowning=false;
		isBuffed=false;
		isDebuffed=false;
	}
	~Pokemon(){
		
	}

	virtual void attackTo(Pokemon* target, Arena currentArena) = 0;	// Purity!
	virtual void levelUp() = 0;		// Purity 
	virtual void getDamaged()=0;
	virtual void buff(Arena ca)=0;



	// Getters

	int getPokemonID() const{
		return pokemonID;
	}
	const std::string& getName() const{
		return name;
	}

	int getHP() const{
		return HP;
	}
	int getATK() const{
		return ATK;
	}
	int getMAG_DEF() const{
		return MAG_DEF;
	}
	int getPHY_DEF() const{
		return PHY_DEF;
	}

	bool isBurning() const{
		return burning;
	}
	bool isDrowning() const{
		return drowning;
	}
	bool isElectrified() const{
		return electrified;
	}
	bool isRooted() const{
		return rooted;
	}

	// Setters

	virtual void setBurning(bool burning){
		this->burning = burning;
	}
	virtual void setDrowning(bool drowning){
		this->drowning=drowning;
	}
	virtual void setElectrified(bool electrified){
		this->electrified = electrified;
	}
	virtual void setRooted(bool rooted){
		this->rooted = rooted;
	}

	void decHP(int a){
		HP-=a;
	}

	// Own Methods

	void revive(){
		burning=false;
		drowning=false;
		electrified=false;
		rooted=false;
		HP=base_hp;
		ATK=base_atk;
		MAG_DEF=base_mag_def;
		PHY_DEF=base_phy_def;
		isBuffed=false;
		isDebuffed=false;
	}

	int max(int a, int b){
		return a>b ? a : b;
	}

protected:
	int pokemonID; 	// Unique

	std::string name;
	
	int base_hp;
	int base_atk;
	int base_mag_def;
	int base_phy_def;

	int HP;
	int ATK;
	int MAG_DEF;
	int PHY_DEF;

	bool burning;
	bool drowning;
	bool electrified;
	bool rooted;

	// Own Attributes

	
	bool isBuffed;
	bool isDebuffed;
	
};

#endif