tile(t1,   3 ,   5 ,blue) .
tile(t2,   1 ,   2 ,blue) .
tile(t3,   4 ,   3 ,blue) .
tile(t4,   2 ,   4 ,red) .
tile(t5,   4 ,   1 ,red) .
tile(t6,   2 ,   3 ,green) .
tile(t7,   1 ,   5 ,green) .
tile(t8,   3 ,   3 ,green) .
tile(t9,   1 ,   1 ,purple) .
tile(t10,   2 ,   5 ,purple) .


filled_area([],A):- A is 0.

filled_area([T|Tiles],A):- tile(T,W,H,C),  filled_area(Tiles,M), A is M+H*W.


deneme(a,b).
deneme(a,c).
deneme(a,d).


filling_list(Wi,He,Pe,Tiles):-sum_width(Tiles,Wi), sum(Tiles,A), Pe*He*Wi=< A,  check_height(Tiles,He), all_diff(Tiles).

all_diff(L) :- \+ (select(X,L,R), memberchk(X,R)).

check_height([],He).
check_height([T|Tiles],He):- tiles:tile(T,W,H,C), H=<He, check_height(Tiles,He).

sum([],0).
sum([T|Tiles],A):-   tiles:tile(T,W,H,C), sum(Tiles,M), A is M+W*H.

sum_width([],0).
sum_width([T|Tiles],A) :-  tiles:tile(T,W,H,C), M is A-W , 0=<M,  sum_width(Tiles,M).

widht([],0) :- true .
widht([Name | NewTile] , W) :- tiles:tile(Name , W1 , _ , _) , XD is W - W1 , 0 =< XD ,  widht(NewTile , XD)    .





/*
subset([], []).
subset([E|Tail], [E|NTail]):-
	subset(Tail, NTail).
subset([_|Tail], NTail):-
	subset(Tail, NTail).


gethelper(BOM):- findall(N,tiles:tile(N,B,C,D),T), subset(T,BOM).
getalltiles(BOM):- bagof(Bim,gethelper(Bim),BOM).
memberr(A):- getalltiles(BOM), member(A, BOM).

filling_list(Wi,He,Pe,Tiles):-   fill_help(Wi,He,Pe,T), lists:perm(T,Tiles).

fill_help(Wi,He,Pe,Tiles):- memberr(Tiles), sum(Tiles,A), Pe=< float(float(A)/float(Wi*He)), sum_width(Tiles,W), 
	W=Wi, check_height(Tiles,He).

all_diff(L) :- \+ (select(X,L,R), memberchk(X,R)).

check_height([],He).
check_height([T|Tiles],He):- tiles:tile(T,W,H,C), H=<He, check_height(Tiles,He).

sum([],0).

sum([T|Tiles],A):-  tiles:tile(T,W,H,C), sum(Tiles,M),  A is M+W*H.

sum_width([],0).
sum_width([T|Tiles],A) :- tiles:tile(T,W,H,C), sum_width(Tiles,M),    A is M+W.
*/


/*
filling_list(Wi,He,Pe,Tiles):- sum_width(Tiles,W), W=Wi.

sum_width([],0).
sum_width([T|Tiles],A) :-  tile(T,W,H,C), sum_width(Tiles,M),  A is M+W.
*/


/*
filling_list(Wi,He,Pe,Tiles):- sum(Tiles,Pe*Wi*He), sum_width(Tiles,Wi), check_height(Tiles,He), all_diff(Tiles).

all_diff(L) :- \+ (select(X,L,R), memberchk(X,R)).

check_height([],He).
check_height([T|Tiles],He):- tile(T,W,H,C), H=<He, check_height(Tiles,He).

sum([],0).
sum([T|Tiles],A):-   tile(T,W,H,C), sum(Tiles,A-W*H). 

sum_width([],0).
sum_width([T|Tiles],A) :-  tile(T,W,H,C), sum_width(Tiles,A-M).
*/

/*

filled_area([],A):- A is 0.

filled_area(Tiles,A):- helper(Tiles,Q), A is Q.



helper([T|Tiles],Q):- tiles:tile(T,W,H,C),helper(Tiles,M), Q is M+H*W .
helper([],0).

*/






