grammar mygram;		

//TODO: check for keyword identifiers

prog: (stmt ';'| defin)+ ;  

stmt: ass | iff | wh | ret | io  ;
defin: 'fun' ID plist stmts 'endf';

// arguments for function definition and function call
plist: '(' idargs  ')';
idargs: (ID|ass) (','(ID|ass) )* | ;
clist: '(' args ')';
args: e (',' e ) * | ;

//statements
stmts: ( stmt ';' )+;
ret: 'return' e;
iff: 'if' cond stmts ('else if' cond stmts)* elsee 'endi';
elsee: 'else' stmts | ;
wh: 'while' cond stmts 'endw';
io: 'input' ID | 'output' e;


cond: e Bop e | cond Lop cond | Uop cond;
//cond: e Bop e condP | Uop cond condP; //left recursion free
//condP: Lop cond condP | ;

ass: ID '=' e; //assignment

//expression related rules
e: e '-' t | e '+' t | t;
//e: t ep; //left recursion free
//ep:  '-' t ep | '+' t ep | ; 
t: t '*' f | t '/' f | t '%' f | f;
//t: f tp; //left recursion free
//tp: '*' f tp| '/' f tp | ;
f: ID | NUM | '('e')' | ID clist ; //function call


NUM: [0-9]+ | [0-9]+'.'[0-9]+; //let 5. be a floating point number? //no
Bop: '<' | '>=' | '==' | '>' | '<=';
Lop: 'and' | 'or';
Uop: '!' ; //not
WS : [ \t\r\n]+ -> skip ;    // skip spaces, tabs, newlines
ID : [A-Za-z]([A-Za-z]|NUM|'_')* ;
COMMENT : '#' ~( '\r' | '\n' )* -> skip ;

/*
		Q: Why ; is neccesery anyway, it already parses
		Q: What is wrong with implementing/replicating the functionality simply with python
        Q: Which is better, stmt ; or ass ;
*/

/*
	T__0=1 #;
    T__1=2 #fun
    T__2=3 #endf
    T__3=4 #(
    T__4=5 #)
    T__5=6 #,
    T__6=7 #return
    T__7=8 #if
    T__8=9 #else if
    T__9=10 #endi
    T__10=11 #else
    T__11=12 #while
    T__12=13 #endw
    T__13=14 #input
    T__14=15 #output
    T__15=16 #=
    T__16=17 #-
    T__17=18 #+
    T__18=19 #*
    T__19=20 #/
    T__20=21 #%
    NUM=21
    Bop=22
    Lop=23
    Uop=24
    WS=25
    ID=26


*/