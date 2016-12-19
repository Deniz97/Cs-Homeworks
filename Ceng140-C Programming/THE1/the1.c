#include <stdio.h>

int check_field(long,int); //main recursion
int check_ideal(long); //checks if the given field is ideal
int nthrow(int); //returns the row number of a given position
void print_field(long,int); //prints the field
long kill_spider(long field, int position); //return a field with a spider put at the position
long put_spider(long field, int position);

int main() {
	/*IMPORTANT NOTE
		if you have came here as an asistant because my code got zero,
		please first check for my input method as that is the one thing
		i am not sure about this piece of bad-practice hell.
	*/
	int row_count,i;
	long field=0,original;
	char temp;

	scanf("%d",&row_count);
	int total_spots = (row_count*(row_count+1))/2 ;

	for(i= total_spots; i>0  ; i-- ){
		scanf(" %c",&temp);
		if(temp=='s') {
			
			field=field | (((long)1)<<(i-1));
		}
	}
	//if you can't tell by now, i am using a long integer's bits to represent my field

	original = field;
	if( check_field(field,row_count) ){
		print_field(original,row_count);
	} 
	else{ printf("No ideal field!\n"); }
	return 0;
}

int check_field(long field,int row_count){
	/*
	Main idea is; check if there is a spider at position i && check if there is 
	empty space at 2 adjacent of i && check if there is spider inbetween
	&& if necessery check if the empty space is at an expected row;
	IF SO, recursively call the check_field function with a copy field of a made move
	*/
	int i,row;
	long copy;

	//if ideal
	if(check_ideal(field)){
		
		return 1;
	}

	//first check upper
	int temp_total= ( (row_count-2) * (row_count-1) ) /2;
	for(i = temp_total;i>0;i--) {
		row=nthrow(i);
		//right vertical
		if(  ( ~field &   (((long)1)<<(i-1)) ) == 0 &&  (field & (((long)1)<<(i+2*row)) ) == 0 ) {
			if((~field & (((long)1)<<(i+row-1)) ) == 0 ) {
				//recursion call
				copy=field;
				copy = kill_spider(copy,i);
				copy = kill_spider(copy, i+row  );
				copy = put_spider(copy, i+2*row+1 );
				if(check_field(copy, row_count)){
					print_field(copy,row_count);
					return 1;
				}
			}
		}
		//left vertical
		if(  ( ~field & (((long)1)<<(i-1)) ) == 0 && (field & (((long)1)<<(i+2*row+2)) ) == 0 ) {
			if((~field & (((long)1)<<(i+row)) ) == 0 ) {
				//recursion call		
				copy=field;
				copy = kill_spider(copy,i);
				copy = kill_spider(copy, i+row+1 );
				copy = put_spider(copy, i+2*row+3 );
				if(check_field(copy, row_count)){
					print_field(copy,row_count);
					return 1;
				}
			}
		}

	}
	//second check lower
	temp_total = (row_count*(row_count+1))/2 ;
	for(i=temp_total;i>3;i--){
		row=nthrow(i);
		//right vertical
		if( ( ~field & (((long)1)<<(i-1)) ) == 0 && (field & (((long)1)<<(i-(2*row-1)-1)) ) == 0 && nthrow( i-(2*row-1) ) == row-2 ){
			if((~field & (((long)1)<<(i-row-1)))== 0 ){
				//recursion call
				copy=field;
				copy = kill_spider(copy,i);
				copy = kill_spider(copy, i-row  );
				copy = put_spider(copy, i-(2*row-1) );
				if(check_field(copy, row_count)){
					print_field(copy,row_count);
					return 1;
				}
			}
		}
		//left vertical
		if( ( ~field & (((long)1)<<(i-1)) ) == 0 && (field &  (((long)1)<<(i-(2*row-3)-1)) )==0 && nthrow( i-(2*row-3) ) == row-2 ) {
			if((~field & (((long)1)<<(i-row)) )== 0) {
				//recursion call
				copy=field;
				copy = kill_spider(copy,i);
				copy = kill_spider(copy, i-row+1  );
				copy = put_spider(copy, i-(2*row-3) );
				if(check_field(copy, row_count)){
					print_field(copy,row_count);
					return 1;
				}
			}
		}	
	}
	//third check horizantol
	temp_total =  (row_count*(row_count+1))/2 ;
	for(i=temp_total;i>3;i--) {
		row=nthrow(i);
		//right horizantol
		if( ( ~field & (((long)1)<<(i-1)) ) == 0 && (field & (((long)1)<<(i-3)) )== 0 && nthrow(i-2) == row ){
			if( (~field & (((long)1)<<(i-2)) )== 0 ){
				//recursion call
				copy=field;
				copy = kill_spider(copy,i);
				copy = kill_spider(copy, i-1 );
				copy = put_spider(copy, i-2);
				if(check_field(copy, row_count)){
					print_field(copy,row_count);
					return 1;
				}
			}
		}
		//left horizantol
		if( ( ~field & (((long)1)<<(i-1)) ) == 0 &&  (field & (((long)1)<<(i+1)) )== 0 && nthrow(i+2) == row ){
			if((~field & (((long)1)<<(i)) )== 0 ){
				//recursion call
				copy=field;
				copy = kill_spider(copy,i);
				copy = kill_spider(copy, i+1 );
				copy = put_spider(copy, i+2);
				if(check_field(copy, row_count)){
					print_field(copy,row_count);
					return 1;
				}

			}
		}
		 
	}
	return 0;
}

void print_field(long field,int row_count){

	int total = (row_count*(row_count+1) ) / 2 ;
	int i,j,k;
	int bom=row_count;

	for(i=0;i<bom;i++){
		
		for(k=0;k<i;k++){
			printf(" ");
		}

		for(j=0;j<row_count;j++,total--){
			if((field & (((long)1)<<(total-1)) )== 0) { printf("e "); }
			else{ printf("s "); }
		}

		row_count--;
		printf("\n");
	}
	printf("\n");
}

long kill_spider(long field, int position) {
	
	return field & ( ~( (((long)1)<<(position-1)) ) );
}

long put_spider(long field, int position){

	return field | (((long)1)<<(position-1));
}

int nthrow(int number) {
	int i;
	if(number<=0) {return 0;}
	for(i=1; ;i++){
		if(number<= (i*(i+1))/2 ){
			return i;
		}
	}
}

int check_ideal(long  field) {

	return (field & (field - 1)) == 0 ? 1 : 0;
}

