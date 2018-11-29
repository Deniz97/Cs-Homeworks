#ifndef POKEELECTRIC_H
#define POKEELECTRIC_H

#include "Pokemon.h"
#include <iostream>

class PokeElectric : public Pokemon
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
		target->setElectrified(true);


	}



	void getDamaged(){
		
		if(burning){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is burning!!"<<std::endl;
				HP-=max(0,BURN_DAMAGE-MAG_DEF);
			}
		}
		if(drowning){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is drowning!!"<<std::endl;
				HP-=max(DROWN_DAMAGE-MAG_DEF,0);
			}
		}
		if(electrified){
			std::cout<<"This should not happen(elec-elec)"<<std::endl;
			
			
		}
		if(rooted){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is rooted!!!!"<<std::endl;
				HP-=max(ROOT_DAMAGE*2-MAG_DEF,0);
			}
		}
		

	}

	void buff(Arena ar){
		if(isBuffed==true || isDebuffed==true){ return; }
		


		if(ar==ELECTRICITY){
			isBuffed=true;
			HP+=100;
			ATK+=10;
		}
		else if(ar==FOREST || ar==MAGMA){
			isDebuffed=true;
			HP-=100;
			ATK-=10;
		}
	}

	

	void levelUp(){
		HP+=50;
		ATK+=7;
		MAG_DEF+=3;
		PHY_DEF+=0;

		base_hp+=50;
		base_atk+=7;
		base_mag_def+=3;
		base_phy_def+=0;
	}

	PokeElectric(int pokemonID, const std::string& name) : Pokemon(pokemonID,name) { 
		HP=500;
		ATK=70;
		MAG_DEF=30;
		PHY_DEF=0;
		base_hp=500;
		base_atk=70;
		base_mag_def=30;
		base_phy_def=0;
	}


	virtual void setElectrified(bool electrified){
		this->electrified = false;
	}
	

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif