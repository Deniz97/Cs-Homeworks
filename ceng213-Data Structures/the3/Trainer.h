#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <vector>

#include "Pokemon.h"

class Trainer
{
public:
	// Public Methods
	Trainer(int trainerID, const std::string& name, Arena favoriteArena, std::vector<Pokemon *>& pokemons){

		this->trainerID = trainerID;
		this->name=name;
		this->favoriteArena=favoriteArena;
		this->pokemons=pokemons;

	}
	~Trainer(){
		/*
		std::vector<Pokemon*>::iterator it = pokemons.begin() ;

		for (; it != pokemons.end(); ++it){
			delete *it;
		}
		*/
	}

	// Getters

	int getTrainerID() const{
		return trainerID;
	}
	const std::string& getName() const{
		return name;
	}
	Arena getFavoriteArena() const{
		return favoriteArena;
	}

	// Own Methods

	int pokoCount(){
		return pokemons.size();
	}

	Pokemon* getPoko(int i){
		return pokemons[i];
	}

	void revivePokos(){
		std::vector<Pokemon*>::iterator it = pokemons.begin() ;

		for (; it != pokemons.end(); ++it){
			(*it)->revive();
		}
	}

	void deletePokos(){
		if(!pokemons.empty()){
			std::vector<Pokemon*>::iterator it = pokemons.begin() ;

			for (; it != pokemons.end(); ++it){
				delete *it;
			}
		}
	}

private:
	int trainerID; 		// Unique
	std::string name;
	Arena favoriteArena;

	std::vector<Pokemon *> pokemons;

	// Own Attributes
	
};

#endif
