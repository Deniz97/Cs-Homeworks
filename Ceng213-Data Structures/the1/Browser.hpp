#ifndef _BROWSER_H_
#define _BROWSER_H_

#include <string>
#include <stdexcept>
#include <cstdlib>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Tab.hpp"

class Browser{

    private:
        int curr_index;
        int tab_count;
        LinkedList<Tab> pages;
        Stack<Tab> closedPages;

public:

	Browser(){
		//pages=LinkedList<Tab>();
        		closedPages= Stack<Tab>();
        		curr_index=-1;
        		tab_count=0;
	}
	void handleTask(string line){

	        		string token = line.substr(0, line.find(" ")); 
	      		string token2 =line.substr(line.find(" ")+1,line.length()-token.length());
	        		if(token=="open_new_page"){
	        			openNewPage(token2);
        			}
        			else if(token=="open_link"){
	        			openLink(token2);	
	        		}
        			else if(token=="open_link_in_new_tab"){
	        			openLinkInNewTab(token2);	
	        		}
        			else if(token=="close_tab"){
	        			closeTab(atoi(token2.c_str()));
	        		}
        			else if(token=="reopen_closed_tab"){
	        			reopenClosedTab();	
	        		}
        			else if(token=="move_tab"){
	        			string tmp = token2.substr(0,token2.find(" "));
	        			string tmp2 = token2.substr(token2.find(" ")+1,token2.length()-tmp.length());
	        			moveTab(  atoi(tmp.c_str()),atoi(  tmp2.c_str() ) );
	        		}
        			else if(token=="display"){
	        			display();
	        		}
        			else if(token=="select_tab"){
	        			selectTab(atoi(token2.c_str()));	
	        		}
        			else if(token=="display_tab_details"){
	        			displayTabDetails();
	        		}
        			else if(token=="close_selected_tab"){ 
	        			closeSelectedTab();
	        		}
        			else if(token=="back"){
	        			back();
	        		}
        			else if(token=="forward"){
	        			forward();
	        		}
        			else { throw out_of_range("YANLIS INPUT AMK");}
        		
	 }
    	

	void openNewPage(string url){
		Tab* tmp=new  Tab();
		tmp->setCurrentPage(url);
		pages.pushBack(*tmp);
		tab_count++;
		curr_index=tab_count-1;
	}
	void openLink(string url){
		pages.getNodePtrAt(curr_index)->getDataPtr()->setCurrentPage(url);
	}
	void openLinkInNewTab(string url){
		
		if(curr_index==-1){
			throw out_of_range("No tabs opened yet, use open_new_page");
		}
		Tab* tmp=new Tab();
		tmp->setCurrentPage(url);
		curr_index++;
		pages.insertAt(curr_index,*tmp);
		tab_count++;
	}
	void closeTab(int index){
		if(index>=tab_count or index<0){
			throw out_of_range("wrong input to close tab");
		}
		if(index==curr_index){
			closeSelectedTab();
			return;
		}
		Tab* dummy = new Tab();
		dummy =pages.getNodePtrAt(index)->getDataPtr();
		dummy->setClosedIndex(index);
		closedPages.push( *dummy );
		pages.eraseFrom(index);
		tab_count--;
		if(index<curr_index){ curr_index--; }
		
		
	}
	void reopenClosedTab(){
		curr_index = closedPages.top().getClosedIndex();
		pages.insertAt(curr_index, closedPages.pop());
		tab_count++;
	}
	void moveTab(int from, int to){
		if(to>=tab_count or from>=tab_count or to<0 or from<0){
			throw out_of_range("wrong input to move tab");
		}
		curr_index=to;
		int tmp;
		if(to<from){
			pages.insertAt(to,pages.getNodeAt(from).getData());
			pages.eraseFrom(from+1);	
		}
		else if(to>from){
			pages.insertAt(to+1,pages.getNodeAt(from).getData());
			pages.eraseFrom(from);
		}
		
	}
	void display(){
		cout << "CURRENT TAB: " <<curr_index<< endl;
		cout << pages.getNodePtrAt(curr_index)->getDataPtr()->getCurentPage() << endl;
		cout <<  "OPEN TABS: "<< tab_count << endl;
		for(int i=0;i<tab_count;i++){

			cout << pages.getNodeAt(i).getData().getCurentPage() << endl;
		}
		cout << "CLOSED TABS: " << closedPages.getSize() <<endl;
		Stack<Tab> dummy;
		while(!closedPages.isEmpty()){
			cout << closedPages.top().getCurentPage() << endl;
			dummy.push(closedPages.pop());
		}
		while(!dummy.isEmpty()){
			closedPages.push(dummy.pop());
		}

	}
	void selectTab(int index){
		curr_index=index;
		
	}
	void displayTabDetails(){
		pages.getNodePtrAt(curr_index)->getDataPtr()->displayDetails();
	}
	void closeSelectedTab(){
		Tab *tmp = pages.getNodePtrAt(curr_index)->getDataPtr();
		tmp->setClosedIndex(curr_index);
		closedPages.push(*tmp);
		pages.eraseFrom(curr_index);
		if(curr_index+1==tab_count){ curr_index--; }
		tab_count--;
	}
	void back(){
		try {
			pages.getNodePtrAt(curr_index)->getDataPtr()->back();
		}
		catch(const exception& e){
			cout << "exception handled" << endl;
			cout << e.what() << endl;
		}
	}
	void forward(){
		try {
			pages.getNodePtrAt(curr_index)->getDataPtr()->forward();
		}
		catch(const exception& e){
			cout << "exception handled" << endl;
			cout << e.what() << endl;
		}
	}
};

#endif