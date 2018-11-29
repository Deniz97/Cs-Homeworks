#ifndef REGION_H
#define REGION_H

#include "pokemon.h"
#include <iostream>
#include <exception>

using namespace std;

class Region {
	private:
		// Add private members, methods and constructors here as you need
		Region* left=NULL;
		Region* right=NULL;
		char division;
		int upper[3];
		int lower[3];
		int l_u[3];
		int l_l[3];
		int r_u[3];
		int r_l[3];
		bool is_unit;
		Pokemon* poko=NULL;
		void setDivision(char d){
			division=d;
		}
		void array_copy(int a[3], const int b[3]){
			a[0]=b[0];
			a[1]=b[1];
			a[2]=b[2];
		}
		void helper_partite(char div);
		bool lessThen(const int a[3],const int b[3])const{
			return a[0]<=b[0] and a[1]<=b[1]  and a[2]<=b[2] ;
		}
		bool moreThen(const int a[3],const int b[3])const{
			return a[0]>=b[0] and a[1]>=b[1]  and a[2]>=b[2] ;
		}
		void print_array(const int array[]) const {
			cout<< array[0] << "-" << array[1] << "-" << array[2]<<endl;
		}
		void deleteArea(int[3],int[3],Region&,char);
		void populateArea(int[3],int[3],Region&,char);

	public:
		// Do NOT make any modifications below
		Region(const int[3], const int[3]);
		Region(const Region&);
		~Region();
		int getMinBorder(char) const;
		int getMaxBorder(char) const;
		void placePokemon(const Pokemon&, int, int, int);
		Pokemon& operator()(int, int, int);
		int getPokemonCount(const int[3], const int[3]) const;
		Region crop(const int[3], const int[3]) const;
		void patch(Region);
		Region& operator=(const Region& r){

			if(left!=NULL){	this->left->~Region(); }
			if(right!=NULL){   this->right->~Region(); }
			if(poko!=NULL) { delete this->poko; }

			array_copy(upper,r.upper);
			array_copy(lower,r.lower);
			this->division=r.division;
			array_copy(l_u,r.l_u);
			array_copy(l_l,r.l_l);
			array_copy(r_u,r.r_u);
			array_copy(r_l,r.r_l);
			
			this->is_unit=r.is_unit;
			if(r.is_unit){
				poko=new Pokemon( *(r.poko));
			}
			if(r.left!=NULL){
				this->left=new Region( *(r.left));
			}
			else{ this->left=NULL;}

			if(r.right!=NULL){
				this->right=new Region( *(r.right));
			}
			else{ this->right=NULL;}
			

			return *this;

		}
};

class pokemonException: public exception {
 	virtual const char* what() const throw() {
    		return "There does not exist any pokemon in the given coordinates!";
	}
};


	
	void Region::helper_partite(char divi){
		if(!is_unit){

		array_copy(l_l,lower);
		array_copy(r_u,upper);
		array_copy(l_u,upper);
		array_copy(r_l,lower);

		if(divi=='x'){
			int fark=(upper[0]-lower[0]+1)/2;
			l_u[0]=upper[0]-fark;
			r_l[0]=lower[0]+fark;
		}
		else if(divi=='y'){
			int fark=(upper[1]-lower[1]+1)/2;
			l_u[1]=upper[1]-fark;
			r_l[1]=lower[1]+fark;
		}
		else if(divi=='z'){
			int fark=(upper[2]-lower[2]+1)/2;
			l_u[2]=upper[2]-fark;
			r_l[2]=lower[2]+fark;
		}

		}
	}

	Region::
	Region(const int l[3], const int u[3]){
		array_copy(upper,u);
		array_copy(lower,l);
		
		left=NULL;
		right=NULL;
		division='x';
		poko=NULL;
		if(u[0]==l[0] and u[1]==l[1] and u[2]==l[2] ){
			
			is_unit=true;
		}
		else{ 
			is_unit=false;
		}
		helper_partite('x');


	}
	
	Region::
	Region(const Region& r){
		
		if(left!=NULL){	this->left->~Region(); }
		if(right!=NULL){   this->right->~Region(); }
 		if(poko!=NULL) { delete this->poko; }
		delete left; delete right;
		//this->~Region();
		array_copy(upper,r.upper);
		array_copy(lower,r.lower);
		this->division=r.division;
		
		array_copy(l_u,r.l_u);
		array_copy(l_l,r.l_l);
		array_copy(r_u,r.r_u);
		array_copy(r_l,r.r_l);
		
		this->is_unit=r.is_unit;
		if(r.is_unit){
			poko=new Pokemon( *(r.poko));
		}
		if(r.left!=NULL){
			this->left=new Region( *(r.left));
		}
		else{ this->left=NULL;}

		if(r.right!=NULL){
			this->right=new Region( *(r.right));
		}
		else{ this->right=NULL;}
	}
	
	Region::
	~Region(){
		//cout<<"Deleting a region: "<<this<<endl;
		if(is_unit and poko!=NULL){
		 //cout<<"Deleting the poko: "<<poko->getName()<<endl;
		  delete poko;}
		if(left!=NULL){  delete left; }
		if(right!=NULL){  delete right;}
	}
	
	
	int Region::getMinBorder(char c) const{
		if(c=='x'){
			return lower[0];
		}
		else if(c=='y'){
			return lower[1];
		}
		else if(c=='z'){
			return lower[2];
		}
		else{ return -1;}
	}
	
	int Region::getMaxBorder(char c) const{
		if(c=='x'){
			return upper[0];
		}
		else if(c=='y'){
			return upper[1];
		}
		else if(c=='z'){
			return upper[2];
		}
		else{ return -1;}
	}
	
	void Region::placePokemon(const Pokemon& new_poko, int x, int y, int z){
		if(is_unit==true){ 
			//cout<<"is unit,placing the pokemon: "<<new_poko.getName()<< endl; 
			poko= new Pokemon(new_poko);
			//cout<<"placed the pokemon: "<<poko->getName()<< endl;
			return;
		}	
		
		//partite baby
		helper_partite(division);

			
		//set next division
		char next_div;
		if(division=='x'){ next_div='y'; }
		if(division=='y'){ next_div='z'; }
		if(division=='z'){ next_div='x'; }

		if( x>=l_l[0] and x<=l_u[0] and y>=l_l[1] and y<=l_u[1] and z>=l_l[2] and z<=l_u[2]   ){
			if(left==NULL){
				//cout << "Creating new left" << endl;
				left=new Region(l_l,l_u);
				left->setDivision(next_div);
			}
			//cout<<"going left"<<endl;
			
			left->placePokemon(new_poko,x,y,z);	

			

		}
		else if(   x>=r_l[0] and x<=r_u[0]  and y>=r_l[1] and y<=r_u[1]  and z>=r_l[2] and z<=r_u[2] ){
			
			if(right==NULL){
			//	cout << "Creating new right" << endl;
				right=new Region(r_l,r_u);
			}
			//cout<<"going right"<<endl;

			right->setDivision(next_div);
			right->placePokemon(new_poko,x,y,z);
		}
		else{
			cout<<"This should not happen(placing pokemon)"<<endl;
		}
		


	}
	
	
	Pokemon& Region::operator()(int x, int y, int z){
		
		
		/*
			cout<<"upper: ";
		print_array(upper);
		cout<<"lower: ";
		print_array(lower);
		cout<<"IS unit? "<<is_unit<<endl;
		cout<<"poko: "<< poko << " and "<<poko->getName()<<endl;
*/
		if(is_unit and poko!=NULL){
			//cout<<"JUST CATHCED: ";
			//cout<<poko->getName()<<endl;
			//cout<<"addr= "<<poko<<endl;
			return  *poko;
		}

		
		if(left!=NULL){
			//cout<<"left not null"<<endl;
			if( x>=l_l[0] and x<=l_u[0] and y>=l_l[1] and y<=l_u[1] and  z>=l_l[2] and z<=l_u[2]   ){
				//cout<<"going left"<<endl;
				Pokemon& temp = (*left)(x,y,z);
				if(left->right==NULL and left->left==NULL){ left->poko=NULL;delete left;left=NULL;}
				
				return temp;

			}
		}
		if(right!=NULL){
			//cout << "right not null"<<endl;
			if(   x>=r_l[0] and x<=r_u[0] and y>=r_l[1] and y<=r_u[1] and z>=r_l[2] and z<=r_u[2] ){
				//cout<< "going right"<<endl;
				Pokemon& temp = (*right)(x,y,z);
				
				if(right->right==NULL and right->left==NULL){right->poko=NULL;delete right; right=NULL;}
				return temp;
			}
		}
		throw pokemonException(); 

	}
	

	int Region::getPokemonCount(const int a[3], const int b[3]) const{
		
		if(is_unit){ 
			//cout<<"found pokemon count at: ";
			//print_array(upper);
			//print_array(lower);
			
			if(lessThen(upper,b) && moreThen(lower,a)  ){ 
				//cout<<"End a pokemon"<<endl;
				//cout<<"NULL IS: "<< (poko==NULL)<<endl;
				//cout<<"poko: "<<poko<<" ";

				//cout << "Returning"<<endl;
				return 1; 
				
			}
			else { return 0;}

		}

		

		if(left!=NULL and right!=NULL){
			//cout<<"going left"<<endl;
			int aa= left->getPokemonCount(a,b) ;
			//cout<<"going right"<<endl;
			int bb = right->getPokemonCount(a,b);
			//cout<<"returning"<<endl;
			return aa+bb;

		}
		else if(left!=NULL){
			//cout<<"going left"<<endl;
			 int aa= left->getPokemonCount(a,b);
			 //cout<<"returning"<<endl;
			 return aa;
		}
		else if(right!=NULL){
			//cout<<"going right"<<endl;
			int aa= right->getPokemonCount(a,b);
			//cout<<"returning"<<endl;
			return aa;
		}
		else{
			return 0;
		}
	}
	
	Region Region::crop(const int a[3], const int b[3]) const{
		if(a[0]==lower[0] and a[1]==lower[1] and a[2]==lower[2] and b[0]==upper[0] and b[1]==upper[1] and b[2]==upper[2]   ){
			//cout<<"found what to crop"<<endl;
			//cout<<"DENEME "<<this<<endl;
			return Region(*this);
		}
		if(left!=NULL and lessThen(b,l_u) and moreThen(a,l_l) ){
			return left->crop(a,b);
		}
		if(right!=NULL  and lessThen(b,r_u) and moreThen(a,r_l)){
			return right->crop(a,b);
		}
		cout<<"Should not be possible(crop)"<<endl;
		
	}
	
	void Region::deleteArea(int low[3], int up[3], Region& reg, char divi){
		int pok;
		int fark=0;
		if(up[0]==low[0] and up[1]==low[1] and up[2]==low[2]){
			if( reg.getPokemonCount(low,up)>0){
				delete &reg(low[0],low[1],low[2]);
				
				
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

			while(fark==0){
				if(divi=='x'){
					fark=(up[0]-low[0]+1)/2;
					l_u[0]=up[0]-fark;
					r_l[0]=low[0]+fark;
					if(fark==0){ divi='y';}
				}
				else if(divi=='y'){
					fark=(up[1]-low[1]+1)/2;
					l_u[1]=up[1]-fark;
					r_l[1]=low[1]+fark;
					if(fark==0){ divi='z';}
				}
				else if(divi=='z'){
					fark=(up[2]-low[2]+1)/2;
					l_u[2]=up[2]-fark;
					r_l[2]=low[2]+fark;
					if(fark==0){ divi='x';}
				}
			}
			deleteArea(l_l,l_u,reg,next_div);
			deleteArea(r_l,r_u,reg,next_div);
		}
	}

	void Region::populateArea(int low[3], int up[3], Region& reg, char divi){
		//cout<<"upper: ";
		//print_array(up);
		//cout<<"lower: ";
		//print_array(low);
		int fark=0;
		
		int pok;
		if(up[0]==low[0] and up[1]==low[1] and up[2]==low[2]){
			if( reg.getPokemonCount(low,up)>0){
				//cout<<"PLACING A POKEMON"<<endl;
				Pokemon& temp = reg(low[0],low[1],low[2]);
				
				this->placePokemon( temp, low[0],low[1],low[2]);
				reg.placePokemon(temp,  low[0],low[1],low[2]     );
				delete &temp;
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
		while(fark==0){
			if(divi=='x'){
				fark=(up[0]-low[0]+1)/2;
				l_u[0]=up[0]-fark;
				r_l[0]=low[0]+fark;
				if(fark==0){ divi='y';}
			}
			else if(divi=='y'){
				fark=(up[1]-low[1]+1)/2;
				l_u[1]=up[1]-fark;
				r_l[1]=low[1]+fark;
				if(fark==0){ divi='z';}
			}
			else if(divi=='z'){
				fark=(up[2]-low[2]+1)/2;
				l_u[2]=up[2]-fark;
				r_l[2]=low[2]+fark;
				if(fark==0){ divi='x';}
			}
		}
			populateArea(l_l,l_u,reg,next_div);
			populateArea(r_l,r_u,reg,next_div);

		}
	}

	void Region::patch(Region reg){
		deleteArea(reg.lower,reg.upper,*this,'x');
		populateArea(reg.lower,reg.upper,reg,'x');




	}
	
	
#endif