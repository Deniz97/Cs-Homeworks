#ifndef TRAINER_H
#define TRAINER_H

#include "pokemon.h"
#include "region.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Trainer {
	private:
		// Add private members, methods and constructors here as you need
		vector<const Pokemon*> pokemons;
		string name;
		int upper[3];
		int lower[3];
		void array_copy(int a[3], const int b[3]){
			a[0]=b[0];
			a[1]=b[1];
			a[2]=b[2];
		}
		
		bool lessThen(const int a[3],const int b[3])const{
			return a[0]<=b[0] and a[1]<=b[1]  and a[2]<=b[2] ;
		}
		bool moreThen(const int a[3],const int b[3])const{
			return a[0]>=b[0] and a[1]>=b[1]  and a[2]>=b[2] ;
		}
		void helper_scan(int low[3],int up[3],Region& reg,char divi);
		void print_array(const int array[]) const {
			cout<< array[0] << "-" << array[1] << "-" << array[2]<<endl;
		}

	public:
		// Do NOT make any modifications below
		Trainer(const string&, const Pokemon&, const int[3], const int[3]);
		Trainer(const Trainer&);
		~Trainer();
		void catchPokemon(const Pokemon& newPokemon) {
			//cout<<"In vector: "<<&newPokemon<<endl;
			 pokemons.push_back(&newPokemon);
		}
		void scanRegion(Region&);
		
		friend ostream& showPokemons(ostream& os, const Trainer& t){
			// cout<<"Showing Pokemons"<<endl;
			 std::vector<const Pokemon*>::const_iterator it = t.pokemons.begin();
			// cout<<"AA"<<endl;
			

			 for ( ; it != t.pokemons.end(); ++it){
	    			os << (*it)->getName()<<endl;
	    		}
		}
};



	
	Trainer::
	Trainer(const string& n, const Pokemon& p, const int l[3], const int u[3]){
		array_copy(upper,u);
		array_copy(lower,l);
		
		this->name=n;
		Pokemon* temp=new Pokemon(p);
		pokemons.push_back(temp);
	}
	
	Trainer::
	Trainer(const Trainer& oldt){
		array_copy(upper,oldt.upper);
		array_copy(lower,oldt.lower);
		
		this->name=oldt.name;
		
		pokemons.resize(oldt.pokemons.size());

		for(unsigned i = 0; i < oldt.pokemons.size(); ++i){
  			pokemons[i] = new Pokemon(*(oldt.pokemons[i]));
  		}
	
	}
	
	Trainer::
	~Trainer(){
		//cout<<"Deleting pokemons for: "<<name<<endl;
		 std::vector<const Pokemon*>::const_iterator it = pokemons.begin();
		// cout<<"AA"<<endl;
		 
		 
			 for ( ; it != pokemons.end(); ++it){
    			
		 	//cout<<"poko: "<<*it;
    			//cout<< ' ' << (*it)->getName()<<endl;;
    			delete (*it);
    			
    		}

	}
	
	void Trainer::helper_scan(int low[3],int up[3],Region& reg,char divi){
		int pok;
		if(up[0]==low[0] and up[1]==low[1] and up[2]==low[2]){
			if( reg.getPokemonCount(low,up)>0){
				Pokemon & temp = reg(low[0],low[1],low[2]);
				//cout<<"Adding a pokemon to trainer: "<<&temp<<endl;
				catchPokemon( temp);
				
			}
			return;
		}
		int l_u[3],l_l[3],r_l[3],r_u[3];
		char next_div;
		if(divi=='x'){ next_div='y'; }
		if(divi=='y'){ next_div='z'; }
		if(divi=='z'){ next_div='x'; }

		pok = reg.getPokemonCount(low,up);

		if(pok!=0){

			array_copy(l_l,low);
			array_copy(r_u,up);
			array_copy(l_u,up);
			array_copy(r_l,low);

			if(divi=='x'){
				int fark=(up[0]-low[0]+1)/2;
				l_u[0]=up[0]-fark;
				r_l[0]=low[0]+fark;
			}
			else if(divi=='y'){
				int fark=(up[1]-low[1]+1)/2;
				l_u[1]=up[1]-fark;
				r_l[1]=low[1]+fark;
			}
			else if(divi=='z'){
				int fark=(up[2]-low[2]+1)/2;
				l_u[2]=up[2]-fark;
				r_l[2]=low[2]+fark;
			}
			helper_scan(l_l,l_u,reg,next_div);
			helper_scan(r_l,r_u,reg,next_div);

			
		}
	}
	
	void Trainer::scanRegion(Region& reg){
		helper_scan(lower,upper,reg,'x');

	}

#endif