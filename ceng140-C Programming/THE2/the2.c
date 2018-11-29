#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wheel {
	char *description;
	char direction;
	int slice_number;
	struct wheel *prev;
	struct wheel *next;
} WHEEL;

WHEEL *head=NULL;

char current_direction = 'R';

WHEEL *add(WHEEL*,char*,char,int);
WHEEL *run(WHEEL*);
WHEEL *delete(WHEEL*);
void test(WHEEL*,int);
void control(WHEEL*);
void  __printwheel(WHEEL*);
void print_main(WHEEL* );
void print_wheel(WHEEL* main);

void print_main(WHEEL* main){
	printf("\n");
	printf("DES= %s\n",main->description);
	printf("DIR= %c\n",main->direction );
	printf("SN= %d\n",main->slice_number);
	printf("CUR_DIR= %c\n",current_direction);
	printf("\n");
}

void print_wheel(WHEEL* main){
	WHEEL* bom=main;
	printf("\n");
	do{
		print_main(main);
		main = main->next;
	}while(main!=bom);

}

int main(){

	int stop;
	char *command;
	WHEEL *main;
	stop=0;
	main = (WHEEL*)malloc(sizeof(WHEEL));
	command=(char*)malloc(sizeof(char)*8);
	main->description = NULL;

	do{
		scanf(" %s",command);
		
		if( strcmp(command,"ADD")==0){
			int length,s_n;
			char *des,dir;
			scanf("%d ",&length);
			des=(char*)malloc(sizeof(char)*(length+1));
			scanf(" %s",des);
			if(  strcmp(des,"DRILL")==0){
				dir='N';
				s_n=-1;
			}
			else{
				scanf(" %c %d",&dir,&s_n);
			}
			main = add(main,des,dir,s_n);
		}
		else if( strcmp(command,"RUN")==0){
			if(  strcmp(main->description,"DRILL")==0){ stop=1; }
			main = run(main);
		}
		else if( strcmp(command,"DELETE")==0){
			main = delete(main);
		}
		else if( strcmp(command,"TEST")==0){
			int limit;
			scanf("%d",&limit);
			test(main,limit);
		}
		else if(strcmp(command,"CONTROL")==0){
			control(main);
		}
		else{
			printf("YANLIS INPUT VERDIN AMIK\n");
		}
		//print_wheel(main);

	}while( strcmp(command,"TEST")!=0 && stop!=1);

	return 0;

}

WHEEL *add(WHEEL *main,char *des,char dir, int s_n){

	WHEEL *new;
	new = (WHEEL*)malloc(sizeof(WHEEL));
	
	if(head==NULL){
		head=new;
		new->next = new;
		new->prev = new;
		free(main);
	}
	else{

		if(current_direction=='R'){
			new->next = main->next;
			new->prev = main;
			main->next->prev = new;
			main->next = new;
		}
		else if(current_direction=='L'){
			new->next = main;
			new->prev = main->prev;
			main->prev->next=new;
			main->prev = new;
		}
	}
	main=new;
	main->description=malloc(sizeof(char)*strlen(des));
	strcpy(main->description,des);
	main->direction = dir;
	main->slice_number=s_n;
	printf("A %s %s %s\n",main->prev->description,main->description,main->next->description);
	return main;

}

WHEEL* delete(WHEEL *main){
	
	WHEEL *temp;
	if(main==head){
		printf("HEADI SILDIN AMIK\n");
		return NULL;
	}
	printf("D %s %s %s\n",main->prev->description,main->description,main->next->description);
	temp=main;
	main->prev->next = main->next;
	main->next->prev = main->prev;
	if(current_direction=='R'){
		main=main->prev;
	}
	else if(current_direction=='L'){
		main = main->next;
	}
	free(temp);
	return main;
	

}

WHEEL* run(WHEEL *main){
	int counter;
	counter = main->slice_number;

	printf("R");

	if( strcmp(main->description,"DRILL")==0){
		printf(" DRILL\n");
		return NULL;
	}

	current_direction=main->direction;


	for( ;counter>0;counter--){
		if(current_direction=='R'){
			main = main->next;
		}
		else if(current_direction=='L'){
			main = main->prev;
		}
		printf(" %s",main->description);
	}
		printf("\n");
	return main;
}


WHEEL* test_run(WHEEL *main){
	int counter;
	counter = main->slice_number;
	current_direction=main->direction;
	
	if( strcmp(main->description,"DRILL")==0){
		return main;
	}

	for( ;counter>0;counter--){
		if(current_direction=='R'){
			main = main->next;
		}
		else if(current_direction=='L'){
			main = main->prev;
		}
		printf(" %s",main->description);
		if( strcmp(main->description,"DRILL")==0){
			return main;
		}
	}
		
	return main;
}



void test(WHEEL *main, int counter){

	main = head;
	printf("T");
	printf(" %s",main->description);
	while( counter>0){
		main = test_run(main);
		counter--;
	}
	if( strcmp(main->description,"DRILL")!=0 && counter==0){
		printf(" DRILL_NOT_FOUND\n");
		return;
	}
	printf("\n");

}

void control(WHEEL *main){

	main = head;
	printf("C");

	if(head->prev==head && head->next==head){
		printf(" %s",head->description );
		printf(" %s\n",head->description );
		return;
	}

	do{
		printf(" %s",main->description);
		main=main->next;
	}while(main!=head->prev);
	printf(" %s",main->description );
	do{
		main=main->prev;
		printf(" %s",main->description);
	}while(main!=head);
	printf("\n");

}


void  __printwheel(WHEEL* current_slice){
	WHEEL* ptr=head;

	printf("Current Direction: ");
	if (current_direction == 'L') {
	printf("Left");
	}
	else if (current_direction == 'R') {
	printf("Right");
	}
	else{
  	printf("BOKTA CIKABILIR");
  	}
  
	printf("\n\n");
  
	
	do{
		
	if (strcmp("DRILL", ptr->description)==0) {
		printf("[DRILL]");
	}
	else {
	printf("[%s, %c, %d]", ptr->description, ptr->direction, ptr->slice_number);
	}
	if (ptr == current_slice)
	printf(" <--");

	printf("\n");

	ptr = ptr->next;
	

	printf("\n");

	}while(ptr!=head);
}
