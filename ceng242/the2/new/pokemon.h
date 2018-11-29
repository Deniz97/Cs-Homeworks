#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <iostream>

using namespace std;

class Pokemon {
	private:
		// Add private members, methods and constructors here as you need
		string name;
		string type;
		int eval;
		int exp_point;
		bool is_owned;
		int helper_winner(string a,string b);
	public:
		
		// Do NOT make any modifications below
		mutable int t_ref_cnt;
		Pokemon(const string&, const string&, int);
		Pokemon(const Pokemon&);
		~Pokemon();
		const string& getName() const{

			return this->name;
		}
		bool operator>>(const Pokemon& old_poko){
			if(this->exp_point>=this->eval and this->eval!=-1){
			this->name=old_poko.name;
			this->type=old_poko.type;
			this->eval=old_poko.eval;
			return true;
			}
			return false;
		}
		friend Pokemon operator&(Pokemon& bir, Pokemon& iki){
			
			int sonuc=-1;
			string a=bir.type;
			string b=iki.type;

			if(a=="flying") a="Fl";
			if(a=="fire") a="Fi";
			if(a=="grass") a="G";
			if(a=="water") a="W";
			if(a=="electric") a="E";

			if(b=="flying") b="Fl";
			if(b=="fire") b="Fi";
			if(b=="grass") b="G";
			if(b=="water") b="W";
			if(b=="electric") b="E";

			if(a=="Fl"){
				if(b=="W" or b=="E"){
					sonuc= 2;
				}
				else{ sonuc= 1;}
			}
			else if(a=="E"){
				if(b=="Fi" or b=="G"){
					sonuc= 2;
				}
				else{ sonuc= 1; }

			}
			else if(a=="G"){
				if(b=="Fi" or b=="Fl"){
					sonuc= 2;
				}
				else{ sonuc= 1; }
				
			}
			else if(a=="W"){
				if(b=="G" or b=="E"){
					sonuc= 2;
				}
				else{ sonuc= 1;}
				
			}
			else if(a=="Fi"){
				if(b=="W" or b=="Fl"){
					sonuc= 2;
				}
				else{sonuc= 1;}
			}
			else{
				cout << "ERROR no known pokemon type";
				sonuc= -1;
			}


		bir.exp_point+=1;
		iki.exp_point+=1;
		if(sonuc==1){
			
			return bir;
		}
		else if(sonuc==2){
			
			return iki;
		}

		}
		Pokemon& operator=(const Pokemon&);
};

//CLASS IS FINISHED HERE


	Pokemon::
	Pokemon(const string & n, const string & t, int e){
		this->name=n;
		this->type=t;
		this->eval=e;
		this->exp_point=0;
		this->is_owned=false;
		 t_ref_cnt =0;
	}
	
	Pokemon::
	Pokemon(const Pokemon &  old_poko){
		this->name=old_poko.name;
		this->type=old_poko.type;
		this->eval=old_poko.eval;	
		this->exp_point=old_poko.exp_point;
		this->is_owned=false;
		 this->t_ref_cnt=0;

	}
	
	Pokemon::~Pokemon(){
		
	}
	

	


	
	
	Pokemon& Pokemon::operator=(const Pokemon & old_poko){
		this->name=old_poko.name;
		this->type=old_poko.type;
		this->eval=old_poko.eval;	
		this->exp_point=old_poko.exp_point;
		this->is_owned=false;
		this->t_ref_cnt=0;
		return *this;

	}

#endif