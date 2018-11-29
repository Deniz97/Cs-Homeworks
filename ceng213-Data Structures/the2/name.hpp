#ifndef NAME_COMPARATOR__
#define NAME_COMPARATOR__
#include "song.hpp"
#include <algorithm> 
#include <string>

class NameComparator
{
public:
  bool operator( )( const Song & s1, const Song & s2 ) const
  {
    //Implement this in accordance with the specifications in the homework text
 	if(s1.getName()<s2.getName()){
 		return true;
 	}
 	else if(s2.getName()<s1.getName()){
 		return false;
 	}
 	if(s1.getBand()<s2.getBand()){
 		return true;
 	}
 	else if(s2.getBand()<s1.getBand()){
 		return false;
 	}
 	if(s1.getYear()<s2.getYear()){
 		return true;
 	}
 	else if(s2.getYear()<s1.getYear()){
 		return false;
 	}
 	return false;

  }
};

#endif
	 	  	  	   	     	  	        	 	
