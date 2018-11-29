#ifndef _TAB_H_
#define _TAB_H_

#include <iostream>
#include <string>
#include "Stack.hpp"

using namespace std;

class Tab{

private:
	string current_page;
	Stack<string> prevPages;
 	Stack<string> nextPages;
 	int closed_index;

public:
	Tab(){
		current_page="";
		prevPages=Stack<string>();
		nextPages=Stack<string>();
		closed_index=-1;
	}

	int getClosedIndex() const{
		return closed_index;
	}
	void setClosedIndex(int index) {
		closed_index=index;
	}
	string getCurentPage() const{
		return current_page;
	};
	void setCurrentPage(string url){
		if(current_page!=""){
			prevPages.push(current_page);
			nextPages.clear();
		}
		current_page=url;
	}
	void back(){
		if(!prevPages.isEmpty()){
			nextPages.push(current_page);
			current_page = prevPages.pop();
		}
		else {
			throw out_of_range("No previous page");
		}
	}
	void forward(){
			if(!nextPages.isEmpty()){
			prevPages.push(current_page);
			current_page=nextPages.pop();
			}
			else {
				throw out_of_range("No page to forward");
			}
	}
	void displayDetails(){
		int counter=0;
		string toPrint;
		while(!nextPages.isEmpty()){
			prevPages.push(nextPages.pop());
			counter++;
		}

		while(counter>0){
			toPrint = prevPages.pop();
			cout << toPrint << endl;
			nextPages.push(toPrint);
			counter--;
		}
		counter=0;
		cout << "> " << current_page <<endl;
		while(!prevPages.isEmpty()){
			toPrint=prevPages.pop();
			cout<< toPrint << endl;
			nextPages.push(toPrint);
			counter++;
		}
		while(counter>0){
			prevPages.push(nextPages.pop());
			counter--;
		}

	}
};

#endif