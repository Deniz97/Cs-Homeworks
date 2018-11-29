#ifndef POKEFIRE_H
#define POKEFIRE_H

#include "Pokemon.h"
#include <iostream>

class PokeFire : public Pokemon
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
		target->setBurning(true);
		

	}

	void getDamaged(){
		
		if(burning){
			std::cout<<"This should not happen(burn-burn)"<<std::endl;

		}
		if(drowning){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is drowning!!!!"<<std::endl;
				HP-=max(DROWN_DAMAGE*2-MAG_DEF,0);
			}
		}
		if(electrified){
			if(HP>0) {	
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is electrified!!"<<std::endl;
				HP-=max(ELECTRIFY_DAMAGE-MAG_DEF,0);
			}
				
		}
		if(rooted){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is rooted!!"<<std::endl;
				HP-=max(ROOT_DAMAGE-MAG_DEF,0);
			}
		}
		

	}

	void buff(Arena ar){
		if(isBuffed==true || isDebuffed==true){ return; }
		

		if(ar==MAGMA){
			HP+=100;
			ATK+=10;
			isBuffed=true;
		}
		else if(ar==SKY || ar==OCEAN){
			HP-=100;
			ATK-=10;
			isDebuffed=true;
		}
	}


	


	void levelUp(){
		HP+=60;
		ATK+=6;
		MAG_DEF+=2;
		PHY_DEF+=1;

		base_hp+=60;
		base_atk+=6;
		base_mag_def+=2;
		base_phy_def+=1;
	}
	PokeFire(int pokemonID, const std::string& name) : Pokemon(pokemonID,name) {
		HP=600;
		ATK=60;
		MAG_DEF=20;
		PHY_DEF=10;
		base_hp=600;
		base_atk=60;
		base_mag_def=20;
		base_phy_def=10;
	}

	virtual void setBurning(bool burning){
		this->burning = false;
	}



protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif