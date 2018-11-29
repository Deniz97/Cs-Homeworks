#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Trainer.h"

#include <vector>
#include <iostream>
#include "Enums.h"

class Tournament
{
public:
	// Public Methods

	Tournament(const std::string& tournamentName){
		this->tournamentName=tournamentName;
	}
	~Tournament(){
		
		
	}

	// Trainer count will always be 2^n.
  	  void registerTrainers(const std::vector<Trainer*>& trainers){
  	  	
  	  	this->trainers = trainers;
  	  }
    
    	// Commence the tournament, and return the champion.
	Trainer* commence(){
		//std::cout<<"starting commence"<<std::endl;
		//std::cout<< trainers[0]<<" "<<trainers[1] <<std::endl;
		//std::vector<Trainer*>::iterator it = trainers.begin() ;
		//std::cout<< *it<< " "<<*(it+1) <<std::endl;


		std::vector<Trainer*> temp;
		int i,temp_int;
		int winner=0;
		while(trainers.size()>1){
			//std::cout<<"in while"<<std::endl;
			//std::cout<<"Trainer count A:"<<trainers.size()<<std::endl;
			i=0;
			while(i<trainers.size()/2){
				std::cout<<"Started Round: "<<i<<" vs "<<trainers.size()-i-1<<std::endl;
				std::cout<<"\t"<<trainers[i]->getName()<<" vs "<<trainers[trainers.size()-1-i]->getName()<<": "<<Helpers::getArenaName(  trainers[i]->getFavoriteArena() )<<std::endl;
				winner=0;
				temp_int=0;
				//std::cout<<"in second while"<<std::endl;
				temp_int= duelBetween(trainers[i], trainers[trainers.size()-1-i], trainers[i]->getFavoriteArena() );
				if(temp_int==1){ std::cout<<"\t"<<"WinnerT:"<<trainers[i]->getName()<<std::endl<<std::endl;	}
				else if(temp_int==-1){ std::cout<<"\t"<<"WinnerT:"<<trainers[ trainers.size()-i-1 ]->getName()<<std::endl<<std::endl;	}
				winner += temp_int;
				//revive all pokos
				//std::cout<<"finished first match"<<std::endl;
				//std::cout<< trainers[1]<<std::endl;
				std::cout<<"\t"<<trainers[trainers.size()-1-i]->getName()<<" vs "<<trainers[i]->getName()<<": "<<Helpers::getArenaName(  trainers[trainers.size()-i-1]->getFavoriteArena() )<<std::endl;
				temp_int = duelBetween( trainers[trainers.size()-i-1], trainers[i], trainers[trainers.size()-1-i]->getFavoriteArena());
				if(temp_int==-1){ std::cout<<"\t"<<"WinnerT:"<<trainers[i]->getName()<<std::endl<<std::endl;	}
				else if(temp_int==1){ std::cout<<"\t"<<"WinnerT:"<<trainers[ trainers.size()-i-1 ]->getName()<<std::endl<<std::endl;	}
				winner += temp_int*-1;
				//revive all pokos
				//std::cout<<"finished second match"<<std::endl;
				//std::cout<< trainers[1]<<std::endl;
				std::cout<<"\t"<<trainers[i]->getName()<<" vs "<<trainers[trainers.size()-1-i]->getName()<<": "<<"Stadium"<<std::endl;
				temp_int = duelBetween(trainers[i], trainers[trainers.size()-i-1], STADIUM);
		
				if(temp_int==1){ std::cout<<"\t"<<"WinnerT:"<<trainers[i]->getName()<<std::endl<<std::endl;;	}
				else if(temp_int==-1){ std::cout<<"\t"<<"WinnerT:"<<trainers[ trainers.size()-i-1 ]->getName()<<std::endl<<std::endl;	}
				winner += temp_int;
				//std::cout<<"finished third match"<<std::endl;
				//std::cout<< trainers[1]<<std::endl;
				//revive all pokos
				if(winner>0){
					//std::cout<< "AAA"<<std::endl;
					std::cout<<"Round Winner: "<<trainers[i]->getName()<<"!"<<std::endl;
					temp.push_back(trainers[i]);
				}
				else if(winner<0){
					//std::cout<< "BBB"<<std::endl;
					std::cout<<"Round Winner: "<<trainers[trainers.size()-i-1]->getName()<<"!"<<std::endl;
					temp.push_back(trainers[trainers.size()-i-1] );

				}
				else{ std::cout<<"This should not happen(commence)"<<std::endl; }
				//std::cout<< temp[0] <<std::endl;
				i++;

			}
			trainers.clear();
			trainers=temp;
			temp.clear();
			//std::cout<<"Trainer count B:"<<trainers.size()<<std::endl;
		}
		//std::cout<<"finished while"<<std::endl;
		//std::cout<<"Trainer champ= "<<trainers[0]<<std::endl;
		//std::cout<<"Trainer: "<<trainers[0]->getName()<<std::endl;
		return *(trainers.begin());
	}

	// Return 1 if Trainer1 wins.
	// Return -1 if Trainer2 wins.
	// It may be called from main.cpp, aside from a Tournament.
	int duelBetween(Trainer* t1, Trainer* t2, Arena curr_arena){
		bool t1first=true;
		int t1pc=t1->pokoCount();
		int t2pc=t2->pokoCount();
		int tp1=0;
		int tp2=0;
		int winner;

		while( t1pc>0 && t2pc>0){
			
			if(t1first){
				winner = duelBetween(t1->getPoko(tp1), t2->getPoko(tp2), curr_arena);
				if(winner==1){
					t1->getPoko(tp1)->levelUp();
					tp2+=1;
					t2pc-=1;
					t1first=false;
				}
				else if(winner==-1){
					t2->getPoko(tp2)->levelUp();
					tp1+=1;
					t1pc-=1;
					t1first=true;
				}
				else{ std::cout<<"This should not happen(duel between trainers)"<<std::endl; }
			}
			else if(!t1first){
				winner = duelBetween( t2->getPoko(tp2), t1->getPoko(tp1), curr_arena);
				if(winner==1){
					t2->getPoko(tp2)->levelUp();
					tp1+=1;
					t1pc-=1;
					t1first=true;
				}
				else if(winner==-1){
					t1->getPoko(tp1)->levelUp();
					tp2+=1;
					t2pc-=1;
					t1first=false;


				}
				else{ std::cout<<"This should not happen(duel between trainers)"<<std::endl; }


			}

		}
		t1->revivePokos();
		t2->revivePokos();
		if(t1pc==0){
			return -1;
		}
		else if(t2pc==0){
			return 1;
		}
		else{ std::cout<<"This should not happen(duel between trainers finish)"<<std::endl; return 0; }
	}

    // Getters

    const std::string& getTournamentName() const{
    	return tournamentName;
    }
	// Own Methods
	
private:
	std::string tournamentName;
	std::vector<Trainer*> trainers;

	// Return 1 if Pokemon1 wins.
	// Return -1 if Pokemon2 wins.
	// It won't (can't) be called from main.cpp, this method is for your own convenience.
	int duelBetween(Pokemon *p1, Pokemon  *p2, Arena ca){

		p1->buff(ca);
		p2->buff(ca);
		while(p1->getHP()>0 && p2->getHP()>0){

			if(p1->getHP()>0){
				p1->getDamaged();
			}
			else{break; }
			if(p1->getHP()>0){
				p1->attackTo(p2, ca);
			}
			else{  break;}
			if(p2->getHP()>0){
				p2->getDamaged();
			}
			else{ break; }
			if(p2->getHP()>0){
				p2->attackTo(p1, ca);
			}
			else{break;}

			if(p1->getHP()<=0){ break; }
		}
		if(p1->getHP()<=0){ std::cout<<"\t\t"<<"WinnerP:"<<p2->getName()<<std::endl; return -1; }
		if(p2->getHP()<=0){ std::cout<<"\t\t"<<"WinnerP:"<<p1->getName()<<std::endl; return 1; }

	}

	// Own Attributes

};

#endif
