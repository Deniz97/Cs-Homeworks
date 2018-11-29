#include <stdio.h>
#include "lab3.h"

void execute();
char* customstrncpy(char *src,size_t n);
char* eliminateDigits(char* string);
char* strip( char* string, char* characters);
char* convertCamelCase(char* string1);
char* twoDjoin(char** list, char delim);

/*

Functions given by instructor/lab3.h

isdigit(), 

isupper(), 

islower(), 

toupper(), 

tolower(),

strlength().
*/
void execute(){



}

char* customstrncpy(char *src, size_t n){

	char *new;
	int i;
	new= (char *) malloc(sizeof(char)*(n+1));

	i=0;
	while( *(src+i)!='\0' && i<n ){
		*(new+i)=*(src+i);
		i++;
	}
	
	*(new+i) = '\0';
	return new;
}

char* eliminateDigits(char* string) {

	int i,j,len,total_memory;
	char* new;
	len=strlength(string);
	total_memory=len+1;
	i=0;j=0;
	new=(char *) malloc(sizeof(char)*(total_memory));
	do{
		if( !(isdigit(*(string+i)) )){
			
			*(new+j)=*(string+i);
			j++;
			
		}
		else{
			total_memory--;
			new = realloc(new,sizeof(char)*total_memory);
		}
		i++;

	}while(*(string+i)!='\0');


	return new;
}

char* strip(char* string, char* characters){

	char *new;
	int i,j,k,len,bom,bam;
	i=0;
	len=strlength(string);
    
	while( i<(len-1) ) {
		bom=0;
		for(k=0;k<strlength(characters);k++){
			if(*(string+i)==*(characters+k)){ bom=1; }
		}
		if(bom==0) { break; }
		i++;
	}	
	if(i==len-1){return NULL;}
	/*now i is the starting position */
	
	j=len-1;
	while(j>0){
		bom=0;
		for(k=0;k<strlength(characters);k++){
			if(*(string+j)==*(characters+k)){ bom=1; }
		}
		if(bom==0){ break; }
		j--;

	}
	/*now j is the ending position */
	/*we can copy the string now */
	k=0;
	bam=i;new=malloc(sizeof(char)*(j-bam+1));
	while(i<=j){
		*(new+k)=*(string+i);
		k++;i++;
	}
	*(new+k)='\0';

	return new;
}


char* convertCamelCase(char* string){

	char *new;
	int len,i,j,total_memory;
	len = strlength(string);
	total_memory=len+1;
	new = (char *) malloc(sizeof(char)*(total_memory));
	i=0;
	j=0;
	do{
		if(*(string+i)=='_' ){

			total_memory--;
			new = realloc(new,sizeof(char)*total_memory  );
			i++;
			*(new+j)=toupper(*(string+i));
			
		}
		else{ *(new+j)=*(string+i); }
		i++;j++;

	}while(*(string+i)!='\0' );

	return new;
}

char* twoDjoin(char** list, char delim){

	char *new;
	int i,j,k,total_memory;
	new=malloc(sizeof(char));
	

	j=0;k=0;
	for(i=0;*(list+i)!=NULL;i++){
		total_memory+=strlength(list[i]);
		new=realloc(new,sizeof(char)*total_memory);

		j=0;
		while(list[i][j]!='\0'){
			
			*(new+k)=list[i][j];
			j++;k++;
		}
		*(new+k)=delim; k++;
	}
	k--;
	*(new+k) = '\0';
	return new;


}
