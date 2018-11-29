#ifndef POKEGRASS_H
#define POKEGRASS_H

#include "Pokemon.h"
#include <iostream>

class PokeGrass : public Pokemon
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
		target->setRooted(true);


	}

	void getDamaged(){
		
		if(burning){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is burning!!!!"<<std::endl;
				HP-=max(BURN_DAMAGE*2-MAG_DEF,0);
			}
		}
		if(drowning){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is drowning!!"<<std::endl;
				HP-=max(DROWN_DAMAGE-MAG_DEF,0);
			}
		}
		if(electrified){
			if(HP>0) {
				std::cout<<"\t\t\t"<<name<<"("<<HP<<")" <<" is electrified!!"<<std::endl;
				HP-=max(ELECTRIFY_DAMAGE-MAG_DEF,0);
			}
			
		}
		if(rooted){
			std::cout<<"This should not happen(root-root)"<<std::endl;
			
		}
		

	}


	void levelUp(){
		HP+=80;
		ATK+=4;
		MAG_DEF+=0;
		PHY_DEF+=3;

		base_hp+=80;
		base_atk+=4;
		base_mag_def+=0;
		base_phy_def+=3;

	}

	void buff(Arena ar){
		if(isBuffed==true || isDebuffed==true){ return; }


		if(ar==FOREST){
			isBuffed=true;
			HP+=100;
			ATK+=10;
		}
		else if(ar==SKY || ar==MAGMA){
			isDebuffed=true;
			HP-=100;
			ATK-=10;
		}
	}


	PokeGrass(int pokemonID, const std::string& name) : Pokemon(pokemonID,name){
		HP=800;
		ATK=40;
		MAG_DEF=0;
		PHY_DEF=30;
		base_hp=800;
		base_atk=40;
		base_mag_def=0;
		base_phy_def=30;
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