#ifndef POKEFLYING_H
#define POKEFLYING_H

#include "Pokemon.h"
#include <iostream>

class PokeFlying : public Pokemon
{
public:
	void attackTo(Pokemon* target, Arena currentArena){
		int hasar=max(1,ATK-target->getPHY_DEF()  ) ;
		char sign;
		if(isBuffed){
			sign='+';
		}
		else if(isDebuffed){
			sign='-';
		}
		else{ sign='/'; }

		std::cout<<"\t\t\t"<<name<<"("<<HP<<") hit "<<target->getName()<<"("<<target->getHP()<<") "<<hasar<<"("<<sign<<")"<<std::endl; 
		target->decHP(  hasar);
		

	}

	void getDamaged(){
		

	}


	void levelUp(){
		HP+=65;
		ATK+=5;
		MAG_DEF+=0;
		PHY_DEF+=3;

		base_hp+=65;
		base_atk+=5;
		base_mag_def+=0;
		base_phy_def+=3;
	}

	void buff(Arena ar){
		if(isBuffed==true || isDebuffed==true){ return; }


		if(ar==SKY){
			isBuffed=true;
			HP+=100;
			ATK+=10;
		}
		else if(ar==OCEAN || ar==ELECTRICITY){
			isDebuffed=true;
			HP-=100;
			ATK-=10;
		}
	}

	

	PokeFlying(int pokemonID, const std::string& name) : Pokemon(pokemonID,name){
		HP=650;
		ATK=55;
		MAG_DEF=0;
		PHY_DEF=15;

		base_hp=650;
		base_atk=55;
		base_mag_def=0;
		base_phy_def=15;
	}

	virtual void setBurning(bool burning){
		this->burning = false;
	}
	virtual void setDrowning(bool drowning){
		this->drowning=false;
	}
	virtual void setElectrified(bool electrified){
		this->electrified = false;
	}
	virtual void setRooted(bool rooted){
		this->rooted = false;
	}

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif