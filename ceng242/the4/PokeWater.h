#ifndef POKEWATER_H
#define POKEWATER_H

#include "Pokemon.h"
#include <iostream>

class PokeWater : public Pokemon
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
		target->setDrowning(true);


	}

	void getDamaged(){
		
		if(burning){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is burning!!"<<std::endl;
				HP-=max(BURN_DAMAGE-MAG_DEF,0);
			}

		}
		if(drowning){
			
			std::cout<<"This should not happen(drown-drown)"<<std::endl;
		}
		if(electrified){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is electrified!!!!"<<std::endl;
				HP-=max(ELECTRIFY_DAMAGE*2-MAG_DEF,0);
			}
			
		}
		if(rooted){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is rooted!!"<<std::endl;
				HP-=max(ROOT_DAMAGE-MAG_DEF,0);
			}
		}
	

	}

	void levelUp(){
		HP+=70;
		ATK+=5;
		MAG_DEF+=1;
		PHY_DEF+=2;
		
		base_hp+=70;
		base_atk+=5;
		base_mag_def+=1;
		base_phy_def+=2;

	}

	void buff(Arena ar){
		if(isBuffed==true || isDebuffed==true){ return; }


		if(ar==OCEAN){
			isBuffed=true;
			HP+=100;
			ATK+=10;
		}
		else if(ar==FOREST || ar==ELECTRICITY){
			isDebuffed=true;
			HP-=100;
			ATK-=10;
		}
	}


	PokeWater(int pokemonID, const std::string& name) : Pokemon(pokemonID,name){
		HP=700;
		ATK=50;
		MAG_DEF=10;
		PHY_DEF=20;
		base_hp=700;
		base_atk=50;
		base_mag_def=10;
		base_phy_def=20;
	}


	virtual void setDrowning(bool drowning){
		this->drowning=false;
	}



protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif