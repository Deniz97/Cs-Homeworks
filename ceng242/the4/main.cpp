#include "TrainerCenter.h"
#include "Tournament.h"
#include "Trainer.h"

#include "PokeFire.h"
#include "PokeWater.h"
#include "PokeGrass.h"

#include <iostream>
#include <vector>

int main(int argv, char** argc)
{
	if(argv < 2)
	{
		return -1;
	}

	TrainerCenter newCenter(argc[1]);
	//std::cout<<"Getting trainers"<<std::endl;
	std::vector<Trainer*> allTrainers = newCenter.getAllTrainers();
	//std::cout<<"Got trainers"<<std::endl;
	
	Tournament newTournament("MegaTournament");
	//std::cout<<"constructed Tournament"<<std::endl;
	newTournament.registerTrainers(allTrainers);
	//std::cout<<"registered trainers"<<std::endl;
	
	Trainer *champion = newTournament.commence();
	//std::cout<<"found the champion"<<std::endl;

	std::cout << newTournament.getTournamentName() << " has finished! The champion is " << champion->getName() << "." << std::endl;

	return 0;
}
