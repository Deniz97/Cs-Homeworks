#ifndef TRAINER_CENTER_H
#define TRAINER_CENTER_H

#include "Trainer.h"
#include "Pokemon.h"
#include "PokeFire.h"
#include "PokeElectric.h"
#include "PokeFlying.h"
#include "PokeGrass.h"
#include "PokeWater.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>




class TrainerCenter
{
public:
	// Public Methods

	TrainerCenter(const std::string& inputFileName){
		Arena arena;
		
		int i,j,a1,a2,p1,p2,p_id,t_id;
		char ignore;
		int trainer_count;
		int pokemon_count;
		
		std::ifstream infile(inputFileName.c_str());
		//std::ifstream infile(inputFileName);
		std::string line,t_name,t_arena,p_name,p_type;
		std::vector<Pokemon*> pokos;
		// new std::vector<*>();
		
		Trainer* temp_trainer;
		Pokemon* temp;

	
		std::getline(infile,line);  
		//std::cout << line<< std::endl;
		
		
		trainer_count= atoi( (line.substr(14)).c_str() );

		std::getline(infile,line);  
		//std::cout << line<< std::endl;  
		pokemon_count= atoi( (line.substr(14)).c_str() );

		
		//std::cout<<trainer_count<<pokemon_count<<std::endl;
		//std::cout << "HERE" << std::endl;  
		std::getline(infile,line);
		//reading trainers and pokos

		for(i=0;i<trainer_count;i++){
			
			std::getline(infile,line);
			a1= line.find("--");
			
			a2 = line.find("--",a1+2);
			
			t_id= atoi(   (line.substr( 0, a1  )).c_str()  );
			t_name= line.substr(  a1+2, a2-a1-2   );
			t_arena = line.substr( a2+2);

			//std::cout<<t_id<<t_name<< t_arena<< std::endl;

			for(j=0;j< pokemon_count ;j++){
				std::getline(infile,line);
				p1= line.find("::");
				
				p2 = line.find("::",a1+2);
				
				p_id= atoi(   (line.substr( 0, p1  )).c_str()  );
				p_name= line.substr(  p1+2, p2-p1-2   );
				p_type = line.substr( p2+2);

				//std::cout<<p_id<<p_name<< p_type<< std::endl;

				if(p_type=="FIRE"){  temp=new PokeFire(p_id,p_name);  }
				else if(p_type=="GRASS"){  temp=new PokeGrass(p_id,p_name); }
				else if(p_type=="FLYING"){  temp=new PokeFlying(p_id,p_name); }
				else if(p_type=="WATER"){  temp=new PokeWater(p_id,p_name); }
				else if(p_type=="ELECTRIC"){  temp=new PokeElectric(p_id,p_name); }
				else{ std::cout<<"This should not happen(trainer center, pokos"<<std::endl; }

				pokos.push_back(temp);



				
			}




			
		
			if(t_arena=="Stadium")
				arena =STADIUM;
			if(t_arena== "Magma")
				arena = MAGMA;
			if(t_arena== "Ocean")
				arena = OCEAN;
			if(t_arena== "ElectriCity")
				arena = ELECTRICITY;
			if(t_arena== "Forest")
				arena = FOREST;
			if(t_arena== "Sky")
				arena = SKY;
		



			temp_trainer = new Trainer(t_id,t_name,arena,pokos);
			//std::cout<<"New trainer"<<temp_trainer->getName()<<" "<<temp_trainer<<std::endl;
			pokos.clear();
			tokos.push_back(temp_trainer);

			std::getline(infile,line);

		}

		

	}
    	~TrainerCenter(){
    		if(!tokos.empty()){
			std::vector<Trainer*>::iterator it = tokos.begin() ;


			for (; it != tokos.end(); ++it){
				(*it)->deletePokos();
				delete *it;
			}
		}

    	}
    
	std::vector<Trainer*>& getAllTrainers(){

		return tokos;

	}

	Trainer* getTrainerWithID(int trainerID){

		std::vector<Trainer*>::iterator it = tokos.begin() ;

		for (; it != tokos.end(); ++it){
			if((*it)->getTrainerID()==trainerID){
				return (*it);
			}
		}
	}

	// Own Methods

private:
	// Own Attributes
	std::vector<Trainer*> tokos;
};

#endif
