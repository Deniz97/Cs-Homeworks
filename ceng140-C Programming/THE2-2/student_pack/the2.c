#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the2.h"


int sqr(int b,int a){
	int i;
	int retval;
	i=0;
	retval=1;
	while(i<a){
		retval=retval*b;
		i++;
	}
	return retval;
}

int branch_it(node* root){
	int b;
	int n;
	int i;
	int retval;
	b=root->key/1000;
	n=(root->key%1000)+1;
	retval=1;
	if(n%b!=0){ 
		/*printf("in branching, returning %d\n",1 );*/
		return 1; 
	}
	for(i=1;sqr(b,i)<=n;i++){
		if(n%sqr(b,i)==0){
			retval=i;
		}
	}
	/*printf("in branching, returning %d\n",retval+1 );*/
	return retval+1;
}


node *init(int branch){
	node* temp;
	temp=malloc(sizeof(node));
	temp->key=1000*branch;
	temp->down=malloc(sizeof(node));
	temp->next=NULL;
	temp->down->key=0;
	temp->down->down=NULL;
	return temp;
}


int branch_factor(node *list){
	return list->key/1000;
}


int num_nodes(node *list){
	
	return (list->key%1000);
}


void clear_level(node* hed){
	node* f;
	node* tmp;
	tmp=hed->next;
	while(tmp!=NULL){
		f=tmp;
		tmp=tmp->next;
		free(f);
	}
}

void clear(node *list){
	node* temp;
	node* f;
	temp=list->down;
	while(temp!=NULL){
		clear_level(temp);
		f=temp;
		temp=temp->down;
		free(f);
	}
	free(list);

}


int is_empty(node *list){
	return list->down->next==NULL;
}


int num_levels(node *n){
	int retval;
	node* temp;
	temp=n->down;
	retval=0;
	while(temp!=NULL){
		retval+=1;
		temp=temp->down;
	}
	return retval;
}


node* insert_helper(node* nodum, node* dwn, int key, char *value){
	node* curr;
	node* ne;
	node* new;
	curr=nodum;
	ne=nodum->next;
	new=NULL;
	
	while(1){
		/*printf("in helper while,key: %d\n",curr->key);*/
		if(ne==NULL){
			/*printf("null condition\n");*/
			new = malloc(sizeof(node));
			curr->next= new;
			curr->next->key=key;
			strncpy(curr->next->value,value,V_SIZE);
			curr->next->next=NULL;
			curr->next->down=dwn;
			break;			
		}
		else if(ne->key>key){
			/*printf("key cond\n");*/
			new=malloc(sizeof(node));
			new->key=key;
			strncpy(new->value,value,V_SIZE);
			new->next=ne;
			curr->next=new;
			new->down=dwn;
			break;
		}
		curr=curr->next;
		ne=ne->next;	
	}
	return new;
}

node *insert(node *list, int key, char *value){
	/*printf("in insert func\n");*/
	int count;
	/*printf("insert func-branch it\n");*/
	int level;
	/*printf("insert func-num_levels\n");*/
	int temp;
	int diff;
	int max_level;
	node*  temp2;
	node* n;
	node* former;
	node* new;
	former=NULL;
	level= num_levels(list);
	count=branch_it(list);


	
	temp2 = find(list,key);
	/*update*/
	if(temp2!=NULL){
		/*printf("insert func-update\n");*/
		while(temp2!=NULL){
			strncpy(temp2->value,value,V_SIZE);
			temp2=temp2->down;
		}
		return list;
	}
	/*insert*/
	if(count>level){
		/*printf("insert funct, new level\ncount:%d level %d\n",count,level);*/
		diff=count-level;
		max_level = list->down->key;
		while(diff>0){
			new=malloc(sizeof(node));
			new->key=max_level-1;
			max_level -= 1;
			new->next=NULL;
			new->down=list->down;
			list->down=new;
			diff-=1;
		}
	}


	level= num_levels(list);
	while(count>0){
		/*printf("insert funct, inserting %d\n",key);*/
		temp=level;
		n=list;
		while(temp>0){
			n=n->down;
			temp-=1;
		}
		/*printf("AAA, %d\n",n->key );*/
		former = insert_helper(n,former,key,value);
		count -= 1;
		level-=1;
	}
	list->key+=1;
	return list;

}

node* does_contain(node* n, int key){
	node* temp;
	node* retval;
	temp=n->next;
	retval=n;
	while(temp!=NULL){
		if(temp->key==key){
			return retval;
		}
		temp=temp->next;
		retval=retval->next;
	}
	return NULL;
}

int delete(node *list, int key){
	int contain;
	node* goal;
	node* todelete;
	node* temp;
	int level;
	contain=0;

	/*delete nodes;*/
	temp=list->down;
	while(temp!=NULL){
		goal = does_contain(temp,key);
		if(goal!=NULL){
			contain=1;
			todelete = goal->next;
			goal->next = goal->next->next;
			free(todelete);	
			
			
		}
		temp=temp->down;
	}
	
	/*delete empty heads*/
	temp=list;
	while(temp->down!=NULL){
		if(temp->down->key!=0 && temp->down->next==NULL){
			todelete=temp->down;
			temp->down=temp->down->down;
			free(todelete);
		}
		temp=temp->down;
	}
	/*fix head keys*/
	temp=list->down;
	level = num_levels(list)*-1 +1;
	while(temp!=NULL){
		temp->key=level;
		level += 1;
		temp=temp->down;
	}




	/*return*/
	if(contain==1){ list->key -= 1; }
	return contain;

	
			
	}



node *find(node *list, int key){

	node* goal;

	node* temp;

	temp=list->down;
	while(temp!=NULL){
		goal = does_contain(temp,key);
		if(goal!=NULL){
			return goal->next;			
		}
		temp=temp->down;
	}
	return NULL;
}



void path(node *list, int key){
	node* temp;
	temp=list->down;
	/*printf("Looking for %d\n",key );*/

	
	printf("%3d v ",list->key );
	
	
	/*printf("\n");*/
	while(temp->key!=key){
		if(temp->next!=NULL && temp->next->key<=key){
			printf("%3d > ",temp->key );
			/*printf("\n");*/
			temp=temp->next;
		}
		else{
			printf("%3d v ",temp->key );
			/*printf("\n");*/
			temp=temp->down;
		}
	}

	printf("%3d:%5s\n",temp->key,temp->value );
	/*printf("DONE\n");*/

}


int num_of_occr(node* list,int key){
	int retval;
	node* temp;
	retval=0;
	temp=list->down;
	while(temp!=NULL){
		if(does_contain(temp,key)!=NULL){
			/*printf("in num of occr, retval+=1\n");*/
			retval+=1;
		}
		temp=temp->down;
	}
	return retval;
}

node* get_hed_ptr(node *list, int level){
	node* temp;
	temp=list->down;
	while(temp!=NULL){
		if((level*-1)==temp->key){
			return temp;
		}
		temp=temp->down;
	}
	return NULL;
}

void print(node *list){
	int counter;
	int k;
	int i=0;
	node* temp;
	printf("%3d      ",num_nodes(list) );
	
	for(;i<num_levels(list);i++){
		printf(" %d", i);
	}
	printf("\n");
	printf("          ");
	for(i=0;i<num_levels(list);i++){
		printf("+ " );
	}
	printf("-\n");
	temp=get_hed_ptr(list,0);

	temp=temp->next;
	
	while(temp!=NULL){

		k=temp->key;
		printf("%3d:%5s", k,temp->value);
		counter=num_of_occr(list,k);
		/*printf("COUNTER= %d\n",counter );*/
		while(counter>0){
			printf(" +");
			counter--;
		}
		temp=temp->next;
		printf("\n");
	}
	
}



int num_of_nodes(node* head){
	node* temp;
	int retval;
	temp=head;
	retval=0;
	while(temp!=NULL){
		retval+=1;
		temp=temp->next;
	}
	return retval;
}




void print_level(node *list, int level){
	int l;
	
	node* temp;
	node* u;
	node* org;
	node *uorg;
	l= num_levels(list);
	if(level==(l-1)){
		/*printf("TOP LEVEL\n");*/
		temp=list->down;
		printf("  %d:      -> ",level*-1);
		temp=temp->next;
		while(temp!=NULL){
			
			printf(" %3d :%5s ->",temp->key,temp->value);
			temp=temp->next;
			
		}
	}
	else{	
		/*printf("Not top level\n");*/
		u=get_hed_ptr(list,level+1);
		temp=u->down;
		/*printf("u key:%d,temp key:%d\n",u->key,temp->key );*/
		uorg=u;
		org=temp;
		
		u=u->next;
		while(temp!=NULL){
			/*printf("aa");*/
			if(u->key==temp->key){
				/*printf("bb");*/
				printf(" %3d :%5s ->",u->key,u->value);
				if(u->next!=NULL){ u=u->next; }
				
			}
			else{
				/*printf("cc");*/
				printf("                ");
			}
			temp=temp->next;

		}
		printf("\n");
		/*printf("DONE\n");*/
		temp=org;
		u=uorg;
		u=u->next;
		while(temp!=NULL){
			if(u->key==temp->key){

				printf("     |      ");
				if(u->next!=NULL){ u=u->next; }
			}
			else{
				printf("              ");
			}
			temp=temp->next;
			

		}
		printf("\n");
		temp=org;
		u=uorg;
		u=u->next;
		while(temp!=NULL){
			
			printf(" %3d :%5s ->",temp->key,temp->value);
			
			temp=temp->next;
			

		}
	}
	printf("\n");

}




