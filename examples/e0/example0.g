#header
<<
#include "charptr.h"
>>

<<
#include "charptr.c"

int main(){
	ANTLR(expr(), stdin);
}
>>

#lexclass START
#token NUM 		"[0-9]+"
#token PLUS 	"\+"
#token SUB		"\-"
#token SPACE 	"[\ \n]" << zzskip(); >>

//expr: NUM (PLUS NUM)*;
op: PLUS NUM | SUB NUM ;
expr: NUM (op)* ;

